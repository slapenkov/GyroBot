/*
 * KalmanFilterSimple1D.cpp
 *
 *  Created on: 16 мая 2017 г.
 *      Author: gray
 */

#include "KalmanFilterSimple1D.h"

KalmanFilterSimple1D::KalmanFilterSimple1D(double q, double r, double f,
		double h) {
	this->Q = q;
	this->R = r;
	this->F = f;
	this->H = h;
}

void KalmanFilterSimple1D::SetState(double state, double covariance) {
	this->State = state;
	this->Covariance = covariance;
}

void KalmanFilterSimple1D::Correct(double data) {
	//time update - prediction
	X0 = F * State;
	P0 = F * Covariance * F + Q;
	//measurement update - correction
	double K = H * P0 / (H * P0 * H + R);
	State = X0 + K * (data - H * X0);
	Covariance = (1 - K * H) * P0;
}

