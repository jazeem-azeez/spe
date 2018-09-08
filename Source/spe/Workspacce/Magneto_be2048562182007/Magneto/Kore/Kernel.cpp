#if !defined ( __KERNEL_CPP_ )
#define __KERNEL_CPP_

#include "x86.h"
//-----------------------
#define VBE_DISPI_IOPORT_INDEX 0x01CE 
#define VBE_DISPI_IOPORT_DATA  0x01CF 
#define VBE_DISPI_INDEX_ID              0x0 
#define VBE_DISPI_INDEX_XRES            0x1 
#define VBE_DISPI_INDEX_YRES            0x2 
#define VBE_DISPI_INDEX_BPP             0x3 
#define VBE_DISPI_INDEX_ENABLE          0x4 
#define VBE_DISPI_INDEX_BANK            0x5 
#define VBE_DISPI_INDEX_VIRT_WIDTH      0x6 
#define VBE_DISPI_INDEX_VIRT_HEIGHT     0x7 
#define VBE_DISPI_INDEX_X_OFFSET        0x8 
#define VBE_DISPI_INDEX_Y_OFFSET        0x9 

#define VBE_DISPI_DISABLED              0x00 
#define VBE_DISPI_ENABLED               0x01 
#define VBE_DISPI_GETCAPS               0x02 
#define VBE_DISPI_8BIT_DAC              0x20 
#define VBE_DISPI_LFB_ENABLED           0x40 
#define VBE_DISPI_NOCLEARMEM            0x80 



void vbe_write(unsigned short index, unsigned short value) 
{ 
   outportw(VBE_DISPI_IOPORT_INDEX, index); 
   outportw(VBE_DISPI_IOPORT_DATA, value); 
} 


void vbe_set(unsigned short xres, unsigned short yres, unsigned short bpp) 
{ 
   vbe_write(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_DISABLED); 
   vbe_write(VBE_DISPI_INDEX_XRES, xres); 
   vbe_write(VBE_DISPI_INDEX_YRES, yres); 
   vbe_write(VBE_DISPI_INDEX_BPP, bpp); 
   vbe_write(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_ENABLED | VBE_DISPI_LFB_ENABLED);    
} 
//-----------------------


#include "cmos.h"
#include "defs.h"
#include "delay.h"
#include "Drivers\Timer\Timer.h"
#include "Drivers\FDC\FDC.h"
#include "Drivers\Sound\PC_Speaker.h"
#include "interrupts.h"


Interrupts interrupts;
Console console;
VGA vga;
FDC fdc;
Keyboard keyboard;

class Kernel
{
 private:
     Delay delay;
     CMOS cmos;
     Timer timer;
     PCspk pcspk;
     void change_console_res(int);
 public:
     Kernel();
     ~Kernel();
     void init();
};

int main()
{
 Kernel kernel;
 kernel.init();
 while(1);
 return 0;
}


Kernel::Kernel()
{
}

Kernel::~Kernel()
{
}

void Kernel::change_console_res(int secs)
{
 cout<<"\n\nChanging Console Res in "<<secs<<" seconds";
 for(;secs!=0; secs--)
 {
  do_delay(1000);
  cout<<".";
 }
 console.setmode(g_90x30_text);
}

void Kernel::init()
{
 cout<<"\nWelcome to Magneto!"<<endl;
 cout<<"Kernel version: 0.1"<<endl;
 interrupts.init();
 delay.init();
 cmos.init();
 fdc.init();
 keyboard.init();
 timer.init();
 change_console_res(5);
 cout<<"Testing vbe...";
 do_delay(3000);
 vbe_set(800, 600, 32);
 cout<<"Done";
 unsigned char * fb = (unsigned char *)0xe0000000;
 fb[1000] = 0xFF0000;
 while(1);
}

#endif
