///////////////////////////////////////////////////////
//                                                   //
//        VESA Screen Driver - Version 1.01          //
//                                                   //
//           By Kevin Campbell 17/12/96              //
//                                                   //
//                                                   //
///////////////////////////////////////////////////////

#ifndef VESA_VDUDRV
#define VESA_VDUDRV

extern class VESA_640_480_DRV   VESA_640_480;
//extern class VESA_320_256_DRV   VESA_320_256;

/*
	These are a set of functions designed to aid in the usage
	of VESA graphics functions. The VESA class library also
	contains many graphical functions of it's own to do simple
	graphics such as lines, cirlces and blitting.

	The functions in this version of the library are crude and
	slow. The performance of these functions makes them unsuitable
	for high-speed applications such as action games and graphics
	packages. They will be optimised and improved upon at a later
	date.

	Things to Note :-

		Do not use any graphical functions unless a VESA mode
		has been set using SetMode().

		Do not use drawhline() for lines that will finish beyond
		the screen co-ordinates, doing so will cause
		unpredictable results (possible crash).

		Do not use the graphical functions for modes other than
		0x101, 0x103 and 0x105. These are the only Packed Pixel
		format modes in 256 colours available to VESA. Using the
		graphical functions in other modes will not crash the
		machine, but will produce erratic displays. To use the
		other modes, use the Info() and ModeInfo() functions to
		create your own graphical routines.
*/

/*
	Future additions to the VESA library:

		High speed RLE Blitting


*/

#include "screen\screen.h"

#define ROM_CHAR_SET_SEG 0xF000  // segment of 8x8 ROM character set
#define ROM_CHAR_SET_OFF 0xFA6E  // begining offset of 8x8 ROM character set

#define CHAR_WIDTH        8
#define CHAR_HEIGHT       8

#define VESA_Int 0x10 		// The VESA Interrupt Number
#define PIXELS 0x00
#define BYTES 0x02
#define SCAN_CURR 0x00
#define SCAN_MAX 0x02
#define VESA_GET_START 0x01
#define VESA_SET_START 0x00
#define VESA_SET_START_VS 0x80

#define VESA_MAX_Y 1024 // Maximum number of Y-Lines

#define REPLACE 0
#define TRANS 1
#define BEHIND 2
#define INVERSE 3

typedef unsigned long int DWORD;

union revision{
  unsigned int full;
  struct {
    char l;
    char h;
  }s;
};

struct VESAInfo {
  char Signature[4];			// "VESA", just ASCII, not C/C++ ASCIIZ
  union revision Version;			// Version number.
  char far *OemStringPtr;		// Pointer to OEM string.
  long Capabilities;			// Undefined up to VESA 1.2
  int far *VideoModePointer;		// Pointer to 'Table of Modes' (Read: load of ModeInfo's)
  unsigned int Memory;			// Memory in bytes divided by 65536 (Num. 64KB Blocks!)
  unsigned int OemSoftwareRev;
  char far *OemVendorNamePtr;
  char far *OemProductNamePtr;
  char far *OemProductRevPtr;
  char Reserved[222];			// Reserved (Read: VESA Crap-Up space)
  char OemData[256];
};

struct VESA_ModeAttributes{
  unsigned Supported : 1;
  unsigned : 1;		// Reserved
  unsigned TTY : 1;
  unsigned Colour : 1;
  unsigned VGA : 1;
  unsigned Window : 1;
  unsigned Linear : 1;
  unsigned : 8;		// Reserved
};

struct VESAMode{
  struct VESA_ModeAttributes ModeAttributes;	// Bits:- 0:Can do it,1:Extra Info,2:BIOS Support,3:Colour?,4:Graphics?
  unsigned char WinA_Attributes;		// Bits:- 0:Exists,1:Readable,2:Writable
  unsigned char WinB_Attributes;		// Bits:- 0:Exists,1:Readable,2:Writable
  unsigned int WinGranularity;			// Smallest window move step.
  unsigned int WinSize;				// Window Size: Norm. 32/64 (KB)
  unsigned int WinA_Segment;			// CPU Segment address
  unsigned int WinB_Segment;			// CPU Segment address
  void far *WindowFunctionPtr;			// Switch-bank direct function pointer
  unsigned int BytesPerScanLine;		// Pixels per row, sort of.
  unsigned int XResoloution;			// Err...
  unsigned int YResoloution;			// Um...
  unsigned char Char_XRES;			// default font Width
  unsigned char Char_YRES;			// Default font Height
  unsigned char NumPlanes;			// Ignore: Usually 4 for 16 colour modes, 1 for 256+ colour modes
  unsigned char BitsPerPixel;			// 16:4,256:8,32K:16,64K:24, or 16.7M:32
  unsigned char NumBanks;			// | Number of banks | 		((X*Y*BitsPerPixel)/8)/64
  unsigned char MemoryModel;			// All Crap. Set to 5 for 256 col modes.
  unsigned char BankSize;			// Ignore, VESA 1.2 adds Num. pages after this.
  unsigned char NumPages;
  unsigned char Reserved;

