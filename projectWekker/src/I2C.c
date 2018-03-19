// includes
#include "I2C.h"

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

// variables
int datacounter;
int caseNumber;
int busy;
int pointer;

int read = 0;
int dataLength = 3;

int array[3];
int array2[3];
int alarm[3];

// functions
void i2cInit() {
	PCLKSEL1 |= 0xC0;						// enable PCLK_I2C1
	PINSEL0 |= 0xF;							// enable pin 0:3
	PINMODE0 |= 0xA;		    // PINMODE0 neither pull-up, pull-down
	PINMODE0_OD |= 0x2;						//OD on Open drain
	ISER0 |= 0x800; 						// enable I2C1 interrupt
	I2C1CONSET = 0x40;					// enable master only functions for I2C0
	I2C1SCLH = 0xA;				// I2C on 100KHz so SCLH and SCLL on 10 (0xA)
	I2C1SCLL = 0xA;
}

int rtcRead(int i) {
	startReceive();
	while (busy == 1) {
	}

	if (i == 0) {
		int hourbcd = array2[2];
		int a = (hourbcd & 0xF);
		int b = (((hourbcd & 0xF0) >> 4) * 10);
		int hourdec = a + b;

		return hourdec;
	} else {
		int minbcd = array2[1];
		int a = (minbcd & 0xF);
		int b = (((minbcd & 0xF0) >> 4) * 10);
		int mindec = a + b;

		return mindec;
	}
}

void rtcWrite(int hourdec1, int mindec2) {
	int hourbcd1 = (hourdec1 / 10) << 4;
	hourbcd1 |= (hourdec1 % 10);
	int minbcd1 = (mindec2 / 10) << 4;
	minbcd1 |= (mindec2 % 10);
	array[0] = 0;
	array[1] = minbcd1;
	array[2] = hourbcd1;
	startTransmit();
}

void setAlarm(int aan, int hour, int minutes) {
	pointer = 0x10;
	int hourbin = (hour / 10) << 4;
	hourbin |= (hour % 10);
	int minutebin = (minutes / 10) << 4;
	minutebin |= (minutes % 10);
	alarm[0] = aan;
	alarm[1] = minutebin;
	alarm[2] = hourbin;
	datacounter = 0;
	I2C1CONSET = 0x20;
}

void startTransmit() {
	pointer = 0x0;
	datacounter = 0;						// initialize datacounter
	I2C1CONSET = 0x20;						// set STA bit
}

void startReceive() {
	pointer = 0x1;
	read = 1;
	busy = 1;
	datacounter = 0;						// initialize datacounter
	I2C1CONSET = 0x20;						// set STA bit
}

void I2C1_IRQHandler(void) {
	caseNumber = I2C1STAT;
	switch (caseNumber) {

	case 0x00:
		/* bus error: Enter not addressed Slave mode and release bus */
		I2C1CONSET = 0x14;					// set STA and AA bit
		I2C1CONCLR = 0x08;					// clear Sl flag
		break;

	case 0x08:
		/* start condition, Slave address + R/W will be transmitted*/
		I2C1DAT = 0xD0;				// write slave address + read bit
		I2C1CONCLR = 0x20;
		I2C1CONSET = 0x04;					// set AA bit
		I2C1CONCLR = 0x08;					// clear Sl flag
		break;

	case 0x10:
		/* start condition, slave address + R/W will be transmitted */
		I2C1DAT = 0xD1;				// write slave address + R/W bit
		I2C1CONCLR = 0x20;
		I2C1CONSET = 0x04;					// set AA bit
		I2C1CONCLR = 0x08;					// clear Sl flag
		break;

	case 0x18:
		/* previous state was 0x08 or 0x10, slave address + R/W transmitted
		 * ACK(nowledge) received, first bit transmitted
		 */
		I2C1DAT = pointer;          // load I2DAT with first data byte (seconds)
		I2C1CONSET = 0x04;					// set AA bit
		I2C1CONCLR = 0x08;					// clear Sl flag
		datacounter++;                      // increment data buffer pointer
		break;

	case 0x20:
		/* slave address + write has been transmitted,
		 * NOT ACK received, Stop condition transmitted
		 */
		I2C1CONSET = 0x14;					// set STO and AA bit
		I2C1CONCLR = 0x08;					// clear Sl flag
		break;

	case 0x28:
		/* Data transmitted, ACK received
		 * if the transmitted data was the last data byte
		 * then transmit STOP condition
		 * otherwise transmit next data byte
		 */
		if (read == 1) { // if lezen = true
			I2C1CONSET = 0x20;
			I2C1CONCLR = 0x08;
			read = 0;
			break;
		} else {
			if (datacounter == dataLength) { // if datacounter equals datalength
				I2C1CONSET = 0x14;				// set STO and AA bit
				I2C1CONCLR = 0x08;				// clear Sl flag
				break;
			} else {	// if not equals
				I2C1DAT = array[datacounter];	// load next data from MTB
				I2C1CONSET = 0x04;				// set AA bit
				I2C1CONCLR = 0x08;				// clear Sl bit
				datacounter++;
				break;
			}
		}
	case 0x30:
		/* data has been transmitted, NOT ACK received,
		 * Stop will be transmitted
		 */
		I2C1CONSET = 0x14;					// set STO and AA bit
		I2C1CONCLR = 0x08;					// Sl flag
		break;

	case 0x38:
		/* Arbitration has been lost during Slave Address + write or Data
		 * Bus is released and not addressed slave mode entered
		 * new START condition will be transmitted when bus is free again
		 */
		I2C1CONSET = 0x24;					// set set STA and AA bit
		I2C1CONCLR = 0x08;					// set Sl clear
		break;

	case 0x40:
		/* previous state was 0x08 or 0x10, Slave address + read has been transmitted
		 * ACK received, data will be received and ACK returned
		 */
		I2C1CONSET = 0x04;					// set AA bit
		I2C1CONCLR = 0x08;					// Sl bit
		break;

	case 0x48:
		/* slave address has been transmitted
		 * NOT ACK received, STOP condition transmitted
		 */
		I2C1CONSET = 0x14;					// set STO and AA bit
		I2C1CONCLR = 0x08;					// Sl clear
		break;

	case 0x50:
		/* DATA has been received, ACK return, DATA read from I2C0DAT
		 * additional data will be received, if the last data byte
		 * then NOT ACK will be returned, otherwise ACK will be returned
		 */
		array2[datacounter] = I2C1DAT;
		datacounter++;
		if (dataLength - 1 == datacounter) {// if datacounter equals datalength
			I2C1CONCLR = 0x0C;				// clear Sl flag and AA bit
			break;
		} else {
			I2C1CONSET = 0x04;				// set AA bit
			I2C1CONCLR = 0x08;				// clear Sl bit
			break;
		}
	case 0x58:
		/* DATA received, NOT ACK returned, DATA will be read from I2C0DAT
		 * STOP condition will be transmitted
		 */
		array2[datacounter] = I2C1DAT;    	// read data byte from MRB
		I2C1CONSET = 0x14;					// set STO and AA bit
		I2C1CONCLR = 0x08;					// clear Sl flag
		busy = 0;
	}
}
