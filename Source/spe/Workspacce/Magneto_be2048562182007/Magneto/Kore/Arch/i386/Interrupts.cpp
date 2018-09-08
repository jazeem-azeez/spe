#include "interrupts.h"

#if !defined ( __INTERRUPTS_CPP_ )
#define __INTERRUPTS_CPP_


namespace //No-name namespace instead of static keyword
{
 void default_handler();
 void cpu0();
 void cpu1();
 void cpu2();		//CPU interrupt functions
 void cpu3();
 void cpu4();
 void cpu5();
 void cpu6();
 void cpu7();
 void cpu8();
 void cpu9();
 void cpu10();
 void cpu11();
 void cpu12();
 void cpu13();
 void cpu14();
 void cpu15();
 void cpu16();

 void default_handler()	//Handles any interrupts that have not been set.
 {			//This function should never run...
//  cout<<"\nDefault Handler";
  asm("mov %ebp,%esp");
  asm("pop %ebp");
  asm("iret");
 }

 void cpu0()
 {
  cout<<"\n\"FATAL ERROR: Divide Error\"";
  while(1);
 }

 void cpu1()
 {
  cout<<"\n\"FATAL ERROR: Debug Exceptions\"";
  while(1);
 }
 
 void cpu2()
 {
  cout<<"\n\"FATAL ERROR: NMI Interrupt\"";
  while(1);
 }

 void cpu3()
 {
  cout<<"\n\"FATAL ERROR: Breakpoint\"";
  while(1);
 }

 void cpu4()
 {
  cout<<"\n\"FATAL ERROR: INTO Detected Overflow\"";
  while(1);
 }

 void cpu5()
 {
  cout<<"\n\"FATAL ERROR: Bound Range Exceeded\"";
  while(1);
 }

 void cpu6()
 {
  cout<<"\n\"FATAL ERROR: Invalid Opcode\"";
  while(1);
 }

 void cpu7()
 {
  cout<<"\n\"FATAL ERROR: Coprocessor Not Available\"";
  while(1);
 }

 void cpu8()
 {
  cout<<"\n\"FATAL ERROR: Double Exception\"";
  while(1);
 }

 void cpu9()
 {
  cout<<"\n\"FATAL ERROR: Coprocessor Segment Overrun\"";
  while(1);
 }

 void cpu10()
 {
  cout<<"\n\"FATAL ERROR: Invalid Task State Segment\"";
  while(1);
 }

 void cpu11()
 {
  cout<<"\n\"FATAL ERROR: Segment Not Present\"";
  while(1);
 }

 void cpu12()
 {
  cout<<"\n\"FATAL ERROR: Stack Fault\"";
  while(1);
 }

 void cpu13()
 {
  cout<<"\n\"FATAL ERROR: General Protection\"";
  while(1);
 }

 void cpu14()
 {
  cout<<"\n\"FATAL ERROR: Page Fault\"";
  while(1);

 }

 void cpu15()
 {
  cout<<"\n\"FATAL ERROR: Reserved\"";
  while(1);
 }

 void cpu16()
 {
  cout<<"\n\"FATAL ERROR: Coprocessor Error\"";
  while(1);
 }

}	//end of namespace


Interrupts::Interrupts()
{
}

Interrupts::~Interrupts()
{
}

void Interrupts::init()
{
 cout<<endl<<"Initializing Interrupts";
 int i = 32;
 int selector = 0;


 asm volatile("movw %%cs,%0" :"=g"(selector));	//Obtain Code Selector
 selector_code = selector;

 init_pic();
 set_exceptions();
 for (;i<256;i++)	//Fill IDT with default entries.
 {
  set_vector(i,default_handler, INT_GATE|BITS_32|PRESENT|RING_0);
 }

 idt_desc.size=(256*8)-1;
 idt_desc.offset=(unsigned long)idt;

 asm("lidt %0" : "=m" (idt_desc));	//Load IDT.

 current_mask = 0xffff;	//disables all interrupts
 cout<<"\t\tDONE";
}

