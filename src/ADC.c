/*
 * ADC.c
 *
 *  Created on: 10 apr. 2017
 *      Author: stefa
 */

#include "ADC.h"

void init_ADC(){
	PCONP |= (1<<12); 				//Turn on ADC power and clock
	PCLKSEL0 |= ((1<<24)|(1<<25));	//Scale the ADC clock by 8 (96/8 = 12MHz)

	PINSEL3 |= (2 << 29); //P1.30 is connected to AD0.4
	PINMODE3 |= (1 << 29); //No pullups/downs
	AD0CR = (1 << 4)|(1 << 21)|(0 << 8); //Turn on ADC
}

void read_ADC(unsigned short *samples){
	for(int i = 0; i < 1024; i++)
	{
		AD0CR |= (1<<24);//start a conversion
		while((AD0DR4 >> 31) && 1){} //wait for conversion
		samples[i] = (AD0DR4>>4) & 0xFFF; //save ADC conversion
	}
}
