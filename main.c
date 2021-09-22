//*****************************************************************************
//
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//
//*****************************************************************************
#define LCD_MAX_STR_LEN     6
#define STARTUP_MODE        0

#define ADC12_SHT_16        0x0200      // 16 clock cycles for sample and hold
#define ADC12_ON            0x0010      // Used to turn ADC12 peripheral on
#define ADC12_SHT_SRC_SEL   0x0200      // Selects source for sample & hold
#define ADC12_12BIT         0x0020      // Selects 12-bits of resolution
#define ADC12_P92           0x000A      // Use input P9.2 for analog input

#define ACLK                0x0100
#define ID                  0x0000
#define UP                  0x0010
//#define TACLR             0x0040

volatile unsigned char mode=STARTUP_MODE;
volatile unsigned int  uiAdcData;
char cAdcBuffer[16];
char RTC_Buffer[32];
unsigned char cEpromBuffer[16];
//*****************************************************************************
//
//*****************************************************************************
#pragma vector=RTC_VECTOR
__interrupt void RTC_ISR(void)
{
    switch(__even_in_range(RTCIV, RTCIV_RT1PSIFG))
    {
        case RTCIV_NONE:      break;        // No interrupts
        case RTCIV_RTCOFIFG:  break;        // RTCOFIFG
        case RTCIV_RTCRDYIFG:               // RTCRDYIFG
                    yh.tm_year  =  (int)changeHexToInt(RTCYEAR>>8);
                    yh.tm_yearLow= (int)changeHexToInt(RTCYEAR & 0x00FF);
                    yh.tm_mon   =  (int)changeHexToInt(RTCMON);
                    yh.tm_mday  =  (int)changeHexToInt(RTCDAY);
                    yh.tm_hour  =  (int)changeHexToInt(RTCHOUR);
                    yh.tm_min   =  (int)changeHexToInt(RTCMIN);
                    yh.tm_sec   =  (int)changeHexToInt(RTCSEC);

memset(RTC_Buffer, 0x00, 32);
sprintf(RTC_Buffer, "%02d%02d %02d %02d %02d %02d %02d", yh.tm_year, yh.tm_yearLow, yh.tm_mon , yh.tm_mday, yh.tm_hour, yh.tm_min, yh.tm_sec);
LCD_showStringScrollRight(RTC_Buffer, 19);


#if 0
             myprintf("%02d%02d-%02d-%02d %02d:%02d:%02d\r\n",
                     (long int)changeHexToInt(RTCYEAR >> 8),
                     (long int)changeHexToInt(RTCYEAR & 0x00FF),
                     (long int)changeHexToInt(RTCMON),
                     (long int)changeHexToInt(RTCDAY),
                     (long int)changeHexToInt(RTCHOUR),
                     (long int)changeHexToInt(RTCMIN),
                     (long int)changeHexToInt(RTCSEC)
                     );
#endif
            break;
        case RTCIV_RTCTEVIFG:               // RTCEVIFG
            //__no_operation();             // Interrupts every minute
           // P9OUT ^= 0x80;
            break;
        case RTCIV_RTCAIFG:   break;        // RTCAIFG
        case RTCIV_RT0PSIFG:  break;        // RT0PSIFG
        case RTCIV_RT1PSIFG:  break;        // RT1PSIFG
        default: break;
    }
}

//*****************************************************************************
// main
//*****************************************************************************
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // Stop WDT
    initGPIO();         // Initializes GPIOs
    initialize_clock(); // initClocks(); // Initialize clocks
    ADC_SETUP();        // set up ADC peripheral

    PowerOnLedBlink();

    initialize_timer(); // Initializes Timer
    initialize_uart();  // Initializes UART
    myLCD_init();       // Initializes Inputs and Outputs for LCD & make LCD to receive commands
    LCD_showString("LCDTST", 6, 1);
    swDelay(10000);
//    rtcInit();
    print_uart("LCD TEST PROGRAM\n");
    swDelay(10000);
    printTest();
  //  _BIS_SR(GIE);       // _BIS_SR(LPM0_bits + GIE); // Enter LPM0 w/ &  Enable interrupts
    swDelay(100000);
    logDEBUG(LOGSRC,"Sending: %s", "printTest data Packet");

    set_RTC();
    //eeprom_Test();
    swDelay(10000);

    while(1)
    {
        swDelay(10000);
        read_RTC();
        swDelay(10000);
        logINFO(LOGSRC,"Sending: %s", "printTest data Packet");
        //print_uart("LCD TEST PROGRAM123\n");

        LCD_showStringScrollRight(RTC_Buffer, 18);

        if (mode)
        {
           // EEPROM_ReadString (0, cEpromBuffer, 16);
          //  LCD_showStringScrollRight(cEpromBuffer,16);
           // LCD_showStringScrollRight("RETHUSHA", 8);
           // LCD_showStringScrollRight("9876543210", 10);
        }
        else
        {
           // EEPROM_ReadString (16, cEpromBuffer, 16);
           // LCD_showStringScrollLeft(cEpromBuffer,16);
            //LCD_showStringScrollLeft("SRI KRISHNA", 11);
            //LCD_showStringScrollLeft("0123456789", 10);
        }
        swDelay(400000);
    }
    return 0;
}


