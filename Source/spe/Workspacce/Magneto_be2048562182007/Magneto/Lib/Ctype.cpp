#include "ctype.h"

#if !defined ( __CTYPE_CPP_ )
#define __CTYPE_CPP_

char itoa(int __i)
{
 switch(__i)
 {
  case 1:return '1';
  case 2:return '2';
  case 3:return '3';
  case 4:return '4';
  case 5:return '5';
  case 6:return '6';
  case 7:return '7';
  case 8:return '8';
  case 9:return '9';
  case 0:return '0';
 };
 return -1;
}

int atoi(char __ch)
{
 switch(__ch)
 {
  case '0':return 0;
  case '1':return 1;
  case '2':return 2;
  case '3':return 3;
  case '4':return 4;
  case '5':return 5;
  case '6':return 6;
  case '7':return 7;
  case '8':return 8;
  case '9':return 9;
 };
 return -1;
}

#endif
