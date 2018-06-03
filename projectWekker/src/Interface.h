/*
 * Interface.h
 *
 *  Created on: 27 okt. 2015
 *      Author: Stefan
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

void setAlarmClock(unsigned int numPressed, unsigned int *x, char *data, unsigned int *state);
void guessSom(unsigned int numPressed, unsigned int *x, char *guess);
int checkAlarm(char alarm[], char data[]);
int generateSum(char *data);
int checkGuess(char *guess, int answer);

#endif /* INTERFACE_H_ */
