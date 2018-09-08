#include "x86.h"
#include "mem.h"
#include "defs.h"
#include "ctype.h"
#include "Silver\Silver.h"
#include "Silver\VGA\Vga.h"


#if !defined ( __CONSOLE_H_ )
#define __CONSOLE_H_

class Console : public Silver
{
 private:
    static unsigned char * vid_mem;
    static unsigned char Is_Text;
    static unsigned int c_maxx, c_maxy, curr_x, curr_y, _textattrib, _fgcolor, _bgcolor, _crtc_io_adr, vga_misc_read;
    void detect_card_type();
    void update_cursor();
    void scroll_line_up();

 public:
    Console();
    ~Console();
    void init();
    void setmode(unsigned char *);
    void update_console();
    void settextbackground(int);
    void settextcolor(int);
    int wherex();
    int wherey();
    void gotoxy(char, char);
    void clrscr();
    void putch(unsigned char);
    void writeln(char *);
    void writeint(unsigned int);
    void writeint(int);
};

extern Console console;

#endif
