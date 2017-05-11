/*
 * RightWheel.cpp
 *
 *  Created on: 12 ��� 2017 �.
 *      Author: gray
 */

#include "RightWheel.h"

void RightWheel::powerUp() {

	GPIO_InitTypeDef gpio;

	//direction gpioc pin 4 init
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //clock
	gpio.GPIO_Pin = GPIO_Pin_4;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &gpio);

	//PWM gpiof pin 6 init
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //clock
	gpio.GPIO_Pin = GPIO_Pin_6;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);

	//timer 17 init
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //clock

	TIM_TimeBaseInitTypeDef tim;
	tim.TIM_Prescaler = (uint16_t) (SystemCoreClock / 200000) - 1; //set timer frequency
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3, &tim);

	//pwm init
	TIM_OCInitTypeDef oc;
	oc.TIM_OCMode = TIM_OCMode_PWM1;
	oc.TIM_Pulse = 0;
	oc.TIM_OutputState = TIM_OutputState_Enable;
	oc.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM3, &oc);

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM3, ENABLE);
	TIM_Cmd(TIM3, ENABLE);

	//init start value
	setSpeed(0);

}

void RightWheel::setSpeed(int16_t speed) {
	if (speed != 0) {
		TIM_PrescalerConfig(TIM3, (uint16_t) (SystemCoreClock / speed) - 1,
		TIM_PSCReloadMode_Update);
		TIM_SetCompare1(TIM3, 100);
	} else
		TIM_SetCompare1(TIM3, 0);
}

void RightWheel::stop() {
}
