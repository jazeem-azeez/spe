///////////////////////////////////////////////////////
//                                                   //
//   Linked List Class Functions - Version 1.00      //
//                                                   //
//           By Kevin Campbell 22/7/95               //
//                                                   //
//                                                   //
///////////////////////////////////////////////////////

struct far details{
  char forename[20];
  char surname[20];
  char day;
  char month;
  int year;
};

struct far linkinfo{
  void *data;
  int size;
  struct far linkinfo *link;
  struct far linkinfo *oldlink;
};

template <class DX>
class linked_list{
  struct linkinfo *curr; // only single entry required for linked list
  int entries;
  int curr_entry;
public:
  linked_list(void);  		// Constructor
  ~linked_list(void); 		// DeConstructor
  char add();		 	// Adds new entry with 'size' data allocated
  char kill(void);    		// Removes entry from list and frees up memory
  char get(void *info);		// Gets data from entry
  char put(void *info);		// Puts data to entry
  char last(); 			// Uses last entry in list
  char next(); 			// Uses next entry in list
  char rewind();      		// Goes to start of list
  char fastforward(); 		// Goes to end of list
  int num(); 			// Returns number of entries in list
  DX *addr();        	// Returns pointer to data
};

// *Note - all char entries return 1 on successful
//         completion and 0 on failure.






//
//
// *Note - templated functions must be inside include file
//
//






///////////////////////////////////////////////////////
//                                                   //
//   Linked List Class Functions - Version 1.00      //
//                                                   //
//           By Kevin Campbell 22/7/95               //
//                                                   //
//                                                   //
///////////////////////////////////////////////////////

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <alloc.h>

template <class DX>
char linked_list<DX>::add(){
  char far *tempstore;
  DX *tempdata;
  struct far linkinfo *nextlink;
  struct far linkinfo *templink;

  if (tempdata=new DX){//[ammount]){
    if (templink=(linkinfo *)malloc(sizeof(linkinfo))){
      if (curr){ // curr exists and should be linked from

	// Preserve Structure

	nextlink=curr->link;

	templink->link=curr->link;
	templink->oldlink=curr;

	nextlink->oldlink=templink;
	curr->link=templink;

	templink->data=tempdata;

	//templink->size=ammount;

	curr=templink; // Set current Linked-List position to new struct

	curr_entry++;

	///////////////////////////////////

      }else{
	// Linked List does not exist
	// Create new linked list structure
	templink->link=NULL;
	templink->oldlink=NULL;
	templink->data=tempdata;
	//templink->size=ammount;
	curr=templink;
	curr_entry++;
      }
      entries++;
    }else{
      delete tempdata;
      return(0);
    }
    return(1);
  }else{
    // Allocation of tempdata failed
    return(0);
  }
}

template <class DX>
char linked_list<DX>::kill(void){
  struct far linkinfo *templink;
  struct far linkinfo *nextlink;
  struct far linkinfo *oldlink;

  if(!(curr==NULL)){ // if curr exists

    // Detach and Rebuild Structure

    nextlink=curr->link;
    oldlink=curr->oldlink;

    if(oldlink)oldlink->link=nextlink;
    if(nextlink)nextlink->oldlink=oldlink;

    // Entry is now completely removed from structure

    templink=curr; // Store removed entry address for deallocation

    ///////////////////////////////////

    if ((curr->link==NULL)&(curr->oldlink==NULL)){
      curr=NULL;
      curr_entry=0;
    }else{
      if(!(curr->oldlink==NULL)){
	curr=curr->oldlink;
	curr_entry--;
      }else{
	curr=curr->link;
      }
    }

    delete (DX *)templink->data;
    free(templink); // Deallocate memory and return to heap
    entries--;

    return(1);

  }else{
    return(0);
  }
}

template <class DX>
char linked_list<DX>::get(void *info){
  if(!(curr==NULL)){
    if(memcpy(info,curr->data,sizeof(DX))){
      return(1);
    }else{
      return(0);
    }
  }else{
    //Linked list does not exist, return error
    return(0);
  }
}

template <class DX>
char linked_list<DX>::put(void *info){
  if(!(curr==NULL)){
    if(memcpy(curr->data,info,sizeof(DX))){
      return(1);
    }else{
      return(0);
    }
  }else{
    //Linked list does not exist, return error
    return(0);
  }
}

template <class DX>
char linked_list<DX>::last(){
  if(curr){
    if(curr->oldlink){
      curr=curr->oldlink;
      return(1);
    }else{
      return(0);
    }
  }else{
    return(0);
  }
}

template <class DX>
char linked_list<DX>::next(){
  if(curr){
    if(curr->link){
      curr=curr->link;
      return(1);
    }else{
      return(0);
    }
  }else{
    return(0);
  }
}

template <class DX>
char linked_list<DX>::rewind(){
  if(curr){
    while (last());
    return(1);
  }else{
    return(0);
  }
}

template <class DX>
char linked_list<DX>::fastforward(){
  if(curr){
    while (next());
    return(1);
  }else{
    return(0);
  }
}

template <class DX>
int linked_list<DX>::num(){
  return(entries);
}

template <class DX>
DX *linked_list<DX>::addr(){
  if(curr){
    return((DX *)curr->data);
  }else{
    return(NULL);
  }
}

template <class DX>
linked_list<DX>::linked_list(void){
  entries=0;
  curr=NULL;
  curr_entry=0;
}

template <class DX>
linked_list<DX>::~linked_list(void){
  while(kill());
}

