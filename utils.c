#include "utils.h"
#include <math.h>

typedef void (*IAP)(unsigned int [],unsigned int[]);

//----------------------------------------------------------------------------
void * s_memset(void * dst,  int ch, int length)
{
  register char *ptr = (char *)dst - 1;

  while(length--)
     *++ptr = ch;

  return dst;
}

//----------------------------------------------------------------------------
void * s_memcpy(void * s1, const void *s2, int n)
{
   register int mask = (int)s1 | (int)s2 | n;

   if(n == 0)
      return s1;

   if(mask & 0x1)
   {
      register const char *src = s2;
      register char *dst = s1;

      do
      {
         *dst++ = *src++;
      }while(--n);

      return s1;
   }

   if(mask & 0x2)
   {
      register const short *src = s2;
      register       short *dst = s1;

      do
      {
        *dst++ = *src++;
      }while( n -= 2);

      return s1;
   }
   else
   {
      register const int *src = s2;
      register       int *dst = s1;

      do
      {
         *dst++ = *src++;
      }while (n -= 4);

      return s1;
   }
}


///////////////////////////////////////////////////////////////////////////////
/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length.
  * @retval  0: pBuffer1 identical to pBuffer2
  *          1: pBuffer1 differs from pBuffer2
  */
char s_strncmp(char* pStr1, char* pStr2, unsigned int strLength)
{
  while (strLength--)
  {
     if(*(pStr1++) != *(pStr2++))
     {
          return 1;
     }
  }
  return 0;
}

int divide(int a, int b)
{
  int result = 0;
  int temp = b;
  
  while (temp >= b)
  {
    temp = a - b * result++;
  }
  
  return result-1;
}

void strReverse(char s[])
{
  int c, i, j;
  
  for (i = 0, j = strlen(s)-1; i<j; i++, j--)
  {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

void reverse(char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}
  
void u_itoa( int n, char s[] )
{
  int i, sign;
  
  if(( sign = n ) < 0 )
    n = -n;
  i = 0;
  do
  {
    s[i++] = n % 10 + '0';
  } while(( n /= 10 ) > 0 );
  
  if( sign < 0  )
    s[i++] = '-';
    
  s[i] = '\0';
  strReverse( s );
}


int uItoa(int x, char str[], int d)
{
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }

    // If number of digits required is more, add 0s at beginning
    while (i < d)
        str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return i;
}

// Converts a floating-point/double number to a string.
void u_ftoa(float n, char* res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    // convert integer part to string
    int i = uItoa(ipart, res, 0);

    // check for display option after point
    if (afterpoint != 0) {
        res[i] = '.'; // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter
        // is needed to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);

        uItoa((int)fpart, res + i + 1, afterpoint);
    }
}

/****************************************************************************/
/****************************************************************************/


