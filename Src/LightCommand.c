/*
 * LightCommand.c
 *
 *  Author: Daniel Cho
 *
 */

#include <stdio.h>
#include <string.h>

#include "LED.h"
#include "UART.h"
#include "LightCommand.h"
#include "stm32l4xx.h"
#include "core_cm4.h"

static volatile uint8_t one_second_elapsed = 0;
char command[20];
uint8_t one_char = 0;
uint8_t line_feed = '\n';
uint8_t enter = '\r';
int redFlash = 0;
int greenFlash = 0;
int remoteModeActive = 1;

static void init_systick()
{
	SysTick->CTRL = 0x0;
	SysTick->LOAD |= ( SysTick_LOAD_RELOAD_Msk & 80000);
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler(void)
{
	static uint32_t counter = 0;
	static int start = 0;
	counter++;
	if (counter == 1000)
	{
		one_second_elapsed = 1;
		counter = 0;
		if (start == 0) {
			start = 1;
			remoteModeMessage();
		}
	}
}

void lightCommand() {
	if (strcmp(command, "RON") == 0) {
		redFlash = 0;
		RON();
	}
	else if (strcmp(command, "ROFF") == 0) {
		redFlash = 0;
		ROFF();
	}
	else if (strcmp(command, "GON") == 0) {
		greenFlash = 0;
		GON();
	}
	else if (strcmp(command, "GOFF") == 0) {
		greenFlash = 0;
		GOFF();
	}
	else if (strcmp(command, "RFLASH") == 0) {
		RFLASH();
		redFlash = 1;
	}
	else if (strcmp(command, "GFLASH") == 0) {
		GFLASH();
		greenFlash = 1;
	}
	else if (strcmp(command, "FLASHOFF") == 0) {
		greenFlash = 0;
		redFlash = 0;
		FLASHOFF();
	}
	else {
		handleInvalidCom();
	}
}

void handleInvalidCom() {
	char response[] = "Invalid Command";
	for (int i = 0; i < sizeof(response); i++) {
		uint8_t character = response[i];
		USART_Write( USART2, &character, 1);
	}
	USART_Write( USART2, &line_feed, 1);
	USART_Write( USART2, &one_char, 1);
}

void remoteModeMessage() {
	char notifyUser[] = "**REMOTE MODE ACTIVE**";
	for (int i = 0; i < sizeof(notifyUser); i++) {
		uint8_t character = notifyUser[i];
		USART_Write( USART2, &character, 1);
	}
	USART_Write( USART2, &line_feed, 1);
	USART_Write( USART2, &enter, 1);
}

void localModeMessage() {
	char notifyUser[] = "**MANUAL OVERRIDE MODE ACTIVE**";
	for (int i = 0; i < sizeof(notifyUser); i++) {
		uint8_t character = notifyUser[i];
		USART_Write( USART2, &character, 1);
	}
	USART_Write( USART2, &line_feed, 1);
	USART_Write( USART2, &enter, 1);
}

void clearCommand() {
	for (int i = 0; i < sizeof command; i++) {
		command[i] = '\0';
	}
}

void addCharacter() {
	int index = 0;
	for (int i = 0; (command[i] != '\0') && (i != sizeof command); i++) {
		index++;
	}
	command[index] = one_char;
}

void deleteCharacter() {

	int i= 0;
	for (;(command[i] != '\0') && (i < sizeof command);) {
		i++;
	}
	if(i>0){
		command[i-1] = '\0';
	}
}

void toggleflags() {
	//LocaModeActive
	if (remoteModeActive == 1) {
		remoteModeActive = 0;
		D8On();
		redFlash = 1;
		greenFlash = 1;
		localModeMessage();

	} //RemoteModeActive
	else {
		remoteModeActive = 1;
		D8Off();
		redFlash = 0;
		greenFlash = 0;
		remoteModeMessage();
	}
	FLASHOFF();
}



void run_lightCommand() {
	init_systick() ;

	while (1)
	{
		//Read UART messages and process command
		one_char = USART_Read_Nonblocking( USART2 ) ;
		//If Current Mode of Operation is Remote Mode
		if (remoteModeActive) {
			//Is it an Enter key?
			if (one_char == '\r') {
				USART_Write( USART2, &line_feed, 1);
				USART_Write( USART2, &one_char, 1);
				lightCommand(); //Handle RON, ROFF, RFLASH, GFLASH, FLASHOFF, and Invalid Command
				clearCommand(); //Clear the command buffer
			}
			//Is the backspace/delete?
			else if (one_char == '\177') {
				USART_Write( USART2, &one_char, 1); //Output to USART2 ... Write backspace/delete
				deleteCharacter(); //delete last character from the buffer
			}
			//Is it non-zero character?
			else if (one_char != 0) {
				USART_Write( USART2, &one_char, 1 ) ;
				addCharacter(); //Add the character to buffer
			}
		}
			//check for one_second_elapsed flag
			if ( one_second_elapsed ) {
				//if RFLASH command was entered
				if (redFlash) {
					RFLASH(); //toggle LEDS
				}
				//if GFLASH command was entered
				if (greenFlash) {
					GFLASH(); //toggle LEDS
				}
				one_second_elapsed = 0;
			}
			one_char=0;
	}
}
