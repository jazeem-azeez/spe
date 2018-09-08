#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <dos.h>
#include <alloc.h>
#include "..\\pixie\\svga.cpp"
#include "..\\pixie\\bitmap.h"
#define NOT_ENOUGH_MEMORY 1
#define NOT_BITMAP_FORMAT 2
#define XRES 800
int BIT_CNT=8;

void BITMAP::DisplayBitmap(FILE *fp)
 {
  int NUM=pow(2,BIT_CNT);
  for(int i=0;i<NUM;i++)
    {
      fread(color,sizeof(RGB_QUAD),1,fp);
      SetPallete(i,color->Red,color->Green,color->Blue);
    }
  int xx,yy,ll;
  xx=iHead->Width;
  yy=iHead->Height;
  int t;
  ll=(((xx-1)/4+1)*4);
  for(i=0;i<yy;i++)
    for(int j=0;j<ll;j++)
      {
       if(j<xx)
	{
	 t=fgetc(fp);
	 if(t!=0)
	   PutPixel(j,(600-i),t);
	}
      }
 }

int BITMAP::ReadBitmapData(FILE *fp)
 {
  fHead=(FILE_HEADER *)malloc(sizeof(FILE_HEADER));
  if(fHead==NULL)
	     return NOT_ENOUGH_MEMORY;
  iHead=(INFO_HEADER *)malloc(sizeof(INFO_HEADER));
  if(iHead==NULL)
	     return NOT_ENOUGH_MEMORY;
  fread(fHead,sizeof(FILE_HEADER),1,fp);
  fread(iHead,sizeof(INFO_HEADER),1,fp);
/*  textmode(0x3);
  printf("%lu %lu",iHead->Xpix,iHead->Ypix);
  getch();
  SetMode(0x103,1);*/
  if(fHead->B!='B' || fHead->M!='M')
	     return NOT_BITMAP_FORMAT;
  BIT_CNT=iHead->BitCount;
  if(BIT_CNT==8)
      color=(RGB_QUAD *)malloc(256*sizeof(RGB_QUAD));
  if(BIT_CNT==4)
      color=(RGB_QUAD *)malloc(16*sizeof(RGB_QUAD));
  return 0;
 }

void BITMAP::LoadBitmap(char *s)
 {
  FILE *fp;
  fp=fopen(s,"r");
  if(fp==NULL)
     {
       textmode(0x3);
       printf("splash screen not found");
       return;
     }
  int res=ReadBitmapData(fp);
  if(res==0)
     {
      DisplayBitmap(fp);
      fclose(fp);
     }
  else
  {
   if(res==2)
     {
      textmode(0x3);
      printf("Not a bitmap");
     }
   else
     {
      textmode(0x3);
      printf("not enough memory");
     }
   }
 }





