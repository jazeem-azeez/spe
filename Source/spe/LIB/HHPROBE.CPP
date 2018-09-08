
#include <stdio.h>                    //For puts()
#include <bios.h>                     //For generating system interrupt
#include <conio.h>                    //For clrscr()
#include <iostream.h>                 //For cout
#include <stdlib.h>                   //For abs() , itoa() and atoi()

void main()
{
	union REGS ii,oo;       //To store input and output for generating
				//BIOS Interrupt
	int a,n;
	char str[3];
	clrscr();
	puts("                        HARDWARE PROBING \n\n");
	int86(17,&ii,&oo);      //Generate system Interrupt 0x17 and
	a=oo.x.ax;              //Store results in integer variable a


	if((a&1)==0)            //Get Disk Drive information
		puts("Disk Drive:                          Abscent\n");
	else
		puts("Disk Drive:                          Present\n");


	if((a&2)==0)            //Get Math co-processor Information
		puts("Math co-processor:                   Abscent\n");
	else
		puts("Math co-processor:                   Present\n");


	cout<<"Initial Video Mode:     ";        // Get Initial Video Mode
	n=(a&48);
	switch(n)
	{
		case 48:puts("             80x25 BW with mono card\n");
			break;
		case 32:puts("             80x25 BW with color card\n");
			break;
		case 16:puts("             40x25 BW with Color Card\n");
			break;
		default:puts("             VGA Graphics Card\n");
			break;
	}


	n=(a&0x100);            //Get DMA information
	if(n==0x100)
		puts("DMA :                                Abscent\n");
	else
		puts("DMA :                                Present\n");


	n=(a<<14)>>13;          //Get No. of serial ports
	n=abs(n);
	cout<<"No. of serial ports Present:         ";
	cout<<itoa(n,str,10)<<endl<<endl;


	if((a&0x1000)==0)       //Get game adapter information
		puts("Game adapter:                        Abscent\n");
	else
		puts("Game adapter:                        Present\n");


	n=a>>14;                //get No. of Parallel Ports
	n=abs(n);
	cout<<"No. of parallel Ports present:       ";
	puts(itoa(n,str,10));
	puts("\n");
	cout<<"\nPress any key to continue....";
	getch();
}


