#include <stdio.h>
#include <dos.h>

#ifdef __cplusplus
    #define __CPPARGS ...
#else
    #define __CPPARGS
#endif

void interrupt get_out(__CPPARGS);    /* interrupt prototype */
void interrupt (*oldfunc)(__CPPARGS); /* interrupt function pointer */


int looping = 1;

int main(void)
{
  puts("Press <Shift><PrtSc> to terminate");

  /* save the old interrupt */
  oldfunc  = _dos_getvect(5);

  /* install interrupt handler */
  _dos_setvect(5,get_out);

  /* do nothing */
  while (looping);

  /* restore to original interrupt routine */
  _dos_setvect(5,oldfunc);

  puts("Success");
  return 0;
}

void interrupt get_out(__CPPARGS) {
  looping = 0;             /* change global var to get out of loop */
}


