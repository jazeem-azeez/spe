
#include "screen\modexy\modexy.h"

#include <dos.h>
#include <stdio.h>
#include <mem.h>


void MODEX_DRV::mxyplot(int x, int y, char colour){
  outportb(SEQU_ADDR, 0x02);
  outportb(0x3c5, 0x01 << (x & 3));

  VgaScreen[((y<<6)+(y<<4)) + (x>>2) + db] = colour;
}

class MODEX_DRV MODEX;

char MODEX_DRV::install(){
  union REGS r;

  VgaScreen = (unsigned char *)MK_FP(0xA000, 0x0000);

  /* Set VGA BIOS mode 13h: */

  r.x.ax = 0x0013;
  int86(0x10, &r, &r);

  /* Turn off the Chain-4 bit (bit 3 at index 4, port 0x3c4): */

  outport(SEQU_ADDR, 0x0604);

  /* Turn off word mode, by setting the Mode Control register
  of the CRT Controller (index 0x17, port 0x3d4): */

  outport(CRTC_ADDR, 0xE317);

  /* Turn off doubleword mode, by setting the Underline Location
     register (index 0x14, port 0x3d4): */

  outport(CRTC_ADDR, 0x0014);

  /* Clear entire video memory, by selecting all four planes, then
  writing 0 to the entire segment. */

  outport(SEQU_ADDR, 0x0F02);
  _fmemset(VgaScreen+1, 0, 0xffff); /* stupid size_t exactly 1 too small */
  VgaScreen[0] = 0;

  /* Update the global variables to reflect the dimensions of this
  mode.  This is needed by most future drawing operations. */

  scr_x   = 320;
  scr_y  = 200;
}

char *MODEX_DRV::getname(){
  return("VGA MODE-X Driver");
}

void MODEX_DRV::box(int x, int y, int width, int height, char colour){
  int tempy;
  int tempcnt;
  for(tempy=0;tempy<height;tempy++){
    for(tempcnt=0;tempcnt<width;tempcnt++){
      mxyplot(x+tempcnt,tempy,colour);
    }
  }
}

//void MODEX_DRV::line(int sx, int sy, int ex, int ey, char colour){
//
//}

void MODEX_DRV::drawhline(int x, int y, int width, char colour){
  //char far *tempptr;
  int tempcnt;
  //tempptr=(&VgaScreen[((320/4) * y) + (x / 4)];
  for(tempcnt=0;tempcnt<width;tempcnt++){
  //  *tempptr=colour;
  //  tempptr++;
    qplot(x+tempcnt,y,colour);
  }

}

void MODEX_DRV::qplot(int x, int y, char colour){
  /* Each address accesses four neighboring pixels, so set
	   Write Plane Enable according to which pixel we want
	   to modify.  The plane is determined by the two least
	   significant bits of the x-coordinate: */

  outportb(SEQU_ADDR, 0x02);
  outportb(0x3c5, 0x01 << (x & 3));

  //outportb(SEQU_ADDR, 0x0F);
  //outportb(0x3c5, 0x02);

   /* The offset of the pixel into the video segment is
     offset = (width * y + x) / 4, and write the given
     color to the plane we selected above.  Heed the active
     page start selection. */

  VgaScreen[((y<<6)+(y<<4)) + (x>>2) + db] = colour; // need to add start address for multi-page
}

//void MODEX_DRV::plot(int x, int y, char colour, char mode){
//
//}

void MODEX_DRV::VWait(char page){
  usepage(page);

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

}

void MODEX_DRV::usepage(char page){
  db=page*80*200;
  //visStart = offset;
  outport(CRTC_ADDR, 0x0C);               /* set high byte */
  outport(CRTC_ADDR+1, db >> 8);
  outport(CRTC_ADDR, 0x0D);               /* set low byte */
  outport(CRTC_ADDR+1, db & 0xff);
}

void MODEX_DRV::clearscr(char page){
  /*outportb(SEQU_ADDR, 0x02);
  outportb(0x3c5, 0x01);

  _fmemset(VgaScreen, 0, 0x5000);

  outportb(SEQU_ADDR, 0x02);
  outportb(0x3c5, 0x01<<1);

  _fmemset(VgaScreen, 0, 0x5000);

  outportb(SEQU_ADDR, 0x02);
  outportb(0x3c5, 0x01<<2);

  _fmemset(VgaScreen, 0, 0x5000);

  outportb(SEQU_ADDR, 0x02);
  outportb(0x3c5, 0x01<<3);

  _fmemset(VgaScreen, 0, 0x5000);
  */
}

//void MODEX_DRV::getinfo(screen_info *data){
//
//}
