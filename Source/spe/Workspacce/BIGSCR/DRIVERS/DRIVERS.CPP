///////////////////////////////////////////////////////
//                                                   //
//  Device Driver Class Functions - Version 1.02     //
//						     //
//           By Kevin Campbell 6/12/96               //
//                                                   //
//                                                   //
///////////////////////////////////////////////////////

#include "drivers\drivers.h"

#include <stdio.h>
#include <conio.h>
#include <dos.h>

char driver::error[100];

char driver::softtest(){
  return(1);
}

char driver::hardtest(){
  return(1);
}

char driver::install(){
  return(1);
}

void driver::kill(){
  return;
}

char *driver::getname(){
  return("Anonymous device driver");
}


void driverlist::add(class driver *drv){
  if(!drivers.add(drv))terminate("Malloc failure - Adding driver (linked list)");
}

void driverlist::kill(class driver *drv){
  if(drivers.find(drv)){
    drivers.kill();
  }
}

char driverlist::check(){
  avail.nuke(); // Kill all entries
  if(drivers.rw()){
    do{
      if(((class driver *)drivers.get())->softtest()){
	if(!avail.add(drivers.get()))terminate("Malloc failure - valid driver (linked list)");
      }
    }while(drivers.next());
  }
  if(avail.num()){
    return(1);
  }else{
    return(0);
  }
}

class driver *driverlist::choose(char *type){
  int choice;
  int cnt=0;
  class driver *curdrv;


  if(!check())return(NULL); // All drivers failed softtest

  for(;;){
    printf("Available %s drivers :\n\n",type);

    if(avail.rw()){
      cnt=0;

      do{
	curdrv=(class driver *)avail.get();
	cnt++;
	printf("  %d: %s\n",cnt,curdrv->getname());
      }while(avail.next());
    }else{
      return(NULL); // No available drivers
    }

    printf("\n");

    do{
      choice=0;
      printf("Choose your %s driver (0 to cancel): ",type);
      scanf("%i",&choice);
      if(choice==0)return(NULL);
    }while(choice<0 | choice>cnt);


    if(!avail.use(choice))return(NULL);
    curdrv=(driver *)avail.get();

    if(curdrv->hardtest()){
      if(curdrv->install()){
	return(curdrv);
      }
    }

    printf("\n\n Driver error - %s\n",curdrv->error);
    kill(curdrv);
    getch();
    clrscr();
  }
}

void driverlist::list(char *type){
  int choice;
  int cnt=0;
  class driver *curdrv;

  check();

  if(avail.rw()){

    printf("\nDetected %s :\n\n",type);

    cnt=0;

    do{
      curdrv=(class driver *)avail.get();
      cnt++;
      printf("  %d: %s\n",cnt,curdrv->getname());
    }while(avail.next());

  }else{
    printf("\nNo supported %s detected\n");
  }

  printf("\n");
}