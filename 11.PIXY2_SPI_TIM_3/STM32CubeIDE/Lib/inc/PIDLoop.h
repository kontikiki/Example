/*
 * PIDLoop.h
 *
 *  Created on: 2023. 2. 22.
 *      Author: user
 */

#ifndef PIDLOOP_H_
#define PIDLOOP_H_

#include "Pixy2.h"
//#include "rcservo.h"

#define PID_MAX_INTEGRAL	2000
#define PIXY_RCS_MIN_POS                     0
#define PIXY_RCS_MAX_POS                     1000
#define PIXY_RCS_CENTER_POS                  ((PIXY_RCS_MAX_POS-PIXY_RCS_MIN_POS)/2)


typedef struct _PIDLoop {
	int32_t m_command;

	uint8_t m_axis;

	int32_t m_pgain;
	int32_t m_igain;
	int32_t m_dgain;

	int32_t m_prevError;
	int32_t m_integral;
} PIDLoop;

void reset(PIDLoop *pid);
void PIDLoop_init(PIDLoop *pid, int32_t pgain, int32_t igain, int32_t dgain,uint8_t axis);
void PIDLoop_update(PIDLoop *pid, int32_t error);


#endif /* PIDLOOP_H_ */
