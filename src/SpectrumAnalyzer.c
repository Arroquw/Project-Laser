/*
 ===============================================================================
 Name        : SpectrumAnalyzer.c
 Author      : Stefan
 Version     :
 Copyright   : (copyright)
 Description : Spectrum Analyzer
 ===============================================================================
 */

/*Used pins:
 * 	DAC = P0.26
 *
 * 	ADC = P1.30
 *
 * SPI:
 * 	SCK = P0.15
 *  SSEL = P0.23	//1 naast originele SSEL pin.
 * 	MISO = P0.17
 * 	MOSI = P0.18
 *
 */

#include <stdio.h>
#include "testsignaal.h"
#include "SPI.h"
#include "GPIO.h"
#include "FFT.h"
#include "ADC.h"
#include "Interrupt.h"

int freq = 500;
int n = 16;

//Main functie
int main(void) {

	init_SPI(); //init SPI
	init_DAC(); //init DAC
	init_ADC();	//init ADC
	gpioInit();	//init GPIO
	init_Interrupt();

	//num of results of FFT. (1/2 num of samples)
	unsigned short samples_FFT[n*2];
	unsigned short samples_ADC[1024];
	unsigned short amplitudes[n];


	fill_sample_array(freq); //fill array with samples

	Run_FFT_Test(freq);	//run FFT on samples

	/*
	for (int i = 0; i < n-1; i++) {
		amplitudes[i] = getAmp(i);	//Fill array with results of FFT
		useSPI(amplitudes[i]);
	}*/
	for(int i=3; i>0; i--){
		useSPI(getAmp(i));
	}
	for(int i=4; i < 15; i++){
		useSPI(getAmp(i));
	}

	while(1){
		to_DAC(); 	//send samples to DAC.
	}

	return 0;
}

void EINT3_IRQHandler(void) {
	//printf("INTERRUPT");
	if(freq < 20000){
		freq += 1000;
	}else{
		freq = 100;
	}

	fill_sample_array(freq); //fill array with samples

	Run_FFT_Test(freq);	//run FFT on samples
/*
	for (int i = 0; i < n-1; i++) {
		//Fill array with results of FFT
		useSPI(getAmp(i));
	}
*/
	for(int i=0; i<4; i++){
		useSPI(getAmp(i));
	}
	for(int i=5; i < 15; i++){
		useSPI(getAmp(i));
	}

	IO0IntClr |= (1 << 3);				//Interrupt flag weghalen
}

