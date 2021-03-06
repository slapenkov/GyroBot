/*
 * GyroBot v1.0 control program
 *
 * @Author Sergey Lapenkov 2017
 *
 * */

// ----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "Timer.h"
#include "MPU6050.h"
#include "BlinkLed.h"
#include "LeftWheel.h"
#include "RightWheel.h"
//#include "KalmanFilterSimple1D.h"
#include "AverageFilter.h"
#include "math.h"
#include "Pid.h"
#include "HardwareSerial.h"
// ----------------------------------------------------------------------------
//Remote control include
#define REMOTEXY_MODE__HARDSERIAL

#include "RemoteXY.h"

HardwareSerial Serial;

#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 9600

//interface configuration
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] = { 255, 1, 0, 0, 0, 10, 0, 6, 5, 0, 4, 128, 3, 16, 94,
		22, 2 };

//struct defined all gui variables
struct {

	// input variable
	int8_t slider_1; // =0..100 slider position

	// other variable
	uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;
#pragma pack(pop)

//accelerations
int16_t accelGyro[6] = { 0 };

double ang = 0;
double speed = 0;
double setPoint = 0;

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int main(int argc, char* argv[]) {
	// Send a greeting to the trace device (skipped on Release).
	trace_puts("Hello ARM World! I am GyroBot v1.0!");

	// At this stage the system clock should have already been configured
	// at high speed.
	trace_printf("System clock: %u Hz\n", SystemCoreClock);

	Timer timer;
	timer.start();
	trace_puts("System timer 1 mS started...");

	MPU6050 mpu;
	BlinkLed led;
	LeftWheel leftWheel;
	RightWheel rightWheel;

	// Perform all necessary initializations for the peripherals.
	led.powerUp();
	trace_puts("Led periph started...");
	mpu.powerUp();
	trace_puts("MPU subsystem started...");
	leftWheel.powerUp();
	rightWheel.powerUp();
	trace_puts("Wheels initialized...");

	//initialize remote control
	RemoteXY_Init();

	uint32_t mseconds = 0;
	// Initialize external devices
	mpu.initialize();
	trace_puts("MPU initialized...");

	//KalmanFilterSimple1D kalman(1, 1, 10, 10);
	//kalman.SetState(0, 0.1);

	AverageFilter filterX, filterZ;
	double Kp = 2000, Ki = 500, Kd = 0;
	Pid pid(&ang, &speed, &setPoint, Kp, Ki, Kd, REVERSE);
	pid.SetOutputLimits(-3000, 3000);
	pid.SetMode(AUTOMATIC);
	trace_puts("Starting PID...");

	trace_printf("Entering to infinite loop...\n");
	// Infinite loop
	while (1) {
		RemoteXY_Handler(); //handle remote events
		timer.waitNewTick(); //wait 1mS tick
		if (mseconds > 4) {
			led.toggle();

			//getting accelerometer data
			mpu.updateAccelGyro();
			double x = mpu.getXaccel();
			double z = mpu.getZaccel();

			//calculate angle from filtered orthogonal accelerometers data
			ang = atan2(filterX.filtering(x), filterZ.filtering(z));
			//kalman.Correct(ang);
			//double angle = kalman.getState();
			//trace_printf("Angle: %f \n", ang);

			//balancing regulator
			//int16_t speed = int(3000 * ang);

			pid.Compute();
			if (abs(speed) < 30)
				speed = 0;

			//trace_printf("Speed: %f \n", speed);

			leftWheel.setSpeed((int16_t) speed);
			rightWheel.setSpeed((int16_t) speed);

			mseconds = 0;
		} else
			mseconds++;

	}
	// Infinite loop, never return.
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
