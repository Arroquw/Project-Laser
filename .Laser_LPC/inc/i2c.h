/*
 * i2c.h
 *
 *  Created on: 21 Mar 2018
 *      Author: Justi
 */


#ifndef I2C_H_
#define I2C_H_

void i2cInit();
void startTransmit(int n);
volatile int *get_busy();


#endif /* I2C_H_ */
