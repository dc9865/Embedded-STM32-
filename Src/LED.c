// Based on code from Yifeng Zhu with University of Maine
// Extended by Larry Kiser, RIT April 1, 2021
// Documentation updates for clarity L. Kiser RIT July 15, 2021
//				also changed 3UL and 1UL to (uint32_t)3 and (uint32_t)1 respectively

#include "LED.h"


//******************************************************************************************
// Green LED on Nucleo board is LD2 Green. This is hard wired to GPIO pin PA5.
//******************************************************************************************
#define NUCLEO_GREEN_LED_PIN (5)	// GPIO PA5

// project specific manually connected LEDs on breadboard shield.
#define ARDUINO_D12 (6)				// GPIO PA6 -- hard wired to Arduino D12
#define ARDUINO_D11 (7)				// GPIO PA7 -- hard wired to Arduino D11
#define ARDUINO_D8 (9)				// GPIO PA9 -- hard wired to Arduino D8

// GPIO Output initialization for GPIO banks A, B, C, and D only
// Expects GPIO to be GPIOA, GPIOB, GPIOC, or GPIOD.
// pin is expected to be 0 through 15
// Note -- if the clock is not enabled the 16 GPIO pins are non-functional!
void GPIO_Output_Init( GPIO_TypeDef *GPIO, uint32_t pin )
{
	// Enable the peripheral clocks of for GPIO
	if ( GPIO == GPIOA )
		RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN ;
	else if ( GPIO == GPIOB )
		RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN ;
	else if ( GPIO == GPIOC )
		RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN ;
	else if ( GPIO == GPIOD )
		RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN ;
	else
		return ;

	// GPIO Mode: Input(00), Output(01), AlterFunc(10), Analog(11, reset)
	GPIO->MODER &= ~( (uint32_t)3 << ( 2 * pin ) ) ;  // clear to input mode (00)
	GPIO->MODER |= (uint32_t)1 << ( 2 * pin ) ;      //  Output(01)
	
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
	GPIO->OSPEEDR &= ~( (uint32_t)3 << ( 2 * pin ) ) ;	// set to cleared which is low speed
	GPIO->OSPEEDR |=   (uint32_t)3 << ( 2 * pin ) ;  // High speed
	
	// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	GPIO->OTYPER &= ~( (uint32_t)1 << pin ) ;       // Push-pull
	
	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	GPIO->PUPDR   &= ~( (uint32_t)3 << ( 2 * pin ) ) ;  // No pull-up, no pull-down
}

// set up PA5, PA6, and PA7 to drive LEDs
void LED_Init(void){
	GPIO_Output_Init( GPIOA, NUCLEO_GREEN_LED_PIN ) ;	// hard wired PA5 to on-board LD2 LED
	GPIO_Output_Init( GPIOA, ARDUINO_D12 ) ;		// init PA6 as output (D12)
	GPIO_Output_Init( GPIOA, ARDUINO_D11 ) ;		// init PA7 as output (D11)
	GPIO_Output_Init( GPIOA, ARDUINO_D8 ) ;			// init PA9 as output (D8)
}

//******************************************************************************************
// Turn Green LED On and GPIOA 6 and 7 to ON
//******************************************************************************************
void LED_On(void){
	GPIOA->ODR |= (uint32_t)1 << NUCLEO_GREEN_LED_PIN ; // PA5
	GPIOA->ODR |= (uint32_t)1 << ARDUINO_D12 ;	// PA6
	GPIOA->ODR |= (uint32_t)1 << ARDUINO_D11 ;	// PA7
}

//******************************************************************************************
// turn RED LED ON
//******************************************************************************************
void RON(void) {
	GPIOA->ODR |= (uint32_t)1 << ARDUINO_D11 ; //PA7
}

//******************************************************************************************
// Turn GREEN LED ON
//******************************************************************************************
void GON(void) {
	GPIOA->ODR |= (uint32_t)1 << ARDUINO_D12 ;	// PA6
}

//******************************************************************************************
// Turn Green LED Off and GPIOA 6 and 7 to OFF
//******************************************************************************************
void LED_Off(void){
	GPIOA->ODR &= ~( (uint32_t)1 << NUCLEO_GREEN_LED_PIN );
	GPIOA->ODR &= ~( (uint32_t)1 << ARDUINO_D12 ) ;	// PA6
	GPIOA->ODR &= ~( (uint32_t)1 << ARDUINO_D11 ) ; // PA7
}

//******************************************************************************************
// Turn RED LED OFF
//******************************************************************************************
void ROFF(void) {
	GPIOA->ODR &= ~( (uint32_t)1 << ARDUINO_D11 ) ; // PA7
}

//******************************************************************************************
// Turn GREEN LED OFF
//******************************************************************************************
void GOFF(void) {
	GPIOA->ODR &= ~( (uint32_t)1 << ARDUINO_D12 ) ;	// PA6
}


//******************************************************************************************
// Set Green LD2 Nucleo LED and GPIOA 6 and 7 to opposite states
//******************************************************************************************
void LED_Toggle(void){
	GPIOA->ODR ^= (uint32_t)1 << NUCLEO_GREEN_LED_PIN ;
	GPIOA->ODR ^= (uint32_t)1 << ARDUINO_D12 ;	// PA6
	GPIOA->ODR ^= (uint32_t)1 << ARDUINO_D11 ;	// PA7
}

//******************************************************************************************
// Set a flag -- regardless whether RED LED is ON or OFF prior to receiving command
//******************************************************************************************
void RFLASH(void) {
	GPIOA->ODR ^= (uint32_t)1 << ARDUINO_D11 ;	// PA7
}

//******************************************************************************************
// Set a flag -- regardless whether GREEN LED is ON or OFF prior to receiving command
//******************************************************************************************
void GFLASH(void) {
	GPIOA->ODR ^= (uint32_t)1 << ARDUINO_D12 ;	// PA6
}

//******************************************************************************************
// Turn off both LEDs
//******************************************************************************************
void FLASHOFF(void) {
	GPIOA->ODR &= ~( (uint32_t)1 << ARDUINO_D12 ) ;	// PA6 -- ROFF
	GPIOA->ODR &= ~( (uint32_t)1 << ARDUINO_D11 ) ; // PA7 -- GOFF
}

void D8On(void) {
	GPIOA->ODR |= (uint32_t)1 << ARDUINO_D8 ;	// PA9
}

void D8Off(void) {
	GPIOA->ODR &= ~( (uint32_t)1 << ARDUINO_D8 ) ;	// PA9
}
