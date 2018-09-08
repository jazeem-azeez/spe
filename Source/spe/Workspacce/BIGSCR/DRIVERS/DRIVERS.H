///////////////////////////////////////////////////////
//                                                   //
//  Device Driver Class Functions - Version 1.02     //
//						     //
//           By Kevin Campbell 6/12/96               //
//                                                   //
//                                                   //
///////////////////////////////////////////////////////

#ifndef DRIVERS_H
#define DRIVERS_H

#include "linklist\voidlist.h"

extern void terminate(char *message);

class driverlist{
  inline char check();
public:
  class void_list drivers;
  class void_list avail;

  inline void add(class driver *drv); // pointer to driver
  inline void kill(class driver *drv); // pointer to driver

  void list(char *type);
  class driver virtual *choose(char *type);
};

class driver{
public:
  char static error[100];
  char virtual softtest();
  char virtual hardtest();
  char virtual install();
  void virtual kill();
  char virtual *getname();
};


#endif