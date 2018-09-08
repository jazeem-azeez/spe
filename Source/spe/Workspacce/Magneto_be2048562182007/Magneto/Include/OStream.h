#include "Silver\Console\Console.h"

#if !defined ( __OSTREAM_H_ )
#define __OSTREAM_H_

namespace std
{
 const char endl = '\n';

 class OStream : private Console
 {
  private:

  public:
     OStream& operator<<(char *cp);
     OStream& operator<<(char c);
     OStream& operator<<(unsigned char *cq);
     OStream& operator<<(unsigned char c1);
     OStream& operator<<(unsigned int n1);
     OStream& operator<<(int n1);
 };

 extern OStream cout;
}


#endif
