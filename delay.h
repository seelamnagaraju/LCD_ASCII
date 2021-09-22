#ifndef _DELAY_H
#define _DELAY_H
#ifdef __cplusplus
extern "C" {
#endif

void delay_us(unsigned int);
void delay_ms(unsigned int);
void delay_sec(unsigned char);
void swDelay(volatile unsigned int);


#ifdef __cplusplus
}
#endif
#endif
//*****************************************************************************
//              @End of file
//*****************************************************************************
