//File That Draws Some Objects .
#include "c:\spe\GL\math3d.h"
#include "c:\spe\GL\cam.h"
#include "c:\spe\GL\box.h"

fstream file;

int minx = 0,miny = 0;
double xscale = 4.5,yscale = 4.5;
double ot;


#define maxx getmaxx()
#define maxy getmaxy()
#define midx (maxx+1)/2
#define midy (maxy+1)/2
#define screen_width maxx+1
#define screen_height maxy+1
/*
#ifndef IBGI
#define maxx screen_width-1
#define maxy screen_height-1
#define midx (screen_width/2)
#define midy (screen_height/2)
#endif
  */
//Isometric Engine .
#ifdef IISO
double zscale = 2;
#define algo(ip)   pg .x  = (midx + (ip.x*xscale-ip.z*zscale)*0.87); pg .y  = (midy +(ip.x*xscale+ip.z*zscale)*0.5 - ip.y*yscale)
#define algo1(ip)  pg1.x  = (midx + (ip.x*xscale-ip.z*zscale)*0.87); pg1.y  = (midy +(ip.x*xscale+ip.z*zscale)*0.5 - ip.y*yscale)
#define algo2(ip)  pg2.x  = (midx + (ip.x*xscale-ip.z*zscale)*0.87); pg2.y  = (midy +(ip.x*xscale+ip.z*zscale)*0.5 - ip.y*yscale)
#define calgo(ip)  pg .x  = (midx + (ip.r*cos(ot)*xscale-ip.z*zscale)*0.87);\
		   pg .y =  (midy + (ip.r*cos(ot)*xscale+ip.z*zscale)*0.5 - ip.r*sin(ot)*yscale)
#endif

//Default Non Isometric Engine .
#ifndef IISO
double zscale = 1.125;
#define algo(p)  pg.x  = midx + p.x*xscale; pg.y = midy - p.y*yscale; pg.x-= p.z*zscale; pg.y+= p.z*zscale
#define algo1(p) pg1.x = midx + p.x*xscale; pg1.y = midy - p.y*yscale; pg1.x-= p.z*zscale; pg1.y+= p.z*zscale
#define algo2(p) pg2.x = midx + p.x*xscale; pg2.y = midy - p.y*yscale; pg2.x-= p.z*zscale; pg2.y+= p.z*zscale
#define calgo(p) pg.x  = midx + p.r*cos(ot)*xscale; pg.y = midy - p.r*sin(ot)*yscale; pg.x-= p.z*zscale; pg.y+= p.z*zscale
#endif



struct pm
{
int p1,p2;
};

struct linemesh
{
pm ld[900];
int no;
};

struct gllineobject
{
point3d p[600];
int no;
point3d cr;
linemesh l;
};

void drawpoint(point3d p,int color = 0)
{
algo(p);
putpixel(pg.x,pg.y,color);
}

void drawpointc(point3dc p,int color = 0)
{
ot=((M_PI*p.o)/180);
calgo(p);
putpixel(pg.x,pg.y,color);
}

void drawline(line3d l,int color = 0)
{
int tcolor = getcolor();
algo(l.p1);
algo1(l.p2);
setcolor(color);
line(pg.x,pg.y,pg1.x,pg1.y);
setcolor(tcolor);
}

void drawtriangle(triangle3d t,int color = 0)
{
line3d l;
l.p1=t.p1,l.p2=t.p2;
drawline(l,color);
l.p1=t.p2,l.p2=t.p3;
drawline(l,color);
l.p1=t.p3,l.p2=t.p1;
drawline(l,color);
}

void drawaxis(int color = 15)
{
line3d l;
l.p1.x=0,l.p1.y=0,l.p1.z=0;
l.p2.x=0,l.p2.y=0,l.p2.z=400;
drawline(l,color);
l.p2.x=0,l.p2.y=200,l.p2.z=0;
drawline(l,color);
l.p2.x=200,l.p2.y=0,l.p2.z=0;
drawline(l,color);
l.p2.x=0,l.p2.y=0,l.p2.z=-400;
drawline(l,color);
l.p2.x=0,l.p2.y=-200,l.p2.z=0;
drawline(l,color);
l.p2.x=-200,l.p2.y=0,l.p2.z=0;
drawline(l,color);
}

void conplot(point3d p,int color)
{
if((int(p.x*1000)%79==0)||(int(p.z*1000)%79==0))
{
drawpoint(p,color);
}
}

void sconplot(point3d p,int color,double oo,double pp)
{
if(((int(oo)%10)==0)||((int(pp)%10)==0))
{
drawpoint(p,color);
}
}

void aotrans(gllineobject &o,double x,double y,double z)
{
int i;
for(i=0;i<o.no;i++)
{
trans(o.p[i],x,y,z);
}
trans(o.cr,x,y,z);
}

void aorot(gllineobject &o,int degx,int degy,int degz)
{
int i;
for(i=0;i<o.no;i++)
{
rot(o.p[i],degx,degy,degz);
}
rot(o.cr,degx,degy,degz);
}

void aoscale(gllineobject &o,double x,double  y,double z)
{
int i;
for(i=0;i<o.no;i++)
{
scale(o.p[i],x,y,z);
}
}


int readobj(char *fn,gllineobject &o)
{
char c;
int i;
o.no=0;
file.open(fn,ios::in);
if(!file){return -1;}
file>>o.no;
o.cr.x=0,o.cr.y=0,o.cr.z=0;
for(i=0;i<o.no;i++)
{
file>>o.p[i].x;
o.cr.x+=o.p[i].x;
file.get(c);
file>>o.p[i].y;
o.cr.y+=o.p[i].y;
file.get(c);
file>>o.p[i].z;
o.cr.z+=o.p[i].z;
}
o.cr.x/=o.no,o.cr.y/=o.no,o.cr.z/=o.no;
file>>o.l.no;
for(i=0;i<o.l.no;i++)
{
file>>o.l.ld[i].p1;
file.get(c);
file>>o.l.ld[i].p2;
}
file.close();
return 0;
}

void drawobj(gllineobject o,int color)
{
int i;
line3d la;
for(i=0;i<o.l.no;i++)
{
la.p1=o.p[o.l.ld[i].p1];
la.p2=o.p[o.l.ld[i].p2];
//camera
if(camera_rot_on)
alrot(la,cam->x,cam->y,cam->z);
if(camera_zoom_on)
alscale(la,Zoom->x,Zoom->y,Zoom->z);
/*
dosen't work as i think

if(camera_trans_on)
altrans(la,Trans->x,Trans->y,Trans->z);
*/
drawline(la,color);
}
}