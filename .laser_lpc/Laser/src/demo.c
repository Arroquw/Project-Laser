/*
 * demo.c
 *
 *  Created on: 3 jun. 2018
 *      Author: Justi
 */

#include <math.h>

#include "demo.h"

#define M_PI 3.1415926535897932384626433832795L

uint16_t array2[1000];
uint16_t array1[1000];

void generateSine() {
	//generates a sine and a cosine to send to the galvanos. This will project a circle.
	double sine[1024];
	for(int i = 0; i < 1000; i++) {
		sine[i] = sin(2*M_PI*500*i/8000);
		array2[i] = 32768 + sine[i] * 32767;
		sine[i] = cos(2*M_PI*500*i/8000);
		array1[i] = 32768 + sine[i] * 32767;
	}
}

uint8_t getDataByte1(int cnt){
	//returns the first array in one byte since I2C sends 8 bits each transfer
	static int counter = 0;
	if(counter >= sizeof array1/sizeof array1[0]){
		counter = 0;
	}

	uint8_t respond;
	if(!cnt){
		respond = (array1[counter] >> 8) & 0xFF;
	}else{
		respond = (array1[counter] & 0xFF);
		counter++;
	}

	return respond;
}

uint8_t getDataByte2(int cnt) {
	//returns the second array in one byte since I2C sends 8 bits each transfer
	static int counter = 0;
	if(counter >= sizeof array2/sizeof array2[0]){
		counter = 0;
	}
	uint8_t respond;
	if(!cnt){
		respond = (array2[counter] >> 8) & 0xFF;
	}else{
		respond = (array2[counter] & 0xFF);
		counter++;
	}

	return respond;
}
