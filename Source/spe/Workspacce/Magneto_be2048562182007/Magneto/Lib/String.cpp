#include "string.h"
#include "defs.h"

#if !defined ( __STRING_CPP_ )
#define __STRING_CPP_

unsigned strlen(const char *str)
{
	unsigned ret_val;

	for(ret_val = 0; *str != '\0'; str++)
		ret_val++;
	return ret_val;
}

#endif
