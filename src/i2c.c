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
#define ISER0				(*(volatile unsigned int *)	0xE000E100)

#define PCLKSEL1			(*(volatile unsigned int *)	0x400FC1AC)
#define PINSEL0				(*(volatile unsigned int *)	0x4002C000)
#define PINMODE0			(*(volatile unsigned int *)	0x4002C040)
#define PINMODE0_OD			(*(volatile unsigned int *)	0x4002C068)

#define I2C1CONSET			(*(volatile unsigned int *)	0x4005C000)
#define I2C1STAT			(*(volatile unsigned int *)	0x4005C004)
#define I2C1DAT				(*(volatile unsigned int *)	0x4005C008)
#define I2C1SCLH			(*(volatile unsigned int *)	0x4005C010)
#define I2C1SCLL			(*(volatile unsigned int *)	0x4005C014)
#define I2C1CONCLR			(*(volatile unsigned int *)	0x4005C018)

#define STA (1 << 5)
#define STO (1 << 4)
#define SIC (1 << 3)
#define AA  (1 << 2)

static volatile int command = 0;
static volatile int busy = 0;
// functions
void i2cInit() {
	PCLKSEL1 |= (1 << 6);						// enable PCLK_I2C1, set on 8MHz
	PINSEL0 |= 0xF;								// enable pin 0:3
	PINMODE0 |= 0xA;		    		// PINMODE0 neither pull-up, pull-down
	PINMODE0_OD |= (2);							//OD on Open drain
	ISER0 |= (1 << 11); 						// enable I2C1 interrupt
	I2C1CONSET = 0x40;				// enable master only functions for I2C0
	I2C1SCLH = 0xC;							// I2C on 1MHz so SCLH + SCLL = 8
	I2C1SCLL = 0xD;

	//I2C1SCLH = 7;							// I2C on 1MHz so SCLH + SCLL = 8
	//I2C1SCLL = 13;
}

void startTransmit(int n) {
	command = n;
	//command |= (1 << 6);
	I2C1CONSET |= STA;
}

volatile int *get_busy() {
	return &busy;
}

// DAC address:   0x00011001
// DAC data bits: db23:0
// DB23 reserved, always 0. DB22 multibyte bit selection.
// C2 C1 C0 command bits. (DB21 20 19)
// A2 A1 A0 address bits. (DB18 17 16) used for channel selection
// followed by 2 16 bit words
void I2C1_IRQHandler(void) {
	busy = 1;
	//static int commandSent = 0;
	static int dataByteNr = 0;
	int caseNumber = I2C1STAT;
	switch (caseNumber) {
	case 0x00:
		/* bus error: Enter not addressed Slave mode and release bus */
		I2C1CONSET |= STO;
		I2C1CONCLR |= SIC;
		break;
	case 0x08:
		/* start condition, Slave address + R/W will be transmitted */
		I2C1DAT = 0x1E;	// high speed mode byte
		//I2C1CONSET |= AA;
		I2C1CONCLR |= STA;
		I2C1CONCLR |= SIC;
		break;
	case 0x10:
		/* repeated start condition, slave address + R/W will be transmitted */
		I2C1DAT = 0x1E; // slave address
		I2C1CONCLR |= STA;
		I2C1CONCLR |= SIC;
		break;
	case 0x18:
		/* previous state was 0x08 or 0x10, slave address + R/W transmitted
		 * ACK received, first byte transmitted
		 */
//		if (!commandSent) {
//			commandSent = 1;
		I2C1DAT = command;
//		}
		I2C1CONCLR |= SIC;
		break;
	case 0x20:
		/* slave address + write has been transmitted,
		 * NOT ACK received, repeated start condition transmitted
		 */
		I2C1SCLH = 4;							// I2C on 1MHz so SCLH + SCLL = 8
		I2C1SCLL = 4;
		I2C1CONSET |= STA;
		I2C1CONCLR |= SIC;
		break;
	case 0x28:
		/* Data transmitted, ACK received
		 * if the transmitted data was the last data byte
		 * then transmit STOP condition
		 * otherwise transmit next data byte
		 */
		if (dataByteNr < 2) {
			I2C1DAT = getDataByte(dataByteNr);
			dataByteNr++;
		} else {
			dataByteNr = 0;
			//commandSent = 0;
			busy = 0;
			I2C1CONSET |= STO;
		}
		I2C1CONCLR |= SIC;
		break;
	case 0x30:
		/* data has been transmitted, NOT ACK received,
		 * Stop will be transmitted
		 */
		I2C1CONSET |= STO;
		I2C1CONCLR |= SIC;
		break;
	case 0x38:
		/* Arbitration has been lost during Slave Address + write or Data
		 * Bus is released and not addressed slave mode entered
		 * new START condition will be transmitted when bus is free again
		 */
		I2C1CONSET |= STA;
		I2C1CONCLR |= SIC;
		break;
	}
}

