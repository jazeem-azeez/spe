#include "x86.h"
#include "defs.h"

#if !defined ( __PC_SPEAKER_H_ )
#define __PC_SPEAKER_H_

class PCspk
{
 private:
    #define SPEAKER_CTRL	0x43
    #define SPEAKER_DATA	0x42
 public:
    PCspk();
    ~PCspk();
    void init();
    void beep();
    void sound(unsigned int);
    void nosound();
};

#endif
