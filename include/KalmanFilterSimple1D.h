/*
 * KalmanFilterSimple1D.h
 *
 *  Created on: 16 мая 2017 г.
 *      Author: gray
 */

#ifndef KALMANFILTERSIMPLE1D_H_
#define KALMANFILTERSIMPLE1D_H_

class KalmanFilterSimple1D {

private:
	double X0; // predicted state
	double P0; // predicted covariance
	double F;  // factor of real value to previous real value
	double Q;  // measurement noise
	double H;  // factor of measured value to real value
	double R;  // environment noise
	double State, Covariance;

public:
	KalmanFilterSimple1D(double q, double r, double f, double h);
	void SetState(double state, double covariance);
	void Correct(double data);

	double getState() {
		return State;
	}
};

#endif /* KALMANFILTERSIMPLE1D_H_ */
