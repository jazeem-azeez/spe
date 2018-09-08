#ifndef BITMAP_H
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <dos.h>
#include <alloc.h>

#define BITMAP_H
#define NOT_ENOUGH_MEMORY 1
#define NOT_BITMAP_FORMAT 2
#define XRES 800
/*

//USES MEMORY AND IS FASTER BUT DOSEN'T PROPERLY DRAW AT END PORTIONS

	typedef unsigned char BYTE;
	typedef unsigned int WORD;
	typedef unsigned long DWORD;

	typedef struct FILE_HEADER
	 {
	  char B,M;
	  DWORD FileSize;
	  WORD Reserved1;
	  WORD Reserved2;
	  DWORD DataOffset;
	 }FILE_HEADER;

	typedef struct INFO_HEADER
	 {
	  DWORD StructSize;
	  long Width;
	  long Height;
	  WORD NumPlanes;
	  WORD BitCount;
	  DWORD Compr;
	  DWORD ImageSize;
	  long Xpix;
	  long Ypix;
	  DWORD ClrUsed;
	  DWORD ClrImp;
	 }INFO_HEADER;

	typedef struct RGB_QUAD
	 {
	  BYTE Blue;
	  BYTE Green;
	  BYTE Red;
	  BYTE Reserved;
	 }RGB_QUAD;

	struct FILE_HEADER our_fhdr=
	 {
	  'B','M',308278,0,0,1078
	 };
	struct INFO_HEADER our_ihdr=
	 {
	 40,640,480,1,8,0,307200,50190,50190,256,0
	 };

	class BITMAP
	 {
	  private:
		   int xoffset,yoffset;
		   FILE_HEADER *fHead;
		   INFO_HEADER *iHead;
		   RGB_QUAD *color;
	  public:
		   int ReadBitmapData(FILE *);
		   void DisplayBitmap(int ,int ,FILE *);
		   void put_BMP(int,int,char *);
	 }X;

int BIT_CNT=8;

void BITMAP::DisplayBitmap(int xoffset,int yoffset,FILE *fp)
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
  yoffset=yy;
//  xoffset=0;
  int t;
  ll=(((xx-1)/4+1)*4);
  for(i=0;i<yy;i++)
    for(int j=0;j<ll;j++)
      {
       if(j<=xx)
	{
	 t=fgetc(fp);
	 if(t!=0)
	   PutPixel(xoffset+j,yoffset-i,t);
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
//  textmode(0x3);
//  printf("%lu %lu",iHead->Xpix,iHead->Ypix);
//  getch();
//  SetMode(0x103,1);
  if(fHead->B!='B' || fHead->M!='M')
	     return NOT_BITMAP_FORMAT;
  BIT_CNT=iHead->BitCount;
  if(BIT_CNT==8)
      color=(RGB_QUAD *)malloc(256*sizeof(RGB_QUAD));
  if(BIT_CNT==4)
      color=(RGB_QUAD *)malloc(16*sizeof(RGB_QUAD));
  return 0;
 }

void BITMAP::put_BMP(int xoffset,int yoffset, char *s)
 {
  FILE *fp;
  fp=fopen(s,"r");
  if(fp==NULL)
     {
       textmode(0x3);
       printf("BMP not found");
       return;
     }
  int res=ReadBitmapData(fp);
  if(res==0)
     {
      DisplayBitmap(xoffset,yoffset,fp);
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

*/

class BITMAP
{
  public :
	 int x,y;
	 int xoff, yoff;
	 unsigned char color;
	 fstream file;
	 char *filepath;

  struct bitmapfileheader
  {
	char bftype[2];  	// File type - should be "BM" for BMP files
	long bfsize;	  	// File size
	char bfreserved1[2];  	// Reserved
	char vfreserved2[2];	// Reserved
	long bfoffbits;		// offset from beginning of file to bitmap data
  } bmfh;

  struct bitmapinfoheader
  {
	long bisize;		// Size of BITMAPINFOHEADER structure
	long biwidth;		// Width of image
	long biheight;		// Height of image
	int  biplanes; 		// No. of planes
	int  bibitcount;	// No. of bpi
	long bicompression;	// Type of compression
	long bisizeimage;     	// Size of image data in bytes
	long bixpelspermeter; 	// Horizontal pixels per meter
	long biypelspermeter; 	// Vertical pixels per meter
	long biclrused;       	// No. of colors used
	long biclrimportant;  	// No. of important colors
  } bmih;

  struct rgbquad
  {
	unsigned char rgbblue;   // Blue part
	unsigned char rgbgreen;  // Green part
	unsigned char rgbred;    // Red part
	unsigned char rgbreserved;
  } rgb;

  BITMAP()
  {
  xoff=0;
  yoff=0;
  }


