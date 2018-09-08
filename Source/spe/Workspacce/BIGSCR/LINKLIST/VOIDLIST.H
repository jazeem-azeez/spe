///////////////////////////////////////////////////////
//                                                   //
//   Linked List Class Functions - Version 2.00      //
//                                                   //
//         By Kevin Campbell 18/12/96                //
//                                                   //
//                                                   //
///////////////////////////////////////////////////////

#ifndef VOID_LIST_H
#define VOID_LIST_H

#include "alloc.h"

extern void terminate(char *message);

struct voidinfo{
  void *data;
  struct voidinfo *link;
  struct voidinfo *oldlink;
};

class void_list{
  struct voidinfo *curr; // only single entry required for linked list
  void *data;
  int entries;
  int curr_entry;
public:
  void_list(void);  			// Constructor
  ~void_list(void); 			// DeConstructor
  char add(void *tempdata=NULL); 	// Adds new entry with 'size' data allocated
  char kill(void);    			// Removes entry from list and frees up memory
  void link(voidinfo *entry);       // Links linked_list onto another
  voidinfo *cutfront();             // Cut's off front of list and returns pointer
  voidinfo *cutend();               // Cut's off end of list and returns pointer
  char nuke(void);			// Removes all entries
  void *get(void);			// Gets data from entry
  char put(void *info);		// Puts data to entry

  char operator=(void *info);	// Puts data to entry
  char operator--(int x); 		// Uses last entry in list
  char operator++(int x); 		// Uses next entry in list

  char last(void);	 		// Uses last entry in list
  char next(void); 			// Uses next entry in list
  char rw(void);	      		// Goes to start of list
  char ff(void); 			// Goes to end of list
  int num(void); 			// Returns number of entries in list
  void count(void);			// Restores info in list
  void *addr(void);    			// Returns pointer to data
  char use(int entry);                  // Goes to specified entry in list
  char find(void *fdata);		// Makes the list with data fdata current
};

// *Note - all char entries return 1 on successful
//         completion and 0 on failure.

#endif