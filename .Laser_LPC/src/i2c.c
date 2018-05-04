#include "i2c.h"
#include "ilda_reader.h"
#include <stdint.h>

#define PCONP 		(*(volatile unsigned int*) 0x400FC0C4)
#define PCLKSEL0 	(*(volatile unsigned int*) 0x400FC1A8)
#define PINSEL1		(*(volatile unsigned int*) 0x4002C004)

#define I2CPADCFG	(*(volatile unsigned int*) 0x4002C07C)

#define ISER0		(*(volatile unsigned int*) 0xE000E100)
#define IPR2		(*(volatile unsigned int*) 0xE000E408)

#define	I2C0CONSET	(*(volatile unsigned int*) 0x4001C000)
#define I2C0STAT	(*(volatile unsigned int*) 0x4001C004)
#define I2C0DAT		(*(volatile unsigned int*) 0x4001C008)
#define I2C0SCLH	(*(volatile unsigned int*) 0x4001C010)
#define I2C0SCLL	(*(volatile unsigned int*) 0x4001C014)
#define I2C0CONCLR	(*(volatile unsigned int*) 0x4001C018)

#define I2EN 	0x40
#define STA 	0x20
#define STO		0x10
#define SIC		0x08
#define AA		0x04
#define MASK	0xF8

volatile uint32_t I2CMasterState = 0;
volatile uint32_t busy = 0;
volatile uint32_t command = 0;
volatile uint32_t timeout = 0;

void I2C0_IRQHandler(void) {
	static int dataByteNr = 0;
	uint8_t status = I2C0STAT & MASK;

	switch(status) {
	case 0x08:
		I2C0DAT = 0x1E;
		I2C0CONCLR = (SIC | STA);
		break;
	case 0x10:
		I2C0DAT = 0x1E;
		I2C0CONCLR = (SIC | STA);
		break;
	case 0x18:
		I2C0DAT = command;
		I2C0CONCLR = SIC;
		break;
	case 0x20:
		I2C0CONSET = STA;
		I2C0CONCLR = SIC;
	case 0x28:
		if (dataByteNr < 2) {
			if(command)
				I2C0DAT = getDataByte2(dataByteNr);
			else
				I2C0DAT = getDataByte1(dataByteNr);
			dataByteNr++;
		} else {
			I2C0CONSET = STO;
			dataByteNr = 0;
			busy = I2C_OK;
			command = 0;
		}
		I2C0CONCLR = SIC;
		break;
	case 0x30:
		I2C0CONSET = STO;
		busy = DATA_NACK;
		I2C0CONCLR = SIC;
		break;
	case 0x38:
	default:
		busy = STATE_ERR;
		I2C0CONCLR = SIC;
		break;
	}
}

void i2cInit(void) {
	PCONP |= (1 << 7);					// I2C0 power enable
	//PCLKSEL0 |= (1 << 14);				// I2C0 clk divider to 1
	PINSEL1 &= ~((3 << 22) | (3 << 24));
	PINSEL1 |= ((1 << 22) | (1 << 24)); 	// SDA0 & SCL0 pin select

	I2C0CONCLR = I2EN | STA | SIC | AA;
	I2CPADCFG &= ~(1 | 1 << 2);				// everything standard mode, for fast mode+ bit 0 and 2 must be 1

	//I2C0SCLH = 0x80;
	//I2C0SCLL = 0x80;					//standard mode speed = pclk/(LL + LH). 16M/80+80 = 100k
	I2C0SCLH = 0x20;
	I2C0SCLL = 0x20;

	ISER0 |= (1 << 10);					// I2C0 interrupt enable
	IPR2 &= (~(0x1F) << 19);			// I2C0 interrupt priority

	I2C0CONSET = I2EN;
}

void startTransmit(int n) {
	I2C0CONSET = STA;
	busy = I2C_BUSY;
	command = n;

	while(busy == I2C_BUSY) {
		if(timeout >= MAX_TIMEOUT) {
			busy = I2C_TIMEOUT;
			break;
		}
		timeout++;
	}
	timeout = 0;
	I2C0CONCLR = STA;
}
