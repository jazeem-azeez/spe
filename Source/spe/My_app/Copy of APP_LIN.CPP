#include<c:\spe\My_app\simu.cpp>
#include<c:\spe\My_app\config.cpp>
#include<c:\spe\My_app\helper.cpp>
#include<c:\spe\My_app\logger.cpp>
#include<c:\spe\My_app\db.cpp>
simulator();
ShowLog();
Database();
Configure();
Help();

void introduction();

class sim_body s1[3];
	float dx,dy,dz;

ENTERCORE();
int Application()
{
	short c;
	introduction();
	bcm c1;
	c1.initiate("Welcome.bcm");
	c1.show();
	L1:
	c=c1.choice();
	if(c==1)
		ENTERCORE();
	else if((c>=0&&c<=255))
		{return 0;}
	else
		return -1;
	return 0;
}

void introduction()
{
	setcolor(GREEN);
	glprintf("Hello World \n\n\tWelcome to the world of physics please wait ...");
	sleep(1);
	clearviewport();
	Enlarge(400,200,"A Simple Physics Engine");
	Reduce(400,200,"A Simple Physics Engine");
	Enlarge(400,300,"BY");
	Reduce(400,300,"BY");
	Enlarge(400,400," Abhi & Jazeem ");
	Reduce(400,400, "Abhi  &  Jazeem");
	setcolor(LIGHTBLUE);
	Enlarge(400,300,"Physicode");
	playwav("Loading.wav");
	delay(500);
	setcolor(WHITE);
}

int ENTERCORE()
{
bcm c1;
char str[64],c;
c1.initiate("Xwindow.bcm");
for(;;)
	{
	c1.show();
	c=c1.choice();
	switch(c)
		{
		case 0:{ cleardevice(),Reduce(400,300,"Logoff");
		return 0;}
		case 1:simulator();break;
		case 2:ShowLog();break;
		case 3:Database();break;
		case 4:Configure();break;
		case 5:helpnavigator("HELP.bcm");;break;
		default:break;
		}
	}

}


int loadreactor()
{
  setupreactor();
  return 0;
}
int no=0;
int reactor()
{
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

	glscanf("%d",&MAX_SIM_BODY);
	for(int no=0;no<MAX_SIM_BODY;no++)
	       {	s1[no].create_body();
	       }

	clearviewport();
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
wait();
	for(no=0;no<MAX_SIM_BODY;no++)
		{
		s1[no].p.putdata3d(s1[no].o.p[0]);
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
for(;collicnt>0;collicnt--,sound(500),delay(64),nosound());
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
	return 1;
}

int simulator()
{
clearviewport();
settextstyle(0,0,1);
setlinestyle(0,0,1);
reactor();
//cleardevice();
//loadreactor();
/*
bcm c1;
char c;
c1.initiate("simulator.bcm");
for(;;)
	{
	c1.show();
	c=c1.choice();
	switch(c)
		{
		case 0:{ cleardevice();
		return 0;}
		case 1:reactor();break;
		case 2:loadreactor();break;
		case 3:cleardevice();break;
		case 4:moveto(106,500);
		       outtext("Enter the new no of objects: ");
		       glscanf("%d",&no);
			break;
		default:break;
		}
	}

*/
return 1;
}

ShowLog()
{
clearviewport();
sleep(1);
return 0;
}

Database()
{
clearviewport();
DB();
return 0;
}


