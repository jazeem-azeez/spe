
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

/* the names of the text styles supported */
char *fname[] = { "DEFAULT font",
				  "TRIPLEX font",
				  "SMALL font",
				  "SANS SERIF font",
				  "GOTHIC font"
				};

int main(void)
{
   /* request auto detection */
   int gdriver = DETECT, gmode, errorcode;
   int style, midx, midy;
   int size = 1;

   /* initialize graphics and local variables */
   initgraph(&gdriver, &gmode, "");

   /* read result of initialization */
   errorcode = graphresult();
   if (errorcode != grOk)  /* an error occurred */
   {
	  printf("Graphics error: %s\n", grapherrormsg(errorcode));
	  printf("Press any key to halt:");
	  getch();
	  exit(1); /* terminate with an error code */
   }

   midx = getmaxx() / 2;
   midy = getmaxy() / 2;

   settextjustify(CENTER_TEXT, CENTER_TEXT);

   /* loop through the available text styles */
   for (style=DEFAULT_FONT; style<=14; style++)
   {
	  cleardevice();
   /*	  if (style == TRIPLEX_FONT)
		 size = 4;
 */

	  /* select the text style */
	  settextstyle(style, HORIZ_DIR, size);

	  /* output a message */
	  outtextxy(midx, midy, "TEXT,text");
	  getch();
   }

   /* clean up */
   closegraph();
   return 0;
}