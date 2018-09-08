//bmp=================================================================
const int ldbmp(const int,const int,const char*);
const int svbmp(const unsigned int,const unsigned int,const unsigned int,
						const unsigned int,const char*);
class bmpFileHeader
	{
	   public:
	  char File_type[2];
	  unsigned long file_size;
	  unsigned int reserved_1;
	  unsigned int reserved_2;
	  unsigned long offset;

	  bmpFileHeader( )
		 {
		File_type[0]='B';
		File_type[1]='M';
		file_size=0;
		reserved_1=0;
		reserved_2=0;
		offset=118;
		 }
	};
 class bmpInfoHeader
	{
	   public:
	  unsigned long header_size;
	  unsigned long width;
	  unsigned long height;
	  unsigned int planes;
	  unsigned int image_bits;
	  unsigned long compression;
	  unsigned long image_size;
	  unsigned long horizontal_ppm;
	  unsigned long vertical_ppm;
	  unsigned long colors_used;
	  unsigned long important_colors;

	  bmpInfoHeader( )
		 {
		header_size=40;
		width=0;
		height=0;
		planes=1;
		image_bits=4;
		compression=0;
		image_size=0;
		horizontal_ppm=0;
		vertical_ppm=0;
		colors_used=16;
		important_colors=16;
		 }
	};

class ColorPalette
	{
	   public:
	  unsigned char blue;
	  unsigned char green;
	  unsigned char red;
	  unsigned char reserved;

	  ColorPalette( )
		 {
		blue=0;
		green=0;
		red=0;
		reserved=0;
		 }
	};

bmpFileHeader Bmp_fh;
bmpInfoHeader Bmp_ih;
ColorPalette ColorTable[16];

