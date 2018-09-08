int no;
#include <headerli.cpp>
#include <c:\spe\MY_APP\helper.cpp>
#include <c:\spe\my_app\simu.cpp>
int	reactor()

	{

	class sim_body s1[2];

	MAX_SIM_BODY=2;
clearviewport();
	for( no=0;no<MAX_SIM_BODY;no++)
		s1[no].create_body();
	//collition check & update physics;
	{

int temp=0,c='n';
//	byte coll_flag=0;
cleardevice();
setbkcolor(BLACK);
//setcolor(GREEN);
setwritemode(XOR_PUT);
HideMouse();
   for(;c!='y';)
	{
//draw object
	for(no=0;no<MAX_SIM_BODY;no++)
		{
		s1[no].drawbody();
		}
	delay(64);
//erase object
	for(no=0;no<MAX_SIM_BODY;no++)
	s1[no].drawbody();
	showtime;
//check input
	if(kbhit())
	c=getch();
  //	showtime;
  int result=-1;

//detect collition
		for(no=0,result;no<MAX_SIM_BODY;no++)
			{
			if(no==temp)
				continue;
			result=s1[no].did_collide_with(s1[temp].o);
			moveto(50,50);
			delay(64);
			bar(50,40,170,60);
			glprintf(" %d",result);
			if(result==0)
				{
				bar(20,10,170,30);
				outtextxy(20,20,"Collition occured");
				s1[no].preprocesscollition(s1[temp].p);
				}
			if(result==1)
			{
			bar(20,10,170,30);
			delay(64);
			}

			}
//process collided objects
	for(no=0;no<MAX_SIM_BODY;no++)
		    {
		    if(s1[no].collitionstate==1)
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
//	exit(3);

	FLOAT_EXCEPTION
	{
//	glprintf("%f",distanceBetween(p1,p2));
	selectcolor();
//	reactor();
	}
	glprintf("\nExiting...");
	getch();
	textmode(0x03);
	closegraph();
	return 1;
	}
