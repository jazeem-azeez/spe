/*

						   * * * * * * * * * * * *
						   * Cursor Reader v1.00 *
						   * * * * * * * * * * * *



							  Programmed by Yas

							   SZABIST Karachi

								  PAKISTAN



	The cursor reader is basically a program which will read cursor files.
The cursor files can be created and can be opened through C and mapped as
mouse cursors.

	This program is actually a part of the GFX Library. The reason for
making this seperate API is to optamize memory and so that the programmer does
not have to take the fatigue of making long arrays which will occupy a lot of
memory in the the orignal program. A lot of memory can be saved and can be
used somewhere else.

	This program is compiled with the Borland Turbo C++ v3.0 compiler.



For comments & suggestions e-mail me at:
										realyas2001@hotmail.com
*/

#ifndef __CURSOR_H
#define __CURSOR_H


#ifndef __GRAPHICS_H
#include<graphics.h>
#endif

#ifndef __DOS_H
#include<dos.h>
#endif

#ifndef __STDIO_H
#include<stdio.h>
#endif




/* These macros will be used to by the function readcursorfile. They will
   give you the status whether a cursor image file has been read or not by
   the program. */

#ifndef FILE_READING_ERROR
#define FILE_READING_ERROR 255
#endif

#ifndef HEADER_READING_ERROR
#define HEADER_READING_ERROR 254
#endif

#ifndef NOT_CURSOR_FILE
#define NOT_CURSOR_FILE 253
#endif

#ifndef TOO_MANY_IMAGES
#define TOO_MANY_IMAGES 252
#endif

#ifndef WIDTH_HEIGHT_ERROR
#define WIDTH_HEIGHT_ERROR 251
#endif

#ifndef TOO_MANY_COLORS
#define TOO_MANY_COLORS 250
#endif

#ifndef FILE_READ_SUCCESSFULLY
#define FILE_READ_SUCCESSFULLY 0
#endif




/* Just in case memory model is not set to Huge, the compiler will not compile
   the program */
#ifndef __HUGE__
#error Building memory model not defined. The memory model should be set to Huge.
#endif




/* This structure contains information about the dimensions and color format
   of a device-independent bitmap (DIB). */

typedef struct
{

	/* Specifies the size of the structure, in bytes. This size does not
	   include the color table or the masks mentioned in the clrused member. */
	unsigned long size;

	/* Specifies the width of the bitmap, in pixels. */
	long width;

	/* Specifies the height of the bitmap, in pixels. If height is positive,
	   the bitmap is a bottom-up DIB and its origin is the lower-left corner.
	   If height is negative, the bitmap is a top-down DIB and its origin is
	   the upper-left corner. Top-down DIBs cannot be compressed. */
	long height;

	/* Specifies the number of planes for the target device. This value must
	   be set to 1. */
	unsigned int planes;

	/* Specifies the number of bits per pixel. The bitcount member of the
	   BITMAPINFOHEADER structure determines the number of bits that define
	   each pixel and the maximum number of colors in the bitmap. This member
	   must be one of the following values. Value description:


	   1	   The bitmap is monochrome then there are only two colors. Each
			   bit in the bitmap array represents a pixel. If the bit is clear,
			   the pixel is displayed with the color of the first entry in the
			   bmiColors tableif the bit is set, the pixel has the color of
			   the second entry in the table.

	   4 	   The bitmap has a maximum of 16 colors, and the bmiColors
			   member contains up to 16 entries. Each pixel in the bitmap is
			   represented by a 4-bit index into the color table. For example,
			   if the first byte in the bitmap is 0x1F, the byte represents
			   two pixels. The first pixel contains the color in the second
			   table entry, and the second pixel contains the color in the
			   sixteenth table entry. */

	unsigned int bitcount;

	/* Specifies the type of compression for a compressed bottom-up bitmap
	   (top-down DIBs cannot be compressed). */
	unsigned long compression;

	/* Specifies the size, in bytes, of the image. */
	unsigned long sizeimage;

	/* Specifies the horizontal resolution, in pixels per meter, of the target
	   device for the bitmap. An application can use this value to select a
	   bitmap from a resource group that best matches the characteristics of
	   the current device. */
	long xpelspermeter;

	/* Specifies the vertical resolution, in pixels per meter, of the target
	   device for the bitmap. */
	long ypelspermeter;

	/* Specifies the number of color indexes in the color table that are
	   actually used by the bitmap. If this value is zero, the bitmap uses
	   the maximum number of colors corresponding to the value of the
	   bitcount member for the compression mode specified by compression.
	   If clrused is nonzero and the bitcount member is less than 16, the
	   clrused member specifies the actual number of colors the graphics
	   engine or device driver accesses. If bitcount is 16 or greater, the
	   clrused member specifies the size of the color table used to optimize
	   performance of the system color palettes. If biBitCount equals 16 or 32,
	   the optimal color palette starts immediately following the three DWORD
	   masks.

	   If the bitmap is a packed bitmap (a bitmap in which the bitmap array
	   immediately follows the BITMAPINFO header and is referenced by a single
	   pointer), the biClrUsed member must be either zero or the actual size
	   of the color table. */
	unsigned long clrused;

	/* Specifies the number of color indexes required for displaying the bitmap.
	   If this value is zero, all colors are required. */
	unsigned long clrimportant;
}BITMAPINFOHEADER;




