#include "drivers\FDC\FDC.h"

#if !defined ( __FDC_CPP_ )
#define __FDC_CPP_

FDC::FDC()
{
}

FDC::~FDC()
{
}

void FDC::init()
{
 int ver;

 /* get floppy controller version */
 sendbyte(CMD_VERSION);
 ver = getbyte();

 if (ver == 0x80)
   cout<<"\nFLOPPY: NEC765 controller found";
 else
   cout<<"\nFLOPPY: Enhanced controller found";
}

/* sendbyte() routine from intel manual */
void FDC::sendbyte(int byte)
{
   volatile int msr;
   int tmo;
   
   for (tmo = 0;tmo < 128;tmo++) {
      msr = inportb(FDC_MSR);
      if ((msr & 0xc0) == 0x80) {
	 outportb(FDC_DATA,byte);
	 return;
      }
      inportb(0x80);   /* delay */
   }
}

/* getbyte() routine from intel manual */
int FDC::getbyte()
{
   volatile int msr;
   int tmo;
   
   for (tmo = 0;tmo < 128;tmo++) {
      msr = inportb(FDC_MSR);
      if ((msr & 0xd0) == 0xd0) {
	 return inportb(FDC_DATA);
      }
      inportb(0x80);   /* delay */
   }

   return -1;   /* read timeout */
}

#endif
