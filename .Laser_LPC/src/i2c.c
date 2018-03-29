/*
 * i2c.c
 *
 *  Created on: 21 Mar 2018
 *      Author: Justi
 */

// includes
#include "i2c.h"
#include "ilda_reader.h"

// defines
#define ISER0				(*(unsigned int *)	0xE000E100)

#define PCLKSEL1			(*(unsigned int *)	0x400FC1AC)
#define PINSEL0				(*(unsigned int *)	0x4002C000)
#define PINMODE0			(*(unsigned int *)	0x4002C040)
#define PINMODE0_OD			(*(unsigned int *)	0x4002C068)

#define I2C1				0x40050000
#define I2C1CONSET			(*(unsigned int *)	0x4005C000)
#define I2C1CONCLR			(*(unsigned int *)	0x4005C018)
#define I2C1STAT			(*(unsigned int *)	0x4005C004)
#define I2C1DAT				(*(unsigned int *)	0x4005C008)
#define I2C1SCLH			(*(unsigned int *)	0x4005C010)
#define I2C1SCLL			(*(unsigned int *)	0x4005C014)

// functions
void i2cInit() {
	PCLKSEL1 |= (1 << 14);						// enable PCLK_I2C1, set on 8MHz
	PINSEL0 |= 0xF;								// enable pin 0:3
	PINMODE0 |= 0xA;		    				// PINMODE0 neither pull-up, pull-down
	PINMODE0_OD |= (3);							//OD on Open drain
	ISER0 |= (1 << 11); 						// enable I2C1 interrupt
	I2C1CONSET = (1 << 6);						// enable master only functions for I2C0
	I2C1SCLH = 0x4;								// I2C on 1MHz so SCLH + SCLL = 8
	I2C1SCLL = 0x4;
}

void startTransmit() {
	I2C1CONSET |= (1 << 5);
}

void I2C1_IRQHandler(void) {
	static int cnt = 0;
	static int failures = 0;
	int caseNumber = I2C1STAT;
	switch (caseNumber) {
	case 0x00:
		/* bus error: Enter not addressed Slave mode and release bus */
		I2C1CONSET |= (1 << 4);
		I2C1CONCLR |= (1 << 3);
		break;
	case 0x08:
		/* start condition, Slave address + R/W will be transmitted*/
		I2C1DAT = 0xD1;	//TODO: find out DAC slave address
		I2C1CONCLR |= (1 << 5);
		I2C1CONCLR |= (1 << 3);
		break;
	case 0x10:
		/* start condition, slave address + R/W will be transmitted */
		I2C1DAT = 0xD1;	//TODO: find out DAC slave address
		I2C1CONCLR |= (1 << 5);
		I2C1CONCLR |= (1 << 3);
		break;
	case 0x18:
		/* previous state was 0x08 or 0x10, slave address + R/W transmitted
		 * ACK(nowledge) received, first bit transmitted
		 */
		I2C1DAT = getDataByte(cnt);
		I2C1CONCLR |= (1 << 3);
		break;
	case 0x20:
		/* slave address + write has been transmitted,
		 * NOT ACK received, Stop condition transmitted
		 */
		I2C1CONSET |= (1 << 5);
		I2C1CONCLR |= (1 << 3);
		break;
	case 0x28:
		/* Data transmitted, ACK received
		 * if the transmitted data was the last data byte
		 * then transmit STOP condition
		 * otherwise transmit next data byte
		 */
		if(!cnt) {
			I2C1DAT = getDataByte(cnt);
			cnt = 1;
		} else {
			I2C1CONSET |= (1 << 4);
			cnt = 0;	//stops transmitting TODO: find out if restart required within i2c or external
		}
		I2C1CONCLR |= (1 << 3);
		break;
	case 0x30:
		/* data has been transmitted, NOT ACK received,
		 * Stop will be transmitted
		 */
		if(failures < 3) {
			I2C1DAT = getDataByte(cnt);
		} else {
			failures = 0;
			I2C1CONSET |= (1 << 4);
			I2C1CONSET |= (1 << 5);
		}
		failures++;
		I2C1CONCLR |= (1 << 3);
		break;
	case 0x38:
		/* Arbitration has been lost during Slave Address + write or Data
		 * Bus is released and not addressed slave mode entered
		 * new START condition will be transmitted when bus is free again
		 */
		I2C1CONSET |= (1 << 5);
		I2C1CONCLR |= (1 << 3);
		break;
	}
}

