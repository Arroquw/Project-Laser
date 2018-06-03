/*
 ===============================================================================
 Name        : projectWekker.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
 ===============================================================================
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include "timer.h"
#include "matrix.h"
#include "interrupt.h"
#include "IR.h"
#include "Interface.h"
#include "I2C.h"
#include "PWM.h"

//Globale variabelen
unsigned int time, x = 0, startIR = 0, numSet = 0, selectNum = 0, alarmOn = 0,
		answer = 0, brightness = 20, counter = 0, freq = 240, state = 0;
unsigned int  bitarray[28];

#define showTime 	0
#define showAlarm 	1
#define showSom 	2
#define setAlarm 	3
#define solveSom 	4

int main(void) {
	initMatrix();		//initializeren
	initTimer();
	initInterrupt();
	IRInit();
	pwmInit();
	i2cInit();

	bitarray[0] = 1;
	char data[] = "12:12";
	char alarm[] = "12:12";
	char som[] = "     ";
	char guess[] = "     ";
	int hour = 0;
	int min = 0;
	createNumber(data, selectNum, numSet, alarmOn);

	while (1) {							//oneindige while loop voor programma
		matrixFunctie(brightness);						//Functie voor display


		hour = rtcRead(0);
		min = rtcRead(1);

		data[0] = ((hour / 10 )+ '0');
		data[1] = ((hour % 10) + '0');
		data[3] = ((min / 10 )+ '0');
		data[4] = ((min % 10) + '0');

		if (state == showSom || state == solveSom) {//algoritme voor het alarm signaal aansturen
			counter++;
			if (freq != 0) {
				if (counter == 1) {
					pwmOn();
				} else if (counter == freq) {
					pwmOff();
				} else if (counter >= (2 * freq)) {
					counter = 0;
				}
			} else {
				pwmOn();
			}
		}

		if (alarmOn == 1) {		//als het alarm aan is, check of tijd == alarm.
			if (checkAlarm(alarm, data) == 1) {
				state = showSom;
				answer = generateSum(som);
			}
		}
		if (startIR == 1) {										//check of er een knop op de afstandsbediening is ingedrukt.
			int digit = checkNumberPressed(bitarray, startIR);	//Welk nummer is er ingedrukt?
			if (digit >= 0 && digit <= 9) {						//is het een cijfer?
				if (state == setAlarm) {
					if (numSet == 0) {
						if (digit < 3) {
							setAlarmClock(digit, &numSet, &alarm, &state); 	//set Alarm clock (1e en 3e positie)
						}
					} else if(numSet == 3){
						if(digit < 6){
							setAlarmClock(digit, &numSet, &alarm, &state); 	//set Alarm clock
						}
					} else {
						setAlarmClock(digit, &numSet, &alarm, &state); 		//set Alarm clock
					}
				} else if (state == solveSom) {
					guessSom(digit, &numSet, &guess);						//invullen van antwoord op som
				}
			}
			matrixFunctie(brightness);
			if (digit == 15) {		//is er op de 'src' knop gedrukt?
				if (state == showTime || state == showAlarm) {	 				//verschillende states
					selectNum = 1;
					state = setAlarm;
				}
				if (state == showSom) {											//Van showSom naar solveSom
					state = solveSom;
				} else if (state == solveSom) {
					numSet = 0;
					if (checkGuess(&guess, answer) == 1) {						//check antwoord op som.
						state = showTime;
						alarmOn = 0;
						counter = 0;
						pwmOff();
						PWM1PR = 0x7d;
						freq = 240;
					} else {		//bij fout antwoord, alarm irritanter maken
						if (PWM1PR > 20) {
							PWM1PR = PWM1PR - 20;
						}
						if (freq >= 40) {
							freq = freq - 40;
						}
						answer = generateSum(som);		//nieuwe som genereren
						state = showSom;
					}
					int i;
					for (i = 0; i < 5; i++) {
						guess[i] = ' ';
					}
				}
			}
			if (state != showSom) {
				if (digit == 43) {					//Alarm aan of uit zetten
					if (alarmOn == 1) {
						alarmOn = 0;
					} else {
						alarmOn = 1;
					}
				} else if (digit == 44) {			//Laat de alarm tijd zien
					if (state == showAlarm) {
						state = showTime;
					} else {
						state = showAlarm;
					}
				}
			}
			matrixFunctie(brightness);
			if (digit == 42) {				//Knop omhoog -> brightness omhoog
				if (brightness < 35) {
					brightness = brightness + 5;
				}
			} else if (digit == 53) {		//Knop omlaag -> brightness omlaag
				if (brightness > 5) {
					brightness = brightness - 5;
				}
			}

			//Verschillende states voor weergave op display
			if (state == setAlarm || state == showAlarm) {//Laat de alarm tijd zien
				createNumber(alarm, selectNum, numSet, alarmOn);
			} else if (state == showSom) {					//Laat de som zien
				selectNum = 0;
				alarmOn = 0;
				createNumber(som, selectNum, numSet, alarmOn);
			} else if (state == solveSom) {			//Antwoord op som invullen
				selectNum = 1;
				createNumber(guess, selectNum, numSet, alarmOn);
				selectNum = 0;
			} else {									//laat de tijd zien.
				selectNum = 0;
				createNumber(data, selectNum, numSet, alarmOn);
			}
			startIR = 0;
			matrixFunctie(brightness);
		}

	}

	return 0;
}

//Interrupt Handler voor timer
void TIMER0_IRQHandler(void) {
	bitarray[27] = ((~bitarray[26]) & 1);	//laatste bit instellen
	T0TCR &= ~1; 						//reset timer counter and stop the timer
	T0TC = 0;								//timer counter gelijk aan 0 stellen
	x = 0;
	startIR = 1;							//Volledige bitreeks uitgelezen
	T0IR |= 1;								//Interrupt flag weghalen
}

//Interrupt handler voor de IR sensor
void EINT3_IRQHandler(void) {
	if ((T0TCR & 2) != 2)				//check of timer loopt
	{
		time = T0TC;					//read timer counter
		T0TCR |= 3; 					//reset timer counter and stop the timer
	}
	T0TCR &= ~2;	 					//start the timer again

	if (time < 1200) 					//check for single bit
			{
		bitarray[x] = IRRead();
		x++;
	} else if (time > 1200) 			//check for double bit
			{
		bitarray[x] = IRRead();
		bitarray[x + 1] = IRRead();
		x += 2;
	}

	IO0IntClr |= (1 << 2);				//Interrupt flag weghalen
}

