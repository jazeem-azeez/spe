#include "delay.h"

#if !defined ( __DELAY_CPP_ )
#define __DELAY_CPP_

static unsigned long delay_count = 1;
static volatile unsigned long ticks = 0;

void delayCalibInt(void);
void __delay(unsigned long loops);

Delay::Delay()
{
}

Delay::~Delay()
{
}

void Delay::init_pit(int h, unsigned char channel)
{
 unsigned int temp=0;
 
 temp = 1193180/h;
	
 outportb(TMR_CTRL, (channel*0x40) + TMR_BOTH + TMR_MD3);
 outportb((0x40+channel), (unsigned char) temp);
 outportb((0x40+channel), (unsigned char) (temp>>8));
}

void Delay::init()
{
 cout<<endl<<"Calibrating Delay Loop...";
 calibrateDelayLoop();
 cout<<"\tdelay count: "<<(int)delay_count<<"\t\tDONE";
}

unsigned long Delay::calibrateDelayLoop(void)
{
    unsigned int prevtick;          /* Temporary variable             */
    unsigned int i;                 /* Counter variable               */
    unsigned int calib_bit;         /* Bit to calibrate (see below)   */

    /* Initialise timer interrupt with MILLISECOND ms interval        */
    init_pit(FREQ, 0);

    interrupts.enable_irq(0, delayCalibInt, INT_GATE|BITS_32|PRESENT|RING_2);


    /* Stage 1:  Coarse calibration                                   */

    do {
        delay_count <<= 1;          /* Next delay count to try        */

        prevtick=ticks;             /* Wait for the start of the next */
        while(prevtick==ticks);     /* timer tick                     */

        prevtick=ticks;             /* Start measurement now          */
        __delay(delay_count);       /* Do the delay                   */
    } while(prevtick == ticks);     /* Until delay is just too big    */

    delay_count >>= 1;              /* Get bottom value for delay     */

    /* Stage 2:  Fine calibration                                     */

    calib_bit = delay_count;        /* Which bit are we going to test */

    for(i=0;i<PRECISION;i++) {
        calib_bit >>= 1;            /* Next bit to calibrate          */
        if(!calib_bit) break;       /* If we have done all bits, stop */

        delay_count |= calib_bit;   /* Set the bit in delay_count     */

        prevtick=ticks;             /* Wait for the start of the next */
        while(prevtick==ticks);     /* timer tick                     */

        prevtick=ticks;             /* Start measurement now          */
        __delay(delay_count);       /* Do the delay                   */

        if(prevtick != ticks)       /* If a tick has passed, turn the */
            delay_count &= ~calib_bit;     /* calibrated bit back off */
    }

    /* We're finished:  Do the finishing touches                      */

    interrupts.disable_irq(0);                /* Our wonderful PIT can stop now  */

    delay_count /= MILLISEC;       /* Calculate delay_count for 1ms   */

    return delay_count;
}

void delayCalibInt(void)      /* The timer ISR                  */
{
 SAVE_REGS;

 ticks++;                  /* Increment the ticks counter    */

 outportb(0x20,0x20);
 RESTORE_REGS;
 __asm__( "leave\n\t"
          "iret"     );
}

void __delay(unsigned long loops)
{
    unsigned long c;
    for(c=0;c<loops;c++);
}

void do_delay(unsigned long milliseconds)
{
    __delay(milliseconds*delay_count);     /* Delay milliseconds ms */
}

#endif
