#include "system.h"

#if !defined ( __SYSTEM_CPP_ )
#define  __SYSTEM_CPP_


int countMemory()
{
 unsigned char highmem, lowmem; unsigned int mem; 
 unsigned int base, ext;
 
 outportb(0x70,0x30); 
 lowmem = inportb(0x71); 
 outportb(0x70,0x31); 
 highmem = inportb(0x71);
 mem = highmem; 
 mem = mem << 8; 
 mem += lowmem; 
 ext=mem;
	
 outportb(0x70,0x17); 
 lowmem = inportb(0x71); 
 outportb(0x70,0x18); 
 highmem = inportb(0x71);
 mem = highmem; 
 mem = mem << 8; 
 mem += lowmem; 
 base=mem;

 return (base + ext);
}

int probe_mem()
{
 unsigned char *mem = (unsigned char *)0x200000; //init at 2MB to no destroy the kernel.
 long i=0x100000;
 
 unsigned char flag=1;
 while(flag)
 {
  mem[i]=0x66;
  if (mem[i]==0x66)
  	i = i + 0x100000;
  else
  	flag = 0;
 }
 int mem_total = i + 2*0x100000;
 return (i / 1048576 + 2);
}

#endif
