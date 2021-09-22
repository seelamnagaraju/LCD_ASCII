/*
 * main.h
 *
 */
//****************************************************************************

#ifndef _MAIN_H_
#define _MAIN_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <msp430.h>
#include <driverlib.h> // Required for the LCD
#include "myGpio.h" // Required for the LCD
#include "myClocks.h" // Required for the LCD
#include "myLcd.h" // Required for the LCD
#include "myprintf.h"
#include "sys_log.h"
#include "utils.h"
#include "i2c_gpio.h"
#include "at24c04.h"
#include "ds1307.h"


//***** Defines ***************************************************************
#define changeIntToHex(dec)     ( ( ((dec)/10) <<4 ) + ((dec)%10) )
#define changeHexToInt(hex)     ( ( ((hex)>>4) *10 ) + ((hex)%16) )


//***** Global Variables ******************************************************


//***** Prototypes ************************************************************
void initialize_clock(void);
void LCD_showString(char * pcString, unsigned int strLength, unsigned int uiPosition);
void LCD_showStringScrollLeft(char *pcString, unsigned int strLength);
void LCD_showStringScrollRight(char *msg, unsigned int strLength);
void swDelay(volatile unsigned long ulDelay);
void swDelaySec(volatile unsigned long ulDelaySec);
void ADC_SETUP(void);
void initialize_timer(void);
void rtcInit(void);

void PowerOnLedBlink(void);

#ifdef __cplusplus
}
#endif
#endif /* _MAIN_H_ */
