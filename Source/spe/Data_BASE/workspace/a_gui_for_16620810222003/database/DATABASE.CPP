
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<dos.h>
#include<vdu.h>

#define datafile "data.dat"
#define tempfile "temp.dat"

struct rec
{
int code;
char name[20];   //structure of a file record used to store in data.dat file
int density,state[20];
float cost;
}r;

void list(int*),addn(),dele(int),modify(int);
int count=1,nor=0,count1=0,pagecount=1;
 void list(int *c)
 {
 int j[5]={2,8,19,27,12},i=0,rp=0,m=0,rc=0;
 FILE *fp;
 long int recsize;
 recsize=sizeof(r);
 count1++;
 fp=fopen(datafile,"rb+");
 if(fp==NULL)
 {
 clr();
 gotoxy(3,5);
 printf("\nFile Creation Error\n\nPlease verify and set the path of ur data.dat file\nif the file does not exist,create a dummy file as data.dat keep it in the \npath specified above or u can change the path in the #define statement\nif u know where the file exists\nPress ESC to exit.");

 }
 rewind(fp);

		 while(fread(&r,recsize,1,fp)==1)
		     {
		       i=0;
		       m=0;

		      if(count1==1)
		      nor++;                     //no.of records

		      rp++;      //record pointer
	       if((rp>18*(pagecount-1))&&(rp<=18*(pagecount)))      //this formula will print the required records
		 {
		      rc++;
		      if(rp==(*c))
		       {
			 textcolor(15);
			 textbackground(10);
		       }
		       else
		       {
		       textcolor(15);
		       textbackground(0);
		       }
			printf("\nrecord no :->%d \n"nor);
		      m=m+j[i];
		      gotoxy(m,rc+5);
		      cprintf("%d.",rp);
		      i++;
		       m=m+j[i];
		      gotoxy(m,rc+5);
		      cprintf("%d",r.code);
		      i++;
		       m=m+j[i];
		      gotoxy(m,rc+5);
		      cprintf("%s",r.name);
		      i++;
		       m=m+j[i];
		      gotoxy(m,rc+5);
		      cprintf("%d",r.density);
		      i++;
			m=m+j[i];
		      gotoxy(m,rc+5);
		      cprintf("%d",r.state);
		      i++;
		       m=m+j[i];
		      gotoxy(m,rc+5);
		      cprintf("%.2f",r.cost);

		      }


	       }

      fcloseall();

 }
void searcher(char key [])
 {
 int j[5]={2,8,19,27,12},i=0,rp=0,m=0,rc=0;
 FILE *fp;
 long int recsize;
 recsize=sizeof(r);
 count1++;
 fp=fopen(datafile,"rb+");
 if(fp==NULL)
 {
 clr();
 gotoxy(3,5);
 printf("\nFile Creation Error\n\nPlease verify and set the path of ur data.dat file\nif the file does not exist,create a dummy file as data.dat keep it in the \npath specified above or u can change the path in the #define statement\nif u know where the file exists\nPress ESC to exit.");

 }
 rewind(fp);

		 while(fread(&r,recsize,1,fp)==1)
		     {
		       i=0;
		       m=0;

		      if(count1==1)
		      nor++;                     //no.of records

		      rp++;      //record pointer
if (strcpy(r.name,key)==0)
{
	       if((rp>18*(pagecount-1))&&(rp<=18*(pagecount)))      //this formula will print the required records
		 {
		      rc++;
		      if(rp==(*c))
		       {
			 textcolor(15);
			 textbackground(10);
		       }
		       else
		       {
		       textcolor(15);
		       textbackground(0);
		       }
			printf("\nrecord no :->%d \n"nor);
		      m=m+j[i];
		      gotoxy(m,rc+5);
		      cprintf("%d.",rp);
		      i++;
		       m=m+j[i];
		      gotoxy(m,rc+5);
		      cprintf("%d",r.code);
		      i++;
		       m=m+j[i];
		      gotoxy(m,rc+5);
		      cprintf("%s",r.name);
		      i++;
		       m=m+j[i];
		      gotoxy(m,rc+5);
		      cprintf("%d",r.density);
		      i++;
			m=m+j[i];
		      gotoxy(m,rc+5);
		      cprintf("%d",r.state);
		      i++;
		       m=m+j[i];
		      gotoxy(m,rc+5);
		      cprintf("%.2f",r.cost);

		      }


	       }
}
      fcloseall();

 }






 void addn()
 {

 FILE *fp;
 struct rec r;
 long int recsize;
 char vh='y';
 fp=fopen(datafile,"rb+");
 fseek(fp,0,SEEK_END);
 recsize=sizeof(r);

		   while(vh=='y'||vh=='Y')
		   {
			clr();
		  _setcursortype(_NORMALCURSOR);
		  printf("\nEnter the Item Code : ");
		  scanf("%d",&r.code);
		  printf("\nEnter the Item Name : ");
		  scanf("%s",r.name);
		  printf("\nEnter the density  : ");
		  scanf("%d",&r.density);
		  printf("\nEnter the Item Cost : ");
		  scanf("%f",&r.cost);
		  printf("\nEnter the state of matter ");
              scanf("%s",&r.state);
		  fwrite(&r,recsize,1,fp);
		  nor++;
		  printf("\nPress y to Add One More Record :");
		  fflush(stdin);
		  vh=getch();
		 }
		fcloseall();
		clr();

		}


void dele(int count)
	   {
		FILE *fp,*ft;
		struct rec r;
		long int recsize;
		int k=0;
		recsize=sizeof(r);
		fp=fopen(datafile,"rb+");
		ft=fopen(tempfile,"wb+");
		rewind(fp);
		while(fread(&r,recsize,1,fp)==1)
			{
			  k++;
			  if(k!=count)
			    fwrite(&r,recsize,1,ft);
			}
			fclose(fp);
			fclose(ft);
			remove(datafile);
			rename(tempfile,datafile);
	}




void modify(int count)
   {
     FILE *fp;
     long int recsize;
     int k=0;
     struct rec r;
     recsize=sizeof(r);
     fp=fopen(datafile,"rb+");

		 _setcursortype(_NORMALCURSOR);

		    rewind(fp);
		       while(fread(&r,recsize,1,fp)==1)
			{
			   k++;

			  if(k==count)
			   {
			     clr();
			     printf("\nEnter the NEW Details:\n");
			     printf("\nEnter the Item Code : ");
			     scanf("%d",&r.code);
			     printf("\nEnter the Item Name : ");
			     scanf("%s",r.name);
			     printf("\nEnter the density  : ");
			     scanf("%d",&r.density);
			     printf("\nEnter the state of matter ");
			     scanf("%s",&r.state);
			     printf("\nEnter the Item Cost per unit: ");
			     scanf("%f",&r.cost);
			     fseek(fp,-recsize,SEEK_CUR);
			     fwrite(&r,recsize,1,fp);
			    }
		       }

	   fcloseall();               //closing all the files
}


void main()

{
char command [20];
for (command=" ";strcpy("exit",command)!=0;printf("\ndbshell:-> ");)
	{
getline
	if (strcpy("help",command)==0)
	else if (strcpy("add",command)==0)
			add();
	else if (strcpy("modify",command)==0)
			
	else if (strcpy("list",command)==0)
	else if (strcpy("search",command)==0)
	else if (strcpy("delete",command)==0)
	else if (strcpy("help",command)==0)
	else if (strcpy("help",command)==0)
	else if (strcpy("help",command)==0)
	else if (strcpy("help",command)==0)

	}

}
