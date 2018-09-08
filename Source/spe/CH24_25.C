/* ==============  Program Description  ============= */
/*   program name : ch24_25.c                         */
/*   getpixel() application.                          */
/* ================================================== */
#include  <graphics.h>

void main()
{
    int     driver = DETECT,mode;
    int     i;

    initgraph(&driver,&mode,"c:\\borlandc\\bgi");
    line(100,100,500,100);
    for ( i = 20; i < 300; i++ )
	if ( getpixel(300,i) == WHITE )
	{
	   setcolor(BLUE);
	   circle(300,i,5);
	}
	else
	   putpixel(300,i,WHITE);
    getch();
    closegraph();
}