/*
 * FFT.h
 *
 *  Created on: 7 apr. 2017
 *      Author: stefa
 */

#ifndef FFT_H_
#define FFT_H_

#include <stdio.h>
#include <string.h>

#include <stdlib.h>
#include <math.h>

#include <assert.h>


#define q	5		/* for 2^3 points */
#define N	(1<<q)		/* N-point FFT, iFFT */

typedef float real;
typedef struct {
	real Re;
	real Im;
} complex;

#ifndef PI
# define PI	3.14159265358979323846264338327950288
#endif

void print_vector(const char *title, complex *x, int n);
void fft(complex *v, int n, complex *tmp);
void ifft(complex *v, int n, complex *tmp);
int Run_FFT_Test(int freq);
int Run_FFT_Live(unsigned short *samples);
int getAmp(int i);

#endif /* FFT_H_ */
