///////////////////////////////////////////////////////
//                                                   //
//        VESA Screen Driver - Version 1.01          //
//                                                   //
//           By Kevin Campbell 17/12/96              //
//                                                   //
//                                                   //
///////////////////////////////////////////////////////


#include <string.h>
#include <dos.h>
#include <stdlib.h>
#include "screen\vesa\vesa.h"

// Driver Modules ////////////////////

class VESA_640_480_DRV VESA_640_480;
//class VESA_320_256_DRV VESA_320_256;


// Static Vars storage space /////////


int 			VESAdrv::curx;
int			VESAdrv::cury;
int 			VESAdrv::VESA_X;
int			VESAdrv::VESA_Y;

struct VESA_LineInfo 	VESAdrv::Lines[VESA_MAX_Y];

unsigned char far *	VESAdrv::rom_char_set;

struct VESAInfo far 	VESA::vesainfo;		// Thingies to hold info
struct VESAMode far 	VESA::modeinfo; 	//
char 			VESA::installed;       	// Is a VESA card installed
union revision 		VESA::level; 		// Level of VESA implemenation
char 			VESA::granularity;    	// Win-shift scale
int 			VESA::curwindow; 	// currently being used VESA window
char far *		VESA::WinPointer;       //
void far *		VESA::VESA_WinFunc;//

//////////////////////////////////////


VESAdrv::VESAdrv(){
  rom_char_set = (char far *)0xF000FA6EL; // rom characters 8x8
}


VESAdrv::~VESAdrv(){

}

// Inline thingies ///////////////////


inline void VESAdrv::UseWin(char window){
  if(window!=curwindow){
    VESA_SetWindow(0,window);
  }
}

inline void VESAdrv::MemDraw(int offset, char far *pic, char window, int width){
  UseWin(window);
  _fmemcpy(&WinPointer[offset],pic,width);
}

inline void VESAdrv::MemCopy(int offset, char far *pic, char window, int width){
  UseWin(window);
  _fmemcpy(pic,&WinPointer[offset],width);
}

// Public functions //////////////////

char VESAdrv::softtest(){
  if(VESA_GetInfo()){
    level=vesainfo.Version;
    curwindow=0;

    VESA_X=0;
    VESA_Y=0;
    curx=0;
    cury=0;

    return(1);

  }else{
    return(0);
  }
}



void VESAdrv::getinfo(screen_info *data){
  data->x_res=VESA_X;
  data->y_res=VESA_Y;
  data->bits_per_plane=8;  // ****** MUST CHANGE LATER ******
}

char VESAdrv::Info(struct VESAInfo far *details){
  if(VESA_GetInfo()){
    _fmemcpy(details,&vesainfo,sizeof(VESAInfo));
    return(1);
  }else{
    return(0);
  }
}


char VESAdrv::ModeInfo(int mode, struct VESAMode far *details){
  if(VESA_ModeInfo(mode)){
    _fmemcpy(details,&modeinfo,sizeof(VESAMode));
    return(1);
  }else{
    return(0);
  }
}


char VESAdrv::SetMode(int mode){
  if(VESA_ModeInfo(mode)){
    if(VESA_SetMode(mode,0,0)){
      curwindow=0;
      VESA_X=modeinfo.XResoloution;
      VESA_Y=modeinfo.YResoloution;
      FP_SEG(WinPointer)=modeinfo.WinA_Segment;
      FP_OFF(WinPointer)=0;
      setoffsets();
      return(1);
    }
  }
  return(0); // Failed to set VESA mode
}


char VESAdrv::Installed(){
  return(installed);
}


char far *VESAdrv::CardName(){
  return(vesainfo.OemStringPtr);
}



char VESAdrv::palset(char palnum, char R, char G, char B){
  /*
  struct far VESA_Pal col;
  col.R=R<<2;
  col.G=G<<2;
  col.B=B<<2;
  if(VESA_Setpal(1,palnum,&col))return(1);
  return(0);
  */
  //
  // Note - need to add this in for VESA 2.0
  //

  outportb(0x3c8,palnum); // Send index value to 0x3c8
  outportb(0x3c9,R);      // Send Red component to 0x3c8
  outportb(0x3c9,G);      // Send Blue component to 0x3c8
  outportb(0x3c9,B);      // Send Green component to 0x3c8
  return(1); // Cannot fail
}

