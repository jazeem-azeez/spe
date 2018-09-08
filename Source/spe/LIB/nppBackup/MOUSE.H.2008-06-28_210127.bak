#ifndef MOUSEH_H
#define MOUSEH_H

#include <process.h>
#include <dos.h>
#define XMAX 800
#define YMAX 600
typedef unsigned int WORD;
typedef unsigned char BYTE;

static void huge MouseHandler();
void DrawCursor(BYTE);
int InitMouse();
int CheckMouse();
int ResetMouse();
void PutMousePixel(WORD,WORD);
void ShowMouse();
void HideMouse();
/*
NOTE:
Mouse drivers dont update mouse cursors in SVGA modes
and hence we need to explicitly draw the mouse cursor
and install a mouse handler to recognize mouse events.
*/


int flag=0;
unsigned int _x=0,_y=0,_b=0;    // x y and button variable
int _xminm=0,_yminm=0,_xmaxm=800,_ymaxm=600;
BYTE _showMouseStatus=1,_wrapAround=0;
const BYTE *_cursor;
const BYTE *_tool;
const BYTE *_temp;
BYTE _arrow[]=
			{
			1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
			1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
			1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
			1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
			1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
			1, 1, 0, 1, 1, 1, 1, 1, 0, 0,
			1, 1, 0, 0, 1, 1 ,1, 1 ,1, 0,
			1, 0, 0, 0 ,0, 1, 1, 1, 1, 1,
			0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
			0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
		       };

BYTE _eraser[]=         {
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0 ,0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		       };

BYTE _cross[]=         {
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
			1, 1, 1, 1, 0, 0, 1, 1, 0, 0,
			1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
			1, 1, 0, 1, 1, 1, 0, 0, 0, 0,
			1, 1, 0, 1, 1, 0, 0, 0, 0, 0,
			1, 1, 1, 1, 0, 0 ,0, 0, 0, 0,
			1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
			1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		       };
BYTE _free[]=         {
			1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
			1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
			1, 0, 0, 0, 1, 0, 0, 0, 0, 0,
			1, 0, 0, 1, 0, 0, 0, 0, 0, 0,
			1, 0, 1, 0, 0, 0, 0, 0, 0, 0,
			1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
			1, 0, 0, 0, 0, 0 ,0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		       };
BYTE _caret[]=         {
			1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
			0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 1, 0, 0, 0, 0 ,0, 0, 0, 0,
			0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
			1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
		       };

BYTE _fill[]=         {
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 1, 1, 1, 0, 0, 0, 0, 0,
			0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
			0, 1, 1, 1, 1, 1, 0, 0, 0, 1,
			0, 1, 1, 1, 0, 1, 0, 0, 0, 1,
			0, 1, 1, 1, 0, 1, 0, 0, 0, 1,
			0, 0, 1, 1, 0, 1, 1, 1, 1, 1,
			0, 0, 0, 1, 0, 1, 1, 1, 1, 1,
			0, 0, 0, 1, 0, 1, 1, 1, 1, 1,
			0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
		       };
BYTE _brush[]=         {
			1, 0, 1, 0, 0, 0, 0, 0, 0, 0,
			0, 1, 0, 0, 1, 0, 0, 0, 0, 0,
			1, 0, 1, 1, 0, 0, 1, 1, 0, 0,
			0, 0, 0, 0, 1, 1, 1, 1, 1, 0,
			1, 1, 1, 1, 0, 1, 1, 1, 1, 0,
			0, 0, 0, 0, 0, 1, 0, 0, 1, 0,
			1, 0, 0, 0, 0, 1, 0, 0 ,1, 0,
			0, 0, 0, 0, 0, 1, 0, 0, 1, 0,
			0, 0, 0, 0, 0, 1, 0, 0, 1, 0,
			0, 0, 0, 0, 0, 1, 1, 1, 1, 0,
		       };

BYTE _larrow[]=         {
			1,1,1,0,1,1,1,1,1,1,
			1,0,0,1,0,0,0,0,1,0,
			1,0,0,0,0,1,1,1,0,0,
			0,1,0,0,0,0,1,0,0,0,
			1,0,0,0,0,0,0,1,0,0,
			1,0,1,0,0,0,0,0,1,0,
			1,0,1,1,0,0,0,0,0,1,
			1,0,1,0,1,0,0,0,0,1,
			1,1,0,0,0,1,0,0,0,1,
			1,0,0,0,0,0,1,1,1,1,
		       };



