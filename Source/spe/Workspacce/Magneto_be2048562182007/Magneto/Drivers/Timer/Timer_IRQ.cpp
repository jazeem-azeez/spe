#include "Drivers\Timer\Timer.h"

#if !defined ( __Timer_IRQ_CPP_ )
#define __Timer_IRQ_CPP_

static unsigned long int TICKS = 0;


void timer_irq()
{
 SAVE_REGS;

 TICKS++;
/* static unsigned char i = 0;
 if(i % 100 == 0) { cout <<"\n"<<i; }
 i++;
 cout<<"\n"<<TICKS; */

 outportb(0x20,0x20);
 RESTORE_REGS;
 __asm__( "leave\n\t"
          "iret"     );
}

#endif
