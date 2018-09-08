#include<stdio.h>
#include<conio.h>
#include<dos.h>
char pagebuffer[80*50];
void main()
{
	int i,j;
	/* Allocation of VDU memory */
	char far *vidmem =(char *) 0xB8000000;
	clrscr();
		   /*

	for(i=0,j=0;i<4000;i=i+1)
	{
	// Screen Displays
	//delay(10);
	if(j<=256)
	j++;
		*(vidmem + i) =j;
		}          */
	printf("string 1");
	for(i=0;i<4000;i++)
	pagebuffer[i]=*(vidmem + i);
	getch();
	clrscr();
	getch();
	for(i=0;i<4000;i++)
	*(vidmem + i)=pagebuffer[i];
	getch();


}