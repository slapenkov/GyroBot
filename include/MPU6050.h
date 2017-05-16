/*
 * MPU6050.h
 *
 *  Created on: 2 мая 2017 г.
 *      Author: gray
 */

#ifndef MPU6050_H_
#define MPU6050_H_

#include "MPU6050_def.h"
#include "HAL_MPU6050.h"
#include "diag/Trace.h"

class MPU6050 {
public:
	MPU6050() = default;

	void powerUp() {
		MPU_I2C_ClockToggling();
		MPU6050_I2C_Init();
	}

	void initialize() {
		MPU6050_Initialize();
	}

	void updateAccelGyro() {
		MPU6050_GetRawAccelGyro(accelGyro);
	}

	double getXaccel();
	double getZaccel();

	double getXZangle();

private:
	int16_t accelGyro[6];
};

#endif /* MPU6050_H_ */
