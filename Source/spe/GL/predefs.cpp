//pre defines
typedef unsigned char  byte;
typedef unsigned short word;
typedef unsigned long  dword;

void setrgbpalette(int color,int r,int g,int b);

void clearviewport();

word getmaxy();

word getmaxx();

byte getcolor();

void setcolor(byte color);

void fadein();

void setbwpal();

void set_palette(byte *palette);

void circle(int x,int y, int radius, byte color = curcolor);

void rectangle(int left,int top, int right, int bottom, byte color = curcolor);

void line(int x1, int y1, int x2, int y2, byte color = curcolor);

char getpixel(int x,int y);

void putpixel(int x,int y,byte color);

void check(int &x,int &y);

void set_mode(byte mode);
