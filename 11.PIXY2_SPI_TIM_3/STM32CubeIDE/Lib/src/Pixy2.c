/*
 * Pixy2.c
 *
 *  Created on: 2023. 2. 19.
 *      Author: user
 */

#include "Pixy2.h"

#define PIXY_DEBUG

uint8_t numBlocks;

Block *blocks = NULL;
Pixy2 pixy;

int16_t getSync() {
	uint8_t i, j, c, cprev;
	int16_t res;
	uint16_t start;

	// parse bytes until we find sync
	for (i = j = 0, cprev = 0; true; i++) {
		res = recv(&c, 1, NULL);
		if (res >= PIXY_RESULT_OK) {
			// since we're using little endian, previous byte is least significant byte
			start = cprev;
			// current byte is most significant byte
			start |= c << 8;
			cprev = c;
			if (start == PIXY_CHECKSUM_SYNC) {
				pixy.m_cs = true;
				return PIXY_RESULT_OK;
			}
			if (start == PIXY_NO_CHECKSUM_SYNC) {
				pixy.m_cs = false;
				return PIXY_RESULT_OK;
			}
		}
		// If we've read some bytes and no sync, then wait and try again.
		// And do that several more times before we give up.
		// Pixy guarantees to respond within 100us.
		if (i >= 4) {
			if (j >= 4) {
#ifdef PIXY_DEBUG
				printf("error: no response\r\n");
#endif
				return PIXY_RESULT_ERROR;
			}

			//delay_us(25);
			for (int i = 0; i < 1800 * 25; i++)
				;

			j++;
			i = 0;
		}
	}
}

int16_t recvPacket() {
	uint16_t csCalc, csSerial;
	int16_t res;

	res = getSync();

	if (res < 0)
		return res;

	if (pixy.m_cs) {
		res = recv(pixy.m_buf, 4, NULL);

		if (res < 0)
			return res;

		pixy.m_type = pixy.m_buf[0];
		pixy.m_length = pixy.m_buf[1];

		csSerial = *(uint16_t*) &(pixy.m_buf[2]);

		res = recv(pixy.m_buf, pixy.m_length, &csCalc);

		if (res < 0)
			return res;

		if (csSerial != csCalc) {
#ifdef PIXY_DEBUG
			printf("error: checksum\r\n");
#endif
			return PIXY_RESULT_CHECKSUM_ERROR;
		}
	} else {
		res = recv(pixy.m_buf, 2, NULL);

		if (res < 0)
			return res;

		pixy.m_type = pixy.m_buf[0];
		pixy.m_length = pixy.m_buf[1];

		res = recv(pixy.m_buf, pixy.m_length, NULL);

		if (res < 0)
			return res;
	}
	return PIXY_RESULT_OK;
}

int16_t sendPacket() {
	// write header info at beginnig of buffer
	pixy.m_buf[0] = PIXY_NO_CHECKSUM_SYNC & 0xff;
	pixy.m_buf[1] = PIXY_NO_CHECKSUM_SYNC >> 8;
	pixy.m_buf[2] = pixy.m_type;
	pixy.m_buf[3] = pixy.m_length;
	// send whole thing -- header and data in one call

	return send(pixy.m_buf, pixy.m_length + PIXY_SEND_HEADER_SIZE);
}

int8_t pixy2_getVersion() {
	pixy.m_length = 0;
	pixy.m_type = PIXY_TYPE_REQUEST_VERSION;
	sendPacket();

	if (recvPacket() == 0) {
		if (pixy.m_type == PIXY_TYPE_RESPONSE_VERSION) {
			pixy.version = (Version*) pixy.m_buf;
			return pixy.m_length;
		} else if (pixy.m_type == PIXY_TYPE_RESPONSE_ERROR)
			return PIXY_RESULT_BUSY;
	}
	return PIXY_RESULT_ERROR;  // some kind of bitstream error
}

