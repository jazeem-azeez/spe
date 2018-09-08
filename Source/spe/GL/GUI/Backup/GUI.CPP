 # include "graphics.h"
# include "math.h"
# include "stdio.h"
# include "dos.h"
# include "conio.h"
# include "string.h"
# include "process.h"
# include "fstream.h"
//# include "bmpimage.h"
//# include "mymouse.h"
//# include "bmpimage.h"
# include "time.h"
# include "console.cpp"
# include "svgautil.c"

# define NORMAL    0
# define EXTENDED  1


#define NOKEY	 0
//key values defined has a sum up of 256
#define UPKEY      328
#define DOWNKEY    336
#define LEFTKEY    331
#define RIGHTKEY   333
#define UPAGE      329
#define DPAGE      337
#define INS        338
#define DEL        339
#define HOME       327
#define END        335
#define ESC        27
#define ENTER      13
#define BACKSPACE  8
#define SPACEBAR   32
#define F1         315
#define F2         316
#define F3         317
#define F4         318
#define F5         319
#define F6         320
#define F7         321
#define F8         322
#define F9         323
#define F10        324
#define ALT_F      289
#define ALT_E      274
#define ALT_R      275
#define ALT_C      302
#define ALT_X      301
#define ALT_H      291
#define ALT_N      305
# define CTRL_RIGHT 371
# define CTRL_LEFT  372

# define NO 0
# define YES 1
# define NONE -1
# define MAX_MENU 20

#define initialize_loop		for(;;){
#define close_loop			if(loop_flag==BREAK)break;}
#define break_loop			break;

int ldsx=0,ldsy=0,ldex=0,ldey=0,steps=0;
float ldstep,ldbarsize;
int loop_flag=0  ;


char byte;
int gdriver = DETECT, gmode, errorcode;
int maxx = 0, maxy = 0,COLOR=BLACK,logstatus=0;
char msg[80];
int movedx,movedy;
int letw,leth;
int visualpage,activepage,pagelimit;
int setsvgamode;
int huge DETECTSVGA(void)
{
	detectgraph(&gdriver, &gmode);

	return (setsvgamode);

}


void wait()
{
       asm    mov dx,3DAh
       l1:
	   asm   in al,dx
	   asm   and al,08h        //wait for vertical retrace to occur
	   asm   jnz l1            // to avoid or reduce flickering
       l2:
	   asm   in al,dx
	   asm   and al,08h
	   asm  jz  l2
}

#define BREAK 1



int ldbar(int xtnd)
{
ldbarsize+=ldstep;
if((ldbarsize+ldsx)>ldex)
return 1;
//printf("\n%f ,%f",ldstep,ldbarsize);
rectangle(ldsx,ldsy,ldex,ldey);
if(xtnd==0)
{
setcolor(WHITE);
setfillstyle(SOLID_FILL,WHITE);
bar(ldsx,ldsy,ldex,ldey);
}
setfillstyle(SOLID_FILL,LIGHTBLUE);
bar(ldsx+1,ldsy+1,ldsx+ldbarsize,ldey-1);
return 0;
}

void setup_ldbar(int x,int y,int ex,int ey,int stps)
{
ldsx=x,ldsy=y,ldex=ex,ldey=ey,steps=stps   ;
ldbarsize=1;
ldstep=(float)(ldex-ldsx)/steps;
ldbar(0);
}

int colortoggle(int flag)
{
int c=getbkcolor(),bk=getcolor();
setcolor(c);
setfillstyle(SOLID_FILL,c);
if(flag!=0)
{
setbkcolor(bk);
}
return c;
}
   
