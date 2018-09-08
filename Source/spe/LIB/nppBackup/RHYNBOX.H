/*
   A header file that contains some useful graphical objects
   for windows programming.
   (C) Copyright Rommel S. Laranjo 1996 && Bryan Bantilan
*/
#include<dos.h>
#include <graphics.h>
#include <stdio.h>
void radio(int x1,int y1,int r, char nam[30])
  {
    setfillstyle(1,WHITE);
    pieslice(x1,y1,0,360,r);
    setcolor(BLACK);
    settextstyle(SMALL_FONT,HORIZ_DIR,4);
    outtextxy(x1+r+10,y1-5,nam);
    outtextxy(x1+r+10,y1-3,"_");
    arc(x1,y1,20,200,r);
    setcolor(WHITE);
    line(x1,y1,x1+r,y1);
    arc(x1,y1,200,20,r);
  }
void down_radio(int x1,int y1,int r)
  {
    setfillstyle(1,WHITE);
    pieslice(x1,y1,0,360,r);
    setcolor(WHITE);
    line(x1,y1,x1+r,y1);
    arc(x1,y1,200,20,r);
    setcolor(BLACK);
    settextstyle(SMALL_FONT,HORIZ_DIR,4);
    setfillstyle(1,BLACK);
    pieslice(x1,y1,0,360,2);/*outtextxy(x1-2,y1-5,"*");*/
    arc(x1,y1,20,200,r);
  }

box(int left, int top, int right, int bottom, int color)
{
	setfillstyle(1,color);
	bar(left, top, right, bottom);

    setcolor(0);line(left + 3, top + 3, right - 3, top + 3);
		line(left + 3, top + 3, left + 3, bottom - 3);
		line(left + 4, bottom - 4, right - 3, bottom - 4);
                line(right - 4, top + 4, right - 4, bottom - 4);
    setcolor(15);line(left + 3, top + 4, right - 3, top + 4);
		 line(left + 4, top + 4, left + 4, bottom - 3);
		 line(left + 3, bottom - 3, right - 3, bottom - 3);
		 line(right - 3, top + 3, right - 3, bottom - 3);
}
button(int left, int top, int right, int bottom, int color)
{
	setfillstyle(1,color);
	bar(left-2, top-2, right+2, bottom+2);

    setcolor(15);line(left, top, right, top);
		 line(left, top, left, bottom);

    setcolor(0);line(left, bottom, right, bottom);
		line(right, top, right, bottom);
}
downbutton(int left, int top, int right, int bottom, int color)
{
	setfillstyle(1,color);
	bar(left-2, top-2, right+2, bottom+2);

    setcolor(0);line(left, top, right, top);
		line(left, top, left, bottom);

    setcolor(15);line(left, bottom, right, bottom);
		 line(right, top, right, bottom);
    delay(2500);
}

beep(unsigned freq, unsigned msec)
{
	sound(freq);
	delay(msec);
	nosound();
}
