
//*****************************************************************************
//  I2C software using bit-banging
//*****************************************************************************

/*-----------------------------------------------------------------------------*/
/* Header inclusions */
/*-----------------------------------------------------------------------------*/
#include <msp430.h>
#include "i2c_gpio.h"

/*-----------------------------------------------------------------------------*/
/* Local Macro definitions */
/*-----------------------------------------------------------------------------*/
#define LED0_ON       LED0_DIR &= ~LED0_PIN; // LED0_OUT |=  LED0_PIN; }
#define LED0_OFF      LED0_DIR |=  LED0_PIN; // LED0_OUT &=~ LED0_PIN; }

// Note: I2C SDA is open drain, this means we need to use INPUT for an SDA high logic.
// I.e. we can't just write digitalWrite(pin, HIGH) for the SDA.
#define SDA_H      { I2C_PxDIR &= ~SDA;  I2C_PxOUT |=  SDA; }
#define SDA_L      { I2C_PxDIR |=  SDA;  I2C_PxOUT &= ~SDA; }
#define SCL_H      { I2C_PxDIR &= ~SCL;  I2C_PxOUT |=  SCL; }  // set
#define SCL_L      { I2C_PxDIR |=  SCL;  I2C_PxOUT &= ~SCL; }  // clear

#define SDA_READ       Read_SDA()
#define I2C_DATA_IN    I2C_PxIN & SDA
#define iDelay         100
#define I2C_DELAY()     __delay_cycles(TIME_DELAY)

