/*
 * ADC.h
 *
 *  Created on: 10 apr. 2017
 *      Author: stefa
 */

#ifndef ADC_H_
#define ADC_H_

#include "GPIO.h"

#define AD0CR    	(* (unsigned int *)(0x40034000))
#define PINSEL3    	(* (unsigned int *)(0x4002C00C))
#define PINMODE3   	(* (unsigned int *)(0x4002C04C))
#define AD0DR4   	(* (unsigned int *)(0x40034020))

void init_ADC();
void read_ADC();


#endif /* ADC_H_ */
