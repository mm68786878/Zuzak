/*
 * clock.c
 *
 *  Created on: Jul 16, 2021
 *      Author: rickweil
 */


#include "stm32l476xx.h"

//******************************************************************************************
// System boots with MSI clock enabled. Switch to HSI.
//******************************************************************************************

void clock_init(void) {

	// Enable the High Speed Internal oscillator (HSI)
    RCC->CR |= ((uint32_t)RCC_CR_HSION);

    // wait until HSI is ready
    while ( (RCC->CR & (uint32_t) RCC_CR_HSIRDY) == 0 ) {;}

    // Select HSI as system clock source
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_HSI;     // 01: HSI16 oscillator used as system clock

    // Wait till HSI is used as system clock source
    while ((RCC->CFGR & RCC_CFGR_SWS) ==  RCC_CFGR_SWS_PLL) {;}

    // Enable the clock to GPIO Ports A, and C
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;    // enable clock for the User LED, UART
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;    // enable clock for the User Button
}
