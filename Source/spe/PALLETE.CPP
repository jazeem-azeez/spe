int c=-1;
class palslider
{
	static const xst;//its const as all three sliders have same x-coord.
	static int count;//counts the no. of object being created.
	int yst;	//to assign diff y co-ord. using count.
	int x;		//actual x-coordinate of the button that moves on palslider.
public:
	palslider(int a)//one arg constructor.
	{
		count++;	//This function accepts value for each palslider.
		yst=count*40;	//and before assigning the values it validates
		if(a>=65)	//them b/w 1 and 64 but the actual value that
		  a=64;		//that gets assigned to the var. x is one less
		if(a<1)		//than the value supplied to the constructor.
		  a=1;
		x=4*(a-1);
	}
	void makeslider()	//it draws palslider.
	{
		setcolor(WHITE);
		line(xst,yst,xst+256,yst);
		setfillstyle(1,WHITE);
		rectangle(xst+x,yst-10,xst+x+4,yst+10);
	}
	void slideright()	//it shifts the palslider one pos. right
	{
		if(x>248)
		  return;
		setcolor(getbkcolor());
		setfillstyle(1,getbkcolor());
		rectangle(xst+x,yst-10,xst+x+4,yst+10);
		x+=4;
		makeslider();
	}
	void slideleft()	//it shifts the palslider one pos. left
	{
		if(x<4)
		  return;
		setcolor(getbkcolor());
		setfillstyle(1,getbkcolor());
		rectangle(xst+x,yst-10,xst+x+4,yst+10);
		x-=4;
		makeslider();
	}
	friend void showcol(palslider r,palslider g,palslider b);
};

//this function had to be a friend func. so that it can pass three objects
//to the function setrgbpalette().
void showcol(palslider r,palslider g,palslider b)
{
	char arr[30]="\0";
	setrgbpalette(c,r.x/4,g.x/4,b.x/4);
	setcolor(c);
	setfillstyle(1,c);
	bar3d(1,150,638,450,0,0);
	sprintf(arr,"(R,G,B)=(%2i,%2i,%2i)",r.x/4,g.x/4,b.x/4);
	gotoxy(63,3);
	cout<<arr;
}

//values assigned to static mambers of the class palslider.
int const palslider::xst=200;
int palslider::count=0;

//main func., controls class palslider and all its funtions
void adjustcolor()
{
	int gd=0,gm;	//to initialize graphics adapter.
	int key;	//to store keys hit by the user.
	int which;
	int focus=0;	//to know which palslider is currently in focus.
	palslider r(32),g(32),b(32);
	palslider *p;
	initgraph(&gd,&gm,"");
	setcolor(WHITE);
	outtextxy(20,20,"Color Table");
	outtextxy(20,40,"RED   :");
	outtextxy(20,80,"GREEN :");
	outtextxy(20,120,"BLUE  :");
	r.makeslider();
	g.makeslider();
	b.makeslider();
	do
	{
  getch();
		key=inportb(0x60);
		if(key==72||key==75||key==77||key==80||key=='c')
		  getch();

		if(key==1)
			return;

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
void  colorchooser()
{
	int x,y,button;
	console c1("adjustclr.con");

	for(;!kbhit();)
	{	getmouseptr(&button,&x,&y);
		if(button==1)
		{c=getpixel(x,y);
		if(!(c>0&&c<16))
			outtext("Invalid color");
		else
		adjustcolor();
		}
	}

}

int getptrcolor()
{
	m.getmousepos();
	return(getpixel(m.x,m.y));
}