/* This structure describes a color consisting of relative intensities of red,
   green, and blue. */

typedef struct
{

	/* Specifies the intensity of blue in the color. */
	unsigned char blue;

	/* Specifies the intensity of green in the color. */
	unsigned char green;

	/* Specifies the intensity of red in the color. */
	unsigned char red;

	/* (Reserved) Set to zero. */
	unsigned char reserved;
}RGBQUAD;


/* This is the first structure that is read in a cursor file. This structure
   contains the basic information regarding the type of file and the total
   number of images the file contains. */

typedef struct
{

	/* (Reserved) Set to zero. */
	unsigned int reserved;

	/* The type member indicates whether the file is an icon file or a cursor
	   file. The value of this member is 1 if it is an icon and is 2 if it is
	   a cursor */
	unsigned int type;

	/* The member count contains information on how many images are there in
	   the file */
	unsigned int count;

}CURSORDIR;



/* This structure contains information on every image present in the cursor
   file */

typedef struct
{
	/* This member contains information on the total width of all the images
	   present int the file */
	unsigned char width;

	/* This member contains information on the total height of all the images
	   present in the file */
	unsigned char height;

	/* This member contains information on the number of colors, the cursor is
	   made up of. */
	unsigned char colorcount;

	/* (Reserved) Set to zero. */
	unsigned char reserved;

	/* This member contains information regarding the x-hotspot of the cursor */
	unsigned int xhotspot;

	/* This member contains information regarding the y-hotspot of the cursor */
	unsigned int yhotspot;

	/* This member contains information on the total number of bytes present
	   in the resource */
	unsigned long bytesinres;

	/* This member contains location in the file where the orignal image is
	   present */
	unsigned long imageoffset;
}CURSORDIRENTRY;




/* This structure contains information on the orignal image and also contains
   the orignal data.

   NOTE: This structure is not actually the CURSORIMAGE structure rather it
		 has a few modifications. These modifications include that the color,
		 xor & and members  */

typedef struct
{

	/* This header contains information on the indivisual cursor images. */
	BITMAPINFOHEADER header;

	/* This member contains information regarding the color table */
	RGBQUAD colors[2];

	/* This is the cursor mask */
	unsigned char xor[64];

	/* This is the screen mask */
	unsigned char and[64];
}CURSOR2IMAGE16;




/* This structure is important to save the mouse cursor shape */

typedef struct
{

	/* This will store the orignal shape of the mouse cursor */
	unsigned int image[32];

	/* This will save the mouse cursor hotspots i.e. the x-hotspot and the
	y-hotspot. Another question which might come to your mind is that why are
	we taking the fatigue of saving the both hotspots in only one variable,
	we could have used this variable for the x-hotspot and the other one for
	the y-hotspot. Well the reason for this is the conservation of memory. If
	we follow the method explained above, we will see that we will have a loss
	of one byte every time a variable of this data type is created. In the
	method I have implemented, we see that since in a cursor of such type i.e.
	a 16 square if we save the hotspot, it will only occupy 4-bits for the
	x-hotspot and 4-bits for the y-hotspot. So in my method there will be no
	loss of memory. */
	unsigned char hotspots;

}MOUSECURSOR;





/* This global variable holds the status whether the mouse is present or not.
   If the mouse pointer is present on screen then the value of this variable
   is 1 and if it is not present then the value of this variable is 0.

   Initally the alue of this variable is set to 0 i.e. no mouse pointer on
   screen. */

unsigned char status=0;



/* Shows mouse pointer on screen */

void showmouse(void)
{
	union REGS regs;

	/* Checking whether the mouse pointer is hidden or not, in case it is
	   hidden then call the interrupt */
	if(status==0)
	{
		regs.x.ax=1;
		int86(51,&regs,&regs);
		status=1;
	}
}


/* Hide mouse pointer on screen */

void hidemouse(void)
{
	union REGS regs;

	/* Checking whether the mouse pointer is shown or not, in case it is shown
	   then call the interrupt */
	if(status==1)
	{
		regs.x.ax=2;
		int86(51,&regs,&regs);
		status=0;
	}
}