/*-----------------------------------------------------------------------------*/
/* Function prototypes */
/*-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------*/
/* Function implementations */
/*-----------------------------------------------------------------------------*/
void inline sleep_us(unsigned int uiDelay)
{
     while(uiDelay--);
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
void I2C_Init(void)
{
    I2C_PxSEL  &= ~( SCL | SDA );   // I/O enabled
    I2C_PxSEL2 &= ~( SCL | SDA );
    sleep_us(iDelay);
    SCL_H
    SDA_H
    sleep_us(iDelay);
}
/*--------------------------------------------------------------------------------
Function    : I2C_Writebit
Purpose     : Write bit to I2C bus
Parameters  : a bit need to write
Return      : None
--------------------------------------------------------------------------------*/
void I2C_Start(void)
{
    SDA_H
    sleep_us(iDelay);
    SCL_H
    sleep_us(iDelay);
    SDA_L
    sleep_us(iDelay);
    SCL_L
    sleep_us(iDelay);
}
void I2C_Stop(void)
{
    SDA_L
    sleep_us(iDelay);
    SCL_H
    sleep_us(iDelay);
    SDA_H
    sleep_us(iDelay);
    SCL_L
    sleep_us(iDelay);
}
/*--------------------------------------------------------------------------------
Function    : I2C_Readbit
Purpose     : Read bit to I2C bus
Parameters  : None
Return      : unsigned char
--------------------------------------------------------------------------------*/
unsigned char Read_SDA(void)
{
    I2C_PxDIR  &= ~SDA;
    return((I2C_PxIN & SDA) != 0);
}
/*--------------------------------------------------------------------------------
Function    : I2C_WriteByte
Purpose     : Write a Byte to I2C bus
Parameters  : unsigned char Data
Return      : None
--------------------------------------------------------------------------------*/
unsigned char I2C_WriteByte(unsigned char c)
{
  unsigned int i=0, mask=0x80, ack;

  for (i=0; i<8; i++) //transmits 8 bits
  {
    if(c & mask) //set data line accordingly(0 or 1)
      SDA_H //data high
    else
      SDA_L //data low

    SCL_H   //clock high
    sleep_us(iDelay);
    SCL_L   //clock low
    c <<= 1;  //shift mask
    sleep_us(iDelay);
  } // for i
  // read ack bit
  SDA_H  //release data line for acknowledge
  SCL_H  //send clock for acknowledge
  sleep_us(iDelay);
  ack=SDA_READ; //read data pin for acknowledge
  SCL_L  //clock low
  sleep_us(iDelay);
  SDA_L  // data low
  return (ack == 0) ? 1:0; // a low ACK bit means success
} /* i2cByteOut() */
/*--------------------------------------------------------------------------------
Function    : I2C_ReadByte
Purpose     : Read a Byte to I2C bus
Parameters  : None
Return      : unsigned char
--------------------------------------------------------------------------------*/
//receives one byte of data from i2c bus
unsigned char I2C_ReadByte(unsigned char master_ack)
{
  unsigned char c=0,mask=0x80;
  SCL_H
  SDA_H
  do  //receive 8 bits
  {
     //sleep_us(iDelay);
     SCL_H //clock high
     sleep_us(iDelay);
     if(SDA_READ==1) //read data
      c |= mask;  //store data
     SCL_L  //clock low
     sleep_us(iDelay);
     mask/=2; //shift mask
  }while(mask>0);

  if(master_ack==1)
    SDA_H //don't acknowledge
  else
    SDA_L //acknowledge

  SCL_H //clock high
  sleep_us(iDelay);
  SCL_L //clock low
  sleep_us(iDelay);
  SDA_L //data low
  return c;
}

/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/
//writes one byte of data(c) to slave device(device_id) at given address(location)
unsigned char I2C_WriteChar(unsigned char device_id, unsigned char location, unsigned char c)
{
  unsigned char slave_ack;
  I2C_Start();      //starts i2c bus
  slave_ack=I2C_WriteByte(device_id); //select slave device
  I2C_WriteByte(location); //send address location
  I2C_WriteByte(c); //send data to i2c bus
  I2C_Stop(); //I2C_Stop i2c bus
  return slave_ack;
}

/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/
unsigned char I2C_ReadChar(unsigned char device_id, unsigned char location)
{
  unsigned char cData;
  I2C_Start();   //starts i2c bus
  cData=I2C_WriteByte(device_id); //select slave device
  I2C_WriteByte(location);  //send address location
  I2C_Stop(); //I2C_Stop i2c bus
  I2C_Start(); //starts i2c bus
  I2C_WriteByte(device_id+1); //select slave device in read mode
  cData=I2C_ReadByte(1); //receive data from i2c bus
  I2C_Stop(); //I2C_Stop i2c bus
  return cData;
}

/*--------------------------------------------------------------------------------
Function    : I2C_WriteData
Purpose     : Write n Byte to I2C bus
Parameters  : DevideAddr    - Devide Address
              Register      - Register Address
              Data          - Pointer to Data need to write
              nLength       - Number of Byte need to write
Return      : None
--------------------------------------------------------------------------------*/
//writes multi bytes data to slave device(device_id) at given address(location)
unsigned char I2C_WriteString(unsigned char device_id, unsigned char location, unsigned char *pBuf, unsigned char len)
{
  unsigned char i,slave_ack;
  I2C_Start();      //starts i2c bus
  slave_ack=I2C_WriteByte(device_id); //select slave device
  slave_ack=I2C_WriteByte(location); //send address location
  for (i=0; i<len; i++)
  {
      slave_ack=I2C_WriteByte(pBuf[i]);  //send data to i2c bus
  }
  I2C_Stop(); //I2C_Stop i2c bus
  return slave_ack;
}
/*--------------------------------------------------------------------------------
Function    : I2C_ReadData
Purpose     : Read n Byte from I2C bus
Parameters  : DevideAddr    - Devide Address
              Register      - Register Address
              Buff          - Pointer to Buffer store value
              nLength       - Number of Byte need to read
Return      : None
--------------------------------------------------------------------------------*/
void I2C_ReadString(unsigned char device_id, unsigned char location, unsigned char *Buf, unsigned char len)
{
    int i;
    I2C_Start();
    I2C_WriteByte(device_id);
    I2C_WriteByte(location);
    I2C_Start();
    I2C_WriteByte(device_id+1);
    for (i=0; i<len; i++)
    {
        if (i == 15)
           Buf[i] = I2C_ReadByte(1);
        else
           Buf[i] = I2C_ReadByte(0);
    }
    I2C_Stop();
    return;
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
unsigned char bin2bcd(unsigned char val)
{
  unsigned char bcdVal;
  bcdVal = (val + 6 * (val / 10));
  return bcdVal;
}
//----------------------------------------------------------------------------------
unsigned char bcd2bin(unsigned char val)
{
  unsigned char bcdVal;
  bcdVal = (val - 6 * (val >> 4));
  return bcdVal;
}
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

//*****************************************************************************
//              @End of file
//*****************************************************************************
