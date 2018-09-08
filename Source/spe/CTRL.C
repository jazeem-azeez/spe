
#include <dos.h>
#include <conio.h>
#include <stdio.h>


#include <stdio.h>
#include <dos.h>

#define ABORT 1

int c_break(void)
{
   printf("Break pressed.  Program aborting ...\n");
   return  (ABORT);
}

void main(void)
{
   ctrlbrk(c_break);
   for(;;)
   {
	  printf("Looping... Press <Ctrl-Break> to quit:\n");
   }
}

    /*


int main(void)
{
   int break_flag;

   printf("Enter 0 to turn control break off\n");
   printf("Enter 1 to turn control break on\n");

   break_flag = getche() - '0';

   setcbrk(break_flag);

   if (getcbrk())
      printf("Cntrl-brk flag is on\n");
   else
      printf("Cntrl-brk flag is off\n");
   return 0;
}

      */