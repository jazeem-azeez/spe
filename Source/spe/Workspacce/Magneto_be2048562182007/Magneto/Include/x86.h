#if !defined ( __X86_H_ )
#define __X86_H_


#define SAVE_REGS __asm__( 	"push %ds\n\t"\
						"push %es\n\t"\
						"push %fs\n\t"\
						"pushl %eax\n\t"\
						"pushl %ebx\n\t"\
						"pushl %ecx\n\t"\
						"pushl %edx\n\t"\
						"movw $0x10,%ax\n\t"\
						"movw %ax,%ds\n\t"\
						"movw %ax,%es")
						
#define RESTORE_REGS __asm__( "popl %edx;\n\t"\
						"popl %ecx;\n\t"\
						"popl %ebx;\n\t"\
						"popl %eax;\n\t"\
						"pop %fs;\n\t"\
						"pop %es;\n\t"\
						"pop %ds;" )




unsigned inportb(unsigned port);
void outportb(unsigned port, unsigned val);
unsigned int inportw(unsigned int port);
void outportw(unsigned int port, unsigned int val);
void __sti();
void __cli();
void halt();

int reboot();


#endif
