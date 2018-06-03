/*
 * GPIO.h
 *
 *  Created on: 23 feb. 2017
 *      Author: stefa
 */
/*
 * test.h
 *
 *  Created on: 19 apr. 2016
 *      Author: Justin
 */

#ifndef TEST_H_
#define TEST_H_

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

void gpioInit();
void gpio0WritePin(int8_t pinNr, int8_t Value);
void gpio1WritePin(int8_t pinNr, int8_t Value);
void gpio2WritePin(int8_t pinNr, int8_t Value);
uint32_t gpio0ReadPin(int8_t pinNr);
uint32_t gpio1ReadPin(int8_t pinNr);
uint32_t gpio2ReadPin(int8_t pinNr);


#endif /* TEST_H_ */