int8_t pixy2_getResolution() {
	pixy.m_length = 1;
	pixy.m_bufPayload[0] = 0; // for future types of queries
	pixy.m_type = PIXY_TYPE_REQUEST_RESOLUTION;
	sendPacket();
	if (recvPacket() == 0) {
		if (pixy.m_type == PIXY_TYPE_RESPONSE_RESOLUTION) {
			pixy.frameWidth = *(uint16_t*) pixy.m_buf;
			pixy.frameHeight = *(uint16_t*) (pixy.m_buf + sizeof(uint16_t));
			return PIXY_RESULT_OK; // success
		} else
			return PIXY_RESULT_ERROR;
	} else
		return PIXY_RESULT_ERROR;  // some kind of bitstream error
}

int8_t pixy2_setServos(uint16_t s0, uint16_t s1) {
	uint32_t res;

	*(int16_t*) (pixy.m_bufPayload + 0) = s0;
	*(int16_t*) (pixy.m_bufPayload + 2) = s1;
	pixy.m_length = 4;
	pixy.m_type = PIXY_TYPE_REQUEST_SERVO;
	sendPacket();
	if (recvPacket() == 0 && pixy.m_type == PIXY_TYPE_RESPONSE_RESULT
			&& pixy.m_length == 4) {
		res = *(uint32_t*) pixy.m_buf;
		return (int8_t) res;
	} else
		return PIXY_RESULT_ERROR;  // some kind of bitstream error
}

int8_t pixy2_getBlocks(bool wait, uint8_t sigmap, uint8_t maxBlocks) {
	blocks = NULL;
	numBlocks = 0;

	while (1) {
		// fill in request data
		pixy.m_bufPayload[0] = sigmap;
		pixy.m_bufPayload[1] = maxBlocks;
		pixy.m_length = 2;
		pixy.m_type = CCC_REQUEST_BLOCKS;

		// send request
		sendPacket();
		if (recvPacket() == 0) {
			if (pixy.m_type == CCC_RESPONSE_BLOCKS) {
				blocks = (Block*) pixy.m_buf;
				numBlocks = pixy.m_length / sizeof(Block);

				return numBlocks;
			}
			// deal with busy and program changing states from Pixy (we'll wait)
			else if (pixy.m_type == PIXY_TYPE_RESPONSE_ERROR) {
				if ((int8_t) pixy.m_buf[0] == PIXY_RESULT_BUSY) {
					if (!wait)
						return PIXY_RESULT_BUSY; // new data not available yet
				} else if ((int8_t) pixy.m_buf[0] != PIXY_RESULT_PROG_CHANGING)
					return pixy.m_buf[0];
			}
		} else
			return PIXY_RESULT_ERROR;  // some kind of bitstream error

		// If we're waiting for frame data, don't thrash Pixy with requests.
		// We can give up half a millisecond of latency (worst case)

		for (int i = 0; i < 1800 * 500; i++)
			;
	}
}

int8_t pixy2_init(SPI_HandleTypeDef *hspi, GPIO_TypeDef *port, uint16_t cs_pin) {

	pixy.m_buf = (uint8_t*) malloc(PIXY_BUFFERSIZE);
	pixy.m_bufPayload = pixy.m_buf + PIXY_SEND_HEADER_SIZE;
	pixy.m_cs = false;
	pixy.version = NULL;
	pixy.frameWidth = 0;
	pixy.frameHeight = 0;
	uint32_t t0;
	int8_t res;

	res = open(hspi, port, cs_pin);
	if (res < 0)
		return res;

	// wait for pixy to be ready -- that is, Pixy takes a second or 2 boot up
	// getVersion is an effective "ping".  We timeout after 5s.

	for (t0 = HAL_GetTick(); HAL_GetTick() - t0 < 5000;) {
		if (pixy2_getVersion() >= 0) // successful version get -> pixy is ready
				{
			printf("getVersion OK\r\n");
			pixy2_getResolution(); // get resolution so we have it
			return PIXY_RESULT_OK;
		}
		HAL_Delay(5);
	}
	// timeout
	return PIXY_RESULT_TIMEOUT;
}

