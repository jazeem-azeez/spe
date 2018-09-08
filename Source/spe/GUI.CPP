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

#if !defined(GUI)
#define GUI


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


char byte;
int gdriver = DETECT, gmode, errorcode;
int maxx = 0, maxy = 0,COLOR=BLACK,logstatus=0;
char msg[80];
int movedx,movedy;
int letw,leth;
int visualpage,activepage,pagelimit;


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

struct tabmenu
{
int x[2],y[2];
int signature;
char str[16];
};


//io manipulation

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
svbmp(240,160,getmaxx(),getmaxy(),"buf.bmp");
moveto(240,160);

rewind(out);

while (!feof(out))
outtext(""+fgetc(out));

}
int startlog()

{
_strdate(datebuf);
_strtime(timebuf);
if ((out = fopen("logfile.log", "a+"))
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

	return reset+256; //correction to avoid pal mixing
}

int initgui(int gdriver=VGA ,int gmode=VGAHI)

{
	/* request auto detection */
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



void switchpage(int active,int visual )
{
	
	setactivepage(active);
	wait();
	setvisualpage(visual);
}

void display_err(char msg[])

{
	switchpage(1,1);
	ldbmp(200,240,"errror.bmp");
	shadowtxt( msg,220,220,WHITE);
	getch();
	clearviewport();
	switchpage(0,0);
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


animate(char filename[16])

{			int i,j;
	wait();
		ldbmp(0,0,filename);
	while(!kbhit()&&m.moving()==9)

	{
		for(i=0;i<16;i++)
		{
		wait();
		setrgbpalette(i,rand()%256,rand()%256,rand()%256);
		}

	}
graphdefaults();
return 0;
}

# endif


