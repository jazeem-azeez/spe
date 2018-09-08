#include <graphics.h>

windraw(char wdf[][])
{
}
static void main()
{
/* request auto detection */
int gdriver = DETECT, gmode, errorcode;
int midx, midy, i;

/* initialize graphics and local
   variables */
initgraph(&gdriver, &gmode, "");

/* read result of initialization */
errorcode = graphresult();
if (errorcode != grOk)  /* an error
    occurred */
{
   printf("Graphics error: %s\n", grapherrormsg(errorcode));
   printf("Press any key to halt:");
   getch();
   exit(1); /* terminate with an error
	       code */
}



}