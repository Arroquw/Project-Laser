/*
 * interrupt.c
 *
 *  Created on: 15 okt. 2015
 *      Author: Stefan
 */
#include "interrupt.h"

void initInterrupt(){
	ISER0 |= (1 << 21);				//enable interrupt voor GPIO
	IO0IntEnR |= (1 << 2);			//enable rising edge interrupt voor p0_2
	IO0IntEnF |= (1 << 2);			//enable falling edge interrupt voor p0_2
	EXTMODE |= (1 << 3);			//Both edge sensitive.
}

