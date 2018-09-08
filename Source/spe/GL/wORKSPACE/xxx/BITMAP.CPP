#include<Graphics.h>
#include"256.h"
#include<fstream.h>
#include<string.h>
#include<conio.h>

class BITMAP
{
  private :
	 int x,y;
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

  public :

  void put_pixel(int &x,int &y,unsigned char &color,int bitno);
  int  power(int no);
  void show_message(char *string);
  int  open_file();
  void load_palette();
  void show_one_bit_bitmap();
  void show_four_bit_bitmap();
  void show_eight_bit_bitmap();
  void Show_BMP(char*);

};//End Of Class All Functions Prototypes


/*Define Functions */

  void BITMAP::put_pixel(int &x,int &y,unsigned char &color,int bitno)
  {
      if (color>=bitno)
      {
	    putpixel(x,y,2);
	    color-=bitno;
      }
      else putpixel(x,y,1);
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
		putpixel(x,y,(color>>4)+1);x++;
		if (x>maxx) { x=1;y--; }
		if (color>=128) color-=128;
		if (color>=64) color-=64;
		if (color>=32) color-=32;
		if (color>=16) color-=16;
		putpixel(x,y,color+1);x++;
		if (x>maxx) { x=1;y--; }
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
			putpixel(x,y,color+1);
		}
		if (bmih.biwidth%4!=0)
		{
			for (int x=bmih.biwidth%4;x<4;x++)
			  file.read((char *)&color,sizeof(color));
		}
	   }
  }
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
	if (bmfh.bftype[0]!='B' | bmfh.bftype[1]!='M' )
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
       } //End Of Show Bitmap

	/*End Of All Functions For Bitmap*/



void main()  //Example How To Use The Class To View A Bmp File
{
	BITMAP Image;//Variable of The Class

	Graphinit();/*256 Graphics Mode Initialisation*/

	Image.Show_BMP("setup.bmp");/*Pass The Path Of The File*/

	getch();

	closegraph();
}
/***************************************************/