void pixy2_printVersion() {
	char buf[64];
	sprintf(buf, "hardware ver: 0x%x firmware ver: %d.%d.%d %s\r\n",
			pixy.version->hardware, pixy.version->firmwareMajor,
			pixy.version->firmwareMinor, pixy.version->firmwareBuild,
			pixy.version->firmwareType);
	printf(buf);
}

void pixy2_printBlock(int n) {

	int i, j;
	char buf[128], sig[6], d;
	bool flag;

	if ((blocks + n)->m_signature > CCC_MAX_SIGNATURE) // color code! (CC)
	{
		// convert signature number to an octal string
		for (i = 12, j = 0, flag = false; i >= 0; i -= 3) {
			d = (((blocks + n)->m_signature) >> i) & 0x07;
			if (d > 0 && !flag)
				flag = true;
			if (flag)
				sig[j++] = d + '0';
		}
		sig[j] = '\0';
		sprintf(buf,
				"CC block sig: %s (%d decimal) x: %d y: %d width: %d height: %d angle: %d index: %d age: %d\r\n",
				sig, (blocks + n)->m_signature, (blocks + n)->m_x,
				(blocks + n)->m_y, (blocks + n)->m_width,
				(blocks + n)->m_height, (blocks + n)->m_angle,
				(blocks + n)->m_index, (blocks + n)->m_age);
	} else
		// regular block.  Note, angle is always zero, so no need to print

		sprintf(buf,
				"sig: %d x: %d y: %d width: %d height: %d index: %d age: %d\r\n",
				(blocks + n)->m_signature, (blocks + n)->m_x, (blocks + n)->m_y,
				(blocks + n)->m_width, (blocks + n)->m_height,
				(blocks + n)->m_index, (blocks + n)->m_age);
	printf(buf);
}

int8_t pixy2_changeProg(const char *prog) {
	int32_t res;

	// poll for program to change
	while (1) {
		strncpy((char*) pixy.m_bufPayload, prog, PIXY_MAX_PROGNAME);
		pixy.m_length = PIXY_MAX_PROGNAME;
		pixy.m_type = PIXY_TYPE_REQUEST_CHANGE_PROG;
		sendPacket();
		if (recvPacket() == 0) {
			res = *(uint32_t*) pixy.m_buf;
			if (res > 0) {
				pixy2_getResolution();  // get resolution so we have it
				return PIXY_RESULT_OK; // success
			}
		} else
			return PIXY_RESULT_ERROR;  // some kind of bitstream error
		HAL_Delay(1);
		//delayMicroseconds(1000);
	}
}

int8_t pixy2_getRGB(uint8_t x, uint8_t y, uint8_t *r, uint8_t *g, uint8_t *b,
		bool saturate) {
	while (1) {
		*(int16_t*) (pixy.m_bufPayload + 0) = x;
		*(int16_t*) (pixy.m_bufPayload + 2) = y;
		*(pixy.m_bufPayload + 4) = saturate;
		pixy.m_length = 5;
		pixy.m_type = VIDEO_REQUEST_GET_RGB;
		sendPacket();
		if (recvPacket() == 0) {
			if (pixy.m_type == PIXY_TYPE_RESPONSE_RESULT
					&& pixy.m_length == 4) {
				*b = *(pixy.m_buf + 0);
				*g = *(pixy.m_buf + 1);
				*r = *(pixy.m_buf + 2);
				return 0;
			}
			// deal with program changing
			else if (pixy.m_type == PIXY_TYPE_RESPONSE_ERROR
					&& (int8_t) pixy.m_buf[0] == PIXY_RESULT_PROG_CHANGING) {
				for (int i = 0; i < 1800 * 500; i++)
					;
				//delayMicroseconds(500); // don't be a drag
				continue;
			}
		}
		return PIXY_RESULT_ERROR;
	}
}
