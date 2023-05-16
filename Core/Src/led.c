/*
 * led.c
 *
 *  Created on: Jul 16, 2021
 *      Author: rickweil
 */

#include "stm32l476xx.h"

// On the NUCLEO board, the green User LED LD2 is connected to ARDUINO® signal D13, and PA5 of the MCU (Port A, Bit 5)
// • When the I/O is HIGH value, the LED is on
// • When the I/O is LOW, the LED is off
#define LED_PORT GPIOA
#define LED_PIN 5

void led_init(void)
{
	// Configure LED_PIN as an output
    GPIOA->MODER &= ~(0x3<<(LED_PIN*2));    // first, clear the two MODE bits for this pin
    GPIOA->MODER |=   0x1<<(LED_PIN*2);     // 0x1 means output

    // ...and as push-pull drive
    GPIOA->OTYPER &= ~(0x1<<LED_PIN) ;

    // ...with medium speed
    GPIOA->OSPEEDR &= ~(0x3<<(LED_PIN*2));  // first, clear the two OSPEED bits for this pin
    GPIOA->OSPEEDR |=   0x1<<(LED_PIN*2) ;  // 0x1 means medium speed

    // Enable the clock to GPIO Port A
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;    // enable clock for the User LED, UART
}

void led_set(_Bool isOn )
{
	if(isOn)
		GPIOA->ODR |=  (1 << LED_PIN);
	else
		GPIOA->ODR &= ~(1 << LED_PIN);
}

_Bool led_isOn(void )
{
	uint32_t bit = GPIOA->ODR & (1<<LED_PIN);

	return (bit != 0);
}
