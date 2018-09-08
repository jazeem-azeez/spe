#include <mem.h>
#include <stdio.h>
#include <conio.h>

#define BASE 0xB8000000

char buf[80*40*2];

/* restore saves the contents of the monochrome screen in buffer */
void restore_mono_screen(char near *buffer)
{
   movedata( _DS,(unsigned)buffer,BASE, 0, 80*40*2);
}

void save_mono_screen(char near *buffer)
{
   movedata(BASE, 0, _DS, (unsigned)buffer, 80*40*2);
}


int main(void)
{
printf("\n\n\t\tEGVAAFAFAFAAFA");
   save_mono_screen(buf);
   clrscr();
   restore_mono_screen(buf);
  // printf("\n\n\t\tEGVAAFAFAFAAFA");
   getch();
   return 0;
}

