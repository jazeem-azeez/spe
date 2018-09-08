///////////////////////////////////////////////////////
//                                                   //
//     Void List Class Functions - Version 1.00      //
//                                                   //
//           By Kevin Campbell 22/7/95               //
//                                                   //
//                                                   //
///////////////////////////////////////////////////////

/*
	This is a piece of example code on how to use the voidlist
	library. This code has been tested with Borland's Turbo C++
	3.0 and should work on most C++ compilers.
*/

/*
	To use this library, include the voidlist files into your project
*/


#include "linklist\voidlist.h"
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <alloc.h>
#include <stdio.h>

#define LINK_SIZE 20

char name[][20]={"JOHN","MARK"};

main(){
  char far *temp;
  void_list names;
  names.add();
  names="JOHN";
  names.add();
  names="MARK";
  names.last();
  temp=(char far *)names.get();
  printf("%s\n",temp);
  names.next();
  temp=(char far *)names.get();
  printf("%s\n",temp);
  //printf("%s\n",names.addr()); // Addr returns a pointer to the data
  getch();

  names.nuke(); // flushes all

  names.add("BOBBY");
  temp=(char far *)names.get();
  printf("%s\n",temp);
  getch();
}