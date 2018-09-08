#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <alloc.h>

void save_screen_area_mem(int,int,int,int,void far *buf[8]);
void restore_screen_area_mem(int ,int ,int ,int ,void far *buf[8],int );

int maxx, maxy;

int main(void)
{
   int gdriver=DETECT, gmode, errorcode;
   void far *ptr[8];

   /* auto-detect the graphics driver and mode */
   initgraph(&gdriver, &gmode, "");
   errorcode = graphresult(); /* check for any errors */
   if (errorcode != grOk)
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1);
   }
   maxx = getmaxx();
   maxy = getmaxy();

   /* draw an image on the screen */
   rectangle(0, 0, maxx, maxy);
   line(0, 0, maxx, maxy);
   line(0, maxy, maxx, 0);

   save_screen_area_mem(0,0,640,480,ptr);    /* save the current screen */
   getch();             /* pause screen */
   cleardevice();       /* clear screen */
   restore_screen_area_mem(0,0,640,480,ptr,COPY_PUT); /* restore the screen */
   getch();             /* pause screen */

   closegraph();
   return 0;
}

void save_screen_area_mem(int sx,int sy,int ex,int ey,void far *buf[8])
{
   unsigned size;
   int xincr = (sx-ex+1)/4,yincr= (sy-ey+1)/4, block;
   int bx=sx;
   size  = imagesize(sx, sy,xincr,yincr);
/* get byte size of image */

   for (block=0; block<8; block++)
   {
      if ((buf[block] = farmalloc(size)) == NULL)
      {
	 closegraph();
	 printf("Error: not enough heap space in save_screen().\n");
	 exit(1);
      }

      sx+=(xincr+1);
      if(sx>=ex)
      {
      sx=bx;
      sy+=yincr;}
      getimage(sx,sy,sx+xincr,sy+yincr,buf[block]);
      }
}

void restore_screen_area_mem(int sx,int sy,int ex,int ey,void far *buf[8],int bit)// done so to reduce error while pgming
{
   int xincr = (sx-ex+1)/4,yincr= (sy-ey+1)/4, block;
   int bx=sx;
   for (block=0; block<8; block++)
   {
      sx+=(xincr+1);
      if(sx>=ex)
      {
      sx=bx;
      sy+=yincr;}
      putimage(sx,sy,buf[block],bit);
      farfree(buf[block]);
      }

}