  // Direct Colour Info

  unsigned char RedMaskSize;
  unsigned char RedFieldPos;
  unsigned char GreenMaskSize;
  unsigned char GreenMaskPos;
  unsigned char BlueMaskSize;
  unsigned char BlueMaskPos;
  unsigned char RsvdMaskSize;
  unsigned char RsvdMaskPos;
  unsigned char DirectInfo;

  // Mandatory VBE 2.0

  unsigned char PhysBasePtr[4];
  unsigned char OffScreenMemOffset[4];
  unsigned int OffScreenMemSize;
  unsigned char Reserveda[206];
};


struct VESA_ModeSet{
  unsigned Mode : 9;
  unsigned Reserved : 5;
  unsigned Linear : 1;
  unsigned Preserve : 1;
};


struct VESA_LineInfo{
  unsigned int offset;
  unsigned char window;
  unsigned char split; // Does the line split
  unsigned int splitpos; // The position of the split (only if split is true).
};

struct VESA_Pal{
  char pad;
  char R;
  char G;
  char B;
};

struct VESA_args{
  int mode;
};





class VESA{
public:
  char VESA_GetInfo(void);
  char VESA_ModeInfo(int mode);
  char VESA_SetMode(int mode, char linear, char preserve);
  char VESA_SetWindow(char window, int position);
  char VESA_GetWindow(char window, int *position);
  char VESA_GetLength(char type, int *pixels, int *bytes, int *scan_lines);
  char VESA_SetLength(char type, int *length, int *scan_lines);
  char VESA_Start(char action, int *pixel, int *line);
  char VESA_Setpal(int numpal, int startpal, VESA_Pal *table);

  static struct VESAInfo far vesainfo;	// Thingies to hold info
  static struct VESAMode far modeinfo; 	//
  static char installed;       		// Is a VESA card installed
  static union revision level; 		// Level of VESA implemenation
  static char granularity;    		// Win-shift scale
  static int curwindow; 		// currently being used VESA window
  static char far *WinPointer;          //
  static void far *VESA_WinFunc;
};


class VESAdrv : public VESA, public VDUdrv{
public:

// VDUdrv functions

  char softtest();

  void box(int x, int y, int width, int height, char colour);
  void line(int sx, int sy, int ex, int ey, char colour);
  void drawhline(int x, int y, int width, char colour);
  void qplot(int x, int y, char colour);
  void plot(int x, int y, char colour, char mode);

  void VWait(char page);
  void usepage(char page);

  void getinfo(screen_info *data);

  char qget(int x, int y, char *colour);
  void blit(int x, int y, struct shape far *data);
  void get(int x, int y, int xs, int ys, char huge *data);
  void put(int x, int y, int xs, int ys, char huge *data);

  char Info(struct VESAInfo far *details);
  char ModeInfo(int mode, struct VESAMode far *details);
  char Installed();

// Specific

  VESAdrv();
  ~VESAdrv();

  char SetMode(int mode);
  char setstart(int x,int y);

  void setoffsets(); // Sets all offset variables

  inline void UseWin(char window);
  inline void MemDraw(int offset, char far *pic, char window, int width);
  inline void MemCopy(int offset, char far *pic, char window, int width);

  inline void scanline(int x, int y, int width, char far *data);
  inline void getline(int x, int y, int width, char far *data);

  inline char VESA_BlitLine(int window,int offset,int width,char far *bdat);
  inline char VESA_GetLine(int window,int offset,int width,char far *bdat);
  inline char VESA_ScanLine(int window,int offset,int width,int colour);

  inline void VESA_DrawReplace(int offset, char colour);
  inline void VESA_DrawTrans(int offset, char colour);
  inline void VESA_DrawBehind(int offset, char colour);
  inline void VESA_DrawInverse(int offset, char colour);

  char palset(char palnum, char R, char G, char B);
  char setpal(VESA_Pal *pd);

  void WaitRetrace();

  static int curx, cury;
  static int VESA_X, VESA_Y;

  static char far *CardName();

  static struct VESA_LineInfo Lines[VESA_MAX_Y];

  static unsigned char far *rom_char_set;

};







				//
				//
//////////////////////////////////////////
//                              //
//  Screen Driver               //
//            Class Modules     //
//                              //
////////                        //
				//
				//
				//
				//

class VESA_640_480_DRV : public VESAdrv{
public:
  //char softtest();
  char hardtest();
  char install();
  char *getname();
};




#endif













