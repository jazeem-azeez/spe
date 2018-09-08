#include <dos.h>

int main(void)
{
   sound(20);
   delay(50);
   nosound();
   return 0;
}
