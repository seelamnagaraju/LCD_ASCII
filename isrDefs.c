#include <stdio.h>
#include <string.h>
#include <msp430.h>
#include "myprintf.h"

extern volatile unsigned char mode;
extern volatile unsigned int  uiAdcData;
extern char cAdcBuffer[16];

//*****************************************************************************
// port 1 interrupt service routine
//*****************************************************************************
#pragma vector=PORT1_VECTOR
/*
__interrupt void Port_1(void)
{
    if (P1IFG & BIT1)
    {
          mode=0;
          P1IFG &= ~BIT1;                  //Clear Pin 1.1 interrupt flag
          P1OUT ^= BIT0;                   // Toggle P1.0
    }
    if (P1IFG & BIT2)
    {
          mode=1;
          P1IFG &= ~BIT2;                  //Clear Pin 1.2 interrupt flag
          P1OUT ^= BIT0;                   // Toggle P1.0
    }
}
*/
__interrupt void PORT1_ISR(void)
{
    volatile unsigned long delay = 0;
    for (delay=0; delay<2000; delay++); // Button debounce

    switch(__even_in_range(P1IV, P1IV_P1IFG7))
    {
        case P1IV_NONE :   break;
        case P1IV_P1IFG0 : break;
        case P1IV_P1IFG1 :
                            mode=1;
                            P1OUT ^= BIT0;   // Toggle P1.0
                            P1IFG &= ~BIT1;  // Clear Pin 1.2 interrupt flag
                            break;
        case P1IV_P1IFG2 :
                            mode=0;
                            P1OUT ^= BIT0;   // Toggle P1.0
                            P1IFG &= ~BIT2;  // Clear Pin 1.2 interrupt flag
                            break;

        case P1IV_P1IFG3 :  break;
        case P1IV_P1IFG4 :  break;
        case P1IV_P1IFG5 :  break;
        case P1IV_P1IFG6 :  break;
        case P1IV_P1IFG7 :  break;
    }
    P1IFG = 0x00;
}

//*****************************************************************************
// Timer A0 interrupt service routine
//*****************************************************************************
#pragma vector = TIMER0_A0_VECTOR
__interrupt void TimerA0_ISR (void)
{
    P1OUT ^= BIT0;                   // Toggle P1.0
   // printf("Timer ISR.........\n");
   ADC12CTL0 = ADC12CTL0 | ADC12ENC; // enable conversion
   ADC12CTL0 = ADC12CTL0 | ADC12SC;  // start conversion
}


//*****************************************************************************
// ADC12 interrupt service routine
//*****************************************************************************
#pragma vector = ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
    uiAdcData=ADC12MEM0;
    u_itoa(uiAdcData, cAdcBuffer);

    if (uiAdcData > 0x800) // if input > 1.65V
    {
        printf("AdcData1= %d\n", uiAdcData);
        print_uart("AdcData1= ");
    }
    else
    {
        printf("AdcData2= %d\n", uiAdcData);
        print_uart("AdcData2= ");
    }
    print_uart(cAdcBuffer);
    print_uart("\n");

    //ADC12CTL0 = ADC12CTL0 | ADC12SC; // start next conversion
}


//*****************************************************************************
// USCI_A1_ISR interrupt service routine (UART)
//*****************************************************************************
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{
    switch(__even_in_range(UCA1IV, USCI_UART_UCTXCPTIFG))
    {
        case USCI_NONE: break;
        case USCI_UART_UCRXIFG:
            while(!(UCA1IFG & UCTXIFG));
            UCA1TXBUF = UCA1RXBUF; // echo char
            __no_operation();
            break;
        case USCI_UART_UCTXIFG: break;
        case USCI_UART_UCSTTIFG: break;
        case USCI_UART_UCTXCPTIFG: break;
    }
}

//*****************************************************************************
// @End of file
//*****************************************************************************
