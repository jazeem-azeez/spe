#include "x86.h"
#include "iostream.h"

#if !defined ( __INTERRUPTS_H_ )
#define __INTERRUPTS_H_


#define EOI			0x20	//end of interrupt


class Interrupts
{
 private:
     void init_pic();
     void set_exceptions();

     int selector_code;
     long current_mask;

     struct idt_gate
     {
      unsigned short offset1;
      unsigned short selector;
      unsigned char dword_count;
      unsigned char type;
      unsigned short offset2;
     } __attribute ((packed));
     idt_gate idt[256];

     struct
     {
      unsigned short size	__attribute ((packed));
      unsigned long offset	__attribute ((packed));
     } idt_desc;

     #define MASTER_VEC	32
     #define SLAVE_VEC	40

     #define PICM		0x20
     #define PICMI		0x21
     #define PICS		0xA0
     #define PICSI		0xA1

     #define ICW1		0x11
     #define ICW4		0x01

     //-----------------------

     #define INT_GATE 0x06     
     #define TRAP_GATE 0x07

     #define BITS_16 0x00
     #define BITS_32 0x08
     #define ABSENT  0x0
     #define PRESENT 0x80

     #define RING_0 0x00
     #define RING_1 0x20
     #define RING_2 0x40
     #define RING_3 0x60

 public:
     Interrupts();
     ~Interrupts();
     void init();
     void set_vector(int intno, void (*pointer)(), unsigned char control);
     void enable_irq(unsigned short x, void (*handler)(), unsigned char control);
     void disable_irq(unsigned short x);
};

extern Interrupts interrupts;

#endif
