#include "Drivers\Timer\Timer.h"

#if !defined ( __Timer_CPP_ )
#define __Timer_CPP_


Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::init()
{
 cout<<endl<<"initializing Timer";
 static unsigned int count = 1193182 / 60; 

 outportb(PIT_MODE_PORT, 0x36);	// Counter 0, LSB and MSB, Mode 3, Binary
					// Mode 3 is Square Wave(SW) generator
					// Count is decremented by 2 for every clock period
					// Upper half of SW constitutes N/2 clock pulses and
					// Lower half constitutes another N/2 for a count N

 outportb(PIT_COUNTER_0_PORT, (char) count & 0xFF);		// Pass the LSB first
 outportb(PIT_COUNTER_0_PORT, (char) count >> 8);		// Followed by the MSB           
 interrupts.enable_irq(0, timer_irq, TRAP_GATE|BITS_32|PRESENT|RING_2);
 cout<<"\t\tDONE";
}

#endif