  void put_pixel(int &x,int &y,unsigned char &color,int bitno);
  int  power(int no);
  void show_message(char *string);
  int  open_file();
  void load_palette();
  void show_one_bit_bitmap();
  void show_four_bit_bitmap();
  void show_eight_bit_bitmap();
  void Show_BMP(char*);
  void setpalette(char *fpath);
  void imageoffset(int x1,int y1)
  {
	xoff=x1,yoff=y1;
  }
  void put_BMP(int x1,int y1,char *filename)
  {
	imageoffset(x1,y1);
	Show_BMP(filename);
  }

}X;//End Of Class All Functions Prototypes



  void BITMAP::put_pixel(int &x,int &y,unsigned char &color,int bitno)
  {
      if (color>=bitno)
      {
	    PutPixel(x+xoff,y+yoff,2);
	    color-=bitno;
      }
      else PutPixel(x+xoff,y+yoff,1);
      x++;
  }

  int BITMAP::power(int no)      //  returns 2 to the power 'no.'
  {
	int prod=1;
	for (int i=1;i<=no;i++)
		prod*=2;
	return(prod);
  }

  void BITMAP::show_message(char *string)
  {
	cout<<string;
  }

  int BITMAP::open_file()
  {
	file.open(filepath,ios::in|ios::binary);
	if (file.fail())  return(0); else return(1);
  }
  void BITMAP::load_palette()
  {
	for (int i=1;i<=bmih.biclrused;i++)    // loading palette
	{
	   file.read((char *)&rgb,sizeof(rgb));
	   setrgbpalette(i,rgb.rgbred>>2,rgb.rgbgreen>>2,rgb.rgbblue>>2);
	}
  }
    void BITMAP::show_one_bit_bitmap()
  {

	   y=bmih.biheight;
	   x=1;
	   while(!file.eof())
	   {
		int maxx=bmih.biwidth;
		file.read((char *)&color,sizeof(color));
		put_pixel(x,y,color,128);
		put_pixel(x,y,color,64);
		put_pixel(x,y,color,32);
		put_pixel(x,y,color,16);
		if (x>maxx) { x=1;y--; }
		put_pixel(x,y,color,8);
		put_pixel(x,y,color,4);
		put_pixel(x,y,color,2);
		put_pixel(x,y,color,1);
		if (x>maxx) { x=1;y--; }
	   }
  }
  void BITMAP::show_four_bit_bitmap()
  {
	y=bmih.biheight;
	   x=1;
	   int maxx=bmih.biwidth;
	   file.read((char *)&color,sizeof(color));
	   while(!file.eof())
	   {
		if (color>=128) color-=128;
		if (color>=64) color-=64;
		if (color>=32) color-=32;
		if (color>=16) color-=16;
		PutPixel(x+xoff,y+yoff,(color>>4)+1);x++;
		if (x+xoff>maxx) { x=1;y--; }/*
     */					    /*
		PutPixel(x+xoff,y+yoff,(color>>4)+1);x++;
		if (x+xoff>maxx) { x=1;y--;}          */
		file.read((char *)&color,sizeof(color));
	   }
  }

  void BITMAP::show_eight_bit_bitmap()
  {
	   for (y=bmih.biheight;y>=1;y--)
	   {
		for (x=1;x<=bmih.biwidth;x++)
		{
			file.read((char *)&color,sizeof(color));
			PutPixel(x+xoff,y+yoff,color+1);
		}
		if (bmih.biwidth%4!=0)
		{
			for (int x=bmih.biwidth%4;x<4;x++)
			  file.read((char *)&color,sizeof(color));
		}
	   }
  }
   void BITMAP::setpalette(char *fpath)
  {
	strcpy(filepath,fpath);
	if (!open_file())
	{
		show_message("Invalid file");
		return;
	}
	file.read((char *)&bmfh,sizeof(bmfh));
	file.read((char *)&bmih,sizeof(bmih));
	if ((bmfh.bftype[0]!='B') |( bmfh.bftype[1]!='M' ))
	{
		show_message("Not a bmp file");
		file.close();
		return;
	}
	if (bmih.bicompression)
	{
		show_message("Cannot load compressed images");
		file.close();
		return;
	}
	if (bmih.biclrused==0) bmih.biclrused=power(bmih.bibitcount);
	if (bmih.bibitcount==24)
	{
		show_message("Cannot load 24-bit BMP.");
		file.close();
		return;
	}
	load_palette();
       file.close();
       } //End Of setpalette

  void BITMAP::Show_BMP(char *fpath)
  {
	strcpy(filepath,fpath);
	if (!open_file())
	{
		show_message("Invalid file");
		return;
	}
	file.read((char *)&bmfh,sizeof(bmfh));
	file.read((char *)&bmih,sizeof(bmih));
	if ((bmfh.bftype[0]!='B' )|( bmfh.bftype[1]!='M' ))
	{
		show_message("Not a bmp file");
		file.close();
		return;
	}
	if (bmih.bicompression)
	{
		show_message("Cannot load compressed images");
		file.close();
		return;
	}
	if (bmih.biclrused==0) bmih.biclrused=power(bmih.bibitcount);
	if (bmih.bibitcount==24)
	{
		show_message("Cannot load 24-bit BMP.");
		file.close();
		return;
	}
	load_palette();
	if (bmih.bibitcount==1)			// 2 color bmp
		show_one_bit_bitmap();
	if (bmih.bibitcount==4)			// 16-color bmp
		show_four_bit_bitmap();
	if (bmih.bibitcount==8)			// 256-color bmp
		show_eight_bit_bitmap();

       file.close();
       } //End Of Show Bitmap

	/*End Of All Functions For Bitmap*/



#endif