unsigned char readcursorfile(unsigned char *file_name,MOUSECURSOR *cursor)
{
	CURSOR2IMAGE16 cursorimage;
	CURSORDIRENTRY cursordirentry;

	{

		CURSORDIR cursordir;
		{

			FILE *cursor_file;


			/* Opening the file in read-only binary mode */
			if((cursor_file=fopen(file_name,"rb"))==NULL)
				return(FILE_READING_ERROR);


			/* Just in case the header is not read this means that the file is not
			   a cursor file */
			if(fread(&cursordir,sizeof(CURSORDIR),1,cursor_file)!=1)
			{
				fclose(cursor_file);
				return(HEADER_READING_ERROR);
			}


			/* Another header present in the file */
			if(fread(&cursordirentry,sizeof(CURSORDIRENTRY),1,cursor_file)!=1)
			{
				fclose(cursor_file);
				return(HEADER_READING_ERROR);
			}


			/* This is the third and the last header present in the cursor file */
			if(fread(&cursorimage,sizeof(CURSOR2IMAGE16),1,cursor_file)!=1)
			{
				fclose(cursor_file);
				return(HEADER_READING_ERROR);
			}


			/* Since we have read all the headers therefore closing the cursor
			   file so that we can free our memory. */
			   fclose(cursor_file);

		}


		/* This member of the CURSORDIR structure should be set to 2 because
		   2 is the value which indicates that the file is a cursor file and
		   not an icon file(Additional Info: Value is set to 1 for icons). */
		if(cursordir.type!=2)
			return(NOT_CURSOR_FILE);


		/* This member of the structure indicates the total number of cursor
		   images in the file. Only one image of the cursor should be present
		   in the file because we can only display one image of mouse pointer
		   using the EGAVGA driver. Therefore the value of the count member
		   should be 1. */
		if(cursordir.count!=1)
			return(TOO_MANY_IMAGES);
	}

	/* The driver EGAVGA can only display cursor images of width and height
	   equal to 16 each. */
	if(!((cursordirentry.width==16)||(cursordirentry.height==16)))
		return(WIDTH_HEIGHT_ERROR);


	/* The EGAVGA driver only has the capability to display cursors of 2 colors.
	   So the cursor images of greater color should not be displayed */
	if(cursordirentry.colorcount!=2)
		return(TOO_MANY_COLORS);


	/* The first header used to check the width and height actually gives the
	   total height of all the images but this header gives the information
	   regarding the current image. */
	if(!((cursorimage.header.width==16)||(cursorimage.header.height==16)))
		return(WIDTH_HEIGHT_ERROR);


	/* Gives the color of the current image as bits per pixel. */
	if(cursorimage.header.bitcount!=1)
		return(TOO_MANY_COLORS);



	/* This block of code is the most important regarding the reading of
	   cursor files. The code has been optamized using various techniques.
	   First of all the things to explain in this is that these files are
	   exactly like bitmap files in which the image is stored upside down.
	   So first of all the thing to note is that in order to save your image
	   in an array you must read the buffers upside down.

	   The other thing to note is that the data present in the file is read
	   through a structure whose members(and & xor) have are of character type
	   which means that the data will be read at one byte per element but our
	   requirement is to get the data and in an array of integer so that the
	   data can be sent to an array for proccessing. So in order to achive
	   this target we must get bytes of data and then align it into an integer
	   variable. This is not the only task what we must see is that the data
	   present in a cursor file is not in a sequence rather there is a gap
	   of 2-bytes, after reading 2-bytes of required data. All this work is
	   done through this block of code. */
	{

		unsigned char element=15,value;

		for(value=0;value<128;value+=4)
		{
			cursor->image[element+16]=(unsigned int)cursorimage.xor[value]<<8;
			cursor->image[element+16]|=(unsigned int)cursorimage.xor[value+1];

			cursor->image[element]=(unsigned int)cursorimage.and[value]<<8;
			cursor->image[element--]|=(unsigned int)cursorimage.and[value+1];
		}
	}


	/* These two lines of code will be used to store the hotspots of the
	   cursor image. */
	cursor->hotspots=(unsigned char)cursordirentry.yhotspot<<4;
	cursor->hotspots|=(unsigned char)cursordirentry.xhotspot;

	/* This value is returned when the cursor file has been read successfully */
	return(FILE_READ_SUCCESSFULLY);
}




/* This function is used to set the mouse cursor to a certain specified shape */

void setmousecursor(MOUSECURSOR cursor)
{
	union REGS regs;
	struct SREGS sregs;

	unsigned char state;

	/* Saving the current state of the mouse pointer whether it is present or
	   not(on screen) */
	state=status;

	/* Hiding the mouse pointer */
	hidemouse();

	regs.x.ax=9;

	/* In the first four bits we have stored the x hotspot */
	regs.x.bx=(unsigned int)cursor.hotspots&15;

	/* In the last four bits we have stored the y hotspot */
	cursor.hotspots&=240;

	/* The value cannot directly be given to the register so we have to shift
	   4 bits to the right. Just to align the data */
	regs.x.cx=(unsigned int)cursor.hotspots>>4;

	/* Some programmers used a different method to change the mouse cursor.
	   code sometimes has problems. This code does not have any problems. */
	regs.x.dx=(unsigned int)FP_OFF((void far *)cursor.image);
	sregs.es=(unsigned int)FP_SEG((void far *)cursor.image);

	int86x(51,&regs,&regs,&sregs);

	/* Checking the state if the mouse was present then show mouse pointer
	   on screen */
	if(state==1)
		showmouse();
}

/* End of __CURSOR_H */
#endif