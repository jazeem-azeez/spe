
#include <dos.h>

int main(void)
{
/*
   Ask overlay manager to check for expanded
   memory and allow it to use 16 pages
   (256K); available only in medium, large
   and huge memory models
*/

/* In the IDE, set Options|Applications to Dos Overlay */

   _OvrInitExt (0x200000L,256);

   return 0;

}
