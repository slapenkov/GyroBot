/*
 * AverageFilter.h
 *
 *  Created on: 16 мая 2017 г.
 *      Author: gray
 */

#ifndef AVERAGEFILTER_H_
#define AVERAGEFILTER_H_

#define DEPTH 10

class AverageFilter {
private:
	double buffer[32];
	int index;

public:
	AverageFilter();

public:
	double filtering(double data);

};
#endif /* AVERAGEFILTER_H_ */
