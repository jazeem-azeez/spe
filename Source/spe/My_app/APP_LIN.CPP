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

class sim_body *first,*head,*tempptr,*insert,*tempptr1;
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
int temp=0,c='n',collicnt=0;

set16bitpal();
MAX_SIM_BODY=1;
	ResetMouse();
	HideMouse();
	point3d cam1,zoom1;
	cam1.x=0,cam1.y=0,cam1.z=0;
	//trans1.x=0,trans1.y=0,trans1.z=0;
	zoom1.x=1,zoom1.y=1,zoom1.z=1;
	setcamzoom(&zoom1);
	setcamera(&cam1);

	camera_rot_on=TURN_ON;
	camera_zoom_on=TURN_ON;
	camera_trans_on=TURN_ON;
	//uses circular linked list
 do
 {
  head=(sim_body *)malloc(sizeof(sim_body));
  head->create_body();

  if(first!='\0')
   {
    tempptr->ptr=head;
    head->prev=tempptr;
    tempptr=head;
   }
  else
   {
    first=head;
    tempptr=head;
    head->prev='\0';
    head->ptr='\0';
   }

fflush(stdin);
glprintf("\n Want to create more (Y/N):");
c =getch();
MAX_SIM_BODY++;
}while(c=='y'||c=='Y');

tempptr->ptr=first;
first->prev=tempptr;

	clearviewport();
	//collition check & update physics;
	{
//	byte coll_flag=0;
cleardevice();
setbkcolor(BLACK);
setcolor(GREEN);
setwritemode(XOR_PUT);
int result=-1,mousesensex=10,mousesensey=10,drs;
tempptr=first;
   for(;c!='y';)
	{
//check input
	if(kbhit())
		c=getch();
	if(c=='c')
//	svbmp(0,0,maxx,maxy,)
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
tempptr=first;
	for(no=0;no<MAX_SIM_BODY;no++)
		{
		//s1[no].p.putdata3d(s1[no].o.p[0]);
		tempptr->drawbody();
		tempptr=tempptr->ptr;
		}
	delay(64);
//erase object
tempptr=first;
	for(no=0;no<MAX_SIM_BODY;no++)
	{
	tempptr->drawbody();
	 tempptr=tempptr->ptr;
	}
	showtime;
  //	showtime;
result=-1;

//detect collition
//tempptr=first;
tempptr1=tempptr;//sync pointers
/*
		for(no=0,result,collicnt=0;no<MAX_SIM_BODY;no++,tempptr=tempptr->ptr)
		for(temp=0,result=-1,tempptr1=first;temp<MAX_SIM_BODY;temp++,tempptr1=tempptr1->ptr)
			{
			if(no==temp)
				continue;
			result=tempptr->did_collide_with(tempptr1->o);
			moveto(50,50);
			bar(50,40,170,60);
			glprintf(" %d",result);
			if(result==0)
				{
//			playwav("colli.wav");
			collicnt++;
			tempptr->preprocesscollition(tempptr1->p);
				}

			}
//sound/effects
for(;collicnt>0;collicnt--,sound(500),delay(64),nosound());
nosound();
//process collided objects
//draw object
*/
wait();
tempptr=first;
	for(no=0;no<MAX_SIM_BODY;no++)
		{
		//s1[no].p.putdata3d(s1[no].o.p[0]);
		tempptr->drawbody();
		tempptr=tempptr->ptr;
		}
	delay(64);
//erase object
tempptr=first;
	for(no=0;no<MAX_SIM_BODY;no++)
	{tempptr->drawbody();
	 tempptr=tempptr->ptr;
	}
	showtime;
	/*
tempptr=first;
	for(no=0;no<MAX_SIM_BODY;no++,tempptr=tempptr->ptr)
		    {

		    if(tempptr->collitionstate==1)//<-look terminator
			tempptr->processcollition();
		    else
			tempptr->updatephy();

		    tempptr->updategl();
		    }
	*/
	}

	}

	tempptr=first;
	tempptr=tempptr->ptr;
	while(tempptr!=first)
	{
	tempptr1=tempptr;
	tempptr=tempptr->ptr;
	free(tempptr1);
	}
	free(tempptr);

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


