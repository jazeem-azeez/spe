#include "mem.h"
#include "defs.h"

#if !defined ( __MEM_CPP_ )
#define __MEM_CPP_

void *memcpy(void *dst_ptr, const void *src_ptr, unsigned long int count)
{
	void *ret_val = dst_ptr;
	const char *src = (const char *)src_ptr;
	char *dst = (char *)dst_ptr;

/* copy up */
	for(; count != 0; count--)
		*dst++ = *src++;
	return ret_val;
}


void *memsetw(void *dst, int val, unsigned long int count)
{
	unsigned short *temp = (unsigned short *)dst;

	for( ; count != 0; count--)
		*temp++ = val;
	return dst;
}

void *memsetb(void *dst, unsigned char val, unsigned long int count)
{
	unsigned char *temp = (unsigned char *)dst;

	for( ; count != 0; count--)
		*temp++ = val;
	return dst;
}

#endif