/***************************< Digital Num. Finder >*************************/
void digit_write(int left,int top,int NUM)
{
   setcolor(10);
   switch(NUM)
   {
   case 1:
	  line(left+11,top+2,left+11,top+9);
	  line(left+11,top+11,left+11,top+18);
	  break;
   case 2:
	   line(left,top,left+10,top);
	   line(left+11,top+2,left+11,top+9);
	   line(left+1,top+10,left+9,top+10);
	   line(left-1,top+11,left-1,top+18);
	   line(left,top+20,left+10,top+20);
	   break;
   case 3:
	   line(left,top,left+10,top);
	   line(left+11,top+2,left+11,top+9);
	   line(left+1,top+10,left+9,top+10);
	   line(left+11,top+11,left+11,top+18);
	   line(left,top+20,left+10,top+20);
	   break;
   case 4:
	   line(left-1,top+2,left-1,top+9);
	   line(left+11,top+2,left+11,top+9);
	   line(left+1,top+10,left+9,top+10);
	   line(left+11,top+11,left+11,top+18);
	   break;
   case 5:
	   line(left,top,left+10,top);
	   line(left-1,top+2,left-1,top+9);
	   line(left+1,top+10,left+9,top+10);
	   line(left+11,top+11,left+11,top+18);
	   line(left,top+20,left+10,top+20);
	   break;
   case 6:
	   line(left,top,left+10,top);
	   line(left-1,top+2,left-1,top+9);
	   line(left+1,top+10,left+9,top+10);
	   line(left-1,top+11,left-1,top+18);
	   line(left+11,top+11,left+11,top+18);
	   line(left,top+20,left+10,top+20);
	   break;
   case 7:
	   line(left,top,left+10,top);
	   line(left-1,top+2,left-1,top+9);
	   line(left+11,top+2,left+11,top+9);
	   line(left+11,top+11,left+11,top+18);
	   break;
   case 8:
	   line(left,top,left+10,top);
	   line(left-1,top+2,left-1,top+9);
	   line(left+11,top+2,left+11,top+9);
	   line(left+1,top+10,left+9,top+10);
	   line(left-1,top+11,left-1,top+18);
	   line(left+11,top+11,left+11,top+18);
	   line(left,top+20,left+10,top+20);
	   break;
   case 9:
	   line(left,top,left+10,top);
	   line(left-1,top+2,left-1,top+9);
	   line(left+11,top+2,left+11,top+9);
	   line(left+1,top+10,left+9,top+10);
	   line(left+11,top+11,left+11,top+18);
	   line(left,top+20,left+10,top+20);
	   break;
   case 0:
	   line(left,top,left+10,top);
	   line(left-1,top+2,left-1,top+9);
	   line(left+11,top+2,left+11,top+9);
	   line(left-1,top+11,left-1,top+18);
	   line(left+11,top+11,left+11,top+18);
	   line(left,top+20,left+10,top+20);
	   break;
   }
  setcolor(WHITE);
}
void digital(int x,int y,int n)
{

int a,b,c,d;
 if(n<10)
 {
 digit_write(x+15,y,0);
 digit_write(x+30,y,n);
 }

 if(n<100 && n>9)
 {
  a=n/10;b=n%10;
  digit_write(x+15,y,a);
  digit_write(x+30,y,b);
 }

  if(n<1000 && n>99)
 {
  a=n/100;
  b=n%10;
  c=(n-((a*100)+b))/10;
  digit_write(x+15,y,a);
  digit_write(x+30,y,c);
  digit_write(x+45,y,b);
 }

  if(n<10000 && n>999)
 {
  a=n/1000;
  b=n%10;

  c=(n-((a*1000)+b))/100;
  d=(n-((a*1000)+b+c*100))/10;

  digit_write(x,y,a);
  digit_write(x+15,y,c);
  digit_write(x+30,y,d);
  digit_write(x+45,y,b);
 }

  if(n<20000 && n>=10000)
 {
  a=n/10000;
  b=n%10;
  c=(n-((a*10000)+b))/1000;
  d=(n-((a*10000)+b+c*1000))/100;
  int e=(n-((a*10000)+b+(c*1000)+(d*100)))/10;
  digit_write(x,y,a);
  digit_write(x+15,y,c);
  digit_write(x+30,y,d);
  digit_write(x+45,y,e);
  digit_write(x+60,y,b);
}
}



FILE *out;
char datebuf[9];
char timebuf[9];
int logstatues;

void log(char msg[])
{
_strtime(timebuf);
    fputs("\nLog:->", out);
    fputs(timebuf,out);
    fputs("\n",out);
    fputs(msg,out);
    fputs("\n",out);
}

