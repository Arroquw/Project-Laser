/*
 * timer.h
 *
 *  Created on: 12 okt. 2015
 *      Author: Stefan
 */

#ifndef TIMER_H_
#define TIMER_H_

#define	PCONP			(*(unsigned int *)(0x400FC0C4))
#define T0				0x40004000

#define T0TCR			(*(unsigned int *)(T0 + 0x004))		//enable/reset timer
#define T0TC			(*(unsigned int *)(T0 + 0x008))		//huidige waarde timer
#define T0MR0			(*(unsigned int *)(T0 + 0x018))
#define ISER0			(*(unsigned int *)(0xE000E100)) 		//enable interrupt van timer 0
#define T0MCR			(*(unsigned int *)(T0 + 0x014)) 	//geeft aan wat er gebeurt op interrupt
#define T0IR			(*(unsigned int *)(T0)) 			//interrupt flags

void initTimer();
#endif /* TIMER_H_ */
