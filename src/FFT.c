/*
 * FFT.c
 *
 *  Created on: 7 apr. 2017
 *      Author: stefa
 */

#include <cr_section_macros.h>

#include "FFT.h"

/* Factored discrete Fourier transform, or FFT, and its inverse iFFT */
float P[N];

/* Print a vector of complexes as ordered pairs. */
void print_vector(const char *title, complex *x, int n) {
	int i;
	printf("%s (dim=%d):", title, n);
	for (i = 0; i < n; i++)
		printf(" %5.2f,%5.2f ", x[i].Re, x[i].Im);
	putchar('\n');

	int y = 0;
	for (int x = 0; x < N / 2; x++) {
		y = ((22050 / (N / 2)) * x);
		printf("\n%dHz: ", y);
		if (y < 1000) {
			printf("    ");
		} else if (y < 10000) {
			printf(" ");
		}

		for (int z = 0; z < ((P[x] / 8000) * 16); z++) {
			printf("*");
		}
		/*
		for (int z = 0; z < P[x] / 100; z++) {
			printf("*");
		}
		*/
	}
	return;
}

/*
 fft(v,N):
 [0] If N==1 then return.
 [1] For k = 0 to N/2-1, let ve[k] = v[2*k]
 [2] Compute fft(ve, N/2);
 [3] For k = 0 to N/2-1, let vo[k] = v[2*k+1]
 [4] Compute fft(vo, N/2);
 [5] For m = 0 to N/2-1, do [6] through [9]
 [6]   Let w.re = cos(2*PI*m/N)
 [7]   Let w.im = -sin(2*PI*m/N)
 [8]   Let v[m] = ve[m] + w*vo[m]
 [9]   Let v[m+N/2] = ve[m] - w*vo[m]
 */
void fft(complex *v, int n, complex *tmp) {
	if (n > 1) { /* otherwise, do nothing and return */
		int k, m;
		complex z, w, *vo, *ve;
		ve = tmp;
		vo = tmp + n / 2;
		for (k = 0; k < n / 2; k++) {
			ve[k] = v[2 * k];
			vo[k] = v[2 * k + 1];
		}
		fft(ve, n / 2, v); /* FFT on even-indexed elements of v[] */
		fft(vo, n / 2, v); /* FFT on odd-indexed elements of v[] */
		for (m = 0; m < n / 2; m++) {
			w.Re = cos(2 * PI * m / (double) n);
			w.Im = -sin(2 * PI * m / (double) n);
			z.Re = w.Re * vo[m].Re - w.Im * vo[m].Im; /* Re(w*vo[m]) */
			z.Im = w.Re * vo[m].Im + w.Im * vo[m].Re; /* Im(w*vo[m]) */
			v[m].Re = ve[m].Re + z.Re;
			v[m].Im = ve[m].Im + z.Im;
			v[m + n / 2].Re = ve[m].Re - z.Re;
			v[m + n / 2].Im = ve[m].Im - z.Im;
		}
	}
	for (int i = 0; i < N / 2; i++) {
		P[i] = sqrt((v[i].Re * v[i].Re) + (v[i].Im * v[i].Im));
	}
	return;
}

int Run_FFT_Test(int freq) {	//Run FFT with samples from sine wave.
	complex v[N], v1[N], scratch[N];

	for (int i = 0; i < N; i++) {
		v[i].Re = (unsigned short) 500* sin(freq * 2 * PI * ((double) i / (double) (44100)));
		v[i].Im = 0;
	}


	fft(v, N, scratch);
	print_vector(" FFT", v, N);

	return 0;
}

int Run_FFT_Live(unsigned short *samples) {	//Run FFT with LIVE samples from audio
	complex v[N], v1[N], scratch[N];

	for (int i = 0; i < N; i++) {
		v[i].Re = samples[i];
		v[i].Im = 0;
	}

	fft(v, N, scratch);
	//print_vector(" FFT", v, N);

	return 0;
}

int getAmp(int i) {
	return (unsigned short) ((P[i] / 8000) * 16);
}
