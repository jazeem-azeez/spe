#include "iostream.h"
#include "interrupts.h"
#include "x86.h"

#if !defined ( __DELAY_H_ )
#define __DELAY_H_

void do_delay(unsigned long milliseconds);

class Delay
{
 private:
    #define MILLISEC 10		/* Take a 10ms fixed timer rate */
    #define FREQ (1000/MILLISEC)	/* Timer freqency for MILLISEC */

    #define TMR_CTRL	0x43	/* I/O for control */
    #define TMR_BOTH	0x30	/* RW both bytes */
    #define TMR_MD3	0x6	/* Mode 3 */

    #define PRECISION	8		/* Calibration precision */

    void init_pit(int, unsigned char);

 public:
    Delay();
    ~Delay();
    void init();
    unsigned long calibrateDelayLoop(void);
};

#endif
