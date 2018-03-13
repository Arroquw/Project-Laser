/*
 * testsignaal.h
 *
 *  Created on: 15 feb. 2017
 *      Author: stefa
 */

#ifndef TESTSIGNAAL_H_
#define TESTSIGNAAL_H_

#include <math.h>
#include <stdio.h>
#include <string.h>
#include "GPIO.h"

#define DACR	 			(*(unsigned int *)(0x4008C000)) // D/A Converter Register, contains value to be converted. And a power control bit.

#define M_PI 3.1415926535897932384626433832795L					//PI definineren
#define NUM_SAMPLES 1024										//Aantal samples
#define SAMPLE_RATE 44100

void init_DAC();
void to_DAC();
void write_output_DAC(int index);
void fill_sample_array(double freq);
unsigned short get_sample(int index);
int get_end_index();

#endif /* TESTSIGNAAL_H_ */
