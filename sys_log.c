#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include "sys_log.h"
#include "myprintf.h"

#if defined(TARGET_WINCE)
// (Windows return '-1' if lengths exceeds 'size' which is different than Linux)
#  define VSNPRINTF        _vsnprintf
#else
// (Linux return the number of bytes that would have been written if the buffer were long enough)
#  define VSNPRINTF         vsnprintf
#endif

#define MAX_MESSAGE_LENGTH   100
#define CONSOLE_OUTPUT       stderr
#define FLUSH_MODULO         5L
#define EPOCH_OFFSET 		 25200  // offset to 'Epoch'

char syslogName[12];

st_time yh;

extern void LCD_showStringScrollLest(char *msg, unsigned int strLength);
extern void LCD_showStringScrollRight(char *msg, unsigned int strLength);

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/* convert UTC EPoch seconds to YMDHMS */
void utcSecondsToYmdHms(uint32_t utcSec)
{
	uint32_t TOD = utcSec % (24L * 60L * 60L); // in seconds
	yh.tm_hour  = (int)(TOD / (60L * 60L));
	yh.tm_min   = (int)((TOD % (60L * 60L)) / 60L);
	yh.tm_sec   = (int)((TOD % (60L * 60L)) % 60L);
	uint32_t N   = (utcSec / (24L * 60L * 60L)) + 719469L;
	uint32_t C   = ((N * 1000L) - 200L) / 36524250L;
	uint32_t N1  = N + C - (C / 4L);
	uint32_t Y1  = ((N1 * 1000L) - 200L) / 365250L;
	uint32_t N2  = N1 - ((365250L * Y1) / 1000L);
	uint32_t M1  = ((N2 * 1000L) - 500L) / 30600L;
	yh.tm_mday  = (int)(((N2 * 1000L) - (30600L * M1) + 500L) / 1000L);
	yh.tm_mon   = (int)((M1 <= 9L)? (M1 + 3L) : (M1 - 9L));
	yh.tm_year  = (int)((M1 <= 9L)? Y1 : (Y1 + 1));
	return;
}

/* format date/time */
// The destination buffer is assumed to be at least 20 bytes in length
// the output format will be: "YYYY/MM/DD hh:mm:ss" (with a terminating null)
const char *utcFormatDateTime(char *dt)
{
#ifdef INTERNAL_RTC
     sprintf(dt, "%04d-%02d-%02d %02d:%02d:%02d", yh.tm_year, yh.tm_mon , yh.tm_mday, yh.tm_hour, yh.tm_min, yh.tm_sec);
    //sprintf(dt, "%02d%02d-%02d-%02d %02d:%02d:%02d", yh.tm_year, yh.tm_yearLow, yh.tm_mon , yh.tm_mday, yh.tm_hour, yh.tm_min, yh.tm_sec);
    //sprintf(dt, "%04d/%02d/%02d %02d:%02d:%02d", 2020, 11, 11, 22, 10, 25);
#elif
	// memset(yh, 0, sizeof(st_time));
    time_t utcSec;
    time ( &utcSec );
    utcSecondsToYmdHms(utcSec); // For system time
    //utcSecondsToYmdHms(utcSec-EPOCH_OFFSET);  // For GPS time
    sprintf(dt, "%04d/%02d/%02d %02d:%02d:%02d", /*2020*/ yh.tm_year, yh.tm_mon , yh.tm_mday, yh.tm_hour, yh.tm_min, yh.tm_sec);
#endif
    return dt;
}


