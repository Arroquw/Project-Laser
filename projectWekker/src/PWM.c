/*
 * PWM.c
 *
 *  Created on: Oct 16, 2015
 *      Author: Bart748
 */
#include "PWM.h"

void pwmInit() {
//	PCONP |= 0x20;
	PCLKSEL0 |= 0x1800;
	PINSEL4 |= (1 << 4);
	PINMODE4 |= (1 << 5);


	PWM1PR = 0x78;
	PWM1MR0 = 100;
	PWM1MR3 = 50;
	PWM1LER = 0x9;
	PWM1LER = 0;
	PWM1MCR = 0x2;
}

void pwmOn(){
	PWM1TCR = 0x3;
	PWM1TCR = 0x9;
	PWM1PCR = 0x800;
}

void pwmOff(){
	PWM1PCR = 0x0;
}
