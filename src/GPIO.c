/*
  * test.cpp
 *
 *  Created on: 8 mrt. 2016
 *      Author: Justin
 */

#include "GPIO.h"

//Write value to output pin. (GPIO 0)
void gpio0WritePin(int32_t pinNr, int32_t value) {
	if (!value) {
		FIO0CLR |= (1 << pinNr);
	} else {
		FIO0SET |= (1 << pinNr);
	}
}

//Read value from input pin. (GPIO 0)
uint32_t gpio0ReadPin(int32_t pinNr) {
	return ((FIO0PIN >> pinNr) & 0x1);
}

//Write value to output pin. (GPIO 1)
void gpio1WritePin(int32_t pinNr, int32_t value) {
	if (!value) {
		FIO1CLR |= (1 << pinNr);
	} else {
		FIO1SET |= (1 << pinNr);
	}
}

//Read value from input pin. (GPIO 0)
uint32_t gpio1ReadPin(int32_t pinNr) {
	return ((FIO1PIN >> pinNr) & 0x1);
}

//Write value to output pin. (GPIO 2)
void gpio2WritePin(int32_t pinNr, int32_t value) {
	if (!value) {
		FIO2CLR |= (1 << pinNr);
	} else {
		FIO2SET |= (1 << pinNr);
	}
}

//Read value from input pin. (GPIO 0)
uint32_t gpio2ReadPin(int32_t pinNr) {
	return ((FIO2PIN >> pinNr) & 0x1);
}

//Initialize GPIO pin's, all pin's are output.
void gpioInit() {
	FIO0DIR0 |= 0xFF;
	FIO0DIR1 |= 0xFF;
	//PINMODE0 |= (1 << 18);
	//FIO0DIR1 &= ~(1 << 2);
	FIO0DIR2 |= 0xFF;
	FIO1DIR0 |= 0xFF;
	FIO1DIR1 |= 0xFF;
	FIO1DIR2 |= 0xFF;
	// stel priority interrupts in
	//IPR0 |= 0xF0000000;
}

unsigned int readPIN2() {
	return ~(FIO0PIN >> 9) & 1; //lees bit 8 data uit
}
