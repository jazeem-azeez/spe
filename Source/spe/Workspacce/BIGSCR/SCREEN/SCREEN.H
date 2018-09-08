
#ifndef SCREEN_H
#define SCREEN_H

#include "linklist\voidlist.h"
#include "drivers\drivers.h"

#define ROM_CHAR_SET_SEG 0xF000  // segment of 8x8 ROM character set
#define ROM_CHAR_SET_OFF 0xFA6E  // begining offset of 8x8 ROM character set

#define CHAR_WIDTH        8
#define CHAR_HEIGHT       8

extern class VDUdrv *screen;
extern void terminate(char far *message);

class screen_info{
public:
  int x_res;
  int y_res;
  char bits_per_plane;
};


class VDUdrv : public driver{
public:

  char virtual softtest();
  char virtual hardtest();
  char virtual install();
  char virtual *getname();

  void virtual box(int x, int y, int width, int height, char colour);
  void virtual line(int sx, int sy, int ex, int ey, char colour);
  void virtual drawhline(int x, int y, int width, char colour);
  void virtual qplot(int x, int y, char colour);
  void virtual plot(int x, int y, char colour, char mode);

  void virtual text(int x,int y,int colour, char *string,int trans_flag=1,unsigned int max_char=66535);
  void virtual letter(int xc,int yc,char c,int colour,int trans_flag);

  void virtual VWait(char page=0);
  void virtual usepage(char page=0);
  void virtual clearscr(char page=0);

  void virtual getinfo(screen_info *data);

  void virtual swapdb();
  void virtual vwaitdb();
  void virtual currdb();
  void virtual alldb();

  static int scr_x;
  static int scr_y;

  static int db;
  static int dx;

};



/*class VDUdrv{
public:
  char name[256];

  char softtest();

  // CONTROL FUNCTIONS - DO NOT TOUCH DIRECTLY

  char hardtest();

  void install();
  void playraw(class sound *data);

  // Screen Functions

  char *CardName();

  // Misc Standard Functions

  char palset(char palnum, char R, char G, char B);
  char setpal(VESA_Pal *pd);
  void VWait();

  // Misc Graphics functions

  void drawhline(int x, int y, int width, char colour);
  void line(int startx, int starty, int endx, int endy, char colour);
  void box(int x, int y, int width, int height, char colour);
  char qplot(int x, int y, char colour);
  char qget(int x, int y, char *colour);
  void text(int x,int y,int color, char *string,int trans_flag,unsigned int max_char=65535);
  //void Text(char
  char plot(int x, int y, char colour, char mode);
  void blit(int x, int y, struct shape *data);
  void get(int x, int y, int xs, int ys, char huge *data);
  void put(int x, int y, int xs, int ys, char huge *data);

};  */



#endif