void Interrupts::init_pic()	//re-programs the pic
{							//IRQ interrupts start at MASTER_VEC
 outportb(PICM, ICW1);
 outportb(PICS, ICW1);
 
 outportb(PICMI, MASTER_VEC);
 outportb(PICSI, SLAVE_VEC);

 outportb(PICMI, 4);
 outportb(PICSI, 2);

 outportb(PICMI, ICW4);
 outportb(PICSI, ICW4);

 outportb(PICMI, 0xff);
 outportb(PICSI, 0xff);
}

void Interrupts::set_exceptions()	//Sets CPU interrupts in the IDT
{
 int i = 17;
 set_vector(0, cpu0, TRAP_GATE|BITS_32|PRESENT|RING_0);
 set_vector(1, cpu1, TRAP_GATE|BITS_32|PRESENT|RING_0);
 set_vector(2, cpu2, TRAP_GATE|BITS_32|PRESENT|RING_0);
 set_vector(3, cpu3, TRAP_GATE|BITS_32|PRESENT|RING_0);
 set_vector(4, cpu4, TRAP_GATE|BITS_32|PRESENT|RING_0);
 set_vector(5, cpu5, TRAP_GATE|BITS_32|PRESENT|RING_0);
 set_vector(6, cpu6, TRAP_GATE|BITS_32|PRESENT|RING_0);
 set_vector(7, cpu7, TRAP_GATE|BITS_32|PRESENT|RING_0);
 set_vector(8, cpu8, TRAP_GATE|BITS_32|PRESENT|RING_0);
 set_vector(9, cpu9, TRAP_GATE|BITS_32|PRESENT|RING_0);
 set_vector(10, cpu10, TRAP_GATE|BITS_32|PRESENT|RING_0);
 set_vector(11, cpu11, TRAP_GATE|BITS_32|PRESENT|RING_0);
 set_vector(12, cpu12, TRAP_GATE|BITS_32|PRESENT|RING_0);
 set_vector(13, cpu13, TRAP_GATE|BITS_32|PRESENT|RING_0);
 set_vector(14, cpu14, TRAP_GATE|BITS_32|PRESENT|RING_0);
 set_vector(15, cpu15, TRAP_GATE|BITS_32|PRESENT|RING_0);
 set_vector(16, cpu16, TRAP_GATE|BITS_32|PRESENT|RING_0);
 for(; i < 31; i++)
 {				//Sets the reserved CPU interrupts
  set_vector(i, cpu15, TRAP_GATE|BITS_32|PRESENT|RING_0);
 }
}

void Interrupts::set_vector(int intno, void (*pointer)(), unsigned char control)
{
 struct addr			//Adds interrupt information to the IDT
 {
  unsigned short offset;
  unsigned short base;
 };
 
 union
 {
  void (*function)();
  struct addr function_addr;
 }intrpt;

 intrpt.function = pointer;

 idt[intno].selector = selector_code;
 idt[intno].dword_count = 0;
 idt[intno].type = control;
 idt[intno].offset1 = intrpt.function_addr.offset;
 idt[intno].offset2 = intrpt.function_addr.base;
}

void Interrupts::enable_irq(unsigned short x, void (*handler)(), unsigned char control)
{
 __asm__ ("cli");
 current_mask &= ~(1<<x) ;	//Zero off the IRQ mask to enable
 if (x>=8)
 {
  current_mask &= ~(1<<2);
  set_vector((x + SLAVE_VEC - 7), handler, control);
 }
 else						//Sets the appropriate interrupt at the same time
 {
  set_vector((x + MASTER_VEC), handler, control);
 }

 outportb(PICMI, current_mask & 0xff);
 outportb(PICSI, (current_mask >> 8) & 0xff);
 __asm__ ("sti");
}

void Interrupts::disable_irq(unsigned short x)
{			
 __asm__ ("cli");					//Re-masks an interrupt
 current_mask |= (1 << x);
 if(x >= 8)
 {
  current_mask |= (1 << 2);
  set_vector((x + SLAVE_VEC - 8), default_handler, INT_GATE|BITS_32|PRESENT|RING_3);
 }
 else						//Removes prevous handler
 {
  set_vector((x + MASTER_VEC), default_handler, INT_GATE|BITS_32|PRESENT|RING_3);
 }
	
 outportb(PICMI, current_mask & 0xFF);
 outportb(PICSI, (current_mask >> 8) & 0xFF);
 __asm__ ("sti");
}

#endif
