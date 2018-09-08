#include "Silver/Console/Console.h"

#if !defined ( __CONSOLE_CPP_ )
#define __CONSOLE_CPP_


unsigned char * Console::vid_mem, Console::Is_Text;
unsigned int Console::c_maxx, Console::c_maxy, Console::curr_x, Console::curr_y, Console::_textattrib, Console::_fgcolor, Console::_bgcolor, Console::_crtc_io_adr, Console::vga_misc_read;


Console::Console()
{
 detect_card_type();
 _crtc_io_adr = 0x3D4;
 vga_misc_read = 0x03CC;
 vid_mem = (unsigned char*) 0xB8000;
 c_maxx = 79; c_maxy = 24;
 curr_x = 0; curr_y = 0;
 _textattrib=7;
 _fgcolor=7;
 _bgcolor=0;
 Is_Text = TRUE;
 clrscr();
}

Console::~Console()
{

}

void Console::detect_card_type()
{
 /* check for monochrome or color VGA emulation 

 if((inportb(vga_misc_read) & 0x01) == 1)
   {
    vid_mem = (unsigned char*) 0xB8000;
    _crtc_io_adr = 0x3D4;
   }
 else
   {
    vid_mem = (unsigned char*) 0xB0000;
    _crtc_io_adr = 0x3B4;
   } */ // Not working....
}

void Console::update_cursor()
{
 unsigned char temp;
 curr_x = curr_x + 1;
 temp = curr_x + curr_y * c_maxx;

 outportb(_crtc_io_adr, 15);
 outportb(_crtc_io_adr + 1, (temp & 0xFF));
 outportb(_crtc_io_adr, 14);
 outportb(_crtc_io_adr + 1, (temp >> 8) & 0xFF);

 curr_x = curr_x - 1;
}

void Console::scroll_line_up(void)
{
 memcpy(vid_mem, vid_mem + (c_maxx+1)*2, (maxy*(maxx+1)*2));
 memsetb(vid_mem + (c_maxx+1) * (c_maxy)*2, NULL, (c_maxx+1)*2);
}

void Console::init()
{
 vga.setmode(g_90x30_text);
 clrscr();
 update_console();
 cout<<endl<<"Initializing console";
 cout<<"\t\tDONE";
}

void Console::setmode(unsigned char *regs)
{
 set_mode(regs);
 clrscr();
 update_console();
}

void Console::update_console()
{
 if(type == TEXT)
 {
  Is_Text = TRUE;
  c_maxx = maxx;
  c_maxy = maxy;
  update_cursor();
 }
 else Is_Text = FALSE;
}


void Console::settextbackground(int col)
{
 if(col>7);
 else
   if(col<0);
   else
     _bgcolor=col;
 _textattrib=(_bgcolor*16)+_fgcolor;
}

void Console::settextcolor(int col)
{
 if(col>15);
 else
   if(col<0);
   else
     _fgcolor=col;
 _textattrib=(_bgcolor*16)+_fgcolor;
}

int Console::wherex(void)
{
 return curr_x;
}

int Console::wherey(void)
{
 return curr_y;
}

void Console::gotoxy(char _x, char _y)
{
 if((_y < 1)&&(_x < 1));
 else if((_y>c_maxy)&&(_x>c_maxx));
      else
	{
         curr_x = _x - 1; curr_y = _y - 1;
         update_cursor();
        }
}

void Console::clrscr()
{
 int i=0;
 for (i=0; i!=c_maxx; i=i+1) putch('\n'); /* BUG: rows = 25; but i has to be 80 for correct exec. */
 curr_x = 0; curr_y = 0;
 update_cursor();	/* Implemetation Error */
}

void Console::putch(unsigned char _ch)
{
 int i;
 switch(_ch)
 {
  case '\r':
  case '\n': curr_x = 0; curr_y = curr_y + 1;
             if(curr_y > c_maxy)
             {
              curr_x = 0; curr_y = c_maxy;
              scroll_line_up();
             }
	break;

  case '\t': for(i=0; i!=TAB; i=i+1)
             {
              putch(' ');
             }
	break;

  case '\b': curr_x = curr_x - 1;
             if(curr_x < 0)
             {
              curr_x = c_maxx; curr_y = curr_y - 1;
              if(curr_y < 0) { curr_x = 0; curr_y = 0; }
             }
             putch(' ');
             curr_x = curr_x - 1;
             if(curr_x < 0)
             {
              curr_x = c_maxx; curr_y = curr_y - 1;
              if(curr_y < 0) { curr_x = 0; curr_y = 0; }
             }
	break;

  default: vid_mem[((curr_y * (c_maxx + 1) + curr_x) * 2)]=_ch;
           vid_mem[((curr_y * (c_maxx + 1) + curr_x) * 2) + 1]=_textattrib;
           curr_x = curr_x + 1;
           if(curr_x > c_maxx)
           {
            putch('\n');
           }
	break;
 }
 update_cursor();
}

void Console::writeln(char *_str)
{
 char _ch;
 while(*_str != '\0')
 {
  _ch=*_str;
  putch(_ch);
  _str++;
 }
}

void Console::writeint(unsigned int _num)
{
 char _tnum[6];
 int _i=0;
 while(_num!=0)
 {
  _tnum[_i]=itoa(_num%10);
  _num=_num/10;
  _i=_i+1;
 }
 _tnum[_i]='\0';
 for(_i=0;_tnum[_i]!='\0';_i=_i+1);
 for(_i=_i-1;_i>=0;_i=_i-1)
 {
  putch(_tnum[_i]);
 }
}

void Console::writeint(int _num)
{
 if(_num < 0)
 {
  _num = _num * -1;
  putch('-');
 }

 char _tnum[10];
 int _i=0;
 while(_num!=0)
 {
  _tnum[_i]=itoa(_num%10);
  _num=_num/10;
  _i=_i+1;
 }
 _tnum[_i]='\0';
 for(_i=0;_tnum[_i]!='\0';_i=_i+1);
 for(_i=_i-1;_i>=0;_i=_i-1)
 {
  putch(_tnum[_i]);
 }
}

#endif
