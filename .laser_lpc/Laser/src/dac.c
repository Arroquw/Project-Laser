/*
 * dac.c
 *
 * used to control the LPC1769's internal DAC
 *
 */
#include "dac.h"


#define PINSEL1 			(*(unsigned int *)(0x4002C004))	// PINSEL1 P0.26 must be enabled (bits 21:20) must be "10"
#define PCLKSEL0			(*(unsigned int *)(0x400FC1A8)) // Peripheral Clock select. (DAC bits 23:22) staat standaard op "00" = CLK/4
#define PINMODE1			(*(unsigned int *)(0x4002C044))	// PINMODE bit (21:20)
#define DACR	 			(*(unsigned int *)(0x4008C000)) // D/A Converter Register, contains value to be converted. And a power control bit.

//Initialize DAC
void init_DAC() {
	PINSEL1 |= (1 << 21);				//Enable DAC AOUT op pin p0.26
	//DACR &= ~(1 << 16);					//Converter register
	PCLKSEL0 |= (1 << 22);//Clock DAC instellen, uit is op CLK/4, aan is op CLK
}

//Write to DAC
void write_output_DAC(int16_t value) {
	DACR = (value << 6);	//Zet 'value' op de output van de DAC.
}
