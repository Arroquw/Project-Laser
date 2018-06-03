/*****************************************************************************
 *   This example shows how to access an MMC/SD card
 *
 *   Copyright(C) 2010, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************/

#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_ssp.h"
//#include "lpc17xx_uart.h"
#include "lpc17xx_timer.h"
#include "stdio.h"

#include "diskio.h"
#include "ff.h"

#include <cr_section_macros.h>
#include <NXP/crp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "lpc17xx.h"
#include "type.h"
#include "uart.h"
#include "timer.h"
#include "rtc.h"
#include "string.h"
//#include "time.h";
#define UART_DEV LPC_UART3

static FATFS Fatfs[1];
//static uint8_t buf[64];
static FIL File ;
static  UINT  btw;         /* File read/write count */
static BYTE res;
//static RTCTime local_time, current_time, *timeinfopointer;

static void init_ssp(void)
{
	SSP_CFG_Type SSP_ConfigStruct;
	PINSEL_CFG_Type PinCfg;

	/*
	 * Initialize SPI pin connect
	 * P0.7 - SCK; - 7
	 * P0.8 - MISO - 6
	 * P0.9 - MOSI - 5
	 * P2.2 - SSEL - used as GPIO - 44
	 */
	PinCfg.Funcnum = 2;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Portnum = 0;
	PinCfg.Pinnum = 7;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 8;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 9;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Funcnum = 0;
	PinCfg.Portnum = 2;
	PinCfg.Pinnum = 2;
	PINSEL_ConfigPin(&PinCfg);

	SSP_ConfigStructInit(&SSP_ConfigStruct);

	// Initialize SSP peripheral with parameter given in structure above
	SSP_Init(LPC_SSP1, &SSP_ConfigStruct);

	// Enable SSP peripheral
	SSP_Cmd(LPC_SSP1, ENABLE);

}

void SysTick_Handler(void)
{

}

int main (void)
{

     DSTATUS stat;

 //   int uY, X_Pos ;
 //   double Angle ;
 //   int i = 0;
 //   struct tm * timeinfo ;
 //	    BYTE Time_STR[28], Time_STR_Old[28];

 	    FIL * fpp ;
 	    DWORD  temp;
 	     BYTE  Float_STR[10] ;
 	     float temp_f ;

//      LPC_SC->PCONP     = 0x072887DE;        /* Power Control for Peripherals   test command   */
    									/* this will power up UART 0,1,2*/
//    SystemClockUpdate();

//     UARTInit(2, 9600);	/* baud rate setting */
//     UARTInit(1, 57600);	/* baud rate setting */
//     UARTInit(0,9600 );	/* baud rate setting */


 	init_SPI();
 	delayMs(0,500);
 	initSDC(0);

 	/*
 	 init_ssp();							// this will power up appropriate peripherals for SSP
     delayMs(0,500) ;
     stat = disk_initialize(0);
      res = f_mount(0, &Fatfs[0]);
*/
     /* Initialize RTC module */
      /*
      RTCInit();

       local_time.RTC_Sec = 0;
       local_time.RTC_Min = 23;
       local_time.RTC_Hour = 10;
       local_time.RTC_Mday = 8;
       local_time.RTC_Wday = 3;
       local_time.RTC_Yday = 12;
       local_time.RTC_Mon = 7;
       local_time.RTC_Year = 11;
       RTCSetTime( local_time );

       RTCStart();
	*/

//    LPC_UART2->IER = IER_THRE | IER_RLS;			/* Disable RBR */
/*
    Init_uLCD();

    delayMs(0,50) ;

    Draw_Text() ;

              delayMs(0,100) ;


              DrawLine1();

              delayMs(0,100) ;

              DrawLine2();

              delayMs(0,100) ;

              Sent_Text();

              delayMs(0,100) ;

                       for(X_Pos=10; X_Pos < 200; X_Pos++)
                       {
                       delayMs(0,20) ;
                     //  uY = rand() % 50 + 1;
                       Angle = ((double)(X_Pos) * 3.14)/180 ;
                        uY = sin(Angle) * 50 ;
                       PutPixel(X_Pos,(200-uY)) ;
                       }

                 //      SysTick_Config(SystemFrequency /100);			// should be one sec ?
	*/
    while(1)
    {


        if( (res = f_open(&File, "data.txt", FA_OPEN_EXISTING | FA_READ | FA_WRITE)) == 0)
        {
        fpp = &File ;

     //   res = f_read(&File, buffer, sizeof(buffer), &br);    /* Read a chunk of src file */

        res = f_lseek(&File, fpp->fsize);

        for (temp=0; temp < 50; temp++)
        {
        	temp_f = temp  ;
       // sprintf(Float_STR,"%3.2f\r\n", temp_f ) ;

          res = f_write(&File,Float_STR,(BYTE)sizeof(Float_STR),&btw ) ;
          delayMs(0,5) ;
        }
          res = f_close(&File)  ;
        }
        				/*
        				current_time = RTCGetTime();
                 	    timeinfo=&current_time ;									//assign dummytime current time
                 	    timeinfopointer = &current_time ;						//current time holder pointer to access year only
                 	    timeinfo->tm_year = (timeinfopointer->RTC_Year)+100;			//year correction
                 	    strcpy(Time_STR_Old,Time_STR) ;								//retain previous time
                 	    strcpy(Time_STR,asctime(timeinfo)) ;
                 	    Sent_Text2(27, Time_STR,Time_STR_Old, strlen(Time_STR));
                 	    delayMs(0,100) ;

                 	    if (res == 0)
                 	    //Sent_Text2(30, "SD Card OK","SD Card ER", strlen("SD Card OK"));
                 	    else
                 	    Sent_Text2(30, "SD Card ER","SD Card OK", strlen("SD Card OK"));
                 	    delayMs(0,2000) ;
                 	    */

    }

return(1);
}


void check_failed(uint8_t *file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while(1);
}
