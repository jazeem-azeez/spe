
#ifndef MODEXY_H
#define MODEXY_H

#define SEQU_ADDR 0x3c4
#define CRTC_ADDR 0x3d4

#include "screen\screen.h"

extern class MODEX_DRV MODEX;

class MODEX_DRV : public VDUdrv{
public:

  //char virtual softtest();
  //char virtual hardtest();
  char install();
  char *getname();

  void box(int x, int y, int width, int height, char colour);
  //void line(int sx, int sy, int ex, int ey, char colour);
  void drawhline(int x, int y, int width, char colour);
  void qplot(int x, int y, char colour);
  //void plot(int x, int y, char colour, char mode);

  //void virtual text(int x,int y,int colour, char *string,int trans_flag,unsigned int max_char=66535);
  //void virtual letter(int xc,int yc,char c,int colour,int trans_flag);


  void VWait(char page);
  void usepage(char page);
  void clearscr(char page);

  //void getinfo(screen_info *data);

// Specific

  char far *VgaScreen;

  inline void mxyplot(int x, int y, char colour);


};

#endif