//----------------------------------------------

void HideMouse()
 {
  if(!_showMouseStatus)  return;
  DrawCursor(0);
  _showMouseStatus=0;
 }

static void far _loadds MouseHandler()
{
	int x1=0,y1=0;
	static int inMouseHandler;
	if(inMouseHandler)return;
	inMouseHandler=1;

	//ASSEMBLY BLOCK
	_asm mov _b,bx
	_asm mov ax,0x0b
	_asm int 0x33
	_asm mov x1,cx
	_asm mov y1,dx
	//ASSEMBLY BLOCK ENDS

	x1+=_x;	y1+=_y;
	if(_wrapAround)
	{
		if(x1>=_xmaxm)x1-=_xmaxm;
		else if(x1<_xminm)x1+=_xmaxm;
		if(y1>=_ymaxm)y1-=_ymaxm;
		else if(y1<_yminm)y1+=_ymaxm;
	}
	else
	{
		if(x1>=_xmaxm)x1=_xmaxm-1;
		else if(x1<_xminm)x1=_xminm;
		if(y1>=_ymaxm)y1=_ymaxm-1;
		else if(y1<_yminm)y1=_yminm;
	}
	_x=x1;
	_y=y1;
	if(_showMouseStatus)
		  DrawCursor(1);
	inMouseHandler=0;
}

//----------------------------------------------
void DrawCursor(BYTE mode)
{
	unsigned int i,j,t=0;
	BYTE c;
	static int inDrawCursor=0;
	static WORD x=0,y=0;
	if(inDrawCursor)return;
	inDrawCursor=1;
	if(mode<2)
	{
		for(i=0;i<10;i++)
			for(j=0;j<10;j++)
				if(_cursor[t++])
					PutMousePixel(x+j,y+i);
	}
	x=_x;
	y=_y;
	if(mode)
	{
		t=0;
		for(i=0;i<10;i++)
			for(j=0;j<10;j++)
				if(_cursor[t++])
					PutMousePixel(x+j,y+i);
	}
	inDrawCursor=0;
}

//-----------------------------------------------------

int InitMouse()
{

  unsigned int segmt=FP_SEG(&MouseHandler);
  unsigned int off=FP_OFF(&MouseHandler);
  unsigned int buttons;
  int m,n;
  m=CheckMouse();
  if(m==0)
  {
	textmode(0x3);
	printf("Mouse driver not installed.  Exiting\n");
	getch();
	exit(1);
  }
  else
	buttons=ResetMouse();
	_cursor=(BYTE *)_arrow;

	//ASSEMBLY BLOCK
	_asm mov cx,31      //cx takes event mask
	_asm mov dx,off     //which specifies for what all
	_asm mov es,segmt   //events the mouse handler is called
	_asm mov ax,0x0c    //11111 i.e movement,left press, left release
	_asm int 0x33       //right press and right release
	_asm mov al,0x0f
	_asm mov cx,1
	_asm mov dx,1
	_asm int 0x33
	//ASSEMBLY BLOCK ENDS

	_x=0;
	_y=0;
	MouseHandler();
	ShowMouse();
	return buttons;
}
//--------------------------------------------------------

int CheckMouse()
{
	unsigned char far *f=(unsigned char far *)getvect(0x33);
	unsigned buttons;
	if(f==0 || *f==0xcf)
		return 0;
	return 1;
}
//---------------------------------------------------------
int ResetMouse()
{
	int buttons;

	//ASSEMBLY BLOCK
	_asm mov al,0x00
	_asm int 0x33
	_asm mov buttons,bx
	//ASSEMBLY BLOCK ENDS

	return buttons;
}

//-------------------------------------------------

void ShowMouse()
{
	if(_showMouseStatus)return;
	DrawCursor(2);
	_showMouseStatus=1;
}
//-----------------------------------------

void PutMousePixel(WORD x,WORD y)
{
	if(x>=XMAX || y>=YMAX)return;
	PutPixel(x,y,0xffff^GetPixel(x,y));
	//here the color 255-present color is used
	//to draw mouse. It is same as 255 XOR color
	//or we can use abs(255-colorval) but XOR is faster
	//hence use it.
}

//--------------------------------------

#endif