char VESAdrv::setpal(VESA_Pal *pd){
  if(VESA_Setpal(256,0,pd))return(1);
  return(0);
}

char VESAdrv::setstart(int x,int y){
  if(VESA_Start(VESA_SET_START,&x,&y)){
    curx=x;
    cury=y;
    return(1);
  }else{
    return(0);
  }
}

void VESAdrv::WaitRetrace(){
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

void VESAdrv::VWait(char page){
  int dby_tmp=page*VESA_Y;
  VESA_Start(VESA_SET_START,&dx,&dby_tmp);
  WaitRetrace();
}

void VESAdrv::usepage(char page){
  db=page*VESA_Y;
}




///////////////////////////////////////////////////////
//                                                   //
//       Misc. Graphics functions for usage	     //
//            to draw thingies on screen             //
//                                                   //
///////////////////////////////////////////////////////


/*void blit(int x, int y, struct shape far *data){
  int cx;
  int cy;
  long address;
  char huge *tempptr;
  int mx=data->x_size;
  int my=data->y_size;
  tempptr=&piccy[0][0];
  for(cy=0;cy<my;cy++){
    address=cy*(data->x_size);
    for(cx=0;cx<mx;cx++){
      qplot(x+cx,y+cy,tempptr[address]);
      address++;
      //scanline(x+cx,y+cy,mx,&tempptr[address]);
    }
  }
}*/

void VESAdrv::get(int x, int y, int xs, int ys, char huge *data){
  int cy;
  int sy=y;
  int ey=y+ys;
  long address;
  int tempptr=0;
  for(cy=sy;cy<ey;cy++){
    getline(x,cy,xs,&data[tempptr]);
    tempptr+=xs; // Move to next line in shape
  }
}


void VESAdrv::put(int x, int y, int xs, int ys, char huge *data){
  int cy;
  int sy=y;
  int ey=y+ys;
  long address;
  int tempptr=0;
  for(cy=sy;cy<ey;cy++){
    scanline(x,cy,xs,&data[tempptr]);
    tempptr+=xs; // Move to next line in shape
  }
}


void VESAdrv::qplot(int x, int y, char colour){
  long offset;
  int tempwin;
  int ty=y+db;

  VESA_LineInfo *cline=&Lines[ty];

  offset=(long)cline->offset+x;

  if(curwindow!=cline->window){
    VESA_SetWindow(0,cline->window);
  }

  if(cline->split){
    if(x>cline->splitpos){
      offset-=65536;
      VESA_SetWindow(0,curwindow+1);
    }
  }

  WinPointer[offset]=colour;
  return;
}


char VESAdrv::qget(int x, int y, char *colour){
  unsigned long offset;
  int tempwin;

  offset=(long)Lines[y].offset+x;

  if(!(curwindow==Lines[y].window)){
    if(!VESA_SetWindow(0,Lines[y].window)){
      return(0);
    }
  }

  if(offset>=65536){
    offset-=65536;
    if(!VESA_SetWindow(0,curwindow+1)){
      return(0);
    }
  }

  *colour=WinPointer[offset];
  return(1);
};


void VESAdrv::plot(int x, int y, char colour, char mode){
  unsigned long offset;
  int tempwin;

  offset=(long)Lines[y].offset+x;

  if(!(curwindow==Lines[y].window)){
    if(!VESA_SetWindow(0,Lines[y].window)){
      return;//(0);
    }
  }

  if(offset>=65536){
    offset-=65536;
    if(!VESA_SetWindow(0,curwindow+1)){
      return;//(0);
    }
  }

  switch(mode){
    case REPLACE:
      VESA_DrawReplace(offset,colour);
      return;//(1);

    case TRANS:
      VESA_DrawTrans(offset,colour);
      return;//(1);

    case BEHIND:
      VESA_DrawBehind(offset,colour);
      return;//(1);

    case INVERSE:
      VESA_DrawInverse(offset,colour);
      return;//(1);
  }
  return;//(0);
};


void VESAdrv::drawhline(int x, int ty, int width, char colour){
  int offset;
  int window;
  int tempwidth;

  int y=ty+db;

  if(Lines[y].split){
    if(x>=Lines[y].splitpos){

      // Line cannot be split, but must use next window.
      window=Lines[y].window+1;
      offset=x-(Lines[y].splitpos);
      VESA_ScanLine(window,offset,width,colour);

    }else{
      if(x+width<Lines[y].splitpos){

	// Line isn't split and so may be drawn as normal
	window=Lines[y].window;
	offset=(Lines[y].offset)+x;
	VESA_ScanLine(window,offset,width,colour);

      }else{

	// Line is split and so needs drawn in two parts

	// First part:
	window=Lines[y].window;
	offset=(Lines[y].offset)+x;
	tempwidth=Lines[y].splitpos-x;
	VESA_ScanLine(window,offset,tempwidth,colour);

	// Second part:
	window=Lines[y].window+1;
	offset=0;// Starting an beginning of window
	tempwidth=(x+width)-Lines[y].splitpos;
	VESA_ScanLine(window,offset,tempwidth,colour);

      }
    }
  }else{
    // Line being draw is all in one segment
    window=Lines[y].window;
    offset=(Lines[y].offset)+x;
    VESA_ScanLine(window,offset,width,colour);
  }
}


void VESAdrv::box(int x, int y, int width, int height, char colour){
  int end=y+height;
  for(int line=y;line<end;line++){
    drawhline(x,line,width,colour);
  }
}


void VESAdrv::line(int startx, int starty, int endx, int endy, char colour){
  int xdiff;
  int ydiff;
  float linex;
  float liney;
  float xgrad;
  float ygrad;
  //int startx=tsx+db;
  //int endx=tex+db;

  if(startx==endx & starty==endy){
    qplot(startx,starty,colour);
    return;
  }

  xdiff=abs(endx-startx);
  ydiff=abs(endy-starty);
  if(ydiff>xdiff){
    // Y=constant, X=var
    xgrad=((float)xdiff/(float)ydiff)*(endx > startx ? 1:-1); // XGradient
    ygrad=(endy > starty ? 1:-1);      // YGradient
    linex=startx;
    for(liney=starty;liney!=endy;liney+=ygrad){
      qplot(linex,liney,colour);
      linex+=xgrad;
    }
  }else{
    // X=constant, Y=var
    ygrad=((float)ydiff/(float)xdiff)*(endy > starty ? 1:-1); // YGradient
    xgrad=(endx > startx ? 1:-1);      // YGradient
    liney=starty;
    for(linex=startx;linex!=endx;linex+=xgrad){
      qplot(linex,liney,colour);
      liney+=ygrad;
    }
  }
}






//
//
//
// Private Functions: these are called by the other functions
// in the VESA class library.
//
//
//







void VESAdrv::scanline(int x, int y, int width, char far *ldata){
  int offset;
  int window;
  int tempwidth;

  if(Lines[y].split){
    if(x>=Lines[y].splitpos){

      // Line cannot be split, but must use next window.
      window=Lines[y].window+1;
      offset=x-(Lines[y].splitpos);
      //VESA_BlitLine(window,offset,width,ldata);
      MemDraw(offset,ldata,window,width);

    }else{
      if(x+width<Lines[y].splitpos){

	// Line isn't split and so may be drawn as normal
	window=Lines[y].window;
	offset=(Lines[y].offset)+x;
	//VESA_BlitLine(window,offset,width,ldata);
	MemDraw(offset,ldata,window,width);

      }else{

	// Line is split and so needs drawn in two parts

	// First part:
	window=Lines[y].window;
	offset=(Lines[y].offset)+x;
	tempwidth=Lines[y].splitpos-x;
	//VESA_BlitLine(window,offset,tempwidth,ldata);
	MemDraw(offset,ldata,window,tempwidth);

	// Second part:
	window=Lines[y].window+1;
	offset=0;// Starting an beginning of window
	tempwidth=(x+width)-Lines[y].splitpos;
	//VESA_BlitLine(window,offset,tempwidth,&ldata[width-tempwidth]);
	MemDraw(offset,&ldata[width-tempwidth],window,tempwidth);
      }
    }
  }else{
    // Line being draw is all in one segment
    window=Lines[y].window;
    offset=(Lines[y].offset)+x;
    //VESA_BlitLine(window,offset,width,ldata);
    MemDraw(offset,ldata,window,width);
  }
}


void VESAdrv::getline(int x, int y, int width, char far *ldata){
  int offset;
  int window;
  int tempwidth;

  if(Lines[y].split){
    if(x>=Lines[y].splitpos){

      // Line cannot be split, but must use next window.
      window=Lines[y].window+1;
      offset=x-(Lines[y].splitpos);
      MemCopy(offset,ldata,window,width);

    }else{
      if(x+width<Lines[y].splitpos){

	// Line isn't split and so may be drawn as normal
	window=Lines[y].window;
	offset=(Lines[y].offset)+x;
	MemCopy(offset,ldata,window,width);

      }else{

	// Line is split and so needs drawn in two parts

	// First part:
	window=Lines[y].window;
	offset=(Lines[y].offset)+x;
	tempwidth=Lines[y].splitpos-x;
	MemCopy(offset,ldata,window,tempwidth);

	// Second part:
	window=Lines[y].window+1;
	offset=0;// Starting an beginning of window
	tempwidth=(x+width)-Lines[y].splitpos;
	MemCopy(offset,&ldata[width-tempwidth],window,width);
      }
    }
  }else{
    // Line being draw is all in one segment
    window=Lines[y].window;
    offset=(Lines[y].offset)+x;
    MemCopy(offset,ldata,window,width);
  }
}


char VESAdrv::VESA_BlitLine(int window,int offset,int width,char far *bdat){
  int cur=0;

  if(!(window==curwindow)){
    if(!VESA_SetWindow(0,window)){
      return(0);
    }
  }

  for(cur=0;cur<width;cur++){
    WinPointer[offset++]=bdat[cur];
  }

  return(1);
}




void VESAdrv::setoffsets(){
  long seg=0;
  long value=0;
  long seg_size=65536;
  for(long line=0;line<VESA_MAX_Y;line++){

    value+=VESA_X;

    Lines[line].split=0;

    if(value>seg_size){ // Split has been reached
      value-=seg_size;   // set pointer back
      seg++;        // Next segment

      if(!(value==0)){ // If line doesn't split evenly
	Lines[line-1].split=1;
	Lines[line-1].splitpos=(VESA_X-value);
      }
    }
    Lines[line].window=seg;
    Lines[line].offset=value;
  }
}


char VESAdrv::VESA_ScanLine(int window,int offset,int width,int colour){
  if(!(window==curwindow)){
    if(!VESA_SetWindow(0,window)){
      return(0);
    }
  }

  for(int cur=0;cur<width;cur++){
    WinPointer[offset]=colour;
    offset++;
  }
  return(1);
}

char VESAdrv::VESA_GetLine(int window,int offset,int width,char far *bdat){
  if(!(window==curwindow)){
    if(!VESA_SetWindow(0,window)){
      return(0);
    }
  }

  for(int cur=0;cur<width;cur++){
    bdat[cur]=WinPointer[offset++];
  }

  return(1);
}


// Various Styles of pixel plotting /////////////////////////////

void VESAdrv::VESA_DrawReplace(int offset, char colour){
  WinPointer[offset]=colour;
}

void VESAdrv::VESA_DrawTrans(int offset, char colour){
  if(colour)WinPointer[offset]=colour;
}

void VESAdrv::VESA_DrawBehind(int offset, char colour){
  if(!(WinPointer[offset]))WinPointer[offset]=colour;
}

void VESAdrv::VESA_DrawInverse(int offset, char colour){
  WinPointer[offset]^colour; // Exclusive OR
}

/////////////////////////////////////////////////////////////////

































































///////////////////////////////////////////////////////
//                                                   //
//           VESA BIOS Hardware Functions            //
//                                                   //
//   As defined by the VBE standard - Version 2.0    //
//                                                   //
//                                                   //
///////////////////////////////////////////////////////




char VESA::VESA_GetInfo(void){
  struct REGS io;
  struct SREGS flags;

  // Set-up structures

  _fstrncpy(vesainfo.Signature,"VBE2",4); // Don't copy Null.
  vesainfo.Version.full=0x0200;

  // Set registers for VESA values

  io.h.ah=0x4F;
  io.h.al=0x00;
  flags.es=FP_SEG(&vesainfo);
  io.x.di=FP_OFF(&vesainfo);

  // Call function 0x00

  int86x(VESA_Int,&io,&io,&flags);

  // Check result

  if(io.h.al==0x4F){
    if(io.h.ah==0x00){
      return(1);
    }else{
      return(0);
    }
  }else{
    return(0);
  }
}


char VESA::VESA_ModeInfo(int mode){
  struct REGS io;
  struct SREGS flags;

  // Set registers for VESA values
  io.h.ah=0x4F;
  io.h.al=0x01;
  flags.es=FP_SEG(&modeinfo);
  io.x.di=FP_OFF(&modeinfo);
  io.x.cx=mode; // Set mode value
  // Call function 0x01
  int86x(VESA_Int,&io,&io,&flags);
  // Check Result
  if(io.h.al==0x4F){
    if(io.h.ah==0x00){
      granularity=64/(modeinfo.WinGranularity); // win-shift scale
      VESA_WinFunc=(void (far*)())(modeinfo.WindowFunctionPtr);
      return(1);
    }else{
      return(0);
    }
  }else{
    return(0);
  }
}

char VESA::VESA_SetMode(int mode, char linear, char preserve){
  struct REGS io;
  struct SREGS flags;
  struct VESA_ModeSet modeset;
  int temp_copy;

  modeset.Mode=mode;
  modeset.Reserved=0;
  modeset.Linear=linear;
  modeset.Preserve=preserve;

  memcpy(&temp_copy,&modeset,2);

  // Set registers for VESA values
  io.h.ah=0x4F;
  io.h.al=0x02;
  io.x.bx=temp_copy;

  int86x(VESA_Int,&io,&io,&flags);
  // Check Result
  if(io.h.al==0x4F){
    if(io.h.ah==0x00){
      return(1);
    }else{
      return(0);
    }
  }else{
    return(0);
  }
}

char VESA::VESA_SetWindow(char window, int position){
  struct REGS io;
  struct SREGS flags;
  void far *tempptr=VESA_WinFunc;

  if(1==1){;//VESA_WinFunc==NULL){

    // Set registers for VESA values
    io.h.ah=0x4F;
    io.h.al=0x05;
    io.h.bh=0x00; // Set Window
    io.h.bl=window; // Window number
    io.x.dx=position*granularity; // Window Position

    int86x(VESA_Int,&io,&io,&flags);
    // Check Result
    if(io.h.al==0x4F){
      if(io.h.ah==0x00){
	curwindow=position;
	return(1);
      }else{
	return(0);
      }
    }else{
      return(0);
    }
  }/*else{
    int temppos=position;//*granularity;

    asm {
    _DX=temppos;
    _BL=window;
    _BH=0x00; // Note - high byte=0x00
    _AH=0x4F;
    _AL=0x05; // VESA, function 0x05

    //(*VESA_WinFunc)();

    asm CALL tempptr

    //if(_AL==0x4F){
    //  if(_AH==0x00){
	curwindow=position;
    //	return(1);
    //  }else{
    //	return(0);
    //  }
    //}else{
    //  return(0);
    //}
  } */
}

char VESA::VESA_GetWindow(char window, int *position){
  struct REGS io;
  struct SREGS flags;

  // Set registers for VESA values
  io.h.ah=0x4F;
  io.h.al=0x05;
  io.h.bh=0x01; // Get Window
  io.h.bl=window; // Window number

  int86x(VESA_Int,&io,&io,&flags);
  // Check Result

  *position=io.x.dx; // Return Window Position

  if(io.h.al==0x4F){
    if(io.h.ah==0x00){
      curwindow=*position;
      return(1);
    }else{
      return(0);
    }
  }else{
    return(0);
  }
}

char VESA::VESA_SetLength(char type, int *length, int *scan_lines){
  struct REGS io;
  struct SREGS flags;

  // Set registers for VESA values
  io.h.ah=0x4F;
  io.h.al=0x06;
  io.h.bl=0x00+type; // Pixels or Bytes?
  io.x.cx=*length; // Desired Length

  int86x(VESA_Int,&io,&io,&flags);

  switch(type){
    case PIXELS:
      *length=io.x.cx;
      break;
    case BYTES:
      *length=io.x.bx;
      break;
  }

  *scan_lines=io.x.dx;

  // Check Result
  if(io.h.al==0x4F){
    if(io.h.ah==0x00){
      return(1);
    }else{
      return(0);
    }
  }else{
    return(0);
  }
}

char VESA::VESA_GetLength(char type, int *pixels, int *bytes, int *scan_lines){
  struct REGS io;
  struct SREGS flags;

  // Set registers for VESA values
  io.h.ah=0x4F;
  io.h.al=0x06;
  io.h.bl=0x01+type; // GetLength

  int86x(VESA_Int,&io,&io,&flags);

  *pixels=io.x.cx;
  *bytes=io.x.bx;
  *scan_lines=io.x.dx;

  // Check Result
  if(io.h.al==0x4F){
    if(io.h.ah==0x00){
      return(1);
    }else{
      return(0);
    }
  }else{
    return(0);
  }
}


char VESA::VESA_Start(char action, int *pixel, int *line){
  struct REGS io;
  struct SREGS flags;

  // Set registers for VESA values
  io.h.ah=0x4F;
  io.h.al=0x07;
  io.h.bh=0x00; // Must be 0
  io.h.bl=action;
  io.x.cx=*pixel;
  io.x.dx=*line;

  int86x(VESA_Int,&io,&io,&flags);

  if(action==VESA_GET_START){
    io.x.cx=*pixel;
    io.x.dx=*line;
  }

  // Check Result
  if(io.h.al==0x4F){
    if(io.h.ah==0x00){
      return(1);
    }else{
      return(0);
    }
  }else{
    return(0);
  }
}


char VESA::VESA_Setpal(int numpal, int startpal, VESA_Pal *table){
  struct REGS io;
  struct SREGS flags;

  // Set registers for VESA values
  io.h.ah=0x4F;
  io.h.al=0x09; // Function 0x09 - edit palette data
  io.h.bl=0x00; // Sub-Function 0x00 - set main palette
  io.x.cx=numpal;
  io.x.dx=startpal;

  io.x.di=FP_OFF(table);
  flags.es=FP_SEG(table);

  int86x(VESA_Int,&io,&io,&flags);

  // Check Result
  if(io.h.al==0x4F){
    if(io.h.ah==0x00){
      return(1);
    }else{
      return(0);
    }
  }else{
    return(0);
  }
}




///////////////////////////
//
// Screen drivers
//

char VESA_640_480_DRV::hardtest(){
  if(VESA_ModeInfo(0x101)){
    return(1);
  }
  return(0);

}

char VESA_640_480_DRV::install(){
  if(VESA_SetMode(0x101,0,0)){
    curwindow=0;
    VESA_X=modeinfo.XResoloution;
    VESA_Y=modeinfo.YResoloution;
    FP_SEG(WinPointer)=modeinfo.WinA_Segment;
    FP_OFF(WinPointer)=0;
    db=0;
    dx=0;
    scr_x=VESA_X;
    scr_y=VESA_Y;
    setoffsets();
    return(1);
  }
  return(0);
}

char *VESA_640_480_DRV::getname(){
  return("VESA Compatible 640*480");
};


