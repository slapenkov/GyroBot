/*
 * LeftWheel.h
 *
 *  Created on: 12 мая 2017 г.
 *      Author: gray
 */

#ifndef LEFTWHEEL_H_
#define LEFTWHEEL_H_

#include "stm32f10x.h"

#define PWM_PERIOD 200

class LeftWheel {
public:
	LeftWheel() = default;

	void powerUp();

	void setSpeed(int16_t speed);

	void stop();
};

#endif /* LEFTWHEEL_H_ */
