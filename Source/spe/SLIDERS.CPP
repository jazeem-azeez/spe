/****************************************************************/
/*	This is a small program to illustrate the different	*/
/*	colors that can be generated with a VGA in 256 Color	*/
/*	mode or a IBM-8514 graphics adapter in dos.This program	*/
/*	uses a grphical interface for ease.                     */
/*		This little program can prove to be a great 	*/
/*	for those who waana know the right amount ofintensities	*/
/*	to be used for red, green and blue to make a particular */
/*	shade.							*/
/****************************************************************/
/*	Compiled with Turbo C++ Version 3.0			*/
/*	Date:4th december,2002					*/
/*	Name of the programmer: KIRTI DHRUVA			*/
/*	Nationality:Indian(delhi)				*/
/*      Email ID:dmwinc2000@yahoo.com			*/
/****************************************************************/
/*	Legal Warning: 						*/
/*	1. You can redistribute this utility untill this	*/
/*         file is kept intact.					*/
/*	2. Redistribution should be free of cost.       	*/
/*      3. You can use this code in your program by mentioning	*/
/*         my name in the that program.				*/
/*      4. This ultility can not be sold under any circumtances */
/*	   without the authors permission.			*/
/****************************************************************/
/*  CONTROLS:							*/
/*	esc=exit						*/
/*	up arrow=focus up					*/
/*	down arrow=focus down					*/
/*	left arrow=move focused slider towards left		*/
/*	right arrow=move focused slider towards right		*/
/*	1=wild mode on (random events occurs)			*/
/*	2=wild mode off						*/
/****************************************************************/

#include<iostream.h>	//for cin,cout,etc.
#include<graphics.h>	//for graphics functions.
#include<conio.h>	//for getch().
#include<stdio.h>	//for sprintf().
#include<stdlib.h>      //for randomize(),random(),etc.

class slider
{
	static const xst;//its const as all three sliders have same x-coord.
	static int count;//counts the no. of object being created.
	int yst;	//to assign diff y co-ord. using count.
	int x;		//actual x-coordinate of the button that moves on slider.
public:
	slider(int a)//one arg constructor.
	{
		count++;	//This function accepts value for each slider.
		yst=count*40;	//and before assigning the values it validates
		if(a>=65)	//them b/w 1 and 64 but the actual value that
		  a=64;		//that gets assigned to the var. x is one less
		if(a<1)		//than the value supplied to the constructor.
		  a=1;
		x=4*(a-1);
	}
	void makeslider()	//it draws slider.
	{
		setcolor(WHITE);
		line(xst,yst,xst+256,yst);
		setfillstyle(1,WHITE);
		rectangle(xst+x,yst-10,xst+x+4,yst+10);
	}
	void slideright()	//it shifts the slider one pos. right
	{
		if(x>248)
		  return;
		setcolor(getbkcolor());
		setfillstyle(1,getbkcolor());
		rectangle(xst+x,yst-10,xst+x+4,yst+10);
		x+=4;
		makeslider();
	}
	void slideleft()	//it shifts the slider one pos. left
	{
		if(x<4)
		  return;
		setcolor(getbkcolor());
		setfillstyle(1,getbkcolor());
		rectangle(xst+x,yst-10,xst+x+4,yst+10);
		x-=4;
		makeslider();
	}
	friend void showcol(slider r,slider g,slider b);
};

//this function had to be a friend func. so that it can pass three objects
//to the function setrgbpalette().
void showcol(slider r,slider g,slider b)
{
	char arr[30]="\0";
	setrgbpalette(1,r.x/4,g.x/4,b.x/4);
	setcolor(WHITE);
	setfillstyle(1,1);
	bar3d(1,150,638,450,0,0);
	sprintf(arr,"(R,G,B)=(%2i,%2i,%2i)",r.x/4,g.x/4,b.x/4);
	gotoxy(63,3);
	cout<<arr;
}

//values assigned to static mambers of the class slider.
int const slider::xst=200;
int slider::count=0;

//main func., controls class slider and all its funtions
void main()
{
	int gd=0,gm;	//to initialize graphics adapter.
	int key;	//to store keys hit by the user.
	int wild=0,which;
	int focus=0;	//to know which slider is currently in focus.
	slider r(32),g(32),b(32);
	slider *p;
	initgraph(&gd,&gm,"");
	setcolor(WHITE);
	outtextxy(20,40,"RED   :");
	outtextxy(20,80,"GREEN :");
	outtextxy(20,120,"BLUE  :");
	r.makeslider();
	g.makeslider();
	b.makeslider();
	randomize();
	gotoxy(1,1);
	cout<<"Press 1 to start and 2 to stop WILD MODE";
	gotoxy(65,1);
	cout<<"WILD MODE OFF";
	do
	{
		if(!wild)
		  getch();
		key=inportb(0x60);
		if(key==72||key==75||key==77||key==80)
		  getch();
		if(key==1)
		{
			closegraph();
			return;
		}
		if(key==3)
		{
			wild=0;
			gotoxy(65,1);
			cout<<"             ";
			gotoxy(65,1);
			cout<<"WILD MODE OFF";
		}
		if(wild==1)
		{
			which=random(4);
			switch(which)
			{
				case 0:key=72;break;
				case 1:key=80;break;
				case 2:key=75;break;
				case 3:key=77;break;
			}
		}
		if(key==2)
		{
			wild=1;
			gotoxy(65,1);
			cout<<"             ";
			gotoxy(65,1);
			cout<<"WILD MODE ON";
		}
		if(key==72)
		{
			setcolor(getbkcolor());
			circle(10,(focus+1)*40,3);
			focus--;
			if(focus==-1)
			  focus=2;
			setcolor(WHITE);
			circle(10,(focus+1)*40,3);
		}
		if(key==80)
		{
			setcolor(getbkcolor());
			circle(10,(focus+1)*40,3);
			focus=(++focus)%3;
			setcolor(WHITE);
			circle(10,(focus+1)*40,3);
		}
		switch(focus)
		{
			case 0:p=&r;break;
			case 1:p=&g;break;
			case 2:p=&b;break;
		}
		if(key==75)
		{
			p->slideleft();
			showcol(r,g,b);
		}
		if(key==77)
		{
			p->slideright();
			showcol(r,g,b);
		}
	}while(1);
}