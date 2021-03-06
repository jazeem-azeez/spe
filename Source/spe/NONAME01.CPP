
#include <stdio.h>
#include <alloc.h>
#include <conio.h>

#define NUM_PTRS  10
#define NUM_BYTES 16

int mania( void )
{
   struct farheapinfo hi;
   char far *array[ NUM_PTRS ];
   int i;

   for( i = 0; i < NUM_PTRS; i++ )
      array[ i ] = (char far *) farmalloc( NUM_BYTES );

   for( i = 0; i < NUM_PTRS; i += 2 )
      farfree( array[ i ] );

   hi.ptr = NULL;
   printf( "   Size   Status\n" );
   printf( "   ----   ------\n" );
   while( farheapwalk( &hi ) == _HEAPOK )
     printf( "%7u    %s\n", hi.size, hi.in_use ? "used" : "free" );
     getch();
   return 0;
}

int main(void)
{
   printf("Changing allocation with sbrk()\n");
   printf("Before sbrk() call: %lu bytes free\n",
          (unsigned long) coreleft());
   sbrk(1000);
   printf(" After sbrk() call: %lu bytes free\n",
           (unsigned long) coreleft());
   return 0;
}
