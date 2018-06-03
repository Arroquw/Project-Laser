/*
 * matrix.c
 *
 *  Created on: 12 okt. 2015
 *      Author: Stefan
 */
#include "matrix.h"
#include <string.h>

//Definities van de verschillende output pins
#define H_CLK 		25
#define H_RST		26
#define H_STO		24
#define H_DTA		22
#define V_RST		21
#define V_CLK		3

//globale variabelen
int line = 1;
char lineArray1[25] ={0}, lineArray2[25] ={0}, lineArray3[25] ={0}, lineArray4[25] ={0}, lineArray5[25] ={0}, lineArray6[25] ={0}, lineArray7[25] ={0};

//functie voor schrijven naar de matrix.
void writeMatrix(unsigned int bit, unsigned int value){
	if(value == 1){					//moet er een 1 worden geschreven?
		FIO0PIN |= (1 << bit);		//zet bepaalde bit op 1.
	}else {
		FIO0PIN &= ~(1 << bit);		//zet bepaalde bit op 0.
	}
}

void initPin(int pin){				//Initializeren van bepaalde pin
	FIO0DIR |= (1 << pin);
	FIO0MASK &= ~(1 << pin);
}

void initMatrix(){					//Init functie
	FIO0PIN |= (1 << 9);
	initPin(H_CLK);
	initPin(H_RST);
	initPin(H_STO);
	initPin(H_DTA);
	initPin(V_RST);
	initPin(V_CLK);
}

void matrixFunctie(int brightness){		//functie voor schrijven naar display
	//A

	writeMatrix(H_DTA, 1);				//de lijn clearen
	int y;
	for(y = 0; y < 25; y++){
		writeMatrix(H_CLK, 1);
		writeMatrix(H_CLK, 0);
	}
	writeMatrix(H_DTA, 0);

	writeMatrix(H_STO, 1);				//horizontaal opslaan
	writeMatrix(H_STO, 0);

	writeMatrix(H_RST, 0);				//horizontaal resetten
	writeMatrix(H_RST, 1);

	// B
	int i;
	for(i = 24; i > -1; i--){			//schrijven horizontale data (per lijn)
		switch(line){
		case 1:
			writeData(lineArray1, i);
			break;
		case 2:
			writeData(lineArray2, i);
			break;
		case 3:
			writeData(lineArray3, i);
			break;
		case 4:
			writeData(lineArray4, i);
			break;
		case 5:
			writeData(lineArray5, i);
			break;
		case 6:
			writeData(lineArray6, i);
			break;
		case 7:
			writeData(lineArray7, i);
			break;
		}
		writeMatrix(H_CLK, 1);
		writeMatrix(H_CLK, 0);
	}
	writeMatrix(H_DTA, 0);

	int x;
	for(x = 0; x < line; x++){			//schrijven van line
		writeMatrix(V_CLK, 1);
		writeMatrix(V_CLK, 0);
	}
	if(line < 7){
		line ++;
	} else {
		line = 1;
	}

	writeMatrix(H_STO, 1);				//Data opslaan
	writeMatrix(H_STO, 0);

	int z;								//loop voor de brightness
	for(z = 0; z < brightness; z++){
		writeMatrix(H_DTA, 0);
	}

	writeMatrix(V_RST, 1);				//verticale en horizontale reset
	writeMatrix(V_RST, 0);

	writeMatrix(H_RST, 0);
	writeMatrix(H_RST, 1);
}

void writeData(char array[], int i){	//functie voor schrijven van data.
	if(array[i] == '1'){
		writeMatrix(H_DTA, 1);
	} else {
		writeMatrix(H_DTA, 0);
	}
}

