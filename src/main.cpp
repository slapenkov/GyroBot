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
	trace_printf("System timer 1 mS start...\n");

	MPU6050 mpu;
	BlinkLed led;

	// Perform all necessary initializations for the peripherals.
	led.powerUp();
	mpu.powerUp();

	uint32_t mseconds = 0;

	trace_printf("Entering to infinite loop...\n");
	// Infinite loop
	while (1) {
		timer.waitNewTick();
		if (mseconds > 499) {
			led.toggle();
			mseconds = 0;
		} else
			mseconds++;

	}
	// Infinite loop, never return.
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
