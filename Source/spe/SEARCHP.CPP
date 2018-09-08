#include <stdio.h>
#include <dir.h>
#include <dos.h>

int main(void)
{
/*
   Available only in medium, large and
   huge memory models
*/

/*
   Use the extended memory from the linear
   address 0x200000L (2MB), as much as
   necessary
*/
/* In the IDE, set Options|Applications to Dos Overlay */

   _OvrInitExt (0x200000L, 0);

   return 0;
}