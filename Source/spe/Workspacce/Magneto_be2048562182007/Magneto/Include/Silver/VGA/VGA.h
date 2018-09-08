#include "x86.h"
#include "Silver\Silver.h"
#include "IOStream.h"

#if !defined ( __VGA_H_ )
#define __VGA_H_

class VGA : public Silver
{
 private:
    unsigned int g_maxx, g_maxy;
    unsigned char Is_Graphics;
 public:
    VGA();
    ~VGA();
    void init();
    void update_vga();
    void setmode(unsigned char *);
};

extern VGA vga;

#endif
