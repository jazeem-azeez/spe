
 #include <stdio.h>
 #include <time.h>
 #include <dos.h>
 #include <stddef.h>
 #include <conio.h>

 int texttime(int xcol,int ycol)
 {

  struct dostime_t t;
  _dos_gettime(&t);
  gotoxy(xcol,ycol);
  printf("The current time is: %2d:%02d:%02d.%02d\n", t.hour, t.minute,
    t.second, t.hsecond);
  return 0;
}