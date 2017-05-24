/*
 * HardwareSerial.h
 *
 *  Created on: 24 мая 2017 г.
 *      Author: gray
 */

#ifndef HARDWARESERIAL_H_
#define HARDWARESERIAL_H_

#include "stm32f10x_usart.h"

//todo: implement serial class

class HardwareSerial {
public:
	HardwareSerial(); //default ctor
	HardwareSerial(USART_TypeDef* USARTx);

	void begin();
	void begin(long baud);

	void write(uint8_t b);

	uint8_t read();

	uint8_t available();
};

#endif /* HARDWARESERIAL_H_ */
