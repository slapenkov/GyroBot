/*
 * HardwareSerial.h
 *
 *  Created on: 24 ��� 2017 �.
 *      Author: gray
 */

#ifndef HARDWARESERIAL_H_
#define HARDWARESERIAL_H_

#include "stm32f10x_usart.h"

//todo: implement serial class

class HardwareSerial {
private:
	static volatile uint8_t bytesAvailable;
public:
	HardwareSerial() = default;

	void begin(uint32_t baud);

	void write(uint8_t b);

	uint8_t read();

	uint8_t available();

};

#endif /* HARDWARESERIAL_H_ */
