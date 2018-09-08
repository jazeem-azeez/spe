#include "drivers\sound\pc_speaker.h"

#if !defined ( __PC_SPEAKER_CPP_ )
#define __PC_SPEAKER_CPP_

PCspk::PCspk()
{
}

PCspk::~PCspk()
{
}

void PCspk::init()
{
}

void PCspk::sound(unsigned int frequency)
{
 unsigned char status;
 frequency = 1193182 / frequency;
	
 outportb(SPEAKER_CTRL , 0xB6);
 outportb(SPEAKER_DATA , (unsigned char)frequency);
 outportb(SPEAKER_DATA , (unsigned char)(frequency >> 0x08));

 status = inportb(0x61);
 if(status != (status|0x03)) outportb(0x61, status|3) ;

}

void PCspk::nosound()
{
 outportb(0x61 , inportb(0x61) & 0xFC );
}

#endif
