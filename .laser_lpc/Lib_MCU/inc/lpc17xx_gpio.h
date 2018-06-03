/***********************************************************************//**
 * @file	: lpc17xx_gpio.h
 * @brief	: Contains all macro definitions and function prototypes
 * 				support for GPIO firmware library on LPC17xx
 * @version	: 1.0
 * @date	: 23. Apr. 2009
 * @author	: HieuNguyen
 **************************************************************************
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
 **************************************************************************/

/* Peripheral group ----------------------------------------------------------- */
/** @defgroup GPIO
 * @ingroup LPC1700CMSIS_FwLib_Drivers
 * @{
 */

#ifndef LPC17XX_GPIO_H_
#define LPC17XX_GPIO_H_

/* Includes ------------------------------------------------------------------- */
#include "LPC17xx.h"
#include "lpc_types.h"


#ifdef __cplusplus
extern "C"
{
#endif


/* Public Types --------------------------------------------------------------- */
/** @defgroup GPIO_Public_Types
 * @{
 */

/**
 * @brief Fast GPIO port byte type definition
 */
typedef struct {
	__IO uint8_t FIODIR[4];		/**< FIO direction register in byte-align */
	   uint32_t RESERVED0[3];	/**< Reserved */
	__IO uint8_t FIOMASK[4];	/**< FIO mask register in byte-align */
	__IO uint8_t FIOPIN[4];		/**< FIO pin register in byte align */
	__IO uint8_t FIOSET[4];		/**< FIO set register in byte-align */
	__O  uint8_t FIOCLR[4];		/**< FIO clear register in byte-align */
} GPIO_Byte_TypeDef;


/**
 * @brief Fast GPIO port half-word type definition
 */
typedef struct {
	__IO uint16_t FIODIRL;		/**< FIO direction register lower halfword part */
	__IO uint16_t FIODIRU;		/**< FIO direction register upper halfword part */
	   uint32_t RESERVED0[3];	/**< Reserved */
	__IO uint16_t FIOMASKL;		/**< FIO mask register lower halfword part */
	__IO uint16_t FIOMASKU;		/**< FIO mask register upper halfword part */
	__IO uint16_t FIOPINL;		/**< FIO pin register lower halfword part */
	__IO uint16_t FIOPINU;		/**< FIO pin register upper halfword part */
	__IO uint16_t FIOSETL;		/**< FIO set register lower halfword part */
	__IO uint16_t FIOSETU;		/**< FIO set register upper halfword part */
	__O  uint16_t FIOCLRL;		/**< FIO clear register lower halfword part */
	__O  uint16_t FIOCLRU;		/**< FIO clear register upper halfword part */
} GPIO_HalfWord_TypeDef;


/**
 * @}
 */


/* Public Macros -------------------------------------------------------------- */
/** @defgroup GPIO_Public_Macros
 * @{
 */

/** Fast GPIO port 0 byte accessible definition */
#define GPIO0_Byte	((GPIO_Byte_TypeDef *)(LPC_GPIO0_BASE))
/** Fast GPIO port 1 byte accessible definition */
#define GPIO1_Byte	((GPIO_Byte_TypeDef *)(LPC_GPIO1_BASE))
/** Fast GPIO port 2 byte accessible definition */
#define GPIO2_Byte	((GPIO_Byte_TypeDef *)(LPC_GPIO2_BASE))
/** Fast GPIO port 3 byte accessible definition */
#define GPIO3_Byte	((GPIO_Byte_TypeDef *)(LPC_GPIO3_BASE))
/** Fast GPIO port 4 byte accessible definition */
#define GPIO4_Byte	((GPIO_Byte_TypeDef *)(LPC_GPIO4_BASE))



/** Fast GPIO port 0 half-word accessible definition */
#define GPIO0_HalfWord	((GPIO_HalfWord_TypeDef *)(LPC_GPIO0_BASE))
/** Fast GPIO port 1 half-word accessible definition */
#define GPIO1_HalfWord	((GPIO_HalfWord_TypeDef *)(LPC_GPIO1_BASE))
/** Fast GPIO port 2 half-word accessible definition */
#define GPIO2_HalfWord	((GPIO_HalfWord_TypeDef *)(LPC_GPIO2_BASE))
/** Fast GPIO port 3 half-word accessible definition */
#define GPIO3_HalfWord	((GPIO_HalfWord_TypeDef *)(LPC_GPIO3_BASE))
/** Fast GPIO port 4 half-word accessible definition */
#define GPIO4_HalfWord	((GPIO_HalfWord_TypeDef *)(LPC_GPIO4_BASE))
#define FIO2PIN 	(* (unsigned int *)0x2009C054)
#define FIO2SET 	(* (unsigned int *)0x2009C058)
#define FIO2CLR	 	(* (unsigned int *)0x2009C05C)


/**
 * @}
 */


/* Public Functions ----------------------------------------------------------- */
/** @defgroup GPIO_Public_Functions
 * @{
 */

/* GPIO style ------------------------------- */
void GPIO_SetDir(uint8_t portNum, uint32_t bitValue, uint8_t dir);
void GPIO_SetValue(uint8_t portNum, uint32_t bitValue);
void GPIO_ClearValue(uint8_t portNum, uint32_t bitValue);
uint32_t GPIO_ReadValue(uint8_t portNum);

/* FIO (word-accessible) style ------------------------------- */
void FIO_SetDir(uint8_t portNum, uint32_t bitValue, uint8_t dir);
void FIO_SetValue(uint8_t portNum, uint32_t bitValue);
void FIO_ClearValue(uint8_t portNum, uint32_t bitValue);
uint32_t FIO_ReadValue(uint8_t portNum);
void FIO_SetMask(uint8_t portNum, uint32_t bitValue, uint8_t maskValue);

/* FIO (halfword-accessible) style ------------------------------- */
void FIO_HalfWordSetDir(uint8_t portNum, uint8_t halfwordNum, uint16_t bitValue, uint8_t dir);
void FIO_HalfWordSetMask(uint8_t portNum, uint8_t halfwordNum, uint16_t bitValue, uint8_t maskValue);
void FIO_HalfWordSetValue(uint8_t portNum, uint8_t halfwordNum, uint16_t bitValue);
void FIO_HalfWordClearValue(uint8_t portNum, uint8_t halfwordNum, uint16_t bitValue);
uint16_t FIO_HalfWordReadValue(uint8_t portNum, uint8_t halfwordNum);

/* FIO (byte-accessible) style ------------------------------- */
void FIO_ByteSetDir(uint8_t portNum, uint8_t byteNum, uint8_t bitValue, uint8_t dir);
void FIO_ByteSetMask(uint8_t portNum, uint8_t byteNum, uint8_t bitValue, uint8_t maskValue);
void FIO_ByteSetValue(uint8_t portNum, uint8_t byteNum, uint8_t bitValue);
void FIO_ByteClearValue(uint8_t portNum, uint8_t byteNum, uint8_t bitValue);
uint8_t FIO_ByteReadValue(uint8_t portNum, uint8_t byteNum);

/************** beun **********/
#define FIO0PIN		(* (unsigned int *)0x2009C014)
#define FIO1PIN 	(* (unsigned int *)0x2009C034)
#define FIO2PIN 	(* (unsigned int *)0x2009C054)
// set direction of pins
#define FIO0DIR0 	(* (unsigned int *)0x2009C000)
#define FIO0DIR1 	(* (unsigned int *)0x2009C001)
#define FIO0DIR2 	(* (unsigned int *)0x2009C002)

#define FIO1DIR0 	(* (unsigned int *)0x2009C020)
#define FIO1DIR1 	(* (unsigned int *)0x2009C021)
#define FIO1DIR2 	(* (unsigned int *)0x2009C022)
#define FIO1DIR3 	(* (unsigned int *)0x2009C023)

#define FIO2DIR0 	(* (unsigned int *)0x2009C040)
#define FIO2DIR1 	(* (unsigned int *)0x2009C041)
#define FIO2DIR2 	(* (unsigned int *)0x2009C042)

#define FIO3DIR0 	(* (unsigned int *)0x2009C060)
#define FIO3DIR1 	(* (unsigned int *)0x2009C061)
#define FIO3DIR2 	(* (unsigned int *)0x2009C062)


#define FIO4DIR0 	(* (unsigned int *)0x2009C080)
#define FIO4DIR1 	(* (unsigned int *)0x2009C081)
#define FIO4DIR2 	(* (unsigned int *)0x2009C082)
// set value of pins
#define FIO0SET 	(* (unsigned int *)0x2009C018)
#define FIO1SET 	(* (unsigned int *)0x2009C038)
#define FIO2SET 	(* (unsigned int *)0x2009C058)
// clear value of pins
#define FIO0CLR 	(* (unsigned int *)0x2009C01C)
#define FIO1CLR 	(* (unsigned int *)0x2009C03C)
#define FIO2CLR	 	(* (unsigned int *)0x2009C05C)

#define ISER0 		(*(unsigned int*) (0xE000E100))
#define ICER0 		(*(unsigned int*) (0xE000E180))
// interrupt priority
#define IPR0 		(*(unsigned int*) (0xE000E400))
// interrupts IO2
#define IO2IntEnR 	(* (unsigned int *)(0x400280B0))
#define IO2IntEnF 	(* (unsigned int *)(0x400280B4))
#define IO2IntClr 	(* (unsigned int *)(0x400280AC))

#define PINSEL0 	(* (unsigned int *)0x4002C000)
#define PINSEL1     (* (unsigned int *)0x4002C004)
#define PINMODE0    (* (unsigned int *)0x4002C040)
#define PINMODE1    (* (unsigned int *)0x4002C044)
#define PCONP 		(* (unsigned int *)0x400FC0C4)
#define PCLKSEL0 	(* (unsigned int *)0x400FC1A8)
#define FIO0MASK 	(*(unsigned int *)(0x2009C010))

void gpioInit();
void gpio0WritePin(int32_t pinNr, int32_t Value);
void gpio1WritePin(int32_t pinNr, int32_t Value);
void gpio2WritePin(int32_t pinNr, int32_t Value);
uint32_t gpio0ReadPin(int32_t pinNr);
uint32_t gpio1ReadPin(int32_t pinNr);
uint32_t gpio2ReadPin(int32_t pinNr);

unsigned int readPIN2();

void gpio2WritePin(int32_t pinNr, int32_t Value);

/**
 * @}
 */


#ifdef __cplusplus
}
#endif

#endif /* LPC17XX_GPIO_H_ */

/**
 * @}
 */

/* --------------------------------- End Of File ------------------------------ */
