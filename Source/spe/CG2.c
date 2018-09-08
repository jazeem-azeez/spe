#include <conio.h>
#include <math.h>
//#include <iostream.h>
#include <graphics.h>
#include <stdlib.h>
#define TFACT 10.0	//Translation Factor
#define SFACT 1.5	//Scaling Factor
#define RFACT .15	//Roration Factor
#define SHFACT 1	//Shearing Factor
#define POINTS 9	//Number Of Points

class Transform
{
private:
int midx,midy,Color;
struct POINT
{
float x,y;
};
POINT A[POINTS];

void Screen(void);
void ScaleA(float,float);
void ScaleB(float,float);
void TranslateA(float,float);
void TranslateB(float,float);
void RotateA(float);
void RotateB(float);
void ShearA(float,float);
void ShearB(float,float);
void Plot();
public:
Transform(void);
void Run(void);
};
void Transform::ShearA(float g,float h)
{
int tx,ty;
for(int i=0;i<POINTS;i++)
	{
	tx = A[i].x;
	ty = A[i].y;

	A[i].x = tx + g*ty;
	A[i].y = h*tx + ty;
	}
Plot();
}

void Transform::ShearB(float g,float h)
{
int tx,ty;
for(int i=0;i<POINTS;i++)
	{
	tx = A[i].x;
	ty = A[i].y;

	A[i].x = tx - g*ty;
	A[i].y = -h*tx + ty;
	}

Plot();
}
void Transform::RotateA(float angle)
{
int tx,ty;
for(int i=0;i<POINTS;i++)
	{
	tx = A[i].x;
	ty = A[i].y;

	A[i].x = tx*cos(angle) - ty*sin(angle);
	A[i].y = tx*sin(angle) + ty*cos(angle);
	}

Plot();

}

void Transform::RotateB(float angle)
{
int tx,ty;
for(int i=0;i<POINTS;i++)
	{
	tx = A[i].x;
	ty = A[i].y;

	A[i].x = tx*cos(angle) + ty*sin(angle);
	A[i].y = -tx*sin(angle) + ty*cos(angle);
	}

Plot();

}
void Transform::TranslateA(float sx,float sy)
{
for(int i=0;i<POINTS;i++)
	{
	A[i].x = A[i].x + sx;
	A[i].y = A[i].y + sy;
	}

Plot();
}
void Transform::TranslateB(float sx,float sy)
{
for(int i=0;i<POINTS;i++)
	{
	A[i].x = A[i].x - sx;
	A[i].y = A[i].y - sy;
	}
Plot();
}

void Transform::ScaleA(float sx,float sy)
{
for(int i=0;i<POINTS;i++)
	{
	A[i].x = A[i].x * sx;
	A[i].y = A[i].y * sy;
	}

Plot();
}

void Transform::ScaleB(float sx,float sy)
{
for(int i=0;i<POINTS;i++)
	{
	A[i].x = A[i].x * (1.0/sx);
	A[i].y = A[i].y * (1.0/sy);
	}
Plot();
}
void Transform::Plot()
{
cleardevice();
Screen();
setcolor(Color);
for(int i=0;i<POINTS-1;i++)
	{
	line(A[i].x+midx,A[i].y+midy,A[i+1].x+midx,A[i+1].y+midy);
	}
	line(A[i].x+midx,A[i].y+midy,A[0].x+midx,A[0].y+midy);
}
void Transform::Run(void)
{
char ch;
Plot();
while(1<2)
{
	if(kbhit())
	{
		ch=getch();

		switch(ch)
		{
		case '+': ScaleA(SFACT,SFACT);break;
		case '-': ScaleB(SFACT,SFACT);break;
		case '2': TranslateA(0,TFACT);break;
		case '8': TranslateB(0,TFACT);break;
		case '6': TranslateA(TFACT,0);break;
		case '4': TranslateB(TFACT,0);break;
		case '/': RotateA(RFACT);break;
		case '*': RotateB(RFACT);break;
		case 'C':
		case 'c': Color++;  Plot(); break;
		case '1': ShearA(0,SHFACT);break;
		case '3': ShearB(0,SHFACT);break;
		case '7': ShearA(SHFACT,0);break;
		case '9': ShearB(SHFACT,0);break;


		case 27:
		case 'x': exit(0);
		}

	}
}

}
Transform::Transform()
{
int gdriver = DETECT, gmode, errorcode;
initgraph(&gdriver, &gmode, "");
Screen();
midx = getmaxx()/2;
midy = getmaxy()/2;
Color = 1;

A[0].x=300/2;	A[1].x=350/2;	A[2].x=350/2;	A[3].x=325/2;
A[0].y=200/2;	A[1].y=250/2;	A[2].y=300/2;	A[3].y=300/2;
A[4].x=325/2;	A[5].x=275/2;	A[6].x=275/2;	A[7].x=250/2;
A[4].y=275/2;	A[5].y=275/2;	A[6].y=300/2;	A[7].y=300/2;
A[8].x=250/2;
A[8].y=250/2;

}

void Transform::Screen(void)
{
setcolor(LIGHTGREEN);
outtextxy(10,450,"Press +/- For Zoom In/Out");
outtextxy(10,460,"Press 8/2 For Up/Down");
outtextxy(330,450,"Press 4/6 For Left/Right");
outtextxy(330,460,"Press //* For Clock/Anti Cockwise");
outtextxy(10,470,"Press 7,9,1,3 For Shearing");
setcolor(LIGHTRED);
outtextxy(330,470,"Press x or ESC to Exit");
setcolor(LIGHTBLUE);
line(midx,0,midx,440);
line(0,midy,640,midy);

line(0,440,640,440);
}

void main(void)
{
Transform *obj = new Transform();
obj->Run();
}