//*****************************************************************************
// System clock initialization routine
//*****************************************************************************
void initialize_clock(void)
{
    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;    // Unlock ports from power manager

    // Startup clock system with max DCO setting ~8MHz
    CSCTL0_H = CSKEY >> 8;         //  0xA500; // password to access clock calibration registers
    CSCTL1 = DCOFSEL_3 | DCORSEL;  // 0x0046; // specifies frequency of main clock
    CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK;  // 0x0133; // assigns additional clock signals
    CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;     // Set all dividers i.e. CSCTL3 = 0x0000; // use clocks at intended frequency, do not slow them down
    CSCTL0_H = 0;                             // Lock CS registers
    return;
}


//*****************************************************************************
//
//*****************************************************************************
void rtcInit(void)
{
    // Configure LFXT 32kHz crystal
       CSCTL0_H = CSKEY >> 8;                  // Unlock CS registers
       CSCTL4 &= ~LFXTOFF;                     // Enable LFXT
       do
       {
         CSCTL5 &= ~LFXTOFFG;                  // Clear LFXT fault flag
         SFRIFG1 &= ~OFIFG;
       } while (SFRIFG1 & OFIFG);              // Test oscillator fault flag
       CSCTL0_H = 0;                           // Lock CS registers

       // Configure RTC_C
       RTCCTL0_H = RTCKEY_H;                   // Unlock RTC
       RTCCTL0_L = RTCTEVIE | RTCRDYIE;        // enable RTC read ready interrupt
                                               // enable RTC time event interrupt

       RTCCTL1 = RTCBCD | RTCHOLD | RTCMODE;   // RTC enable, BCD mode, RTC hold

       RTCYEAR = 0x2020;                       // Year = 0x2010
       RTCMON = 0x0b;                           // Month = 0x04 = April
       RTCDAY = 0x0b;                          // Day = 0x06 = 6th
       RTCDOW = 0x04;                          // Day of week = 0x04 = Thursday
       RTCHOUR = 0x15;                         // Hour = 0x15
       RTCMIN = 0x47;                          // Minute = 0x47
       RTCSEC = 0x50;                          // Seconds = 0x50

       //RTCADOWDAY = 0x2;                       // RTC Day of week alarm = 0x2
       //RTCADAY   = 0x20;                         // RTC Day Alarm = 0x20
       //RTCAHOUR  = 0x10;                        // RTC Hour Alarm
       //RTCAMIN   = 0x23;                         // RTC Minute Alarm

       myprintf("\r\n\r\n32.768kHz Internal RTC program Start\r\n");

       RTCCTL1 &= ~(RTCHOLD);                  // Start RTC

  //     __bis_SR_register(LPM3_bits | GIE);     // Enter LPM3 mode w/ interrupts enabled
       __no_operation();
}

//*****************************************************************************
// ADC initialization routine
//*****************************************************************************
void ADC_SETUP(void)
{
    ADC12CTL0  = ADC12_SHT_16 | ADC12_ON;   // Turn on, set sample & hold time
    ADC12CTL1  = ADC12_SHT_SRC_SEL;         // Specify sample & hold clock source
    ADC12CTL2  = ADC12_12BIT;               // 12-bit conversion results
    ADC12MCTL0 = ADC12_P92;                 // P9.2 is analog input
    ADC12IER0  = ADC12IE0;                  // enable ADC interrupt
    return;
}

//*****************************************************************************
// LCD  String Display routine
//*****************************************************************************
void LCD_showString(char * cString, unsigned int strLength, unsigned int uiPosition)
{
    int i;
    for(i=0; i<strLength; i++) // To scroll through ASCII codes
    {
          myLCD_showChar( *cString++, uiPosition++);
          swDelay(100);
    }
}

