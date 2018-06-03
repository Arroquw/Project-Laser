/*
 * timer.c
 *
 *  Created on: 12 okt. 2015
 *      Author: Stefan
 */
#include "timer.h"

void initTimer(){

	PCONP |= 2;				//enable clock voor timer
	ISER0 |= 2;				//enable interrupt op timer 0
	T0MR0 =  4000;			//Match register op 4x de tijd voor een bit van de IR.
	T0MCR |= 3;				//Match control register - bij een match timer resetten en interrupt geven.
	T0TCR |= 3;				//Timer control register - timer enabled en in reset mode.
}

