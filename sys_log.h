// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#ifndef _LOG_H
#define _LOG_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define LOGSRC          __FILE__,__LINE__
#define sys_log_f	       1
#define INTERNAL_RTC       1

// NOTE: These MUST mirror the "LOG_XXXX" definitions
#define SYSLOG_NONE         0 // LOG_EMERG   [not used]
#define SYSLOG_ALERT        1 // LOG_ALERT   [not used]
#define SYSLOG_CRITICAL     2 // LOG_CRIT
#define SYSLOG_ERROR        3 // LOG_ERR
#define SYSLOG_WARNING      4 // LOG_WARNING
#define SYSLOG_NOTICE       5 // LOG_NOTICE  [not used]
#define SYSLOG_INFO         6 // LOG_INFO
#define SYSLOG_DEBUG        7 // LOG_DEBUG
#define SYSLOG_SAVE         8 // LOG_SAVE

typedef struct
{
    int tm_sec;   /* seconds after the minute, 0 to 60
                     (0 - 60 allows for the occasional leap second) */
    int tm_min;   /* minutes after the hour, 0 to 59 */
    int tm_hour;  /* hours since midnight, 0 to 23 */
    int tm_mday;  /* day of the month, 1 to 31 */
    int tm_mon;   /* months since January, 0 to 11 */
    int tm_year;  /* years since 1900 */
    int tm_yearLow;  /* years since 1900 */
    int tm_wday;  /* days since Sunday, 0 to 6 */
    int tm_yday;  /* days since January 1, 0 to 365 */
    int tm_isdst; /* Daylight Savings Time flag */
}st_time;

extern st_time yh;

void logDEBUG(const char *ftn, int line, const char *fmt, ...);
void logINFO(const char *ftn,  int line, const char *fmt, ...);
void logWARNING(const char *ftn, int line, const char *fmt, ...);
void logERROR(const char *ftn, int line, const char *fmt, ...);
void logCRITICAL(const char *ftn, int line, const char *fmt, ...);
void logPRINTF(const char *ftn, int line, int level, const char *fmt, ...);


// ----------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif
#endif

//*****************************************************************************
//              @End of file
//*****************************************************************************
