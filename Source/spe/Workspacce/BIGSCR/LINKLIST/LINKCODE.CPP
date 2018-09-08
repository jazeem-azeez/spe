///////////////////////////////////////////////////////
//                                                   //
//   Linked List Class Functions - Version 1.00      //
//                                                   //
//           By Kevin Campbell 22/7/95               //
//                                                   //
//                                                   //
///////////////////////////////////////////////////////

/*
	This is a piece of example code on how to use the linklist
	library. THis code has been tested with Borland's Turbo C++
	3.0 and should work on most C++ compilers.
*/

/*
	To use this library, include the linklist files into your project
*/


#include "linklist\linklist.h"
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <alloc.h>
#include <stdio.h>

#define LINK_SIZE 20

main(){
  char temp[LINK_SIZE];
  linked_list<char> names;
  names.add();
  names.put("J");
  names.add();
  names.put("M");
  names.last();
  names.get(temp);
  printf("%s\n",names.addr());
  names.next();
  printf("%s\n",names.addr()); // Addr returns a pointer to the data
  getch();
}