/*
 * matrix.h
 *
 *  Created on: 12 okt. 2015
 *      Author: Stefan
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#define PINSEL1 				(*(unsigned int *)(0x4002C004))
#define FIO0DIR 				(*(unsigned int *)(0x2009C000))
#define FIO0MASK 				(*(unsigned int *)(0x2009C010))
#define FIO0PIN 				(*(unsigned int *)(0x2009C014))
#define FIO0SET 				(*(unsigned int *)(0x2009C018))
#define FIO0CLR					(*(unsigned int *)(0x2009C01C))

void delay(unsigned int pulses);
void writeMatrix(unsigned int bit, unsigned int value);
void matrixFunctie(int brightness);
void initPin(int pin);
void initMatrix();
void writeData(char array[], int i);
void createNumber(char data[], int setAlarm, int numSet, int alarm);

#endif /* MATRIX_H_ */
