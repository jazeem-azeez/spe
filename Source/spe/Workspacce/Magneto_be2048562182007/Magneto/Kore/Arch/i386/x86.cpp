#include "x86.h"
#include "defs.h"

#if !defined ( __X86_CPP_ )
#define __X86_CPP_

unsigned inportb(unsigned port)
{
	unsigned ret_val;

	__asm__ __volatile__("inb %w1,%b0"
		: "=a"(ret_val)
		: "d"(port));
	return ret_val;
}


void outportb(unsigned port, unsigned val)
{
	__asm__ __volatile__("outb %b0,%w1"
		:
		: "a"(val), "d"(port));
}

unsigned int inportw(unsigned int port)
{

    unsigned int Result;
    asm volatile("movw %1, %%dx;\
                 in %%dx, %%ax;\
                 movw %%ax, %0"
                :"=m"(Result)
                :"m"(port)
                :"%eax","%edx");
    return Result;

/*	unsigned int ret_val;

	__asm__ __volatile__("inw %w1,%b0"
		: "=a"(ret_val)
		: "d"(port));
	return ret_val;*/
}


void outportw(unsigned int port, unsigned int val)
{
/*	__asm__ __volatile__("outw %b0,%w1"
		:
		: "a"(val), "d"(port));*/

    asm volatile("movw %0, %%dx;\
                  movw %1, %%ax;\
                  out %%ax, %%dx;"
                : 
                :"m"(port),"m"(val)
                :"%eax","%edx");
}


void __sti()	//enable
{
	__asm__ __volatile__( "sti" );	
}


void __cli()
{
	__asm__ __volatile__( "cli" );	
}

void halt()
{
	__asm__ __volatile__( "hlt" );	
}


int reboot()
{
 __cli();
 int temp;		// A temporary int for storing keyboard info. The keyboard can be use to
 			//  reboot the PC

 // Get ready for reboot...flush the keyboard controller
 do
 {
  temp = inportb( 0x64 );
  if ( temp & 1 ) inportb( 0x60 );
 }
 
 while ( temp & 2 ); // Reboot the computer...

 outportb(0x64, 0xFE);

 return ERROR;
}

#endif
