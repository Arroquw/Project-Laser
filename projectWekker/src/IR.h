/*
 * IR.h
 *
 *  Created on: 15 okt. 2015
 *      Author: Stefan
 */

#ifndef IR_H_
#define IR_H_

#define FIO0DIR 				(*(unsigned int *)(0x2009C000))
#define FIO0MASK 				(*(unsigned int *)(0x2009C010))
#define FIO0PIN 				(*(unsigned int *)(0x2009C014))

void IRInit();
unsigned int IRRead();
int checkNumberPressed(unsigned int bitarray[], unsigned int start);

#endif /* IR_H_ */