void shadowtxt(char Txt[],int TxtX,int TxtY,int TxtCol)
{
  setcolor(0);outtextxy(TxtX+1,TxtY+1,Txt);
  setcolor(TxtCol);outtextxy(TxtX,TxtY,Txt);
}

void showlog()
{
rewind(out);
while (!feof(out))
cout<<fgetc(out);
}

int startlog()
{
_strdate(datebuf);
_strtime(timebuf);
if ((out = fopen("logfile.log", "wt"))
    == NULL)
{
   fprintf(stderr, "Cannot open input file.\n");
   return 1;
}
logstatus=0;
//while (!feof(in))
   log("Started");
   return 0;
}

int closelog()
{
log("Closed");
fclose(out);
return 0;
}

int letter(void)
{
	union {
		unsigned int reset;
		unsigned char character[2];
	};
	reset = NOKEY;
	character[NORMAL] = (char)getch();
	if (!character[NORMAL])
		character[EXTENDED] = (char) getch();

	return reset+256; //correction
}

int initgui(int gdriver= VGA, int gmode=VGAMED)

{
	/* request auto detection *//*
	setsvgamode=SVGA640x480x256;

	installuserdriver("Svga256",DETECTSVGA);
				      */
	initgraph(&gdriver, &gmode, "");
	/* read result of initialization */

	errorcode = graphresult();
	if (errorcode != grOk)  /* an error occurred */
	{
	   printf("Graphics error: %s\n", grapherrormsg(errorcode));
	   printf("Press any key to halt:");
	   getch();
	   exit(1); /* terminate with an error code */
	}
	settextjustify(LEFT_TEXT, CENTER_TEXT);
	letw=textwidth("W");
	leth=textheight("W");
	maxx=getmaxx(),maxy=getmaxy(),COLOR=getmaxcolor();
	visualpage=activepage=0;
	m.initmouse();
	m.restrictmouseptr(0,0,maxx,maxy);
	m.showmouseptr();
	return 0;
}

float gcin(char *str)
	{
	byte=0;
	while(byte!=ENTER)
		{
		 byte=letter();
		 if(byte==BACKSPACE)
			{
			movedx=getx()-letw,str--;
			if(movedx<=0)
				{movedy=gety()-leth;
				movedx=maxy;
				}
			else
			movedy=gety();
			moveto(movedx,movedy);
			bar(movedx,movedy,movedx+letw,movedy+leth);
			}
		 else
		     outtext(""+byte);
		     *str=byte;
		     str++;
		}
		*str='\0';
		if(logstatus==0)
			log(str);
		return (atof(str));
	}

void switchpage(int act,int vis )
{
	activepage=act, visualpage=vis;
	setactivepage(activepage);
	wait();
	setvisualpage(visualpage);
}

int toggleactivepage()
{
	if(activepage==0)
	activepage=1;
	else
	activepage=0;
	setactivepage(activepage);
}

int togglevisualpage()
{
if(visualpage==0)
	visualpage=1;
	else
	visualpage=0;
	setvisualpage(visualpage);
}

int display_icon(int &sx,int &sy,char details[16])
{
	ldbmp(sx,sy,"icon.bmp");
	outtextxy(sx,sy+70,details);
	sx+=80;
	if(sx>=maxx)
	{sy+80;
	sx=60;
	}
	moveto(sx,sy);
	return 0;
}

void showmsg(char msg[80])
{
	wait();
	ldbmp(20,10,"msgwin.bmp");
	outtextxy(25,80,msg);
}

void Dim(char c,char s)
{
	char i;
	switch(s)
	{
		case 1 :for(i=60;i>0;i--)
			{
			setrgbpalette(c,i,0,0);
			delay(15);
			}
			break;
		case 2 :for(i=60;i>0;i--)
			{
			setrgbpalette(c,0,i,0);
			delay(15);
			}
			break;
		case 3 :for(i=60;i>0;i--)
			{
			setrgbpalette(c,0,0,i);
			delay(15);
			}
			break;
	}
}

