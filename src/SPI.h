/*
 * SPI.h
 *
 *  Created on: 22 feb. 2017
 *      Author: stefa
 */

#ifndef SPI_H_
#define SPI_H_

#define PINMODE_OD1		(*(unsigned int *)(0x4002C06C))

#define S0SPCR			(*(unsigned int *)(0x40020000))  	//SPI control register. Controls operation of SPI
#define S0SPSR			(*(unsigned int *)(0x40020004))		//SPI status register. Shows status of SPI
#define S0SPDR			(*(unsigned int *)(0x40020008))		//SPI Data register. Bi-directional register transmit and receive data for SPI. Writing transmits data.
#define S0SPCCR			(*(unsigned int *)(0x4002000C))		//SPI Clock counter register. Control's frequency of master's SCK0
#define S0SPINT			(*(unsigned int *)(0x4002001C))		//SPI interrupt flag. Contains interrupt flag.

void init_SPI();
void useSPI(unsigned short data);

#endif /* SPI_H_ */
