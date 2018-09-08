///////////////////////////////////////////////////////
//                                                   //
//   Linked List Class Functions - Version 2.00      //
//                                                   //
//         By Kevin Campbell 18/12/96                //
//                                                   //
//                                                   //
///////////////////////////////////////////////////////

#ifndef INT_LIST_H
#define INT_LIST_H

#include "alloc.h"

extern void terminate(char *message);

struct intinfo{
  int data;
  struct intinfo *link;
  struct intinfo *oldlink;
};

class int_list{

  struct intinfo *curr; // only single entry required for linked list
  int entries;
  int curr_entry;

public:

  int_list();	  			// Constructor
  ~int_list();	 			// DeConstructor

  char add(int val=0); 	     		// Adds new entry with value val
  char kill();    			// Removes entry from list and frees up memory
  void link(intinfo *entry);       	// Links linked_list onto another
  intinfo *cutfront();             	// Cut's off front of list and returns pointer
  intinfo *cutend();               	// Cut's off end of list and returns pointer
  char nuke();				// Removes all entries
  int  get();				// Gets data from entry
  char put(int val);			// Puts data to entry

  char operator=(int val);		// Puts data to entry
  char operator--(int x); 		// Uses last entry in list
  char operator++(int x); 		// Uses next entry in list

  char last(void);	 		// Uses last entry in list
  char next(void); 			// Uses next entry in list
  char rw(void);	      		// Goes to start of list
  char ff(void); 			// Goes to end of list
  int  num(void); 			// Returns number of entries in list
  void count(void);			// Restores info in list
  char use(int entry);                  // Goes to specified entry in list
  char find(int fdata);			// Makes the list with data fdata current
};

// *Note - all char entries return 1 on successful
//         completion and 0 on failure.

#endif