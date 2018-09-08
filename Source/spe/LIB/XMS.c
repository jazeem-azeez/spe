/*           Copyright 1995 by Ethan Brodsky.  All rights reserved          */

/* ÛÛ XMS.C ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ */

#pragma option -w- // Prevent "Function should return a value" warning

  void xms_init(void);

  unsigned int xms_getversion(void);
  unsigned int xms_getfreemem(void);

  int xms_allocate(int far *handle, unsigned int size);
  int xms_reallocate(int handle, unsigned int newsize);
  int xms_free(int far *handle);

  typedef struct
    {
      unsigned long length;
      unsigned int  sourcehandle;
      unsigned long sourceoffset;
      unsigned int  desthandle;
      unsigned long destoffset;
    } MOVEPARAMS;

  int xms_move(MOVEPARAMS far *params);

/* ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ */

#include <mem.h>

  void far *xms_driver = NULL; /* Pointer to XMS driver (Set by xms_init()) */

  void xms_init()
    {
      asm {
        mov  ax, 0x4310
        int  0x2F
        mov  word ptr [xms_driver], bx
        mov  word ptr [xms_driver+2], es
      }
    }

/* ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ */

  unsigned int xms_getversion()
    {
      asm {
        mov  ah, 0x00
        call [xms_driver]
      }
    }

/* ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ */

  unsigned int xms_getfreemem()
    {
      asm {
        mov  ah, 0x08
        call [xms_driver]
        mov  ax, dx
      }
    }

/* ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ */

  int xms_allocate(int far *handle, unsigned int size)
    {
      asm {
        mov  ah, 0x09
        mov  dx, size
        call [xms_driver]
        les  di, [handle]
        mov  es:[di], dx
      }
    }

/* ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ */

  int xms_reallocate(int handle, unsigned int newsize)
    {
      asm {
        mov  ah, 0x0F
        mov  bx, newsize
        mov  dx, handle
        call [xms_driver]
      }
    }

/* ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ */

  int xms_free(int far *handle)
    {
      asm {
        mov  ah, 0x0A
        les  di, [handle]
        mov  dx, es:[di]
        call [xms_driver]
        mov  word ptr es:[di], 0
      }
    }

/* ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ */

  int xms_move(MOVEPARAMS far *params)
    {
      asm {
        push ds
        mov  ah, 0x0B
        lds  si, [params]
        call [xms_driver]
        pop  ds
      }
    }

/*ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ*/

#pragma option -w  // Re-enable "function should return a value" warning
