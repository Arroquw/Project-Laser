/*
 * i2c.h
 *
 *  Created on: 21 Mar 2018
 *      Author: Justi
 */


#ifndef I2C_H_
#define I2C_H_

extern void I2C0_IRQHandler( void );
extern void i2cInit( void );
extern void startTransmit(int n);

//#define I2C_IDLE 0
#define I2C_STARTED 		1
#define I2C_RESTARTED 		2
#define I2C_REPEATED_START 	3
#define DATA_ACK			4
#define DATA_NACK			5
#define I2C_BUSY			6
#define NO_DATA				7
#define I2C_OK				8
#define I2C_TIMEOUT			9
#define STATE_ERR			10
#define MAX_TIMEOUT			0xFFFFFF

#endif /* I2C_H_ */
