/*
 * IR.c
 *
 *  Created on: 15 okt. 2015
 *      Author: Stefan
 */
#include "IR.h"

unsigned int  toggle, prevtoggle, first_time = 1, second_time = 1, number;

//Init
void IRInit() {
	FIO0DIR &= ~(1 << 2); //zet bit 8 op input
	FIO0MASK &= ~(1 << 2);
}

// Functie uitlezen van IR sensor
unsigned int IRRead() {
	return ~(FIO0PIN >> 2) & 1; //lees bit 8 data uit
}

//Functie berekenen welk nummer er gedrukt is.
int checkNumberPressed(unsigned int bitarray[], unsigned int start){
	if (start == 1)
	{
		if (first_time == 1) //checken of eerste keer
		{
			toggle = bitarray[4];
			number = bitarray[16] * 32 + bitarray[18] * 16 + bitarray[20] * 8 + bitarray[22] * 4 + bitarray[24] * 2 + bitarray[26] * 1;
			first_time = 0;
		}
		else
		{
			prevtoggle = toggle;
			toggle = bitarray[4];
			number = bitarray[16] * 32 + bitarray[18] * 16 + bitarray[20] * 8 + bitarray[22] * 4 + bitarray[24] * 2 + bitarray[26] * 1;
			if (toggle == prevtoggle)						//checken of toggle is geswitched
			{
				return 100;
			}

		}
		start = 0;
	}
	return number;	//nummer terugsturen
}