//--------------------------------------------------------------
//--------------------------------------------------------------
/* base logging print function */
int logPrint(int level, const char *fn, int line, const char *fmt, va_list ap)
{        
  /* extract source file from name */
  // It is important that 'fn' not contain any string formatting characters
  char trace[32], c_time[32];
  const char *lvlName = "?";    /* 'Level' title */
  int fnLen = strlen(fn), fi = fnLen - 1, fLen = 0;
  const char *f = (char*)fn, *fp = (char*)0;
  char cvs[60], *c = cvs;     
  char msg[MAX_MESSAGE_LENGTH + 2];
  int msgLen = 0;
  int bufSize, vsnLen;
  memset(cvs,0x00,60);
  memset(trace,0x00,32);
  memset(c_time,0x00,32);

  if (fn && *fn && (line > 0)) 
  {
		for (; fi >= 0; fi--)
		{
		    if (fn[fi] == '.')
			{
			  fp = &fn[fi]; 
			}           
			if ((fn[fi] == '/') || (fn[fi] == '\\')) 
			{ 
			  f = &fn[fi + 1];
			  fLen = fp? (fp - f) : (fnLen - (fi + 1));
			  break;
			}
		}
		if ((fLen + 7) < sizeof(trace)) 
		{
            sprintf(trace,"%.*s:%d",fLen,f,line);
            fn = trace;
        }
    }
  // 'f'    - points to the beginning of the source file name
  // 'fp'   - points to the (first) '.' before the extension
  // 'fLen' - is the length of the source file name without the extension
   
  switch (level)
  {
      case SYSLOG_NONE        :   lvlName = "EMERG";    break;  // EMERG errors
      case SYSLOG_ALERT       :   lvlName = "ALERT";    break;  // ALERTs
      case SYSLOG_CRITICAL    :   lvlName = "CRIT";     break;  // Critical errors
      case SYSLOG_ERROR       :   lvlName = "ERROR";    break;  // General errors
      case SYSLOG_WARNING     :   lvlName = "WARN";     break;  // Warnings
      case SYSLOG_NOTICE      :   lvlName = "NOTICE";   break;  // NOTICEs
      case SYSLOG_INFO        :   lvlName = "INFO";     break;  // Informational
      case SYSLOG_DEBUG       :   lvlName = "DBUG";     break;  // Debug
      case SYSLOG_SAVE        :   lvlName = "SAVE";     break;  // SAVE
  }

  utcFormatDateTime(c_time);
//  LCD_showStringScrollRight(c_time, strlen(c_time));

  sprintf(c,"%s",c_time);
  c += strlen(c);

   /* format the message */
   memset(msg,0x00,MAX_MESSAGE_LENGTH + 2);
   
   if (fn && *fn)
   {
        // pre-pend function information
        msgLen = sprintf(msg, "%d%s.%s[%s][%s]", level % 10, syslogName, lvlName, fn, cvs);
   }
    
    // append message
    // (Note: Windows return value for 'VSNPRINTF' is different than Linux)
     bufSize = MAX_MESSAGE_LENGTH - msgLen;
     vsnLen  = VSNPRINTF(&msg[msgLen], bufSize, fmt, ap);
    
    if ((vsnLen < 0) || (vsnLen >= bufSize)) 
    {
        // Windows returns '-1' if the written length exceeds 'bufSize'
        // Linux returns the number of bytes that _would_ have been written
        msgLen = MAX_MESSAGE_LENGTH;
    } 
    else
    {
        // 'vsnLen' bytes written
        msgLen += vsnLen;
    }
    // trailing '\n'
    if (msg[msgLen - 1] != '\n') 
    {
        strcpy(&msg[msgLen++], "\n");
    } 
    else
    {
        msg[msgLen] = 0;
    }

   /* LOG message Save */
    printf("%s", (char*)msg); //console print
	print_uart(msg);
	//myprintf(msg);
    return 0;
}

//--------------------------------------------------------------
/* log messages */
void logPRINTF(const char *ftn, int line, int level, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    logPrint(level, ftn, line, fmt, ap);
    va_end(ap);
}

//--------------------------------------------------------------
/* log debug messages */
void logDEBUG(const char *ftn, int line, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    logPrint(SYSLOG_DEBUG, ftn, line, fmt, ap);
    va_end(ap);
}

/* log info messages */
void logINFO(const char *ftn, int line, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    logPrint(SYSLOG_INFO, ftn, line, fmt, ap);
    va_end(ap);
}

/* log warning messages */
void logWARNING(const char *ftn, int line, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    logPrint(SYSLOG_WARNING, ftn, line, fmt, ap);
    va_end(ap);
}

/* log error messages */
void logERROR(const char *ftn, int line, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    logPrint(SYSLOG_ERROR, ftn, line, fmt, ap);
    va_end(ap);
}

/* log critical messages */
void logCRITICAL(const char *ftn, int line, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    logPrint(SYSLOG_CRITICAL, ftn, line, fmt, ap);
    va_end(ap);
}
//------------------ end of file  ----------------------------------
