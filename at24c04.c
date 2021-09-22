#include <msp430.h>
#include <stdint.h>

#include "i2c_interface.h"
#include "i2c_gpio.h"
#include "myprintf.h"

// Prototype statements for functions found within this file.
void I2C_Error(void);

#define I2C_EEPROM_ADDR        0xA0
#define I2C_NUMBYTES           16
#define I2C_EEPROM_HIGH_ADDR   0x00
#define I2C_EEPROM_LOW_ADDR    0x30



extern unsigned char cEpromBuffer[16];
extern void swDelay(volatile unsigned long ulDelay);

//====================================================================================
unsigned char EEPROM_WriteChar(unsigned int MemAddress, unsigned char uiData)
{
    I2C_WriteChar(I2C_EEPROM_ADDR, MemAddress, uiData);
    return 0;
}


//====================================================================================
unsigned char EEPROM_ReadChar(unsigned int MemAddress)
{
    unsigned char Buff;
    Buff=I2C_ReadChar(I2C_EEPROM_ADDR, MemAddress);
    return Buff;
}

//====================================================================================
/**
  * @brief  Write a value in a register of the device through BUS.
  * @param  Addr: Device address on BUS Bus.
  * @param  Reg: The target register address to write
  * @param  Value: The target register value to be written
  * @retval HAL status
  */
unsigned short EEPROM_WriteString(unsigned int MemAddress, unsigned char *pData, unsigned char TxBuffSize)
{
    I2C_WriteString(I2C_EEPROM_ADDR, MemAddress, pData, TxBuffSize);
    return 1;
}

//====================================================================================
/**
  * @brief  Read a register of the device through BUS
  * @param  Addr: Device address on BUS
  * @param  Reg: The target register address to read
  * @retval HAL status
  */
//uint8_t I2C_EEPROM_ReadData(uint8_t Addr, uint16_t Reg)
unsigned short EEPROM_ReadString(unsigned int MemAddress, unsigned char *pData, unsigned char RxBuffSize)
{
    I2C_ReadString(I2C_EEPROM_ADDR, MemAddress, pData, RxBuffSize);
    return 1;
}

//====================================================================================
void long_EEpromWrite (unsigned int Address, long num )
{
    char Buff[4]={0};
    Buff[0] =   (char)((num  & 0xFF000000)>>24);
    Buff[1] =   (char)((num  & 0x00FF0000)>>16);
    Buff[2] =   (char)((num  & 0x0000FF00)>>8);
    Buff[3] =   (char)((num  & 0x000000FF)>>0);
    EEPROM_WriteString(Address, Buff, 4);
    return ;
}

//====================================================================================
long long_EEpromRead (unsigned int Address)
{
    long num=0;
    char Buff[5]={0};
    EEPROM_ReadString(Address, Buff, 4);
    num =  Buff[0] | Buff[1] | Buff[2] | Buff[3] ;
    return num;
}

//====================================================================================
/**
  * @brief  Manages error callback by re-initializing I2C.
  * @param  None
  * @retval None
  */
void I2C_Error(void)
{
  /* De-initialize the I2C comunication bus */
  //I2C_DeInit();

  /* Re-Initiaize the I2C comunication bus */
  I2C_Init();
}


//====================================================================================
void eeprom_Test(void)
{
      //myprintf("%d:%d:%d\r\n", (long int)hour, (long int)min, (long int)sec);
       I2C_Init();
       print_uart("I2C TEST PROGRAM\n");
       EEPROM_WriteString(0, "READ I2C PROGRAM", 16); // I2C_WriteString(0xA0, 0, "143 TEST PROGRAM", 16);
       swDelay(50000);
       EEPROM_WriteString(16, "NAGARAJU PROGRAM", 16);
       swDelay(50000);
       EEPROM_ReadString (16, cEpromBuffer, 16);    // I2C_ReadString(0xA0, 0, cEpromBuffer, 16);
       swDelay(1000);
       return;
}


//*****************************************************************************
//              @End of file
//*****************************************************************************
