#include "x86.h"
#include "iostream.h"
#include "interrupts.h"

#if !defined ( __Timer_H_ )
#define __Timer_H_

void timer_irq();

class Timer
{
 private:
    #define PIT_COUNTER_0_PORT 0x40
    #define PIT_MODE_PORT 0x43
 public:
    Timer();
    ~Timer();
    void init();
};

#endif
