

#include <stdio.h>
#include <conio.h>
#include <stdarg.h>

int vscnf(char *fmt, ...)
{
   va_list argptr;
   int cnt;

   printf("Enter an integer, a float, and a string (e.g. i,f,s,)\n");
   va_start(argptr, fmt);
   cnt = vscanf(fmt, argptr);
   va_end(argptr);

   return(cnt);
}

int main(void)
{
   int inumber;
   float fnumber;
   char string[80];

   vscnf("%d, %f, %s", &inumber, &fnumber, string);
   printf("%d %f %s\n", inumber, fnumber, string);

   return 0;
}
