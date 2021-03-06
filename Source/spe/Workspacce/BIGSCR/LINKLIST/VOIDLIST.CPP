///////////////////////////////////////////////////////
//                                                   //
//   Linked List Class Functions - Version 2.00      //
//						     //
//          By Kevin Campbell 18/12/96               //
//                                                   //
//                                                   //
///////////////////////////////////////////////////////

#include "linklist\voidlist.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <alloc.h>

char void_list::add(void *tempdata){
  char *tempstore;
  struct voidinfo *nextlink;
  struct voidinfo *templink;

  if (templink=new voidinfo){
    if (curr){ // curr exists and should be linked from

      // Preserve Structure

      nextlink=curr->link;

      templink->link=curr->link;
      templink->oldlink=curr;

      nextlink->oldlink=templink;
      curr->link=templink;

      templink->data=tempdata;

      curr=templink; // Set current Linked-List position to new struct

      curr_entry++;

      ///////////////////////////////////

    }else{
      // Linked List does not exist
      // Create new linked list structure

      templink->link=NULL;
      templink->oldlink=NULL;
      templink->data=tempdata;
      curr=templink;
      curr_entry++;
    }
    entries++;
  }else{
    terminate("Malloc Failure - Linked list - Node allocation");
  }
  return(1);
}

char void_list::kill(void){
  struct voidinfo *templink;
  struct voidinfo *nextlink;
  struct voidinfo *oldlink;

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
      if(curr->link==NULL){
	curr=curr->oldlink;
	curr_entry--;
      }else{
	curr=curr->link;
      }
    }

    delete templink; // Deallocate memory and return to heap
    entries--;

    return(1);

  }else{
    return(0);
  }
}

void void_list::link(voidinfo *entry){
  curr=entry;
  count();
}

voidinfo *void_list::cutfront(){
  voidinfo *tempptr;
  if(curr){
    tempptr=curr->oldlink;
    curr->oldlink=NULL; // Cap main list end
    if(tempptr)tempptr->link=NULL; // Cap aux list start
    count();
    return(tempptr);
  }else{
    return(NULL);
  }
}

voidinfo *void_list::cutend(){
  voidinfo *tempptr;
  if(curr){
    tempptr=curr->link;
    curr->link=NULL;       // Cap main list start
    if(tempptr)tempptr->oldlink=NULL; // Cap aux list end
    count();
    return(tempptr);
  }else{
    return(NULL);
  }
}

char void_list::nuke(void){
  if(curr){
    while(kill());
    return(1);
  }else{
    return(0);
  }
}

char void_list::put(void *info){
  if(!(curr==NULL)){
    curr->data=info;
    return(1);
  }else{
    //Linked list does not exist, return error
    return(0);
  }
}

void *void_list::get(void){
  if(!(curr==NULL)){
    return(curr->data);
  }else{
    //Linked list does not exist, return error
    return(NULL);
  }
}

char void_list::find(void *fdata){
  rw();
  do{
    if(curr->data==fdata)return(1); // leaves linked list at position
  }while(next());
  return(0);
}

char void_list::last(){
  if(curr){
    if(curr->oldlink){
      curr=curr->oldlink;
      curr_entry--;
      return(1);
    }else{
      return(0);
    }
  }else{
    return(0);
  }
}

char void_list::next(){
  if(curr){
    if(curr->link){
      curr=curr->link;
      curr_entry++;
      return(1);
    }else{
      return(0);
    }
  }else{
    return(0);
  }
}


char void_list::rw(){
  if(curr){
    while (last());
    return(1);
  }else{
    return(0);
  }
}

char void_list::ff(){
  if(curr){
    while (next());
    return(1);
  }else{
    return(0);
  }
}

void void_list::count(void){
  entries=0;
  curr_entry=1;
  if(curr){
    rw();
    do{
      entries++;
    }while(next());
  }
}

int void_list::num(){
  return(entries);
}

void *void_list::addr(){
  if(curr){
    return(curr->data);
  }else{
    return(NULL);
  }
}

char void_list::use(int entry){
  while(curr_entry!=entry){
    if(curr_entry>entry){
      if(!last())return(0); // Failed
    }else{
      if(!next())return(0); // Failed
    }
  };
  return(1); // Pass :)
}

void_list::void_list(){
  entries=0;
  curr=NULL;
  data=NULL;
  curr_entry=0;
}

void_list::~void_list(){
  nuke();//while(kill());
}




char void_list::operator=(void *info){
  if(!(curr==NULL)){
    curr->data=info;
    return(1);
  }else{
    //Linked list does not exist, return error
    return(0);
  }
}

char void_list::operator--(int x){
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

char void_list::operator++(int x){
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