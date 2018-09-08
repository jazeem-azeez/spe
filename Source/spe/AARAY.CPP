#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<dir.h>
#include<stdlib.h>
#include<iostream.h>
#include<stat.h>
#include<direct.h>
#include<string.h>
#include<fstream.h>
#include<iomanip.h>

char *current_directory(char *path);
struct find_t ffblk;

char a[10][100];
int z=1;
static c=1;



//classupdate to database
class update
{
  char name[10];
  char name1[30];
  char org[30];
  char cell[20];
  char email[30];
  public:
  void create();
  void getdata()
  {
   printf("\nENTER YOUR DATA:");
   cin>>name;
  }
  void putdata();
};
update c1;

//function to update database
 void update::putdata()
  {
   cout<<name<<" ";
   strcpy(a[z],name);
   z++;
  }


//main program

int main()
 {
  clrscr();
  gotoxy(20,8);
  printf("AARAYA ANTIVIRUS");
do
{  clrscr();
   gotoxy(20,12);
   printf("MENU");
   gotoxy(20,13);
  printf("PRESS A TO KNOW ABOUT AUTHOR");
   gotoxy(20,14);
  printf("PRESS I TO INTRODUCTION ABOUT ANTIVIRUS");
    gotoxy(20,15);
  printf("PPESS P TO SEE PROCESS RUNNING IN THE SYSTEM");
   gotoxy(20,16);
 printf("PRESS S TO ACTIVATE ANTIVIRUS");
 gotoxy(20,17);
 printf("PRESS U TO UPDATA YOUR ANTIVIRUS DATABASE");
   gotoxy(20,18);
 printf("PRESS E TO EXIT");
   textcolor(WHITE);
   gotoxy(20,19);
 printf("PLEASE PROVIDE YOUR INPUT |");

switch(getche())
   {
   case 'a':
	 clrscr();
	 textcolor(WHITE);
	 gotoxy(15,10);

	 printf("NAME             : VIJAY SINGH ");
	 gotoxy(15,11);
	 printf("REGISTRATION NO  : 3050071075");
	 gotoxy(15,12);
	 printf("TRADE            : B.TECH-M.TECH CSE");
	 gotoxy(15,13);
	 printf("CELL NO          : 9814353853");
	 gotoxy(15,14);
	 printf("INSTITUTE        : LOVELY PROFESSIONAL UNIVERSITY");
	 getch();
	 break;
   case 'p': clrscr();
	     system("c:\\tc1\\processs.exe");
	     break;
   case 'i':clrscr();
	   char a[300]={" THIS IS THE SIMPLE ANTIVIRUS UTILITY DESIGNED IN PURPOSE TO DELETE A VIRUS"};
	   char b[300]={" OR A FILE , BY VIJAY SINGH .THIS VIRUS UTILITY SHOW THE BASIC FUNCTIONS OF "};

	   char c[300]={" AN ANTIVIRUS THAT HOW A ANTIVIRUS WORKS ON VERY LOW LEVEL. THIS UTILITY CAN"};

	   char d[300]={" CATCH A VIRUS AND CAN REMOVE THAT VIRUS. "};
	   char e[300]={" THIS UTILITY ALSO PROVIDE THE FACILITY ,TO UPDATION OF DATABASE MANUALLY"};

			 //sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss

	    textcolor(WHITE);
	    printf("\n\n\n\n\n\n");
	    printf("WELCOME user");
	    printf("\n\n");
	    textcolor(GREEN);
	    for(int i=1;i<=strlen(a);i++)
	    {
	     printf("%c",a[i]);
	     delay(50);
	    }
	    for( i=1;i<=strlen(b);i++)
	    {
	     printf("%c",b[i]);
	     delay(50);
	    }
	    for( i=1;i<=strlen(c);i++){printf("%c",c[i]);delay(50);}
	    for( i=1;i<=strlen(d);i++){printf("%c",d[i]);delay(50);}
	    for(i=1;i<=strlen(e);i++){printf("%c",e[i]);delay(50);}
	    printf("\n\n\n");
	    textcolor(WHITE);
	    printf("THANK YOU");
	    printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t CREATED BY VIJAY SINGH");
   getch();
   break;
   case 'e':clrscr();
	    textcolor(WHITE);
	    gotoxy(20,20);
	    printf("YOU ARE ABOUT TO EXIT ANTIVIRUS " );
	    gotoxy(20,21);
	     printf("PRESS Y TO CONFIRM ELSE PRESS N TO GO BACK [Y|N]:");

       switch(getche())
	    {
	    case 'y':
		     exit(1);
	    break;
	     case 'n':main();
	    break;
	    default :main();
	    break;
	   }
	   break;
  case 's':clrscr();
	   void antivirus();
	   antivirus();
	   break;
  case 'u':
  clrscr();
  update item;
  fstream f;
  f.open("data",ios::ate|ios::in|ios::out|ios::binary);
  f.seekg(0,ios::beg);
  cout<<"|OLD DATA BASE||\n ";
  while(f.read((char*)&item,sizeof(item)))
  { item.putdata();
  }
  f.clear();
  cout<<"\nADD NEW DATA BASE|";
  item.getdata();
  char ch;
  cin.get(ch);
  f.write((char*)&item,sizeof(item));
  f.seekg(0);
  cout<<"\n||CURRENT DATA BASE||\n";
  while(f.read((char*)&item,sizeof(item)))
  {
  item.putdata();
  }
  int last=f.tellg();
  int n=last/sizeof(item);
  cout<<"\n\nTOTAL DATA BASE ENTRY|"<<n;
  getch();
  break;
 }
}while(getche()!='e');
return 0;
}








