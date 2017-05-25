/*
 * HardwareSerial.cpp
 *
 *  Created on: 24 мая 2017 г.
 *      Author: gray
 */

#include "HardwareSerial.h"



void HardwareSerial::begin(uint32_t baud) {
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	RCC_APB2PeriphClockCmd((RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO),
			ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	//usart2 tx - PA2
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2; //select pin PA9
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; //set max speed
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; //Alternate func, set Push-Pull
	GPIO_Init(GPIOA, &GPIO_InitStruct); //Set GPIO props

	//usart2 rx - PA3
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3; //Select PA10
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; //Input floating
	GPIO_Init(GPIOA, &GPIO_InitStruct); //Store in GPIO props

	USART_InitStruct.USART_BaudRate = baud; //Set speed
	USART_InitStruct.USART_WordLength = USART_WordLength_8b; //Length 8 bits
	USART_InitStruct.USART_StopBits = USART_StopBits_1; //1 stop-bit
	USART_InitStruct.USART_Parity = USART_Parity_No; //No parity
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //No flow control
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //On transmitter and receiver of USART1
	USART_Init(USART1, &USART_InitStruct); //Store USART1 props

	USART_Cmd(USART1, ENABLE); //On USART1

	HardwareSerial::bytesAvailable = 0;
}

void HardwareSerial::write(uint8_t b) {
	while (!(USART1->SR & USART_SR_TC))
		;
	USART1->DR = (uint16_t) b;
}

uint8_t HardwareSerial::read() {
	HardwareSerial::bytesAvailable--;
	return (uint8_t) USART_ReceiveData(USART2);
}

uint8_t HardwareSerial::available() {
	return HardwareSerial::bytesAvailable;
}
