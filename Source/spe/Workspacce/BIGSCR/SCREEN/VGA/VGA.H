///////////////////////////////////////////////////////
//                                                   //
//        VGA Graphics Driver - Version 1.00         //
//                                                   //
//           By Kevin Campbell 15/10/96              //
//                                                   //
//                                                   //
///////////////////////////////////////////////////////

extern class VGA_DRV VGA_320_200;

#include "screen\screen.h"

class VGA_DRV : public VDUdrv{
public:


// VDUdrv functions

  char softtest();
  char hardtest();
  char install();
  char *getname();

  void box(int x, int y, int width, int height, char colour);
  void line(int sx, int sy, int ex, int ey, char colour);
  void drawhline(int x, int y, int width, char colour);
  void qplot(int x, int y, char colour);
  void plot(int x, int y, char colour, char mode);

  void VWait(char page);
  void usepage(char page);

  void getinfo(screen_info *data);

// Specific functions

  void HLine(int x1, int x2, int y, char color);
  void VLine(int x, int y1, int y2, char color);
  void whackbuffer(char page);
  void clearbuffer(char page);

  void fastblit(int x,int y,char far *tile);

  //VGA_DRV();
  //~VGA_DRV();

// Variables

  int OldMode;				// variable to save user's original mode
  unsigned char far *VgaScreen;		// variable to point to screen
  unsigned char far *UserFont;		// variable to save user's original font
  unsigned char far *Font;

  char far *scrbuf[2];

  int VGA_X;
  int VGA_Y;
  int VGA_B;

};






