#define vid (char far*)0xb8000000
#include<dos.h>
union REGS i,o;

void dbox(int c1,int r1,int c2,int r2,int bg,int fg)
{
int i;
for(i=(2+(2*c1-2)+160*(r1-1));i<=(2*c2-2)+(160*(r1-1));i+=2)
{
 *(vid+i)=205;
 *(vid+i+1)=bg*16+fg;
}
for(i=(160*(r2-1))+(2+(2*c1-2));i<=(2*c2-2)+(160*(r2-1));i+=2)
{
 *(vid+i)=205;
 *(vid+i+1)=bg*16+fg;
}

for(i=(160*(r1-1)+160)+(2*c1-2);i<160*(r2-1);i+=160)
{
*(vid+i)=186;
*(vid+i+1)=bg*16+fg;
}
for(i=(160*(r1-1)+160)+(2*c2-2);i<160*(r2-1);i+=160)
{
 *(vid+i)=186;
 *(vid+i+1)=bg*16+fg;
}
i=160*(r1-1)+(2*c1-2);
*(vid+i)=201;
*(vid+i+1)=bg*16+fg;
i=(r1-1)*160+(2*c2-2);
*(vid+i)=187;
*(vid+i+1)=bg*16+fg;
i=160*(r2-1)+(2*c1-2);
*(vid+i)=200;
*(vid+i+1)=bg*16+fg;
i=(r2-1)*160+(2*c2-2);
*(vid+i)=188;
*(vid+i+1)=bg*16+fg;
}


void dline1(int c1,int r1,int c2,int r2)
{
int i;

if(r1==r2)
{
for(i=(2+(2*c1-2)+160*(r1-1));i<=(2*c2-2)+(160*(r2-1));i+=2)
*(vid+i)=205;

i=160*(r1-1)+(2*c1-2);
*(vid+i)=199;
i=(r1-1)*160+(2*c2-2);
*(vid+i)=182;
}
if(c1==c2)
{
for(i=(160*(r1-1)+160)+(2*c1-2);i<160*(r2-1);i+=160)
*(vid+i)=186;
i=160*(r1-1)+(2*c1-2);
*(vid+i)=203;
i=(r2-1)*160+(2*c1-2);
*(vid+i)=202;

}
}

void dline2(int c1,int r1,int c2,int r2)
{
int i;

if(r1==r2)
{
for(i=((2*c1-2)+160*(r1-1));i<=(2*c2-2)+(160*(r2-1));i+=2)
*(vid+i)=205;
}
if(c1==c2)
{
for(i=(160*(r1-1))+(2*c1-2);i<=160*(r2-1);i+=160)
*(vid+i)=186;
}
}

void sbox(int c1,int r1,int c2,int r2)
{
int i;

for(i=(2+(2*c1-2)+160*(r1-1));i<=(2*c2-2)+(160*(r1-1));i+=2)
*(vid+i)=196;
for(i=(160*(r2-1))+(2+(2*c1-2));i<=(2*c2-2)+(160*(r2-1));i+=2)
*(vid+i)=196;

for(i=(160*(r1-1)+160)+(2*c1-2);i<160*(r2-1);i+=160)
*(vid+i)=179;

for(i=(160*(r1-1)+160)+(2*c2-2);i<160*(r2-1);i+=160)
*(vid+i)=179;

i=160*(r1-1)+(2*c1-2);
*(vid+i)=218;
i=(r1-1)*160+(2*c2-2);
*(vid+i)=191;
i=160*(r2-1)+(2*c1-2);
*(vid+i)=192;
i=(r2-1)*160+(2*c2-2);
*(vid+i)=217;
}

void sline1(int c1,int r1,int c2,int r2)
{
int i;

if(r1==r2)
{
for(i=(2+(2*c1-2)+160*(r1-1));i<=(2*c2-2)+(160*(r2-1));i+=2)
*(vid+i)=196;

i=160*(r1-1)+(2*c1-2);
*(vid+i)=195;
i=(r1-1)*160+(2*c2-2);
*(vid+i)=180;
}
if(c1==c2)
{
for(i=(160*(r1-1)+160)+(2*c1-2);i<160*(r2-1);i+=160)
*(vid+i)=179;
i=160*(r1-1)+(2*c1-2);
*(vid+i)=194;
i=(r2-1)*160+(2*c1-2);
*(vid+i)=193;

}
}

void sline2(int c1,int r1,int c2,int r2)
{
int i;

if(r1==r2)
{
for(i=((2*c1-2)+160*(r1-1));i<=(2*c2-2)+(160*(r2-1));i+=2)
*(vid+i)=196;
}
if(c1==c2)
{
for(i=(160*(r1-1))+(2*c1-2);i<=160*(r2-1);i+=160)
*(vid+i)=179;
}
}
void plus(int c1,int r1)
{
int i;
i=160*(r1-1)+(2*c1-2);
*(vid+i)=197;
}

void crec(int x1,int y1,int x2,int y2,char ch)
{
 char far *v;
 int i,j;
  for(i=x1;i<=x2;i++)
  {
    for(j=y1;j<=y2;j++)
     {

       v=vid+160*(j-1)+2*(i-1);
       *v=' ';
       v++;
       *v=ch*16;
      }
   }
}


void clr()
 {

 i.h.ah=6;
 i.h.al=0;
 i.h.ch=0;
 i.h.cl=0;
 i.h.dh=24;
 i.h.dl=79;
 i.h.bh=7;
 int86(16,&i,&o);
 }