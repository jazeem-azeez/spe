#include "Silver\VGA\VGA.h"

#if !defined ( __VGA_CPP_ )
#define __VGA_CPP_

VGA::VGA()
{
 g_maxx = 300;
 g_maxy=200;
 Is_Graphics = FALSE;
}

VGA::~VGA()
{
}

void VGA::init()
{
 update_vga();
}

void VGA::update_vga()
{
 if(type = GRAPHICS)
 {
  g_maxx = 300;
  g_maxy=200;
  Is_Graphics = TRUE;
 }
 else Is_Graphics = FALSE;
}

void VGA::setmode(unsigned char *regs)
{
 set_mode(regs);
}

#endif
