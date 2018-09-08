
#include <stdio.h>
#include <stdlib.h>
#include <alloc.h>
#include <string.h>
#include <dos.h>
#include <conio.h>

int main(void)
{

int result;
int port = 0;
result = inport(port);
printf("Word read from port %d = 0x%X\n", port, result);
return 0;
}

 int ttime(int xcol,int ycol)
 {

  struct dostime_t t;
  _dos_gettime(&t);
  gotoxy(xcol,ycol);
  printf("%2d: %02d: %02d.%02d\n", t.hour, t.minute,
    t.second, t.hsecond);
  return 0;
}
int gltime(int x,int y)
{
  struct dostime_t t;
  _dos_gettime(&t);
  gotoxy(xcol,ycol);
  printf("%2d: %02d: %02d.%02d\n", t.hour, t.minute,
    t.second, t.hsecond);
  return 0;

}

int sysinfo(void)
{
   char *path, *ptr;
   int i = 0;
   directvideo=1;
   while (environ[i])
       printf("%s\n",environ[i++]);

   return 0;
}