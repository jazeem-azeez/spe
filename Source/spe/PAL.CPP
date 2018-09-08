
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

int main(void)
{
/* request auto detection */
   int gdriver = DETECT, gmode, errorcode;
   int i;

/* structure for returning palette copy */
   struct palettetype far *pal=(void *) 0;

/* initialize graphics and local variables */
   initgraph(&gdriver, &gmode, "" );

/* read result of initialization */
   errorcode = graphresult();
/* an error occurred */
   if (errorcode != grOk)
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
/* terminate with an error code */
      exit(1);
   }

   setcolor(getmaxcolor());

/* return a pointer to the default palette */
   pal = getdefaultpalette();

   for (i=0; i<16; i++)
   {
      printf("colors[%d] = %d\n", i, pal->colors[i]);
      getch();
   }

/* clean up */
   getch();
   closegraph();
   return 0;
}

