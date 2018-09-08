
#include<dos.h>
#include<graphics.h>


# define RIGHT		0
# define LEFT  		1
# define UP		2
# define DOWN		3
# define UPRIGTH 	4
# define UPLEFT 	5
# define DOWNRIGHT	6
# define DOWNLEFT	7
# define NOTMOVED 	9
union REGS i,o;
struct SREGS s;


 getmouseptr(int *button,int *x,int *y)

  {
    i.x.ax=3;
    int86(0x33,&i,&o);
    *button=o.x.bx;
    *x=o.x.cx;
    *y=o.x.dx;
    return 0;
  }

class mouse
{
public:

	int button,x,y,oldxx,oldyy,clickbtn;
	int click_delay;
	int initmouse();
	void showmouseptr();
	void restrictmouseptr(int x1,int y1,int x2,int y2);
	void getmousepos();
	void hidemouseptr();
	int click(int x1,int y1,int x2,int y2);
	int moving( );

	void togglemouse()

	{
	if(clickbtn==1)
	clickbtn+=1;
	else
	clickbtn-=1;
	}

	int doubleclick(int x1,int y1,int x2,int y2)

	{
	getmousepos();
	int ans=0;
	if(x>x1&&x<x2&&y>y1&&y<y2&&(button==clickbtn))
	{
	ans=1;
	delay(click_delay);
	getmousepos();
	if(x>x1&&x<x2&&y>y1&&y<y2&&(button==clickbtn))
	ans=2;
	}
	return ans;
	}

	void show_mouse_cord(int sx,int sy)
	{
	getmousepos();
	setcolor(BLACK);
	char str1[23],str2[6];
	itoa(x,str1,10);
	itoa(y,str2,10);
	strncat(str1," x ",3);
	strncat(str1,str2,4);
	outtextxy(sx,sy,str1);
	//gotoxy(x/8,y/8);
	//cout<<x<<" X "<<y;
	}
}m;

int mouse::initmouse()
  {clickbtn=1;
   i.x.ax=0;
   int86(0x33,&i,&o);
   return(o.x.ax);
  }


void mouse:: showmouseptr()
  {
    i.x.ax=1;
    int86(0x33,&i,&o);

  }


void mouse:: hidemouseptr()
  {
    i.x.ax=2;
    int86(0x33,&i,&o);

  }


void mouse::restrictmouseptr(int x1,int y1,int x2,int y2)

{
_AX=7;
_CX=x1;
_DX=x2;
geninterrupt(0x33);
_AX=8;
_CX=y1;
_DX=y2;
geninterrupt(0x33);
}

void mouse::getmousepos()
{getmouseptr(&button,&x,&y);
}

int mouse::click(int x1,int y1,int x2,int y2)

{
getmousepos();
	if(x>x1&&x<x2&&y>y1&&y<y2&&(button==clickbtn))
	{return 1;
	}
	return 0;
}

int mouse :: moving()

{

getmousepos();
	if (x > oldxx && y == oldyy ) return RIGHT;
	if (x < oldxx && y == oldyy ) return LEFT;
	if (y < oldyy && x == oldxx ) return UP;
	if (y > oldyy && x == oldxx) return DOWN;

	if (x > oldxx && y > oldyy ) return UPRIGTH;
	if (x > oldxx && y < oldyy ) return DOWNRIGHT;

	if (x < oldxx && y > oldyy ) return UPLEFT;
	if (x < oldxx && y < oldyy ) return DOWNLEFT;

return 9;
}
