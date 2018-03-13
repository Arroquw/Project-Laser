/*
 * testsignaal.c
 *
 *  Created on: 14 feb. 2017
 *  Author: stefan
 */

#include "testsignaal.h"

unsigned short samples[NUM_SAMPLES + 1];

int end_sample = 0, start_sample = 0;

//Initialize DAC
void init_DAC() {
	PINSEL1 |= (1 << 21);				//Enable DAC AOUT op pin p0.26
	//DACR &= ~(1 << 16);					//Converter register
	PCLKSEL0 |= (1 << 22);//Clock DAC instellen, uit is op CLK/4, aan is op CLK
}

//Write to DAC
void write_output_DAC(int index) {
	unsigned short value = samples[index];
	//printf("%d\n", value);
	DACR = (value << 6);				//Zet 'value' op de output van de DAC.
}

//Get sample from array
unsigned short get_sample(int index) {
	return samples[index];
}

//Get end index from array.
int get_end_index() {
	return end_sample;
}

//Fill array with samples
void fill_sample_array(double freq) {
	double counter = 0;
	double full = SAMPLE_RATE / freq;
	double counter_add = 0.485;

	//Loop for making samples and fill array.
	for (int i = 0; i < NUM_SAMPLES + 1; i++) {
		samples[i] = 500 + (unsigned short)500 * sin(freq * 2 * M_PI * ((double)counter / (double)(SAMPLE_RATE)));
		samples[i + 1] = samples[i];

		if(counter >= (full - counter_add)) {	//Periode voorbij? stop samplen.
			end_sample = i;
			if(samples[end_sample] > 450){
				start_sample = 1;
			}else {
				start_sample = 0;
			}
			break;
		}

		counter+= counter_add;
	}
}

//Send samples to DAC
void to_DAC() {
	for(int i = start_sample; i <= end_sample; i++){
		write_output_DAC(i);		//send sample to DAC
	}
}
