# include <gui.cpp>
# include <world.cpp>
# define KEYBOARD -1

/////////////////////////////////////////
# include <pallete.cpp>
///////////////////////////////////
void keyboard();
void help()	 ;
void database(); 
void controls();
void config_display();
void mouse_btn();
void simulate();
void quit();
void show_log();
void extapp();
void config();

//world w;

void main()

{
int flag=0;
initgui();
startlog();
m.hidemouseptr();
console c1("MAIN.CON");
m.showmouseptr();
while(c!=ESC)
{			  if(kbhit())
				c=letter();
switch(flag=c1.choice())

	{
	case 0:quit();				break;
	case 1:simulate();			break;
	case 2:config();			break;
	case 3:show_log();			break;
	case 4:extapp();			break;
	case KEYBOARD:keyboard();	break;
	}
	if(flag!=0)
	{
	flag=0;
	wait();
	c1.show();
	}
}
getch();
m.hidemouseptr();
closegraph();
}

void keyboard()
{
outtextxy(200,200,"keyboard");
}

void help()
{
svbmp(0,0,getmaxx(),getmaxy(),"buf.bmp");
ldbmp(0,0,"help.bmp");
getch();
ldbmp(0,0,"buf.bmp");
}

void database()
{
svbmp(0,0,getmaxx(),getmaxy(),"buf.bmp");
restorecrtmode();
m.hidemouseptr();
log("database.exe");
{
   int result;

   clrscr();
   result = spawnl(P_WAIT,"database.exe", NULL);
   if (result == -1)
   {
      perror("Error from spawnl");

   }
}
setgraphmode(getgraphmode());
ldbmp(0,0,"buf.bmp");
m.showmouseptr();
}

void controls()

{
 ldbmp(0,200,"controls.bmp");
 getch();
}

void config_display()
{
console c1("disppty.con");
int c=getgraphmode();
while(kbhit()!=ESC)
{
	switch(c1.choice())
	{
		case 0:setgraphmode(c);
		case 1:setgraphmode(VGAHI);		break;
		case 2:setgraphmode(VGAMED);		break;
		case 3:setgraphmode(VGALO);		break;
		case 4:setgraphmode(c);
		case KEYBOARD:keyboard();		break;
	}
	wait();
	c1.show();
}
}

void mouse_btn()
{
console c1("mouseppty.con");
int t=m.clickbtn;
//setwritemode(XOR_PUT);
while(kbhit()!=ESC)
{
	switch(c1.choice())
	{
		case 0:		return;
		case 1:m.togglemouse();
			outtextxy(m.x,m.y,"x");
			break;
		case 2:return;
		case 3:if(t!=m.clickbtn)
			 m.togglemouse();			break;
		case KEYBOARD:keyboard();		break;
	}
//	wait();
//	c1.show();
}

}


void simulate()
{
console c1("simulate.con");
w.list();	
while(kbhit()!=ESC)
{
	switch(c1.choice())
	{
		case 0:return;
		case 1:return;
	  	case 2:w.load();			break;
	 	case 3:w.delobj();			break;
		case 4:database();			break;
	 	case 5:w.list();			break;
		case 6:help();				break;
		case KEYBOARD:keyboard();		break;
	}
	w.list();	
	c1.show();
}

}
void quit()
{
outtextxy(200,200,"quit");
closegraph();
closelog();
_cexit();

}
void show_log()
{
outtextxy(200,200,"Opening Log");
showlog();
}
void extapp()
{
svbmp(0,0,getmaxx(),getmaxy(),"buf.bmp");
m.hidemouseptr();
restorecrtmode();
cout<<"Enter the external module to be run: ";
cin>>msg;
log(msg);
system(msg);
setgraphmode(getgraphmode());
ldbmp(0,0,"buf.bmp");
m.showmouseptr();
}
void config()
{
console c1("config.con");
while(kbhit()!=ESC)
{
	switch(c1.choice())
	{
		case 0:return;
		case 1:return;
		case 2:help();				break;
		case 3:colorchooser();			break;
		case 4:config_display();		break;
		case 5:controls();			break;
		case 6:mouse_btn();			break;
		case 7:extapp();			break;
		case KEYBOARD:keyboard();		break;
	}
	wait();
	c1.show();
}


}

