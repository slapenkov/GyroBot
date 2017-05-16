/*
 * RightWheel.h
 *
 *  Created on: 12 мая 2017 г.
 *      Author: gray
 */

#ifndef RIGHTWHEEL_H_
#define RIGHTWHEEL_H_

#include <stdlib.h>
#include "stm32f10x.h"

#define PWM_PERIOD 200

class RightWheel {
public:
	RightWheel() = default;

	void powerUp();

	void setSpeed(int16_t speed);

	void stop();
};

#endif /* RIGHTWHEEL_H_ */
