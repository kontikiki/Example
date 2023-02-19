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
Version *version = NULL;
uint16_t frameWidth = 0;
uint16_t frameHeight = 0;

uint8_t *m_buf = NULL;
uint8_t *m_bufPayload = NULL;

uint8_t m_type;
uint8_t m_length;
bool m_cs;

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
				m_cs = true;
				return PIXY_RESULT_OK;
			}
			if (start == PIXY_NO_CHECKSUM_SYNC) {
				m_cs = false;
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

	if (m_cs) {
		res = recv(m_buf, 4, NULL);

		if (res < 0)
			return res;

		m_type = m_buf[0];
		m_length = m_buf[1];

		csSerial = *(uint16_t*) &m_buf[2];

		res = recv(m_buf, m_length, &csCalc);

		if (res < 0)
			return res;

		if (csSerial != csCalc) {
#ifdef PIXY_DEBUG
			printf("error: checksum\r\n");
#endif
			return PIXY_RESULT_CHECKSUM_ERROR;
		}
	} else {
		res = recv(m_buf, 2, NULL);

		if (res < 0)
			return res;

		m_type = m_buf[0];
		m_length = m_buf[1];

		res = recv(m_buf, m_length, NULL);

		if (res < 0)
			return res;
	}
	return PIXY_RESULT_OK;
}

int16_t sendPacket() {
	// write header info at beginnig of buffer
	m_buf[0] = PIXY_NO_CHECKSUM_SYNC & 0xff;
	m_buf[1] = PIXY_NO_CHECKSUM_SYNC >> 8;
	m_buf[2] = m_type;
	m_buf[3] = m_length;
	// send whole thing -- header and data in one call

	return send(m_buf, m_length + PIXY_SEND_HEADER_SIZE);
}

int8_t pixy2_getVersion() {
	m_length = 0;
	m_type = PIXY_TYPE_REQUEST_VERSION;
	sendPacket();

	if (recvPacket() == 0) {
		if (m_type == PIXY_TYPE_RESPONSE_VERSION) {
			version = (Version*) m_buf;
			return m_length;
		} else if (m_type == PIXY_TYPE_RESPONSE_ERROR)
			return PIXY_RESULT_BUSY;
	}
	return PIXY_RESULT_ERROR;  // some kind of bitstream error
}

int8_t pixy2_getResolution() {
	m_length = 1;
	m_bufPayload[0] = 0; // for future types of queries
	m_type = PIXY_TYPE_REQUEST_RESOLUTION;
	sendPacket();
	if (recvPacket() == 0) {
		if (m_type == PIXY_TYPE_RESPONSE_RESOLUTION) {
			frameWidth = *(uint16_t*) m_buf;
			frameHeight = *(uint16_t*) (m_buf + sizeof(uint16_t));
			return PIXY_RESULT_OK; // success
		} else
			return PIXY_RESULT_ERROR;
	} else
		return PIXY_RESULT_ERROR;  // some kind of bitstream error
}

int8_t pixy2_getBlocks(bool wait, uint8_t sigmap, uint8_t maxBlocks) {
	blocks = NULL;
	numBlocks = 0;

	while (1) {
		// fill in request data
		m_bufPayload[0] = sigmap;
		m_bufPayload[1] = maxBlocks;
		m_length = 2;
		m_type = CCC_REQUEST_BLOCKS;

		// send request
		sendPacket();
		if (recvPacket() == 0) {
			if (m_type == CCC_RESPONSE_BLOCKS) {
				blocks = (Block*) m_buf;
				numBlocks = m_length / sizeof(Block);

				return numBlocks;
			}
			// deal with busy and program changing states from Pixy (we'll wait)
			else if (m_type == PIXY_TYPE_RESPONSE_ERROR) {
				if ((int8_t) m_buf[0] == PIXY_RESULT_BUSY) {
					if (!wait)
						return PIXY_RESULT_BUSY; // new data not available yet
				} else if ((int8_t) m_buf[0] != PIXY_RESULT_PROG_CHANGING)
					return m_buf[0];
			}
		} else
			return PIXY_RESULT_ERROR;  // some kind of bitstream error

		// If we're waiting for frame data, don't thrash Pixy with requests.
		// We can give up half a millisecond of latency (worst case)

		for (int i = 0; i < 1800 * 500; i++)
			;
	}
}

int8_t pixy2_init(SPI_HandleTypeDef* hspi,GPIO_TypeDef* port,uint16_t cs_pin) {
	uint32_t t0;
	int8_t res;

	res = open(hspi,port,cs_pin);
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
			version->hardware, version->firmwareMajor, version->firmwareMinor,
			version->firmwareBuild, version->firmwareType);
	printf(buf);
}

void pixy2_printBlock(int n) {

	// int i, j;
	char buf[128];
	//, sig[6], d;
	//bool flag;

	/*
	 if ((blocks+n)->m_signature > CCC_MAX_SIGNATURE) // color code! (CC)
	 {
	 // convert signature number to an octal string
	 for (i = 12, j = 0, flag = false; i >= 0; i -= 3)
	 {
	 d = (blocks+n)->m_signature >> i) & 0x07;
	 if (d > 0 && !flag)
	 flag = true;
	 if (flag)
	 sig[j++] = d + '0';
	 }
	 sig[j] = '\0';
	 sprintf(buf, "CC block sig: %s (%d decimal) x: %d y: %d width: %d height: %d angle: %d index: %d age: %d\r\n",sig, (blocks+n)->m_signature, (blocks+n)->m_x, (blocks+n)->m_y, (blocks+n)->m_width, (blocks+n)->m_height, (blocks+n)->m_angle, (blocks+n)->m_index, (blocks+n)->m_age);
	 }
	 else // regular block.  Note, angle is always zero, so no need to print
	 */
	sprintf(buf,
			"sig: %d x: %d y: %d width: %d height: %d index: %d age: %d\r\n",
			(blocks + n)->m_signature, (blocks + n)->m_x, (blocks + n)->m_y,
			(blocks + n)->m_width, (blocks + n)->m_height,
			(blocks + n)->m_index, (blocks + n)->m_age);
	printf(buf);
}
