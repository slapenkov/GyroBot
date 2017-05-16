/*
 * MPU6050.cpp
 *
 *  Created on: 2 мая 2017 г.
 *      Author: gray
 */

#include "MPU6050.h"
#include "math.h"

double MPU6050::getXaccel() {
	return (double) accelGyro[1];
}

double MPU6050::getZaccel() {
	return (double) accelGyro[2];
}

double MPU6050::getXZangle() {
	return atan2(accelGyro[1], accelGyro[2]);
}
