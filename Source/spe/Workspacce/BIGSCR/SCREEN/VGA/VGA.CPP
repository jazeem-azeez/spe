#include <string.h>
#include <dos.h>
#include <stdlib.h>
#include "screen\vga\vga.h"


// Globals Variables //////////////////

class VGA_DRV VGA_320_200;

// Function Declarations //////////////


// Function Code //////////////////////

char VGA_DRV::softtest(){
  return(1);
}

char VGA_DRV::hardtest(){
  return(1);
}

char VGA_DRV::install(){
  union REGS regs;

  VgaScreen = (unsigned char far*)MK_FP(0xA000, 0x0000); // set pointer to screen address
  OldMode = peekb(0x0040, 0x0049);   // save user's video mode first
  Font = (unsigned char far*)MK_FP(peek(0x0000,0x010e), peek(0x0000,0x010c)); // set font ptr

  scrbuf[0]=(char far *)farmalloc(66536);
  scrbuf[1]=(char far *)farmalloc(66536);

  if(scrbuf[0]==NULL | scrbuf[1]==NULL)terminate("VGA Driver - Malloc error - Double buffer creation");

  clearbuffer(0);
  clearbuffer(1);


  scr_x=320;
  scr_y=200;
  VGA_B=9;

  regs.h.ah = 0x00;			// service 0, Set Video Mode
  regs.h.al = 0x13;			// set graphics mode to 320x200x256
  int86(0x10, &regs, &regs);	// execute BIOS call

  return(1);
}

char *VGA_DRV::getname(){
  return("VGA Compatible graphics card");
}

void VGA_DRV::getinfo(screen_info *data){
  data->x_res=320;
  data->y_res=256;
  data->bits_per_plane=8;
}


void VGA_DRV::box(int x1, int y1, int width, int height, char color){
  int xctr, yctr;
  int pitch  = 320 - width;
  unsigned char far *dst = scrbuf[db] + (y1 * 320) + x1;

  for (yctr = 0; yctr < height; yctr++)
  {
    for (xctr = 0; xctr < width; xctr++)
    {
      /*switch (mode)
      {
	case REPLACE: *dst++ = color; break;
	case REVERSE: *dst++ ^= color; break;
	case OVERLAY: if (color) *dst = color; dst++; break;
	case UNDERLAY: if (!*dst) *dst = color; dst++; break;
      }*/
      *dst++ = color;

    }
    dst += pitch;
  }
}


void VGA_DRV::line(int x1, int y1, int x2, int y2, char color)
{
  float tempx, tempy, incx, incy, dx, dy;

  if (x1 == x2)                 // draw vertical line if applicable
  {
    VLine(x1, y1, y2, color);
    return;
  }

  if (y1 == y2)        		// draw horizontal line if applicable
  {
    HLine(x1, x2, y1, color);
    return;
  }

  dx = abs(x2 - x1);			// get delta x, delta y
  dy = abs(y2 - y1);

  if (dx > dy)          		// if x is primary axis...
  {
    incx = x2 > x1 ? 1:-1;
    incy = dy/dx * (y2 > y1 ? 1:-1);
    tempy = y1;
    for (tempx = x1; tempx != x2; tempx += incx)
    {
      qplot(tempx, tempy, color);
      tempy += incy;
    }

  }else{
    incy = y2 > y1 ? 1:-1;
    incx = dx/dy * (x2 > x1 ? 1:-1);
    tempx = x1;
    for (tempy = y1; tempy != y2; tempy += incy)
    {
      qplot(tempx, tempy, color);
      tempx += incx;
    }
  }
}



void VGA_DRV::HLine(int x1, int x2, int y, char color)
{
  int x;

  if(x2 > x1)
    for(x = x1; x <= x2; x++)
      qplot(x, y, color);
  else
    for(x = x2; x <= x1; x++)
      qplot(x, y, color);
}

void VGA_DRV::VLine(int x, int y1, int y2, char color)
{
  int y;

  if(y2 > y1)
    for(y = y1; y <= y2; y++)
      qplot(x, y, color);
  else
    for(y = y2; y <= y1; y++)
      qplot(x, y, color);
}


void VGA_DRV::qplot(int x, int y, char colour){
  *(scrbuf[db]+(y*scr_x)+x)=colour;
}

void VGA_DRV::plot(int x, int y, char colour, char mode){

  unsigned char far *ptr = scrbuf[db] + (y * 320) + x;

  //switch (mode)
  //{
    /*case REPLACE: 	*ptr = color; break;
    case REVERSE:	*ptr ^= color; break;
    case OVERLAY:	if (color) *ptr = color; break;
    case UNDERLAY:	if (!*ptr) *ptr = color; break;*/
    *ptr=colour;
  //}
}

void VGA_DRV::drawhline(int x, int y, int width, char colour){
  int cnt;
  char far *tempaddr;

  tempaddr=scrbuf[db]+(y*320)+x;

  for(cnt=0;cnt<width;cnt++){
    *tempaddr=colour;
    tempaddr++;
  }
}


void VGA_DRV::VWait(char page){

// VWait routine - used courtesy of James Slaughter
// Thanks James :)

  asm{
    mov dx,0x3DA
  }
Rep1:
  asm{
    in al,dx
    and al,0x08
    jnz Rep1
  }
Rep2:
  asm{
    in al,dx
    and al,0x08
    jz Rep2
  }
  // Whack the buffer to screen

  whackbuffer(page);
}

void VGA_DRV::usepage(char page){
  db=page;
}

void VGA_DRV::whackbuffer(char page){
  _fmemcpy(VgaScreen,scrbuf[page],65535);  // ******
  // Need to fix so as to copy all 64k.
}

void VGA_DRV::clearbuffer(char page){
  _fmemset(scrbuf[page],0,65535);
}

void VGA_DRV::fastblit(int x, int y, char far *tile){
  // Extremely fast blitting routine
  // (Will be <g>) Written in asm for max speed.

  char count;

  long far *tempscr=(long far *)(scrbuf[db]+(y*320)+x);

  for(count=0;count<8;count++){
    *(tempscr++)=*(long far *)(tile++);
    *(tempscr++)=*(long far *)(tile++);
    tempscr+=78; // Remaining count to get to next screen line
  }


  /*
  int tmpds=_DS; // Preserve regsiters
  int tmpdi=_DI; //
  int tmpsi=_SI; //


  asm{

    mov ES SEG scrbuf[0]
    mov DI ((x*320)+y)
    mov DS SEG tile
    mov SI OFFSET tile
    // Might be able to ignore that last line...
    //mov _AX [DS:SI]









  }

  _DS=tmpds; // Preserve regsiters
  _DI=tmpdi; //
  _SI=tmpsi; //   */
}
