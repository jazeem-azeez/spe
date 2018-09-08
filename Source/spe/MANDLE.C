#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <process.h>
#include <stdlib.h>

typedef struct {float x;floaty;} complex;
typedef struct {unsigned short modeattributes;
                unsigned char unused[10];
                void (far *switchbank)();
                unsigned char unused2 [240];
                }modeinfo;
                
void (far *switchbank)();
int bank;

int getsvgainfo()
{
    unsigned char vesainfo[256];
    asm mov ax,04f00h
    asm les di ,vesainfo
    asm int 10h
    asm cmp al,4fh
    asm jz done
    return 0;
    done:
    return 1;
}

int getvesainfo()
{
    unsigned char vesainfo[256];
    asm mov ax,4f00h
    asm les di,vesainfo
    asm int 10h
    asm cmp al,4fh
    asm jz done
    return 0;
    done:
    return 1;
}
int getvesamdeinfo (int mode,modeinfo far *mi)
{
    asm mov ax, 4f01h
    asm mov cx,mode
    asm les di,mi
    asm int 10h
    return (mi-> modeattributes &1);
}
void setvesamode(int mode)
{
    asm mov ax,4f02h
    asm mov bx,mode
    asm int 10h
}

int init(void)
{
    modeinfo mi;
    if (!getvesainfo())
    {
        printf("No vesa compatible card found");
        exit(1);
        
    }
    if(!getvesamdeinfo(0x101,&mi))
    {
        printf("Mode Not supported");
        exit(2);
    }
        
    switchbank=mi.switchbank;
    setvesamode(0x101);
}

void putpixel(int x,int y,char col)
{
    int off;
    asm mov ax,640
    asm mov bx,y
    asm mul bx
    asm add ax,x
    asm jnc noc
    asm inc dx    
    
    noc:
    asm mov off,ax
    asm cmp dx,bank
    asm jz same
    asm mov bank,dx
    asm xor bx,bx
    switchbank();
    
    same:
    asm push di
    asm mov ax,0A000h
    asm mov es,ax
    asm mov di,off 
    asm mov al,col
    asm[es:dl],al
    asm pop di 
    
}
void setmode (int mode)
{
    asm mov ax,mode
    asm int 10h
}

complex complexsquare(complex c)
{
    complex csq;
    csq.x= c.x*c.x-c.y*c.y;
    csq=2*c.x*c.y;
    return (csq);
}

int iterate (complex zinit, int maxiter)
{
    complex z=zinit;
    int cnt=0;
    while((z.x*z.x+z.y*z.y<=4.0)&&(cnt<maxter))
    {
    x=complexsquare(z);
    z.x+=zinit.x;
    z.y+=zinit.y;
    cnt++;
    }
    return (cnt);
}

void mandelbrot(int xwmin,int ywmin,int nx,int ny,int maxiter,float realmin,float realmax,float imagmin,float imagmax)
{
float realinc=(realmax-realmin)/nx;
float imaginc=(imagmax-imagmin)/ny;
complex z;
int x,y;
int clr ,cnt;
for(x=0,z.x=realmin;x<nx;x++,z.x+=realinc)
    for(y=0,z.y=imagmin;y<ny;y++,z.y+=imaginc)
    {
        cnt =iterate(z,maxiter);
        if(cnt==maxiter)
            clr=0;
        else
            clr=cnt;
        putpixel(xwmin+x,ywmin+y,clr);

    }
}

void main()
{
init();
int nx,ny,maxiter;
float realmin,realmax,imagmin,imagemax;

//realmin=-2.5;realmax=0.75;
//imagmin=-1.25;imagmax=1.25;
//realmin=-0.811717;realmax=-0.725850;
//imagmin=-0.084586;imagmax=0.159774;
realmin=-0.776080;realmax=-0.771164;
imagmin=0.122275;imagmax=0.126609;
//realmin=-0.782403;realmax=0.781972;
//imagmin=-0148035;imagmax=0.148446;
//realmin=-0.744120;realmax=-0.740625;
//imagmin=0.160905;imagmax=0.167029;
int xwmin=0,ywmin=0,xwmax=640,ywmax480,xmin,ymin,xmax,ymax;
nx=640;
ny=480;
maxiter=256;
void mandelbrot(xwmin,ywmin,nx,ny,maxiter,realmin,realmax,imagmin,imagmax)l;getch();
setmode(0x03);
}