void Bright(char c,char s)
{
	char i;
	switch(s)
	{
		case 1 :for(i=0;i<60;i++)
			{
			setrgbpalette(c,i,0,0);
			delay(15);
			}
			break;
		case 2 :for(i=0;i<60;i++)
			{
			setrgbpalette(c,0,i,0);
			delay(15);
			}
			break;
		case 3 :for(i=0;i<60;i++)
			{
			setrgbpalette(c,0,0,i);
			delay(15);
			}
			break;
	}
}

void Enlarge(int x,int y,char c[])
{
	int i;
	setfillstyle(0,0);
	for(i=1;i<10;i++)
	{
		settextstyle(1,0,i);
		bar(x-24,y-25,x+23,y+55);
		outtextxy(x,y-i,c);
		delay(20);
	}
}

void Reduce(int x,int y,char c[])
{
	int i;
	setfillstyle(0,0);
	for(i=9;i>0;i--)
	{
		settextstyle(1,0,i);
		bar(x-33,y-29,x+33,y+58);
		outtextxy(x,y-i,c);
		delay(20);
	}
}

int cursor1[6][32]={
		{0x0000,0x0000,0x0000,0x0000,
		0x8001,0xc003,0xf00f,0xfc3f,
		0xfc3f,0xf00f,0xc003,0x8001,
		0x0000,0x0000,0x0000,0x0000,
		0xffff,0x8001,0xffff,0x8001,
		0x4002,0x2004,0x1008,0x0240,
		0x0240,0x0810,0x2004,0x4002,
		0x8001,0xffff,0x8001,0xffff},
		{0xe1ff,0xe1ff,0xe1ff,0xe1ff,
		0xe1ff,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0000,
		0x1e00,0x1200,0x1200,0x1200,
		0x13ff,0x1249,0x1249,0xf249,
		0x9001,0x9001,0x9001,0x8001,
		0x8001,0x8001,0xffff,0x0000},
		{0x0000,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0000,0x0000,
		0xffff,0xffff,0xfff7,0x0007,
		0x0007,0xeee7,0x0007,0x0007,
		0xeee7,0x0007,0x0007,0xeee7,
		0x0007,0x0007,0xeee7,0xeee7},
		{0xffff,0xf1c7,0xe013,0xc001,
		0x1000,0x1000,0x1000,0x1000,
		0xc001,0xe003,0xf007,0xf10f,
		0xfc1f,0xfe3f,0xff8f,0xffff,
		0x0000,0x0e38,0x1144,0x2082,
		0x4001,0x4001,0x4001,0x4001,
		0x2002,0x1004,0x0808,0x0410,
		0x0220,0x0140,0x0080,0x0000},
		{0xfeff,0xfd7f,0xfbbf,0xf7df,
		0xefef,0xdff7,0xbffb,0x7ffd,
		0x7ffd,0x7ffd,0x7ffd,0xbefb,
		0xdc77,0xe28f,0xfeff,0xfc7f,
		0x0100,0x0280,0x0440,0x0820,
		0x1010,0x2008,0x4004,0x8002,
		0x8002,0x8002,0x8002,0x4104,
		0x2388,0x1d70,0x0100,0x0380},
		{0xfeff,0xfd7f,0xfbbf,0xf7df,
		0xefef,0xdff7,0xbffb,0x7ffd,
		0x7ffd,0x7ffd,0x7ffd,0xbefb,
		0xdc77,0xe28f,0xfeff,0xfc7f,
		0x0100,0x0280,0x0440,0x0820,
		0x1010,0x2008,0x4004,0x8002,
		0x8002,0x8002,0x8002,0x4104,
		0x2388,0x1d70,0x0100,0x0380}};
		
