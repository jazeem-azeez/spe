#include "Drivers\Keyboard\Keyboard.h"

#if !defined ( __KEYBOARD_CPP_ )
#define  __KEYBOARD_CPP_ 

Keyboard::Keyboard()
{

}

Keyboard::~Keyboard()
{
}

void Keyboard::init()
{
 cout<<endl<<"Initializing Keyboard";
 interrupts.enable_irq(1, keyboard_irq, TRAP_GATE|BITS_32|PRESENT|RING_2);
 cout<<"\t\tDONE";
}

void Keyboard::update_leds(unsigned char stat)
{
 while(busy());
 outportb(KB_PORT, KB_SET_LEDS);

 while(busy());
 outportb(KB_PORT, stat);
}

int Keyboard::busy()
{
 unsigned char temp = inportb(KB_CTRLR);
 
 if(temp & 0x2) return 1;
 else return 0;
}

void Keyboard::clear_hw_buf()
{
 unsigned temp;
 do
 {
  temp = inportb(KB_CTRLR);
  if((temp & 0x01) != 0) 
  {
   (void)inportb(KB_PORT);
   continue;
  }
 } while((temp & 0x02) != 0);
}

void Keyboard::while_not_ready()
{
 volatile long i = 10;
 while (i-- && (inportb(KB_CTRLR) & 0x02));
}

void Keyboard::set_typematic_delay(unsigned char rate)
{
 while_not_ready();
 outportb(KB_PORT, KB_SET_TYPEMATIC_DELAY);
 outportb(KB_PORT, rate);
}


#endif
