/*
 * GPIO.h
 *
 *  Created on: 23 feb. 2017
 *      Author: stefa
 */
/*
 * test.h
 *
 *  Created on: 19 apr. 2016
 *      Author: Justin
 */

#ifndef TEST_H_
#define TEST_H_

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

// read/write value of pins

#define FIO0PIN		(* (unsigned int *)0x2009C014)
#define FIO1PIN 	(* (unsigned int *)0x2009C034)
#define FIO2PIN 	(* (unsigned int *)0x2009C054)
// set direction of pins
#define FIO0DIR0 	(* (unsigned int *)0x2009C000)
#define FIO0DIR1 	(* (unsigned int *)0x2009C001)
#define FIO0DIR2 	(* (unsigned int *)0x2009C002)

#define FIO1DIR0 	(* (unsigned int *)0x2009C020)
#define FIO1DIR1 	(* (unsigned int *)0x2009C021)
#define FIO1DIR2 	(* (unsigned int *)0x2009C022)
#define FIO1DIR3 	(* (unsigned int *)0x2009C023)

#define FIO2DIR0 	(* (unsigned int *)0x2009C040)
#define FIO2DIR1 	(* (unsigned int *)0x2009C041)
#define FIO2DIR2 	(* (unsigned int *)0x2009C042)

#define FIO3DIR0 	(* (unsigned int *)0x2009C060)
#define FIO3DIR1 	(* (unsigned int *)0x2009C061)
#define FIO3DIR2 	(* (unsigned int *)0x2009C062)


#define FIO4DIR0 	(* (unsigned int *)0x2009C080)
#define FIO4DIR1 	(* (unsigned int *)0x2009C081)
#define FIO4DIR2 	(* (unsigned int *)0x2009C082)
// set value of pins
#define FIO0SET 	(* (unsigned int *)0x2009C018)
#define FIO1SET 	(* (unsigned int *)0x2009C038)
#define FIO2SET 	(* (unsigned int *)0x2009C058)
// clear value of pins
#define FIO0CLR 	(* (unsigned int *)0x2009C01C)
#define FIO1CLR 	(* (unsigned int *)0x2009C03C)
#define FIO2CLR	 	(* (unsigned int *)0x2009C05C)

#define ISER0 		(*(unsigned int*) (0xE000E100))
#define ICER0 		(*(unsigned int*) (0xE000E180))
// interrupt priority
#define IPR0 		(*(unsigned int*) (0xE000E400))
// interrupts IO2
#define IO2IntEnR 	(* (unsigned int *)(0x400280B0))
#define IO2IntEnF 	(* (unsigned int *)(0x400280B4))
#define IO2IntClr 	(* (unsigned int *)(0x400280AC))

#define PINSEL0 	(* (unsigned int *)0x4002C000)
#define PINSEL1     (* (unsigned int *)0x4002C004)
#define PINMODE0    (* (unsigned int *)0x4002C040)
#define PINMODE1    (* (unsigned int *)0x4002C044)
#define PCONP 		(* (unsigned int *)0x400FC0C4)
#define PCLKSEL0 	(* (unsigned int *)0x400FC1A8)
#define FIO0MASK 	(*(unsigned int *)(0x2009C010))

void gpioInit();
void gpio0WritePin(int32_t pinNr, int32_t Value);
void gpio1WritePin(int32_t pinNr, int32_t Value);
void gpio2WritePin(int32_t pinNr, int32_t Value);
uint32_t gpio0ReadPin(int32_t pinNr);
uint32_t gpio1ReadPin(int32_t pinNr);
uint32_t gpio2ReadPin(int32_t pinNr);

unsigned int readPIN2();

#endif /* TEST_H_ */