const int wtbmpflhdr(const char *BmpFile)
	{
	   fstream File(BmpFile,ios::out|ios::nocreate|ios::binary);

	   if(!File)
	  return 1;

	   File.seekp(0,ios::beg);

	   File.write((char*)&Bmp_fh,sizeof(Bmp_fh));

	   File.close( );

	   return 0;
	}

 const int wtbmpinfhdr(const char *BmpFile)
	{
	   fstream File(BmpFile,ios::out|ios::nocreate|ios::binary|ios::app);

	   if(!File)
	  return 1;

	   File.write((char*)&Bmp_ih,sizeof(Bmp_ih));

	   File.close( );

	   return 0;
	}

  const int wtbmpclrtbl(const char *BmpFile)
	{
	   fstream File(BmpFile,ios::out|ios::nocreate|ios::binary|ios::app);

	   if(!File)
	  return 1;

	   unsigned char RGB_0=char(0);
	   unsigned char RGB_128=char(128);
	   unsigned char RGB_192=char(192);
	   unsigned char RGB_255=char(255);

	   unsigned char Palette[16][4]={
				  { RGB_0   , RGB_0   , RGB_0   , RGB_0 },
				  { RGB_128 , RGB_0   , RGB_0   , RGB_0 },
				  { RGB_0   , RGB_128 , RGB_0   , RGB_0 },
				  { RGB_128 , RGB_128 , RGB_0   , RGB_0 },
				  { RGB_0   , RGB_0   , RGB_128 , RGB_0 },
				  { RGB_128 , RGB_0   , RGB_128 , RGB_0 },
				  { RGB_0   , RGB_128 , RGB_128 , RGB_0 },
				  { RGB_192 , RGB_192 , RGB_192 , RGB_0 },
				  { RGB_128 , RGB_128 , RGB_128 , RGB_0 },
				  { RGB_255 , RGB_0   , RGB_0   , RGB_0 },
				  { RGB_0   , RGB_255 , RGB_0   , RGB_0 },
				  { RGB_255 , RGB_255 , RGB_0   , RGB_0 },
				  { RGB_0   , RGB_0   , RGB_255 , RGB_0 },
				  { RGB_255 , RGB_0   , RGB_255 , RGB_0 },
				  { RGB_0   , RGB_255 , RGB_255 , RGB_0 },
				  { RGB_255 , RGB_255 , RGB_255 , RGB_0 }
					 };

	   for(int color=0;color<16;color++)
	  File.write((char*)&Palette[color],sizeof(Palette[color]));

	   File.close( );

	   return 0;
	}


 const int sv16clrbmp(const int x,const int y,const char *BmpFile)
	{
	   fstream File(BmpFile,ios::out|ios::nocreate|ios::binary|ios::app);

	   if(!File)
	  return 1;

	   unsigned char Color;
	   unsigned char Rgb_color_index_1;
	   unsigned char Rgb_color_index_2;

	   int screen_x;
	   int screen_y;
	   int extra_pixel_flag=0;
	   int extra_bytes=(Bmp_ih.width%8);
	   int horizontal_pixels=Bmp_ih.width;
	   int vertical_pixels=Bmp_ih.height;

	   if(extra_bytes!=0)
	  {
		 extra_bytes=(8-extra_bytes);
		 extra_bytes/=2;
	  }

	   if((Bmp_ih.width%2)==1)
	  {
		 extra_pixel_flag=1;
		 horizontal_pixels--;
	  }

	   for(int i=0;i<vertical_pixels;i++)
	  {
		 for(int j=0;j<horizontal_pixels;j++)
		{
		   screen_x=(x+j);
		   screen_y=(y-i);

		   Rgb_color_index_1=getpixel(screen_x,screen_y);

		   j++;
		   screen_x=(x+j);

		   Rgb_color_index_2=getpixel(screen_x,screen_y);

		   Rgb_color_index_1<<=4;
		   Color=(Rgb_color_index_1|Rgb_color_index_2);

		   File.put(Color);
		}

		 if(extra_pixel_flag)
		{
		   Color<<=8;
		   screen_x=(x+j);

		   Rgb_color_index_1=getpixel(screen_x,screen_y);

		   Rgb_color_index_1<<=4;
		   Color=Rgb_color_index_1;

		   File.put(Color);
		}

		 Color<<=8;

		 for(int k=0;k<extra_bytes;k++)
		File.put(Color);
	  }

	   File.close( );

	   return 0;
	}


 const int svbmp(const unsigned int x_1,const unsigned int y_1,
			 const unsigned int x_2,const unsigned int y_2,	const char *BmpFile)
	{
	   fstream File(BmpFile,ios::out|ios::binary|ios::trunc);

	   if(!File)
	  return 1;

	   File.close( );

	   unsigned long horizontal_pixels=((x_2-x_1)+1);
	   unsigned long vertical_pixels=((y_2-y_1)+1);

	   int extra_bytes=(horizontal_pixels%8);

	   horizontal_pixels+=extra_bytes;
	   horizontal_pixels/=2;

	   unsigned long image_size=(horizontal_pixels*vertical_pixels);
	   unsigned long file_size=(image_size+118);

	   // Writing bmp File Header

	   Bmp_fh.file_size=file_size;
	   Bmp_fh.offset=118;

	   if(wtbmpflhdr(BmpFile))
	  return 1;

	   // Writing bmp Info Header

	   Bmp_ih.width=((x_2-x_1)+1);
	   Bmp_ih.height=((y_2-y_1)+1);
	   Bmp_ih.image_size=image_size;

		 Bmp_ih.image_bits=4;
		 Bmp_ih.colors_used=16;
		 Bmp_ih.important_colors=16;

	   if(wtbmpinfhdr(BmpFile))
	  return 1;


	   // Writing Color Table

	   if(wtbmpclrtbl(BmpFile))
	  return 1;


	   // Saving bmp

	  sv16clrbmp(x_1,y_2,BmpFile);

	   return 0;
	}

 const int rdbmpflhdr(const char *BmpFile)
	{
	   fstream File(BmpFile,ios::in|ios::nocreate|ios::binary);

	   if(!File)
	  return 1;

	   File.seekg(0,ios::beg);

	   File.read((char*)&Bmp_fh,sizeof(Bmp_fh));

	   File.close( );

	   return 0;
	}


 const int rdbmpinfhcr(const char *BmpFile)
	{
	   fstream File(BmpFile,ios::in|ios::nocreate|ios::binary);

	   if(!File)
	  return 1;

	   File.seekg(14,ios::beg);

	   File.read((char*)&Bmp_ih,sizeof(Bmp_ih));

	   File.close( );

	   return 0;
	}

 const int rdbmpclrtbl(const char *BmpFile)
	{
	   fstream File(BmpFile,ios::in|ios::nocreate|ios::binary);

	   if(!File)
	  return 1;

	   int palette_size=16;//sony1 16->96

	   if(Bmp_ih.image_bits==1)
	  palette_size=2;

	   File.seekg(54,ios::beg);

	   for(int color=0;color<palette_size;color++)
	  File.read((char*)&ColorTable[color],sizeof(ColorTable[color]));

	   File.close( );

	   return 0;
	}


 const int gtclr(const int index)
	{
	   int color=0;

	   int red=ColorTable[index].red;
	   int green=ColorTable[index].green;
	   int blue=ColorTable[index].blue;

		 if(red==0 && green==0 && blue==0)
		color=0;

		 else if(red==0 && green==0 && blue==128)
		color=1;

		 else if(red==0 && green==128 && blue==0)
		color=2;

		 else if(red==0 && green==128 && blue==128)
		color=3;

		 else if(red==128 && green==0 && blue==0)
		color=4;

		 else if(red==128 && green==0 && blue==128)
		color=5;

		 else if(red==128 && green==128 && blue==0)
		color=6;

		 else if(red==192 && green==192 && blue==192)
		color=7;

		 else if(red==128 && green==128 && blue==128)
		color=8;

		 else if(red==0 && green==0 && blue==255)
		color=9;

		 else if(red==0 && green==255 && blue==0)
		color=10;

		 else if(red==0 && green==255 && blue==255)
		color=11;

		 else if(red==255 && green==0 && blue==0)
		color=12;

		 else if(red==255 && green==0 && blue==255)
		color=13;

		 else if(red==255 && green==255 && blue==0)
		color=14;

		 else if(red==255 && green==255 && blue==255)
		color=15;

		 else
		color=index;

	   return color;
	}


 const int shw16clrbmp(const int x,const int y,const char *BmpFile)
	{
	   fstream File(BmpFile,ios::in|ios::nocreate|ios::binary);

	   if(!File)
	  return 1;

	   File.seekg(Bmp_fh.offset,ios::beg);

	   unsigned char Color;

	   int screen_x;
	   int screen_y;
	   int extra_pixel_flag=0;
	   int extra_bytes=(Bmp_ih.width%8);
	   int horizontal_pixels=Bmp_ih.width;
	   int vertical_pixels=(Bmp_ih.height-1);

	   if(extra_bytes!=0)
	  {
		 extra_bytes=(8-extra_bytes);
		 extra_bytes/=2;
	  }

	   if((Bmp_ih.width%2)==1)
	  {
		 extra_pixel_flag=1;
		 horizontal_pixels--;
	  }

	   for(int i=vertical_pixels;i>=0;i--)
	  {
		 for(int j=0;j<horizontal_pixels;j++)
		{
		   File.get(Color);

		   screen_x=(x+j);
		   screen_y=(y+i);

		   putpixel(screen_x,screen_y,gtclr(Color>>4));

		   j++;
		   screen_x=(x+j);
		   Color<<=4;

		   putpixel(screen_x,screen_y,gtclr(Color>>4));
		}

		 if(extra_pixel_flag)
		{
		   File.get(Color);

		   screen_x=(x+j);

		   putpixel(screen_x,screen_y,gtclr(Color>>4));
		}

		 for(int k=0;k<extra_bytes;k++)
		File.get(Color);
	  }

	   File.close( );

	   return 0;
	}


 const int ldbmp(const int x,const int y,const char *BmpFile)
	{
	   fstream File(BmpFile,ios::in|ios::nocreate|ios::binary);

	   if(!File)
	  return 1;

	   File.close( );

	   // Reading bmp File Header

	   if(rdbmpflhdr(BmpFile))
	  return 1;

	   if(Bmp_fh.File_type[0]!='B' || Bmp_fh.File_type[1]!='M')
	  return 2;


	   // Reading bmp Info Header

	   if(rdbmpinfhcr(BmpFile))
	  return 1;

	   if(Bmp_ih.image_bits!=4)
	  return 3;

	   if(Bmp_ih.compression!=0)
	  return 4;


	   // Reading Color Table

	   if(rdbmpclrtbl(BmpFile))
	  return 1;

	   // Showing bmp

	  shw16clrbmp(x,y,BmpFile);

	   return 0;
	}

