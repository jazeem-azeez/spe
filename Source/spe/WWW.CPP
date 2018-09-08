int no;
float _xscale,_yscale,_zscale;
#include <headerli.cpp>
#include <c:\spe\MY_APP\helper.cpp>
#include <c:\spe\my_app\simu.cpp>
int loadreactor()
{
MAX_SIM_BODY=2;
setupreactor();
return 1;
}

	class sim_body s1[2];
	float dx,dy,dz;


int	reactor()

{
// camara
loadreactor();
ResetMouse();
HideMouse();
point3d cam1,zoom1;
cam1.x=0,cam1.y=0,cam1.z=0;
//trans1.x=0,trans1.y=0,trans1.z=0;
zoom1.x=1,zoom1.y=1,zoom1.z=1;
setcamzoom(&zoom1);
setcamera(&cam1);

camera_rot_on=TURN_ON;
camera_zoom_on=TURN_ON ;
camera_trans_on=TURN_ON;

clearviewport();
	for( no=0;no<MAX_SIM_BODY;no++)
		{
		s1[no].create_body();
		getch();
		 }
	//collition check & update physics;
	{

int temp=0,c='n',collicnt=0;
//	byte coll_flag=0;
cleardevice();
setbkcolor(BLACK);
//setcolor(GREEN);
setwritemode(XOR_PUT);
int result=-1,mousesensex=10,mousesensey=10,drs;
   for(;c!='y';)
	{


//check input
	if(kbhit())
		c=getch();
	drs=1;
	dx=((1+_x)/(mousesensex)),dy=((1+_y)/(mousesensey));
	dz=(dx+dy)/2;
	if (_bios_keybrd(_KEYBRD_SHIFTSTATUS) & CAPS_ON)
	{
		outtextxy(680,10,"changing view");
		if (_bios_keybrd(_KEYBRD_SHIFTSTATUS) & INSRT_ON)
		drs=-1;
		if(_bios_keybrd(_KEYBRD_SHIFTSTATUS) & CTRL)
		rotcamera(&cam1,dx*drs,0,0);
		if (_bios_keybrd(_KEYBRD_SHIFTSTATUS) & ALT)
		rotcamera(&cam1,0,dy*drs,0);
		if((_bios_keybrd(_KEYBRD_SHIFTSTATUS) &RIGHT_SHIFT)||(_bios_keybrd(_KEYBRD_SHIFTSTATUS) &LEFT_SHIFT))
		rotcamera(&cam1,0,0,dz*drs);

		bar(1,5,300,20);
		moveto(2,10);
		glprintf("dx-> %.2f x dy-> %.2f x dz-> %.2f",dx,dy,dz);
	}
	if (!(_bios_keybrd(_KEYBRD_SHIFTSTATUS) & CAPS_ON))
		bar(680,5,790,20);

//code repated to reduce flickering
//draw object
//wait();
	for(no=0;no<MAX_SIM_BODY;no++)
		{
//		s1[no].p.putdata3d(s1[no].o.p[0]);
		s1[no].drawbody();
		}
	delay(64);
//erase object
	for(no=0;no<MAX_SIM_BODY;no++)
	s1[no].drawbody();
	showtime;
  //	showtime;
result=-1;

//detect collition
		for(no=0,result,collicnt=0;no<MAX_SIM_BODY;no++)
		for(temp=0,result=-1;temp<MAX_SIM_BODY;temp++)
			{
			if(no==temp)
				continue;
			result=s1[no].did_collide_with(s1[temp].o);
			moveto(50,50);
			bar(50,40,170,60);
			glprintf(" %d",result);
			if(result==0)
				{
//			playwav("colli.wav");
			collicnt++;
			s1[no].preprocesscollition(s1[temp].p);
				}

			}
//sound/effects
for(;collicnt>0;collicnt--,sound(50),delay(64),nosound());
nosound();
//process collided objects
//draw object
wait();
	for(no=0;no<MAX_SIM_BODY;no++)
		{
		s1[no].drawbody();
		}
	delay(64);
//erase object
	for(no=0;no<MAX_SIM_BODY;no++)
	s1[no].drawbody();
	showtime;

	for(no=0;no<MAX_SIM_BODY;no++)
		    {

		    if(s1[no].collitionstate==1)//<-look terminator
			s1[no].processcollition();
		    else
			s1[no].updatephy();

		    s1[no].updategl();
		    }
	}

	}
	ShowMouse();
	cleardevice();
	return 1;
	}
int main()
{
	int no;
	//sysinfo();
	SetMode(_800x600,1);
	initsvga();
	InitMouse();
	ShowMouse();/*
	point3d p1,p2;
	p1.x=1.0,p1.y=3.0,p1.z=2.0;
	p2.x=1.0,p2.y=3.0,p2.z=2.0;*/
	setup_float_exception();

	if(0!=glsetup(0))
	{
	closegraph();
	textmode(0x03);
	printf("\nSorry Please Contact your Administrator");
	getch();
	return 1;
	}

	FLOAT_EXCEPTION
	{
	void far *buf[8];
	setcolor(GREEN);
	line (200,100,600,500);
	save_screen_area_mem(200,100,600,500,buf);
	getch();
	clearviewport();
	restore_screen_area_mem(200,100,600,500,buf,0);
	getch();
	}
	glprintf("\nExiting...");
	getch();
	textmode(0x03);
	closegraph();
	return 1;
	}