//*****************************************************************************
// LCD  String Scroll Left routine
//*****************************************************************************
#if 0
void LCD_showStringScrollLeft(char *msg, unsigned int strLength)
{
    int i, j, s = 5;
    char buffer[LCD_MAX_STR_LEN];
    unsigned char oldMode=mode;

    for (i=0; i<strLength+7; i++)
    {
        if (mode != oldMode) break;
        memset(buffer, ' ',  LCD_MAX_STR_LEN);
        for (j=0; j<strLength; j++)
        {
            if (((s+j) >= 0) && ((s+j) < LCD_MAX_STR_LEN))
            {
                buffer[s+j] = msg[j];
            }
        }
        s--;
        LCD_showString(buffer, LCD_MAX_STR_LEN, 1);
        swDelaySec(3);
    }
}
#endif
void LCD_showStringScrollLeft(char *msg, unsigned int strLength)
{
    int i, s = 5, strSize;
    char buffer[LCD_MAX_STR_LEN];
    unsigned char oldMode=mode;
    char *cPtr;
    strSize = strLength + 7;
    cPtr = (char*) malloc(strSize * sizeof(char)); // Allocating the memory
    if(cPtr==NULL) return; // Memory allocate failure
    memset(cPtr, ' ', strSize);
    memcpy(&cPtr[0], msg, strLength);
    for ( i=0;  i<strSize; i++ )
    {
        if (mode != oldMode) break;
        memset(buffer, ' ',  LCD_MAX_STR_LEN);
        if(s>=0)
        {
            memcpy(&buffer[s--], &cPtr[0], i+1);
        }
        else
        {
            memcpy(&buffer[0], &cPtr[i-5], 6);
        }
        LCD_showString(buffer, LCD_MAX_STR_LEN, 1);
        swDelaySec(3);
    }
    free(cPtr); // deallocating the memory
    return;
}

//*****************************************************************************
// LCD  String Scroll Left routine
//*****************************************************************************
void LCD_showStringScrollRight(char *msg, unsigned int strLength)
{
    int i, k, strSize;
    char buffer[LCD_MAX_STR_LEN];
    unsigned char oldMode=mode;
    char *cPtr;
    strSize = strLength + 7;
    cPtr = (char*) malloc(strSize * sizeof(char)); // Allocating the memory
    if(cPtr==NULL) return; // Memory allocate failure
    memset(cPtr, ' ', strSize);
    memcpy(&cPtr[7], msg, strLength);
    for (i=strSize, k=1; i>0; i--)
    {
        if (mode != oldMode) break;
        memset(buffer, ' ',  LCD_MAX_STR_LEN);
        memcpy(buffer, &cPtr[strSize-k], k++);
        LCD_showString(buffer, LCD_MAX_STR_LEN, 1);
        swDelaySec(3);
    }
    free(cPtr); // deallocating the memory
    return;
}

//*****************************************************************************
// SW Delay routines
//*****************************************************************************
void swDelay(volatile unsigned long ulDelay) {  // SW Delay
    if (ulDelay > 0) {
         do ulDelay--;
         while(ulDelay != 0);
    }
}

void swDelaySec(volatile unsigned long ulDelaySec) {
    int j;
    for (j=0; j<ulDelaySec; j++) {
        __delay_cycles(1000000);
    }
}

//*****************************************************************************
// Timer init routine
//*****************************************************************************
void initialize_timer(void)
{
    TA0CCR0  = 32768;    // Upper limit   = 1000;    // 1ms
    TA0CTL = ACLK | ID | UP |TACLR;   //ACLK, UP_MODE, no clock div
    //TA0CTL = TASSEL_2 + MC_1 + ID_0;   // SMCLK / 1 = 1 MHz / 1 = 1 MHz = 0.001 ms, upmode
    TA0CCTL0 = CCIE;     //ENable Compare 0  interrupt enabled
    return;
}

//*****************************************************************************
// PowerOnLedBlink routine
//*****************************************************************************
void PowerOnLedBlink(void)
{
    char i;
    for(i=0; i<4; i++)
     {
         //P1OUT ^= BIT0;
         P1OUT |= BIT0;     // bit set
         swDelaySec(3);
         P1OUT &= ~BIT0;    // bit clear
         swDelaySec(3);
     }
}
//*****************************************************************************
// LCD test routine
//*****************************************************************************
int myLCD_Test(void) {
    /*
    myLCD_showChar( ' ', 1 ); // Display blank space in space 1
    myLCD_showChar( ' ', 2 ); // Display blank space in space 2
    myLCD_showChar( ' ', 3 ); // Display blank space in space 3
    myLCD_showChar( ' ', 4 ); // Display blank space in space 4
    myLCD_showChar( ' ', 5 ); // Display blank space in space 5
    myLCD_showChar( ' ', 6 ); // Display blank space in space 6
    */
    int i;
    LCD_showString("      ", 6, 1);
    for(i=48;i<91;i=i+1) // To scroll through ASCII codes
    {
        myLCD_showChar( i , 1 ); // Display ASCII codes 48-90
        swDelay(200000);
    }
    LCD_showString("DONE", 6, 2);
    return 0;
}

//*****************************************************************************
//              @End of file
//*****************************************************************************