//***********************************************************************
void antivirus()
{
  update item;
  fstream f;
  f.open("data",ios::ate|ios::in|ios::out|ios::binary);
  f.seekg(0,ios::beg);
  while(f.read((char*)&item,sizeof(item)))
  { item.putdata();
  }
clrscr();
void ch_drive();
ch_drive();
}
//*****************antivirus********************************************


void ch_drive()
 {
  void ch_dir();
  void ch_file();
  ch_file();
  ch_dir();
 }

void ch_file()
{

  //char a[8][10]={"","VIRUS","RANJAN","WIN32","NEWFOLDER","WORM","DELETE","CRESS"};
  textcolor(YELLOW);
  gotoxy(20,15);
  cprintf("Antivirus checking file system....");
  gotoxy(20,16);
  cprintf("_________________________________");
  gotoxy(20,18);
  cprintf("_________________________________");
  textcolor(GREEN);

  char name1[10];
  char drive[_MAX_DRIVE];
  char dir[_MAX_DIR];
  char file[_MAX_FNAME];
  char exte[_MAX_EXT];
  char curdir[MAXPATH];
  current_directory(curdir);


  int done,l;
  char s,ext[20]={'\0'};
  strcpy(ext,"*.*\0");
    gotoxy(20,17);
    cprintf(" %s",curdir);
    l=strlen(curdir);

    done = _dos_findfirst(ext,_A_NORMAL,&ffblk);
    while (!done)
    {
       _splitpath(ffblk.name,drive,dir,file,exte);
       gotoxy(20+l,17);
       cprintf("\\%s",file);
       gotoxy(20+l+strlen(file),17);
       cprintf(".%s    ",exte);
       delay(10);
       int j=1;
       while(j!=z-1)
       {

	if(strcmp(a[j-1],file)==0&&strcmp(".EXE",exte)==0)
	 {
	  gotoxy(20,19);
	  cprintf("VIRUS DETECTED %s%s",file,exte);
	  if(remove(ffblk.name)==0)
	   {
	    gotoxy(20,20);
	    cprintf("VIRUS HAS BEEN SUCCESSFULLY REMOVED ");
	    getch();
	    break;
	   }
	  else
	  {
		 gotoxy(20,19);
		 cprintf("VIRUS DOES NOT REMOVED              ");
		 rename(ffblk.name,"VIRUS.TXT");
		 break;
	  }
     } j++;
   }
    done = _dos_findnext(&ffblk);
  }
}
//**********************************************************************/
//**********************important information***************************/


//*********************************************************************
//*********************************************************************



void ch_dir()
{

class vijay{
public:
char new1[MAXPATH];
char old[MAXPATH];
vijay *next;
};vijay *top=NULL,*ptr,*temp;


  temp=((vijay*)malloc(sizeof(vijay)));
 struct ffblk file;
 int done;

 done = findfirst("*.*",&file,FA_DIREC);
  while (!done) {
  if(!(strcmp(file.ff_name,""))) {
	 gotoxy(20,21);
	 cprintf("SCAN SUCCESSFUL");
	 getch();};
if(((file.ff_attrib & 16)==16)&& file.ff_name[0]!='.')
    {
      ptr=((vijay*)malloc(sizeof(vijay)));
      strcpy(ptr->new1,file.ff_name);
      ptr->next=top;
      top=ptr;
    }
   done = findnext(&file);
 }
  current_directory(temp->old);
  ptr=top;
  while(ptr!=NULL)
   {
       chdir(ptr->new1);
       ch_file();
       ptr=ptr->next;
       chdir(temp->old);
   }
	 gotoxy(20,21);
	 cprintf("SCAN SUCCESSFUL");
	 getch();

}






void cwd()
{
   char curdir[MAXPATH];

   current_directory(curdir);
   return;
}
char *current_directory(char *path)
{
   strcpy(path, "X:\\");      /* fill string with form of response: X:\ */
   path[0] = 'A' + getdisk();    /* replace X with current drive letter */
   getcurdir(0, path+3);  /* fill rest of string with current directory */
   return(path);
}


