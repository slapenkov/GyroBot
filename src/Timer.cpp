//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#include "Timer.h"
#include "cortexm/ExceptionHandlers.h"

// ----------------------------------------------------------------------------

#if defined(USE_HAL_DRIVER)
extern "C" void HAL_IncTick(void);
#endif

// ----------------------------------------------------------------------------

volatile Timer::ticks_t Timer::ms_delayCount;
volatile uint8_t Timer::newTick;

// ----------------------------------------------------------------------------

void Timer::sleep(ticks_t ticks) {
	ms_delayCount = ticks;

	// Busy wait until the SysTick decrements the counter to zero.
	while (ms_delayCount != 0u)
		;
}

void Timer::waitNewTick(void) {
	while (newTick == 0); //wait for new tick
	newTick = 0;
}

// ----- SysTick_Handler() ----------------------------------------------------

extern "C" void SysTick_Handler(void) {
#if defined(USE_HAL_DRIVER)
	HAL_IncTick();
#endif
	Timer::tick();
}
// ----------------------------------------------------------------------------
