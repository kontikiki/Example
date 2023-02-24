/*
 * PIDLoop.h
 *
 *  Created on: 2023. 2. 22.
 *      Author: user
 */

#ifndef PIDLOOP_H_
#define PIDLOOP_H_

#include "Pixy2.h"
#define PID_MAX_INTEGRAL         2000

#define PIXY_RCS_MIN_POS                     0
#define PIXY_RCS_MAX_POS                     1000L
#define PIXY_RCS_CENTER_POS                  ((PIXY_RCS_MAX_POS-PIXY_RCS_MIN_POS)/2)

typedef struct PIDLoop{
	int32_t m_command;

	int32_t m_pgain;
	int32_t m_igain;
	int32_t m_dgain;

	int32_t m_prevError;
	int32_t m_integral;
}PIDLoop;

void reset(PIDLoop* pid) {
	pid->m_command = PIXY_RCS_CENTER_POS;
	pid->m_prevError = 0x80000000L;
}

void PIDLoop_init(PIDLoop* pid,int32_t pgain, int32_t igain, int32_t dgain) {
	pid->m_pgain = pgain;
	pid->m_igain = igain;
	pid->m_dgain = dgain;

	reset(pid);
}

void PIDLoop_update(PIDLoop* pid,int32_t error) {
	int32_t pid_value;

	if (pid->m_prevError != 0x80000000L) {
		// integrate integral
		pid->m_integral += error;
		// bound the integral
		if (pid->m_integral > PID_MAX_INTEGRAL)
			pid->m_integral = PID_MAX_INTEGRAL;
		else if (pid->m_integral < -PID_MAX_INTEGRAL)
			pid->m_integral = -PID_MAX_INTEGRAL;

		// calculate PID term
		pid_value = (error * (pid->m_pgain) + (((pid->m_integral) * (pid->m_igain)) >> 4)
				+ (error - (pid->m_prevError)) * (pid-> m_dgain)) >> 10;

		pid->m_command += pid_value; // since servo is a position device, we integrate the pid term
		if (pid->m_command > PIXY_RCS_MAX_POS)
			pid->m_command = PIXY_RCS_MAX_POS;
		else if (pid->m_command < PIXY_RCS_MIN_POS)
			pid->m_command = PIXY_RCS_MIN_POS;

	}

	// retain the previous error val so we can calc the derivative
	pid->m_prevError = error;
}

#endif /* PIDLOOP_H_ */
