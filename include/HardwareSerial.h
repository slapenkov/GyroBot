/*
 * HardwareSerial.h
 *
 *  Created on: 24 мая 2017 г.
 *      Author: gray
 */

#ifndef HARDWARESERIAL_H_
#define HARDWARESERIAL_H_

#define SERIAL_TX_BUFFER_SIZE 64
#define SERIAL_RX_BUFFER_SIZE 64

#include "stm32f10x_usart.h"

class HardwareSerial {
private:
	static volatile uint8_t _rx_buffer_head;
	static volatile uint8_t _rx_buffer_tail;
	static volatile uint8_t _tx_buffer_head;
	static volatile uint8_t _tx_buffer_tail;

protected:
	static uint8_t _rx_buffer[SERIAL_RX_BUFFER_SIZE];
	static uint8_t _tx_buffer[SERIAL_TX_BUFFER_SIZE];

public:
	HardwareSerial() = default;

	void begin(uint32_t baud);

	void write(uint8_t b);

	uint8_t read(void);

	uint8_t available(void);

	inline static void incomingEvent(void) {
		uint8_t i = (uint8_t) (_rx_buffer_head + 1) % SERIAL_RX_BUFFER_SIZE;

		if (i != _rx_buffer_tail) {
			_rx_buffer[_rx_buffer_head] = (uint8_t) USART_ReceiveData(USART2);
			_rx_buffer_head = i;
		} else
			USART_ReceiveData(USART2); //dummy read
	}

};

#endif /* HARDWARESERIAL_H_ */
