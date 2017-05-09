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
#include "StepperServo.h"
#include "BlinkLed.h"

// ----------------------------------------------------------------------------
//
int16_t accelGyro[6] = { 0 };

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

	// Perform all necessary initializations for the peripherals.
	led.powerUp();
	trace_puts("Led periph started...");
	mpu.powerUp();
	trace_puts("MPU subsystem started...");

	uint32_t mseconds = 0;
	// Initialize external devices
	mpu.initialize();
	trace_puts("MPU initialized...");

	trace_printf("Entering to infinite loop...\n");
	// Infinite loop
	while (1) {
		timer.waitNewTick(); //wait 1mS tick
		if (mseconds > 499) {
			led.toggle();
			mpu.readAccelGyro(accelGyro);
			trace_printf("Some data %i:%i:%i-%i:%i:%i\n", accelGyro[0],
					accelGyro[1], accelGyro[2], accelGyro[3], accelGyro[4],
					accelGyro[5]);

			mseconds = 0;
		} else
			mseconds++;

	}
	// Infinite loop, never return.
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
