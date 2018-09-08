#include "OStream.h"

#if !defined ( __OSTREAM_CPP_ )
#define __OSTREAM_CPP_


namespace std
{
 OStream cout;

 OStream& OStream::operator<<(char *cp)
 {
  writeln(cp) ;
  return *this;
 }

 OStream& OStream::operator<<(char c)
 {
  putch(c) ;
  return *this;
 }

 OStream& OStream::operator<<(unsigned char *cq)
 {
  writeln((char *)cq) ;
  return *this;
 }

 OStream& OStream::operator<<(unsigned char c1)
 {
  putch((char)c1) ;
  return *this;
 }

 OStream& OStream::operator<<(unsigned int n1)
 {
  writeint(n1) ;
  return *this;
 }

 OStream& OStream::operator<<(int n1)
 {
  writeint(n1) ;
  return *this;
 }

}

#endif
