/*
*/

#ifndef  _UTILS_H_
#define  _UTILS_H_
#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------
void * s_memset(void * dst,  int ch, int len);
void * s_memcpy(void * s1, const void *s2, int len);
char s_strncmp(char *s1, char *s2, unsigned int len);
int divide(int a, int b);
void strReverse(char s[]);
void reverse(char* str, int len);
void u_itoa( int n, char s[] );
int uItoa(int x, char str[], int d);
void u_ftoa(float n, char* res, int afterpoint);
//----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif
#endif

//*****************************************************************************
//              @End of file
//*****************************************************************************
