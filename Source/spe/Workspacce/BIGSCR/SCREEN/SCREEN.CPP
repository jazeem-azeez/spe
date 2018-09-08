///////////////////////////////////////////////////////
//                                                   //
//  Screen Driver Class Functions - Version 1.00     //
//						     //
//           By Kevin Campbell 1/12/96               //
//                                                   //
//                                                   //
///////////////////////////////////////////////////////

#include "screen\screen.h"

class VDUdrv *screen;

char far *rom_char_set = (char far *)0xF000FA6EL; // rom characters 8x8

int VDUdrv::scr_x=0;
int VDUdrv::scr_y=0;
int VDUdrv::db=0;
int VDUdrv::dx=0;

		      //
		     //
//////////////////////////
//                 //
// Just some crap /////
//               //
//              //
	       //
	      //



char VDUdrv::softtest(){
  return(1);
};

char VDUdrv::hardtest(){
  return(1);
};

char VDUdrv::install(){
  return(0);
};

char *VDUdrv::getname(){
  return("Unnamed screen driver");
};

#pragma argsused
void VDUdrv::qplot(int x, int y, char colour){
  terminate("Plot function is missing from screen driver");
}

#pragma argsused
void VDUdrv::plot(int x, int y, char colour, char mode){
  terminate("Plot function is missing from screen driver");
}


#pragma argsused
void VDUdrv::box(int x, int y, int width, int height, char colour){
  int tempy;
  for(tempy=0;tempy<height;tempy++){
    drawhline(x,y+tempy,width,colour);
  }
};

#pragma argsused
void VDUdrv::line(int sx, int sy, int ex, int ey, char colour){
  /*float tempx, tempy, incx, incy, dx, dy;

  if (sx == ex)                 // draw vertical line if applicable
  {
    VLine(sx, sy, (xs-ey), colour);
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
  } */
};

#pragma argsused
void VDUdrv::drawhline(int x, int y, int width, char colour){
  int tempx;
  for(tempx=0;tempx<width;tempx++){
    qplot(x+tempx,y,colour); // Naff drawhline() func
  }
};

void VDUdrv::letter(int xc,int yc,char c,int colour,int trans_flag){
  int offset,x,y;
  unsigned char data;
  char far *work_char;
  unsigned char bit_mask = 0x80;

  work_char = rom_char_set + c * CHAR_HEIGHT;

  for (y=0; y<CHAR_HEIGHT; y++){
    bit_mask = 0x80;

    for (x=0; x<CHAR_WIDTH; x++){
      if ((*work_char & bit_mask)){
	qplot(xc+x,yc+y,colour);
      }else{
	if (!trans_flag){
	  qplot(xc+x,yc+y,0);
	}
      }
      bit_mask >>=1 ;
    }
    work_char++;
  }
}


void VDUdrv::text(int x,int y,int colour, char *string,int trans_flag,unsigned int max_char){
  int index;

  for (index=0; string[index]!=0&(index!=max_char); index++){
    letter(x+(index<<3),y,string[index],colour,trans_flag);
  }
}

#pragma argsused
void VDUdrv::VWait(char page){
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
};
#pragma argsused
void VDUdrv::usepage(char page){};

#pragma argsused
void VDUdrv::getinfo(screen_info *data){};

void VDUdrv::clearscr(char page){
  usepage(page);
  box(0,0,320,200,0);  // Doesn't really work.
};

// Not currently implemented /////////////

void VDUdrv::swapdb(){};
void VDUdrv::vwaitdb(){};
void VDUdrv::currdb(){};
void VDUdrv::alldb(){};



