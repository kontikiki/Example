/*
 * rcservo.h
 *
 *  Created on: 2023. 2. 25.
 *      Author: user
 */

#ifndef RCSERVO_H_
#define RCSERVO_H_

#include "stm32f4xx_hal.h"
#include "PIDLoop.h"

#define RCS_MIN_PWM     1000
#define RCS_MAX_PWM     2000
#define RCS_PWM_RANGE   (RCS_MAX_PWM-RCS_MIN_PWM)


#define RCS_GAIN_SCALE  10
#define RCS_NUM_AXES    2

void rcs_init();

int32_t rcs_setPos(uint8_t channel, uint16_t pos);
int32_t rcs_setLimits(uint8_t channel, int16_t lower, int16_t upper);
void rcs_setLimits_all();


#endif /* RCSERVO_H_ */
