// ---------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------
#ifndef _AT24C04_H
#define _AT24C04_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define RTC_ADDR (0x51)

#define EEPROM_OK  0
#define EEPROM_ORR 1

//------------ Function Prototypes --------------------------------------------------
unsigned char EEPROM_WriteChar(unsigned int MemAddress, unsigned char uiData);
unsigned char EEPROM_ReadChar(unsigned int MemAddress);
unsigned short EEPROM_WriteString(unsigned int MemAddress, unsigned char *pData, unsigned char TxBuffSize);
unsigned short EEPROM_ReadString (unsigned int MemAddress, unsigned char *pData, unsigned char RxBuffSize);
void long_EEpromWrite (unsigned int MemAddress, long num );
long long_EEpromRead  (unsigned int MemAddress);

void eeprom_Test(void);

// ---------------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif
#endif

//*****************************************************************************
//              @End of file
//*****************************************************************************