char * boxin(int x,int y,int xlen, int ylen,char *finalstr)
{
   int midx, midy, ht,wt;
   char byte;
   char outstr[18];
   midx = x;
   midy = y;
   ht = textheight ("W");
   wt = textwidth  ("W");
   xlen*=wt;
   ylen*=ht;
   setcolor(GREEN);
   setbkcolor(BLACK);
   setfillstyle(SOLID_FILL,WHITE);
   settextjustify(CENTER_TEXT, CENTER_TEXT);
	setcolor(BLACK);
	bar(midx-xlen,midy-(ht),midx+(wt*10),midy+ylen);
	setcolor(GREEN);
	rectangle(midx-xlen,midy-ylen,midx+xlen,midy+ylen);

   int i =-1,j=0;
   for(finalstr[0]='\0';;)
   {

	byte=getch();
	i++;
	setcolor(BLACK);
	bar(midx-xlen,midy-ylen,midx+xlen,midy+ylen);
	setcolor(GREEN);
	rectangle(midx-xlen,midy-ylen,midx+xlen,midy+ylen);
	outstr[i]=byte;
	outstr[i+1]='\0';
	outtextxy(midx,midy,outstr);

	if (byte==ENTER)   //Enter
	{
	finalstr[i]='\0';
	break;
	}
	/*
TO MAKE UP USE LINKED LIST WHICH I THINK IS A BETTER iDEA
	if(byte==LEFTKEY)
	{
		
	}
	 *//*
	if(byte==RIGHTKEY)
	{
		
	} *//* 
	 if(byte==DEL)
	{
		
	} */

	 if (byte==BACKSPACE)	//Backspace
	{
	i-=2;
	setcolor(BLACK);
	bar(midx-xlen,midy-ylen,midx+xlen,midy+ylen);
	setcolor(GREEN);
	rectangle(midx-xlen,midy-ylen,midx+xlen,midy+ylen);
	outstr[i+1]='\0';
	outtextxy(midx,midy,outstr);
	continue;
	}
	finalstr[i]=byte;
	if(i>xlen/wt)
	{
	finalstr[i]='\0';
	break;
	}
}
   cleardevice();
 return (&finalstr[0]);
}
int getpass(char  orginal_pass[18])
{
   /* request auto detection */
   int midx, midy, ht,wt;
   char byte;
   char pass_str[18],outstr[18];

   midx = getmaxx() / 2;
   midy = getmaxy() / 2;

   /* get information about current text settings */

   /* display the information */
   ht = textheight ("W");
   wt = textwidth  ("W");
   /* clean up */
   clearviewport();

   //draws rectangle to enter the password
   setcolor(GREEN);
   setbkcolor(BLACK);
   setfillstyle(SOLID_FILL,WHITE);

   settextjustify(CENTER_TEXT, CENTER_TEXT);

	setcolor(BLACK);
	bar(midx-(wt*10),midy-(ht),midx+(wt*10),midy+ht);
	setcolor(GREEN);
	rectangle(midx-(wt*10),midy-(ht),midx+(wt*10),midy+ht);

   int i =-1,j=0;
   for(pass_str[0]='\0';;)
   {

	byte=getch();
	i++;
	setcolor(BLACK);
	bar(midx-(wt*10),midy-(ht),midx+(wt*10),midy+ht);
	setcolor(GREEN);
	rectangle(midx-(wt*10),midy-(ht),midx+(wt*10),midy+ht);

	for(j=0;j<i+1;j++)
	outstr[j]='*';
	outstr[j]='\0';
	outtextxy(midx,midy,outstr);

	if (byte==13)   //Enter
	{
	pass_str[i]='\0';
	break;
	}

	if (byte==8)	//Backspace
	{
	i-=2;

	setcolor(BLACK);
	bar(midx-(wt*10),midy-(ht),midx+(wt*10),midy+ht);
	setcolor(GREEN);
	rectangle(midx-(wt*10),midy-(ht),midx+(wt*10),midy+ht);

	for(j=0;j<=i;j++)
	outstr[j]='*';
	outstr[j]='\0';
	outtextxy(midx,midy,outstr);

	continue;
	}
	pass_str[i]=byte;
}
   cleardevice();
   if(strcmp(pass_str,orginal_pass)==0)
   {
   outtextxy(200,120,"Access Permitted");
   return 0;

   }
   else
   {
   outtextxy (200,120,"Access denied");
   getpass(orginal_pass);
	}

 return 1;
}
/*
void main()
{
char msg[80];
//setsvgamode=SVGA800x600x256;
initgui();
printf("%d X %d",maxx,maxy);

boxin(240,200,16,1,msg);
getch();
closegraph();
restorecrtmode();
}*/