//Isometric Engine .
int minx = 0,miny = 0;
double xscale = 4.5,yscale = 4.5;

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


double mod(double a)
{
if(a<0)
{a*=-1;}
return a;
}

struct point3d
{
double x,y,z;
};

struct line3d
{
point3d p1,p2;
};

struct triangle3d
{
point3d p1,p2,p3;
};


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



void trans(point3d &p,double x,double y,double z)
{
p.x+=x;
p.y+=y;
p.z+=z;
}


void attrans(triangle3d &t,double x,double y,double z)
{
trans(t.p1,x,y,z);
trans(t.p2,x,y,z);
trans(t.p3,x,y,z);
}

void rtrans(double &x,double &y,int deg)
{
double r = rad(deg);
double x1,y1;
x1=x*cos(r)-y*sin(r);
y1=x*sin(r)+y*cos(r);
x=x1;
y=y1;
}

void rot(point3d &p,int degx,int degy,int degz)
{
rtrans(p.y,p.z,degx);
rtrans(p.z,p.x,degy);
rtrans(p.x,p.y,degz);
}


void atrot(triangle3d &t,int degx,int degy,int degz)
{
rot(t.p1,degx,degy,degz);
rot(t.p2,degx,degy,degz);
rot(t.p3,degx,degy,degz);
}
