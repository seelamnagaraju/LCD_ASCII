#ifndef __I2C_RTC_H
#define __I2C_RTC_H
#ifdef __cplusplus
extern "C" {
#endif

#include <msp430.h>

/*-----------------------------------------------------------------------------*/
/* Macro definitions  */
/*-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------*/
/* Local Macro definitions */
/*-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------*/
/* Function prototypes  */
/*-----------------------------------------------------------------------------*/
void set_RTC(void);
void read_RTC(void);

//*****************************************************************************
#ifdef __cplusplus
}
#endif
#endif
//*****************************************************************************
//              @End of file
//*****************************************************************************
