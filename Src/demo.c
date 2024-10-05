/*
 * demo.c
 *
 *  Created on: Feb 14, 2021
 *      Author: larry kiser
 *  Update to starter code for non-blocking assignment.
 *
 *  Updated on: Sept 20, 2021
 *      Author: Mitesh Parikh
*/

/**
#include <stdio.h>
#include <string.h>

#include "LED.h"
#include "UART.h"
#include "demo.h"
#include "stm32l4xx.h"
#include "core_cm4.h"

static volatile uint8_t two_seconds_elapsed = 0;

static void delay_loop( int value )
{
	// spin loop consuming CPU to spend time.
	for (int i = 0; i < value; i++)
		;
}

static void init_systick()
{
	// Use the SysTick global structure pointer to do the following in this
	// exact order with separate lines for each step:
	//
	// Disable SysTick by clearing the CTRL (CSR) register.


	// Set the enable bit in the CTRL (CSR) to start the timer.
	SysTick->CTRL = 0x0;

	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;

	// Set the LOAD (RVR) to 160,000 to give us a 2 millisecond timer.
	SysTick->LOAD |= ( SysTick_LOAD_RELOAD_Msk & 160000);

	// Set the clock source bit in the CTRL (CSR) to the internal clock.
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;

	// Set the enable bit in the CTRL (CSR) to start the timer.
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;


}

static void delay_systick()
{
	// Using the SysTick global structure pointer do the following:
	//
	// Check for the COUNTFLAG to be set. Return as soon as it is set..
	// This loop for the COUNTFLAG is a blocking call but not for more than 1 millisecond.
}

void SysTick_Handler(void)
{
	static uint32_t counter = 0;
	counter++;
	if (counter == 1000)
	{
		two_seconds_elapsed = 1;
		counter = 0;
	}

}


void run_demo()
{

	init_systick() ;

	//Enable SysTick Interrupt and set priority
	//NVIC_SetPriority(SysTick_IQRn, 0);		//Set Priority to 1
	//NVIC_EnableIRQ(SysTick_IQRn);			//Enable interrupt of USART1 peripheral

	// Initialize SysTick Timer

	// Disable the CSR Register
	//SysTick->CTRL = 0UL;

	// Set Load Value - 10ms Timer
	//SysTick->LOAD |= ( SysTick_LOAD_RELOAD_Msk & (uint32_t) (800000UL - 1UL) );

	//Set the Clock source to Internal Clock
	//SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;

	//Enable CSR register / SysTick Timer
	//SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

	//SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;

	//SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;		//enable the SysTick clock

	while (1)
	{
		if ( two_seconds_elapsed )
		{
			LED_Toggle();
			two_seconds_elapsed = 0;
		}
	}
}
**/
