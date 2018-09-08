/*
		DATE --> 18-10-2003
     CODE WRITTEN BY --> U.SRINIVAS (srinivascse@yahoo.com)

     THIS DEMO PROGRAM SHOW'S HOW TO USE THE VDU.H UTILITY FILE,
     THROUGH WHICH SIMPLE ELEMENTS OF DOS GUI CAN BE MADE.
     THIS IS DIRECT DISPLAY(DIRECT WRITING IN TO VIDEO MEMORY)
     BY WHICH WE CAN AVOID PRINTF,CPRINTF STATEMENTS IN PROGRAM.

     THIS FILE CONTAIN FUCTIONS SUCH AS

     1. DBOX(...) --> WHICH DRAW'S A DOUBLE-LINED BOX
     2. DLINE(...)--> WHICH DRAW'S A DOUBLE LINE
     3. SBOX(...) --> WHICH DRAW'S A SINGLE-LINED BOX
     4. SLINE(...)--> WHICH DRAW'S A SINGLE LINE
     5. CREC(...) --> WHICH CREATE A COLOURED RECTANGLE

     COMPILED USING TURBOC 3.0

     FOR  ANY DOUBTS AND SUGGESTIONS PLZ MAIL ME : srinivascse@yahoo.com
									*/


#include<stdio.h>
#include<conio.h>
#include<d:\cprgs\vdu.h>

void main()
{
clr();
crec(5,3,75,21,1);
dbox(6,3,74,21,1,15);
crec(25,5,55,5,2);
gotoxy(27,5);
textbackground(2);
textcolor(5);
cprintf(" This is a demo program ");
crec(10,10,30,15,4);
sbox(10,10,30,15);
getch();
}
