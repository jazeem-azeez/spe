#include <conio.h>

int main(void)
{
   textmode(BW40);
   cprintf("ABC");
   getch();

   textmode(C40);
   cprintf("ABC");
   getch();

   textmode(BW80);
   cprintf("ABC");
   getch();

   textmode(C80);
   cprintf("ABC");
   getch();

   textmode(MONO);
   cprintf("ABC");
   getch();

   return 0;
}

