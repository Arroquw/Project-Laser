/*
 * Interface.c
 *
 *  Created on: 27 okt. 2015
 *      Author: Stefan
 */
#include "Interface.h"

//Functie voor instellen van alarm tijd
void setAlarmClock(unsigned int numPressed, unsigned int *x, char *alarm,
		unsigned int *state) {
	int i = *x;
	*(alarm + i) = numPressed + '0';
	if (*x == 1) {
		*x = *x + 2;
	} else {
		*x = *x + 1;
	}
	if (*x == 5) {
		*x = 0;
		*state = 0;
	}
}

//Functie voor controlleren van alarm
int checkAlarm(char *alarm, char *data) {
	int i;
	for (i = 0; i < 5; i++) {
		if (*(alarm + i) != *(data + i)) { //zijn ze niet hetzelfde? return 0
			return 0;
		}
	}
	return 1;								//zijn ze hetzelfde? return 1
}

//Functie voor genereren van som.
int generateSum(char *som) {
	int a = (rand() % 10);	//4 random getallen
	int b = (rand() % 10);
	int c = (rand() % 10);
	int d = (rand() % 10);


	if (a < c) {	//een negatief antwoord uitsluiten
		int temp = a;
		a = c;
		c = temp;
	}
	if (b < d) {
		int temp = b;
		b = d;
		d = temp;
	}


	*(som + 0) = a + '0';
	*(som + 1) = b + '0';
	*(som + 3) = c + '0';
	*(som + 4) = d + '0';

	int answer;
	int operator = (rand() % 3); 	//random een +, -, of *
	switch (operator) {				//switch voor de operator
	case 0:
		*(som + 2) = '+';
		answer = (((10 * a) + b) + ((10 * c) + d));	//antwoord genereren
		break;
	case 1:
		*(som + 2) = '-';
		answer = (((10 * a) + b) - ((10 * c) + d)); //antwoord genereren
		break;
	case 2:
		*(som + 2) = '*';
		answer = (((10 * a) + b) * ((10 * c) + d)); //antwoord genereren
		break;
	}
	return answer;
}

//Functie voor invullen van antwoord op som
void guessSom(unsigned int numPressed, unsigned int *x, char *guess) {
	int i = *x;
	*(guess + i) = numPressed + '0';
	if (*x < 4) {
		*x = *x + 1;
	}
}

//Functie voor controlleren van antwoord
int checkGuess(char *guess, int answer) {
	int i, a, b, c, d, e, space = 0;
	int intGuess = 0;
	for (i = 0; i < 5; i++) {		//lege velden eruithalen
		if (*(guess + i) == ' ') {
			space++;
		}
	}
	a = (*(guess + 0) - '0');
	b = (*(guess + 1) - '0');
	c = (*(guess + 2) - '0');
	d = (*(guess + 3) - '0');
	e = (*(guess + 4) - '0');

	switch (space) {	//algoritme voor antwoord omzetten naar int
	case 0:
		intGuess = ((10000 * a) + (1000 * b) + (100 * c) + (10 * d) + e);
		break;
	case 1:
		intGuess = ((1000 * a) + (100 * b) + (10 * c) + d);
		break;
	case 2:
		intGuess = ((100 * a) + (10 * b) + c);
		break;
	case 3:
		intGuess = ((10 * a) + b);
		break;
	case 4:
		intGuess = a;
		break;
	}

	if (intGuess != answer) {	//checken of antwoord gelijk is met juiste antwoord
		return 0;
	} else {
		return 1;
	}
}

