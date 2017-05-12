/*
 * LeftWheel.cpp
 *
 *  Created on: 12 мая 2017 г.
 *      Author: gray
 */

#include "LeftWheel.h"

void LeftWheel::powerUp() {

	GPIO_InitTypeDef gpio;

	//direction gpioc pin 5 init
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //clock
	gpio.GPIO_Pin = GPIO_Pin_5;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &gpio);

	GPIO_ResetBits(GPIOC, GPIO_Pin_5);

	//PWM gpiof pin 7 init
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE); //clock

	GPIO_PinRemapConfig(GPIO_Remap_TIM17, ENABLE);

	gpio.GPIO_Pin = GPIO_Pin_7;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);

	//timer 17 init
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM17, ENABLE); //clock

	TIM_TimeBaseInitTypeDef tim;
	tim.TIM_Prescaler = (uint16_t) (SystemCoreClock / 200000) - 1; //set timer frequency
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_ClockDivision = TIM_CKD_DIV1;
	tim.TIM_Period = 200;
	TIM_TimeBaseInit(TIM17, &tim);

	//pwm init
	TIM_OCInitTypeDef oc;
	oc.TIM_OCMode = TIM_OCMode_PWM1;
	oc.TIM_Pulse = 0;
	oc.TIM_OutputState = TIM_OutputState_Enable;
	oc.TIM_OutputNState = TIM_OutputNState_Disable;
	oc.TIM_OCPolarity = TIM_OCPolarity_High;
	oc.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OC1Init(TIM17, &oc);

	TIM_BDTRInitTypeDef bdtr;
	TIM_BDTRStructInit(&bdtr);
	bdtr.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
	TIM_BDTRConfig(TIM17, &bdtr);

	TIM_OC1PreloadConfig(TIM17, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM17, ENABLE);

	TIM_Cmd(TIM17, ENABLE);

	TIM17->CCER |= TIM_CCER_CC1E;

	//init start value
	setSpeed(1000);
}

void LeftWheel::setSpeed(int16_t speed) {
	if (speed != 0) {
		TIM_PrescalerConfig(TIM17,
				(uint16_t) (SystemCoreClock / (PWM_PERIOD * speed)) - 1,
				TIM_PSCReloadMode_Update);
		TIM_SetCompare1(TIM17, 100);
	} else
		TIM_SetCompare1(TIM17, 0);
}

void LeftWheel::stop() {
}
