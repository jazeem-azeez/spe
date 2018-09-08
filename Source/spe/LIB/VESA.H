
#ifndef _VESA
#define _VESA

#define _640x480    0x101
#define _800x600    0x103
#define _1024x768   0x105


# include <c:\spe\lib\initsvga.c>
#include <dos.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>

typedef unsigned char BYTE;

struct VesaInfo
{
	char sign[4];      //VESA
	short version;     //VESA version
	char far *oem;     //Name of the card
	long capabilities;
	unsigned far *mode; //pointer to available modes
	short totmem;
	char reserved[236];
};
struct ModeInfo
{
	unsigned short mode;
	BYTE wina;
	BYTE winb;
	unsigned short granularity;
	unsigned short winsize;
	unsigned short winasegment;
	unsigned short winbsegment;
	void (far *bankSwitch)(void);
	unsigned short bytesperline;
	unsigned short width;
	unsigned short height;
	BYTE charwidth;
	BYTE charheight;
	BYTE bitplanes;
	BYTE bitsperpixel;
	BYTE banks;
	BYTE memorymodel;
	BYTE banksize;
	BYTE imagepages;
	BYTE reserved1;
	BYTE redmasksize;
	BYTE redfieldposition;
	BYTE greenmasksize;
	BYTE greenfieldposition;
	BYTE bluemasksize;
	BYTE bluefieldposition;
	BYTE rsvdmasksize;
	BYTE rsvdfieldposition;
	BYTE directcolormode;
	BYTE reserved2[216];
};
int SetMode(int,int);
void PutPixel(int,int,unsigned char);
void SwitchBank(int );
BYTE GetPixel(int,int);
int GetVesaInfo(struct VesaInfo far*);
void SetPallete(BYTE i,BYTE r,BYTE g,BYTE b);
int GetModeInfo(int mode,struct ModeInfo far *modeinfo);

#define FAST_MUL(x)	((x<<9)+(x<<8)+(x<<5))

//the above macro defines a multiply by 800 method
//by using left shifts. As shift operations are very fast
//this method is used.y*(800)=y*(512)+y*(256)+y*(32)=y<<9+y<<8+y<<5
//This method saves valuable CPU cycles
//As 26 cycles are needed for a MUL inst and just 6 for a SHIFT

union REGS i,o;
struct SREGS s;

void SetPallete(BYTE i,BYTE r,BYTE g,BYTE b)
 {
  outp(0x03c6,0xff);  //Prepare ports for input using 0xff at 0x3c6
  outp(0x03c8,i);     //Port 0x3c8 holds the color index
  outp(0x03c9,r>>2);  //Port 0x3c9 takes RGB values in serial order
  outp(0x03c9,g>>2);  //Even though 8-bit color uses 8 bit for RGB
  outp(0x03c9,b>>2);  //the hardware has a 6-bit DAC register for the color
		   //so we right shift each color 2 bits
		   //If you dont bitmap is not displayed correctly
 }
int GetVesaInfo(struct VesaInfo far *v)
{

	   //ASSEMBLY BLOCK
	   _asm	mov ax,0x04f00
	   _asm	les di,v
	   _asm	int 0x10
	   _asm	cmp ax,0x4f
	   _asm	jz done
	   //ASSEMBLY BLOCK ENDS

		return 0;
	   done:
		return 1;
}
int GetModeInfo(int mode,struct ModeInfo far *modeinfo)
{

	   //ASSEMBLY BLOCK
	   _asm	mov ax,0x4f01
	   _asm	mov cx,[mode]
	   _asm	les di,modeinfo
	   _asm	int 0x10
	   //ASSEMBLY BLOCK ENDS

	   return (modeinfo->mode & 1);
}

void setvesamode(int mode)
{
	asm mov ax,4f02h
	asm mov bx, mode
	asm int 10h
}
int SetMode(int m,int n)
 {

  struct VesaInfo v;
  int r;
  if(n==0)
   {
	r=GetVesaInfo(&v);
	glprintf("Detecting video card:");
	/*
	for(int stupefy=0;stupefy<=79;stupefy++)
	{
	  glprintf(".");     //looks good but non functional
	  delay(63); //1000/16 aprox
	}
	*/
	glprintf("\nManufacturer:%s\nVersion:%d\nCard:%s\nMemory:%d MB[MAX]\n",v.sign,v.version,v.oem,v.totmem);
    fflush(stdin);
    sleep(2);
    //getch();
   }
  if(r==0)
  {
  setvesamode(m);
  return 0;
  }

  else
   {
    struct ModeInfo m1;
    r=GetModeInfo(m,&m1);
    if(r!=0)
    {

       //ASSEMBLY BLOCK
       _asm mov ax,0x4f02
       _asm mov bx,m
       _asm int 0x10
       //ASSEMBLY BLOCK ENDS
    }
    else
    {
     printf("The following card has been detected...");
     printf("\n%s\n%d\n%s\n%d",v.sign,v.version,v.oem,m1.granularity);
     printf("\nThis card does not support this mode you are trying to run...");
     getch();
     textmode(0x3);
     exit(0);
    }

   }
  return 1;
 }


BYTE GetPixel(int x,int y)
 {
  BYTE c;
  static int bank1;
  static char far *vid_mem=(char far*)0xA0000000L;
  unsigned long len=0xffff+1l,offset;
  static int pbank1=-1;
  //offset=(unsigned long)y*(unsigned long)800+x; IS DONE AS  BELOW
  offset=(unsigned long)FAST_MUL((unsigned long)y)+x;
  bank1=offset/len;
  offset=offset%len;
  if(bank1!=pbank1)
   {
    SwitchBank(bank1);
    pbank1=bank1;
   }
  //c=peekb(0xA000,(unsigned)offset);
  c=*(vid_mem+offset);
  return c;
 }

void PutPixel(int x,int y,BYTE color)
 {
  static int bank;
  static char far *vid_mem=(char far*)0XA0000000L;
  unsigned long len=0xffff+1l,offset;
  static int pbank=-1;
// offset=(unsigned long)y*(unsigned long)800+x; IS DONE AS BELOW
  offset=(unsigned long)FAST_MUL((unsigned long)y)+x;

  bank=offset/len;
  offset=offset%len;
  if(bank!=pbank)
   {
    SwitchBank(bank);
    pbank=bank;
   }
 // pokeb(0xA000,(unsigned)offset,color);
 *(vid_mem+offset)=color;
  //direct memory write faster than library function pokeb
  return;
 }

void SwitchBank(int b)	//switches the current bank to a new one
 {

   //ASSEMBLY BLOCK
   _asm mov ax,0x4f05
   _asm mov bx,0
   _asm mov dx,b
   _asm int 0x10
   //ASSEMBLY BLOCK ENDS

   return;
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

typedef struct
{
	unsigned short modeattributes;
	unsigned char unused1[10];
	void (far*switchbank)();
	unsigned char unused2[240];
}modeinfo;

void (far*switchbank)();

int bank;

char getsvgainfo()
{
	unsigned char vesainfo[256];
	asm mov ax,04f00h
	asm les di, vesainfo
	asm int 10h
	asm cmp al,4h
	asm jz done
	return 0;
	done:
	return 1;
}

char getvesainfo()
{
	unsigned char vesainfo[256];
	asm mov ax,04f00h
	asm les di, vesainfo
	asm int 10h
	asm cmp al,4h
	asm jz done
	return 0;
	done:
	return 1;
}

int getvesamdeinfo(int mode,modeinfo far *mi)
{
	asm mov ax,4f01h
	asm mov cx, mode
	asm les di,mi
	asm int 10h
	return(mi->modeattributes&1);
}


#endif