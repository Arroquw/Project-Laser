/*
 * SPI.c
 *
 *  Created on: 22 feb. 2017
 *      Author: stefa
 */

#include "SPI.h"
#include "GPIO.h"
#include "testsignaal.h"


void init_SPI(){
	PINSEL0 |= (3 << 30);	//set pins "31:30" op '11' voor pinfunctie SCK
	PINSEL1 |= (3 << 0); 	//set pins "1:0" op '11' voor pinfunctie SSEL
	PINSEL1 |= (3 << 2);	//set pins "3:2" op '11' voor pinfunctie MISO
	PINSEL1 |= (3 << 4);	//set pins "5:4" op '11' voor pinfunctie MOSI

	PINMODE0 |= (3 << 30);//clk is pull down mode
	PINMODE1 |= (3 << 2);// Setup miso inact
	PINMODE1 |= (3 << 4);// Setup MOSI inact

	S0SPDR |=0xAA; // send first data

	PINMODE_OD1 |= (1 << 1);

	PCLKSEL0 |= (3 << 16); 	//bits17:16, PCLK_SPI Peripheral clock selection for SPI. reset value 00
	S0SPCCR |= 8; 				//set clk speed counter.

	PCONP |= (1 << 8); 			// Enable SPI

	S0SPCR |= 0x00000024;		//control register. enable master and 16 bit mode.

	S0SPDR |= 0xAFAF;			// send first data
}

void useSPI(unsigned short data){
	gpio0WritePin(23, 0);			//set ss low;

	//reset data register
	unsigned int random = S0SPDR;	//Write the data to transmitted to the SPI Data Register. This write starts the SPI data transfer
	random++;

	S0SPDR = data;					//send data

	while(((S0SPSR >> 7)&1) == 0){	//Wait for status register flag
		asm("nop");
	}
	gpio0WritePin(23, 1);			//ss high
}
