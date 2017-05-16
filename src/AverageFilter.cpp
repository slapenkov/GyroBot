/*
 * AverageFilter.cpp
 *
 *  Created on: 16 мая 2017 г.
 *      Author: gray
 */

#include "AverageFilter.h"

AverageFilter::AverageFilter() {
	index = 0;
	for (int i = 0; i < 32; i++) {
		buffer[i] = 0;
	}
}

double AverageFilter::filtering(double data) {
	buffer[index] = data;
	index++;
	if (index == DEPTH)
		index = 0;

	double sum = 0;
	for (int i = 0; i < DEPTH; i++) {
		sum += buffer[i];
	}
	return sum / DEPTH;
}