//functie voor omzetten van nummer naar data
void createNumber(char data[], int setAlarm, int numSet, int alarm){
	char line1[5] ={0}, line2[5] ={0}, line3[5] ={0}, line4[5] ={0}, line5[5] ={0}, line6[5] ={0}, line7[5] ={0};
	int i;
	for(i = 0; i < 5; i++){					//de juiste data per nummer.
		if(data[i] == '1'){
			strncpy(line1, "11111", 5);
			strncpy(line2, "11011", 5);
			strncpy(line3, "10011", 5);
			strncpy(line4, "11011", 5);
			strncpy(line5, "11011", 5);
			strncpy(line6, "10001", 5);
			strncpy(line7, "11111", 5);
		}
		else if(data[i] == '2'){
			strncpy(line1, "11111", 5);
			strncpy(line2, "10001", 5);
			strncpy(line3, "11101", 5);
			strncpy(line4, "10001", 5);
			strncpy(line5, "10111", 5);
			strncpy(line6, "10001", 5);
			strncpy(line7, "11111", 5);
		}
		else if(data[i] == '3'){
			strncpy(line1, "11111", 5);
			strncpy(line2, "10001", 5);
			strncpy(line3, "11101", 5);
			strncpy(line4, "11001", 5);
			strncpy(line5, "11101", 5);
			strncpy(line6, "10001", 5);
			strncpy(line7, "11111", 5);
		}
		else if(data[i] == '4'){
			strncpy(line1, "11111", 5);
			strncpy(line2, "10101", 5);
			strncpy(line3, "10101", 5);
			strncpy(line4, "10001", 5);
			strncpy(line5, "11101", 5);
			strncpy(line6, "11101", 5);
			strncpy(line7, "11111", 5);
		}
		else if(data[i] == '5'){
			strncpy(line1, "11111", 5);
			strncpy(line2, "10001", 5);
			strncpy(line3, "10111", 5);
			strncpy(line4, "10001", 5);
			strncpy(line5, "11101", 5);
			strncpy(line6, "10001", 5);
			strncpy(line7, "11111", 5);
		}
		else if(data[i] == '6'){
			strncpy(line1, "11111", 5);
			strncpy(line2, "10001", 5);
			strncpy(line3, "10111", 5);
			strncpy(line4, "10001", 5);
			strncpy(line5, "10101", 5);
			strncpy(line6, "10001", 5);
			strncpy(line7, "11111", 5);
		}
		else if(data[i] == '7'){
			strncpy(line1, "11111", 5);
			strncpy(line2, "10001", 5);
			strncpy(line3, "11101", 5);
			strncpy(line4, "11011", 5);
			strncpy(line5, "11011", 5);
			strncpy(line6, "11011", 5);
			strncpy(line7, "11111", 5);
		}
		else if(data[i] == '8'){
			strncpy(line1, "11111", 5);
			strncpy(line2, "10001", 5);
			strncpy(line3, "10101", 5);
			strncpy(line4, "10001", 5);
			strncpy(line5, "10101", 5);
			strncpy(line6, "10001", 5);
			strncpy(line7, "11111", 5);
		}
		else if(data[i] == '9'){
			strncpy(line1, "11111", 5);
			strncpy(line2, "10001", 5);
			strncpy(line3, "10101", 5);
			strncpy(line4, "10001", 5);
			strncpy(line5, "11101", 5);
			strncpy(line6, "10001", 5);
			strncpy(line7, "11111", 5);
		}
		else if(data[i] == '0'){
			strncpy(line1, "11111", 5);
			strncpy(line2, "10001", 5);
			strncpy(line3, "10101", 5);
			strncpy(line4, "10101", 5);
			strncpy(line5, "10101", 5);
			strncpy(line6, "10001", 5);
			strncpy(line7, "11111", 5);
		}
		else if(data[i] == ':'){
			strncpy(line1, "11111", 5);
			strncpy(line2, "11111", 5);
			strncpy(line3, "11011", 5);
			strncpy(line4, "11111", 5);
			strncpy(line5, "11011", 5);
			strncpy(line6, "11111", 5);
			strncpy(line7, "11111", 5);
		}
		else if(data[i] == 'R'){
			strncpy(line1, "11111", 5);
			strncpy(line2, "10001", 5);
			strncpy(line3, "10101", 5);
			strncpy(line4, "10011", 5);
			strncpy(line5, "10101", 5);
			strncpy(line6, "10101", 5);
			strncpy(line7, "11111", 5);
		}
		else if(data[i] == 'C'){
			strncpy(line1, "11111", 5);
			strncpy(line2, "10001", 5);
			strncpy(line3, "10111", 5);
			strncpy(line4, "10111", 5);
			strncpy(line5, "10111", 5);
			strncpy(line6, "10001", 5);
			strncpy(line7, "11111", 5);
		}
		else if(data[i] == '+'){
			strncpy(line1, "11111", 5);
			strncpy(line2, "11111", 5);
			strncpy(line3, "11011", 5);
			strncpy(line4, "10001", 5);
			strncpy(line5, "11011", 5);
			strncpy(line6, "11111", 5);
			strncpy(line7, "11111", 5);
		}
		else if(data[i] == '-'){
			strncpy(line1, "11111", 5);
			strncpy(line2, "11111", 5);
			strncpy(line3, "11111", 5);
			strncpy(line4, "10001", 5);
			strncpy(line5, "11111", 5);
			strncpy(line6, "11111", 5);
			strncpy(line7, "11111", 5);
		}
		else if(data[i] == '*'){
			strncpy(line1, "11111", 5);
			strncpy(line2, "11111", 5);
			strncpy(line3, "10101", 5);
			strncpy(line4, "11011", 5);
			strncpy(line5, "10101", 5);
			strncpy(line6, "11111", 5);
			strncpy(line7, "11111", 5);
		}
		else{
			strncpy(line1, "11111", 5);
			strncpy(line2, "11111", 5);
			strncpy(line3, "11111", 5);
			strncpy(line4, "11111", 5);
			strncpy(line5, "11111", 5);
			strncpy(line6, "11111", 5);
			strncpy(line7, "11111", 5);
		}

		if(setAlarm == 1){			//moet een nummer onderstreept?
			if(i == numSet){
				strncpy(line7, "00000", 5);
			}
		}
		if(alarm == 1){				//staat het alarm aan?
			if(i == 2){
				strncpy(line1, "11110", 5);
			}
		}

		int y;
		for(y = 0; y < 5; y++){		//schrijven van alle data naar de lijn array's
			lineArray1[y +(5*i)] = line1[y];
			lineArray2[y +(5*i)] = line2[y];
			lineArray3[y +(5*i)] = line3[y];
			lineArray4[y +(5*i)] = line4[y];
			lineArray5[y +(5*i)] = line5[y];
			lineArray6[y +(5*i)] = line6[y];
			lineArray7[y +(5*i)] = line7[y];
		}
	}
}



