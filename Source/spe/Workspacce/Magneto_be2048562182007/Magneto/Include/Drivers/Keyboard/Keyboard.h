#include "x86.h"
#include "iostream.h"
#include "interrupts.h"

#if !defined ( __KEYBOARD_H_ )
#define __KEYBOARD_H_

#define KB_PORT			0x60    /* keyboard port */
#define KB_CTRLR		0x64    /* keyboard controller port */

#define KB_SET_LEDS		0xED
#define KB_SET_TYPEMATIC_DELAY	0xF3

static char KB_BUF[256];


void keyboard_irq();

class Keyboard
{
 private:
    void update_leds(unsigned char);
    int busy();
    void clear_hw_buf();
    void while_not_ready();
    void send_data(char);
 public:
    Keyboard();
    ~Keyboard();
    void init();
    void set_typematic_delay(unsigned char);
};

#endif
