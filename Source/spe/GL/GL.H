# include <graphics.h>
# include <c:\spe\lib\lib.h>
# include <c:\spe\GL\glrtns.h>
# include <c:\spe\GL\image.h>
# include <c:\spe\GL\adtvs.h>
# include <c:\spe\GL\mathd.h>

#include <bios.h>
#include <ctype.h>

#define RIGHT_SHIFT  	0x01
#define LEFT_SHIFT   	0x02
#define CTRL   			0x04
#define ALT    			0x08
#define CAPS_ON         0x40
#define INSRT_ON 		0x80
/*
==================================GL DESIGN/ARCHITECTURE==========================
||						     ==========================							||
||																		||
||						          ------------------------------------ GL-------------------------			||
||							|		|		 /	      \			| 			||
||							|		|		|		|					||
||	----------------------------------------------lib.h		mathd.h		glroutines	additives.cpp	|	||
||	|						|		|			|		|	|	||
||	|						|		|		        BCM.h		|	|	||
||                  ---------------------------------    dev.h		math3d.h			        cam	|       ||
||		|	|	|		   /    \			------------------------------- image.cpp	||
||		|	|	|		  |	|			|		|		|		||
||		|	|	|	disk.cpp	mouse.cpp		|		|		|		||
||	VESA.h	|	|							|		|		|		||
||			|	|						Xbitmap.cpp	pcx.h		bmp.h		||
||		  sound.cpp	processor.cpp										||
|_________________________________________________________________________|
=======================================================================================
glroutines //glrtns
additives //adtvs
*/
/*

*/
point3d Camx,Zoomx,Transx;

gllineobject obj1,obj2;

int _2dgltestrun()
{
int x,y;
char c[2];
for(int i=0;i<16;i++)
	{
	wait();
	circle(midx,midy,10);
	bar(midx-10,midy-10,midx+10,midy+10) ;
	rectangle(midx-10,midy-10,midx+10,midy+10);
	setcolor(i);
	LOCKON_rectangle(midx,midy);
	explode_rectangle(midx-15,midy-15,midx+15,midy+15);
	}
for(i=0;i<=maxx*maxy;i++)
	putpixel(rand()%maxx,rand()%maxy,rand()%16);
return	-1;
}

int _3dgltestrun()
{
HideMouse();
point3d cam1,zoom1;
cam1.x=0,cam1.y=0,cam1.z=0;
//trans1.x=0,trans1.y=0,trans1.z=0;
zoom1.x=1,zoom1.y=1,zoom1.z=1;
setcamzoom(&zoom1);
setcamera(&cam1);
//setcamtrans(&trans1);
cleardevice();

glprintf("\t\tTesting GL  for possible errors");
glprintf("\nThe test is X&Cube rotating");
glprintf("\nPress any key to start ");
glprintf("\npress y if you see the test sucessful");
readobj("Xcube.gld",obj1);
readobj("Xglx.gld",obj2);
aotrans(obj1,-obj1.cr.x,-obj1.cr.y,-obj1.cr.z);
aoscale(obj1,80,80,80);
aotrans(obj2,-obj2.cr.x,-obj2.cr.y,-obj2.cr.z);
aoscale(obj2,9,9,9);
setwritemode(XOR_PUT);
camera_rot_on=TURN_ON;
camera_zoom_on=TURN_ON ;
camera_trans_on=TURN_ON;
drawaxis(GREEN);

for(;!kbhit();)
{
rotcamera(&cam1,0,2,2);
aorot(obj2,2,2,0);
drawobj(obj1,11);
drawobj(obj2,15);

delay(16);
showtime;
drawobj(obj2,15);
drawobj(obj1,11);

}
if('y'==getch())
{
clearviewport();
outtextxy(370,310,"3dGL [status- ok]");
delay(500);
return 0;}
else
return -1;
}

int glsetup(int c)
{
Camx.x=0,Camx.y=0,Camx.z=0;
setcamera(&Camx);
Zoomx.x=1.0,Zoomx.y=1.0,Zoomx.z=1.0;
setcamzoom(&Zoomx);
Transx.x=1.0,Transx.y=1.0,Transx.z=1.0;
setwritemode(XOR_PUT);
if(c)
{
      _2dgltestrun();
      getch();
      cleardevice();
return(_3dgltestrun());
}
return 0;
}