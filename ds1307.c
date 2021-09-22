#include <msp430.h>
#include <stdint.h>

#include "i2c_interface.h"
#include "i2c_gpio.h"
#include "ds1307.h"
#include "myprintf.h"
#include "sys_log.h"

#define DS1307_ADDRESS 0xD0  ///< I2C address for DS1307
#define DS1307_CONTROL 0x07 ///< Control register

#define YEAR       0x20 // 2020
#define MONTH      0x11
#define DAY        0x29
#define WEEKDAY    0x06
#define HOUR       0x10
#define MINIT      0x24
#define SEC        0x10

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const unsigned char clock[7] = {SEC, MINIT, HOUR, WEEKDAY, DAY, MONTH, YEAR};

extern char RTC_Buffer[32];
extern st_time yh;
extern unsigned char bcd2bin(unsigned char);
extern const char *utcFormatDateTime(char *dt);

void set_RTC(void)
{
    //printf("Set RTC Time....!");
    I2C_WriteString(DS1307_ADDRESS, 0x00, clock, 7);
}

void read_RTC(void)
{
      int add=0;
      yh.tm_sec = bcd2bin(I2C_ReadChar(DS1307_ADDRESS, add++) & 0x7F);
      yh.tm_min = bcd2bin(I2C_ReadChar(DS1307_ADDRESS, add++));
      yh.tm_hour = bcd2bin(I2C_ReadChar(DS1307_ADDRESS, add++));
      yh.tm_wday = bcd2bin(I2C_ReadChar(DS1307_ADDRESS, add++));
      yh.tm_mday = bcd2bin(I2C_ReadChar(DS1307_ADDRESS, add++));
      yh.tm_mon = bcd2bin(I2C_ReadChar(DS1307_ADDRESS, add++));
      yh.tm_year = bcd2bin(I2C_ReadChar(DS1307_ADDRESS, add)) + 2000U;
      utcFormatDateTime(RTC_Buffer);
      return;
}
