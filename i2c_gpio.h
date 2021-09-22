#ifndef __I2C_GPIO_H
#define __I2C_GPIO_H
#ifdef __cplusplus
extern "C" {
#endif

#include <msp430.h>

//#define USE_I2C_GPIO

/*-----------------------------------------------------------------------------*/
/* Macro definitions  */
/*-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------*/
/* Local Macro definitions */
/*-----------------------------------------------------------------------------*/
#define LED0_OUT        P1OUT
#define LED0_DIR        P1DIR
#define LED0_PIN        BIT1

#define I2C_PxSEL       P1SEL0
#define I2C_PxSEL2      P1SEL1
#define I2C_PxDIR       P1DIR
#define I2C_PxOUT       P1OUT
#define I2C_PxIN        P1IN

#define SDA             BIT6  // p1.6
#define SCL             BIT7  // p1.7

#define ACK             0x00
#define NACK            0x01

#define TIME_DELAY      100

#define changeIntToHex(dec)     ( ( ((dec)/10) <<4 ) + ((dec)%10) )
#define changeHexToInt(hex)     ( ( ((hex)>>4) *10 ) + ((hex)%16) )

/*-----------------------------------------------------------------------------*/
/* Function prototypes  */
/*-----------------------------------------------------------------------------*/
void I2C_Init(void);
unsigned char I2C_WriteByte(unsigned char Data);
unsigned char I2C_ReadByte (unsigned char ack);

unsigned char I2C_WriteChar(unsigned char device_id, unsigned char location, unsigned char data);
unsigned char I2C_ReadChar(unsigned char device_id, unsigned char location);
unsigned char I2C_WriteString(unsigned char device_id, unsigned char location, unsigned char *pBuf, unsigned char len);
void I2C_ReadString(unsigned char device_id, unsigned char location, unsigned char *Buf, unsigned char len);

//*****************************************************************************
#ifdef __cplusplus
}
#endif
#endif
//*****************************************************************************
//              @End of file
//*****************************************************************************
