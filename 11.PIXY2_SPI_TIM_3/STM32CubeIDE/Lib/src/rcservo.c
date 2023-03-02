/*
 * rcservo.c
 *
 *  Created on: 2023. 2. 25.
 *      Author: user
 */

#include "rcservo.h"

static uint16_t g_rcsPos[RCS_NUM_AXES];
static int16_t g_rcsMinPwm[RCS_NUM_AXES];
static int16_t g_rcsPwmGain[RCS_NUM_AXES];
extern TIM_HandleTypeDef htim10;
extern TIM_HandleTypeDef htim11;

void rcs_init() {
	int i;

	for (i = 0; i < RCS_NUM_AXES; i++) {
		g_rcsMinPwm[i] = RCS_MIN_PWM;
		g_rcsPwmGain[i] = 1 << RCS_GAIN_SCALE;
		rcs_setPos(i, PIXY_RCS_CENTER_POS);
	}

	//rcs_enable(0, 1);
	//rcs_enable(1, 1);
	rcs_setLimits_all();
}

int32_t rcs_setLimits(uint8_t channel, int16_t lower, int16_t upper) {
	if (channel >= RCS_NUM_AXES || upper > 500 || upper < -500 || lower > 500
			|| lower < -500)
		return -1;

	g_rcsMinPwm[channel] = RCS_MIN_PWM + lower;
	// MAXPOS*gain = RANGE+upper-lower -> gain<<RCS_GAIN_SCALE = ((RANGE+upper-lower)<<RCS_GAIN_SCALE)/MAXPOS
	g_rcsPwmGain[channel] = ((RCS_PWM_RANGE + upper - lower) << RCS_GAIN_SCALE)/ PIXY_RCS_MAX_POS;

	// update
	rcs_setPos(channel, g_rcsPos[channel]);

	return 0;
}

void rcs_setLimits_all() {

	rcs_setLimits(0, -200, 200);
	rcs_setLimits(1, -200, 200);
}

int32_t rcs_setPos(uint8_t channel, uint16_t pos) {
	uint16_t newPos;

	if (channel >= RCS_NUM_AXES || pos > PIXY_RCS_MAX_POS)
		return -1;
	else if (channel == 0) {
		newPos = ((uint32_t) pos * g_rcsPwmGain[channel]) >> RCS_GAIN_SCALE;
		//TIM10->CCR1=g_rcsMinPwm[channel] + newPos;
		htim10.Instance->CCR1=g_rcsMinPwm[channel] + newPos;
		//__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,g_rcsMinPwm[channel] + newPos);

		HAL_Delay(1);

	} else if(channel == 1) {
		newPos = ((uint32_t) pos * g_rcsPwmGain[channel]) >> RCS_GAIN_SCALE;
		//TIM11->CCR1=g_rcsMinPwm[channel] + newPos;
		htim11.Instance->CCR1=g_rcsMinPwm[channel] + newPos;
		//__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,g_rcsMinPwm[channel] + newPos);

		HAL_Delay(1);
	}

	g_rcsPos[channel] = pos;

	return 0;
}

