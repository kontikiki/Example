/*
 * PIDLoop.c
 *
 *  Created on: 2023. 2. 25.
 *      Author: user
 */
#include "PIDLoop.h"


void reset(PIDLoop *pid) {
	pid->m_command = PIXY_RCS_CENTER_POS;
	//rcs_setPos(pid->m_axis,pid->m_command);
	pid->m_prevError = 0x80000000L;
}


void PIDLoop_init(PIDLoop *pid, int32_t pgain, int32_t igain, int32_t dgain,uint8_t axis) {
	pid->m_pgain = pgain;
	pid->m_igain = igain;
	pid->m_dgain = dgain;
	pid->m_axis=axis;

	reset(pid);
}

void PIDLoop_update(PIDLoop *pid, int32_t error) {
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

		pid->m_command += pid_value;
		if (pid->m_command > PIXY_RCS_MAX_POS)
			pid->m_command = PIXY_RCS_MAX_POS;
		else if (pid->m_command < PIXY_RCS_MIN_POS)
			pid->m_command = PIXY_RCS_MIN_POS;

		//rcs_setPos(pid->m_axis,pid->m_command);
	}

	// retain the previous error val so we can calc the derivative
	pid->m_prevError = error;
}
