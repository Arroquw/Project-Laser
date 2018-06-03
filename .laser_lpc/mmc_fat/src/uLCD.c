/****************************************************************************
 *   $Id:: uarttest.c 6098 2011-01-08 02:26:20Z nxp12832                    $
 *   Project: NXP LPC17xx UART example
 *
 *   Description:
 *     This file contains UART test modules, main entry, to test UART APIs.
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/
#include <cr_section_macros.h>
#include <NXP/crp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

#include "lpc17xx.h"
#include "type.h"
#include "uart.h"
#include "timer.h"


extern volatile uint32_t UART0Count;
extern volatile uint8_t UART0Buffer[BUFSIZE];
extern volatile uint32_t UART1Count;
extern volatile uint8_t UART1Buffer[BUFSIZE];
extern volatile uint8_t UART2Buffer[BUFSIZE];
extern volatile uint8_t UART2Count ;

void Sent_Text(void) ;
void Send_Char(void) ;
void Draw_Text(void) ;
void DrawLine1(void) ;
void DrawLine2(void) ;
void PutPixel(int , int );
void Init_uLCD(void) ;
void Sent_Text2(char, char*, char*, uint32_t);



void SetFont(void)
{
	//240 x 320 resolution
	 UART2Buffer[0]= 0x46 ;
	 UART2Buffer[1]= ',' ;
	 UART2Buffer[2]= 0x01 ;			// font
	 UART2Count = 0x03 ;
	 UARTSend( 2, (uint8_t *)UART2Buffer, UART2Count );

}

void Send_Char(void)
{
	 UART2Buffer[0]= 0x54 ;
	 UART2Buffer[1]= 'H' ;			// char
	 UART2Buffer[2]= 0x0 ;			// col
	 UART2Buffer[3]= 0x0 ;			// row
	 UART2Buffer[4]= 0xff ;			// col 1
	 UART2Buffer[5]= 0xff ;		// row 2

	 UART2Count = 6 ;
	 UARTSend( 2, (uint8_t *)UART2Buffer, UART2Count );

}

void Draw_Text(void)
{
	 UART2Buffer[0]= 0x53 ;

	 UART2Buffer[1]= 0x00 ;			//
	 UART2Buffer[2]= 0x20 ;			// 2 bytes col in pix

	 UART2Buffer[3]= 0x00;			//
	 UART2Buffer[4]= 0x00 ;			//  2 bytes row in pix

	 UART2Buffer[5]= 0x02 ;			//font
	 UART2Buffer[6]= 0xEE ;			//col 1
	 UART2Buffer[7]= 0xF0 ;			//col 2
	 UART2Buffer[8]= 0x02 ;			//width
	 UART2Buffer[9]= 0x02 ;			//height
	 UART2Buffer[10]= 'W' ;			//string
	 UART2Buffer[11]= 'i' ;			//string
	 UART2Buffer[12]= 'n' ;			//string
	 UART2Buffer[13]= 'd' ;			//string
	 UART2Buffer[14]= ' ' ;			//string
	 UART2Buffer[15]= 'M' ;			//string
	 UART2Buffer[16]= 'o' ;			//string
	 UART2Buffer[17]= 'n' ;			//string
	 UART2Buffer[18]= 'i' ;			//string
	 UART2Buffer[19]= 't' ;			//string
	 UART2Buffer[20]= 'o' ;			//string
	 UART2Buffer[21]= 'r' ;			//string

	 UART2Buffer[22]= 0x00 ;			//string

	 UART2Count = 23 ;
	 UARTSend( 2, (uint8_t *)UART2Buffer, UART2Count );

}

void Sent_Text(void)
{
	 UART2Buffer[0]= 0x73 ;
	 UART2Buffer[1]= 0 ;			// col
	 UART2Buffer[2]= 2 ;			//row
	 UART2Buffer[3]= 0x03 ;			//font
	 UART2Buffer[4]= 0xE0 ;			//col 1
	 UART2Buffer[5]= 0xF0 ;			//col 2
	 UART2Buffer[6]= '5' ;			//string
	 UART2Buffer[7]= '0' ;			//string
	 UART2Buffer[8]= 'm' ;			//string
	 UART2Buffer[9]= 'p' ;			//string
	 UART2Buffer[10]= 'h' ;			//string
	 UART2Buffer[11]= 0x00 ;			//string

	 UART2Count = 12 ;
	 UARTSend( 2, (uint8_t *)UART2Buffer, UART2Count );

}

void DrawLine1(void)
{
	//240 x 320 resolution
	 UART2Buffer[0]= 0x4C ;

	 UART2Buffer[1]= 0 ;  //X1 MSB
	 UART2Buffer[2]= 10 ;  //X1 LSB

	 UART2Buffer[3]= 0 ;	 //Y1	MSB
	 UART2Buffer[4]= 50 ;	 //Y1	LSB

	 UART2Buffer[5]= 0 ;  //X2  MSB
	 UART2Buffer[6]= 10 ;  //X2  LSB

	 UART2Buffer[7]= 0 ;	 //Y2 LSB
	 UART2Buffer[8]= 200 ;	 //Y2 MSB

	 UART2Buffer[9]= 0xED ;
	 UART2Buffer[10]= 0xDE ;	 		// color

	 UART2Count = 11 ;
	 UARTSend( 2, (uint8_t *)UART2Buffer, UART2Count );

}

void DrawLine2(void)
{
	//240 x 320 resolution
	 UART2Buffer[0]= 0x4C ;

	 UART2Buffer[1]= 0 ;  //X1 MSB
	 UART2Buffer[2]= 10 ;  //X1 LSB

	 UART2Buffer[3]= 0 ;	 //Y1	MSB
	 UART2Buffer[4]= 200 ;	 //Y1	LSB

	 UART2Buffer[5]= 0 ;  //X2  MSB
	 UART2Buffer[6]= 240 ;  //X2  LSB

	 UART2Buffer[7]= 0 ;	 //Y2 LSB
	 UART2Buffer[8]= 200 ;	 //Y2 MSB

	 UART2Buffer[9]= 0xED ;
	 UART2Buffer[10]= 0xDE ;	 		// color

	 UART2Count = 11 ;
	 UARTSend( 2, (uint8_t *)UART2Buffer, UART2Count );

}

void PutPixel(int x, int y)
{
	char X1, X2, Y1, Y2 , temp ;
	X1= (char) x ;
	X2= (char)(x >> 8) ;
	Y1= (char) y ;
	Y2= (char)(y >> 8) ;

	UART2Buffer[0]= 0x50 ;

	UART2Buffer[1]= X2 ;  //X1 MSB
	UART2Buffer[2]= X1 ;  //X1 LSB

	UART2Buffer[3]= Y2 ;	 //Y1	MSB
	UART2Buffer[4]= Y1 ;	 //Y1	LSB

	UART2Buffer[5]= 0xED ;
	UART2Buffer[6]= 0xDE ;	 		// color

	UART2Count = 7 ;
	UARTSend( 2, (uint8_t *)UART2Buffer, UART2Count );

	//graph area 230 X 150
	//upper  left corner 10,50
	//bottom right corner 240,200
	//origin 10,200
	//pixel margin between Y= 200 to 50
	//pixel margin between X= 10 to 240
}

void Sent_Text2(char row, char Str[28], char Str_Old[28], uint32_t Len)
{
	uint32_t i ;

	 memcpy (UART2Buffer,'\0',sizeof(UART2Buffer));

	 	 UART2Buffer[0]= 0x73 ;
	 	 UART2Buffer[1]= 0 ;			// col
	 	 UART2Buffer[2]= row ;			//row
	 	 UART2Buffer[3]= 0x01 ;			//font
	 	 UART2Buffer[4]= 0x01 ;			//col 1
	 	 UART2Buffer[5]= 0x01 ;			//col 2

	 	 for(i=0; i < Len; i++)
	 		 UART2Buffer[i+6] = Str_Old[i] ;


	 	 UART2Buffer[i+6]= 0x00 ;			//string

	 	 UART2Count = i+7 ;
	 	 UARTSend( 2, (uint8_t *)UART2Buffer, UART2Count );

	delayMs(0,100) ;

	 UART2Buffer[0]= 0x73 ;
	 UART2Buffer[1]= 0 ;			// col
	 UART2Buffer[2]= row ;			//row
	 UART2Buffer[3]= 0x01 ;			//font
	 UART2Buffer[4]= 0xE0 ;			//col 1
	 UART2Buffer[5]= 0xF0 ;			//col 2

	 for(i=0; i < Len; i++)
		 UART2Buffer[i+6] = Str[i] ;


	 UART2Buffer[i+6]= 0x00 ;			//string

	 UART2Count = i+7 ;
	 UARTSend( 2, (uint8_t *)UART2Buffer, UART2Count );

}
void Init_uLCD(void)
{
UART2Buffer[0]= 0x55 ;			// auto baud
	  UART2Count = 0x01 ;
    UARTSend( 2, (uint8_t *)UART2Buffer, UART2Count );
   // LPC_UART2->IER = IER_THRE | IER_RLS | IER_RBR;	/* Re-enable RBR */

    delayMs(0,50) ;

    UART2Buffer[0]= 0x51 ;					// new buad rate 115200
    UART2Buffer[1]= 0x0C ;
    	 UART2Count = 0x02 ;
        UARTSend( 2, (uint8_t *)UART2Buffer, UART2Count );
       // LPC_UART2->IER = IER_THRE | IER_RLS | IER_RBR;	/* Re-enable RBR */

        delayMs(0,50) ;

        UARTInit(2, 57600);	// new baud rate setting

        delayMs(0,50) ;

 //   LPC_UART2->IER = IER_THRE | IER_RLS;			/* Disable RBR */
    UART2Buffer[0]= 0x45 ;					//clear screen
	UART2Count = 0x01 ;
    UARTSend( 2, (uint8_t *)UART2Buffer, UART2Count );

    delayMs(0,100) ;

         UART2Buffer[0]= 0x4B ;					// background color
         UART2Buffer[1]= 0x01 ;
         UART2Buffer[2]= 0x01;
          	  UART2Count = 3 ;
              UARTSend( 2, (uint8_t *)UART2Buffer, UART2Count );

          delayMs(0,100) ;

}
/*****************************************************************************
**                            End Of File
*****************************************************************************/
