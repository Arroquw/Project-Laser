/*
 * interrupt.h
 *
 *  Created on: 15 okt. 2015
 *      Author: Stefan
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#define ISER0 			(*(unsigned int *)(0xE000E100))
#define IO0IntEnR 		(*(unsigned int *)(0x40028090))		//interrupt enable rising edge
#define IO0IntEnF 		(*(unsigned int *)(0x40028094))		//interrupt enable falling edge
#define IO0IntClr 		(*(unsigned int *)(0x4002808C))		//interrupt clear
#define EXTMODE 		(*(unsigned int *)(0x400FC148))		//interrupt edge sensitive

void init_Interrupt();


#endif /* INTERRUPT_H_ */
