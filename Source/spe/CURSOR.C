//#########################################################################
//----------------- MOUSE CURSOR CODE GENERATOR PROGRAM ------------------#
//#########################################################################
//----I Have Written & Compiled This Program In TURBO C++ 3.0 Compiler----#
//-----------------------Date : 5th January, 2007-------------------------#
//#########################################################################
//---------------------- PROGRAMMER : Suman Debnath ----------------------#
//--------------------Email: debnath.suman@yahoo.co.in--------------------#
//---------------------Contact No. : (+91) 9433734317---------------------#
//---------------------Computer Science & Engineering---------------------#
//-------------------------Academy Of Technology--------------------------#
//--------------------West Bengal , Republic of India.--------------------#
//#########################################################################
//--------Copying is granted as long as this notice stays attached--------#
//---------------------------to this software-----------------------------#
//#########################################################################

#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<dir.h>
#include<string.h>
#include<stdlib.h>

#define UP 1
#define DOWN 0


void coder();                //To read the image & code
void save();                 //To save the code
void flash();                //To clear the drawing area
void setHotPoint();          //To set the hot point of the cursor
void setBorder();            //To set the black border
void open_cursor_file(int);  //To open autosaved cursors files
void findHotXHotY();         //To find the Hot X,Y Co_ordinates of the cursor
int checkExistHotPoint();    //To check a Hotpoint already exist or not
void findFiles(int);         //To browse the cursor files
void showFile(char*);        //To show filenames one by one
void previewFile(char*);     //To preview the files
void clearPreview();         //To clear Preview zone
void modifySavedCursor();    //To modify any saved cursor
void showHelp(char*);        //To show help
void noOfOutputFiles();      //To show the number of output files
//To Create Buttons & Text
void BUTTONGRAY(int,int,int,int,int,int,int);
void BUTTON(int,int,int,int,int,int,int);
void TEXT(int,int,char*,int,int,int,int);


int gen=0;
int hotX=0,hotY=0,hotPointColor=12,HOTX,HOTY,COLOR;           //By default

char msg[80],*menu1[]={"Generate","HotPoint"," Border","AutoSave"," Flash","Default"," Apply"," Close"},
	     *menu2[]={"OpenFirst","  Next"," Previous"," Modify"},
	     *help1[]={"To Scan Drawing Area & Generate Code & Mask",
		       "To Set HotPoint of Cursor, Right Click To Set",
		       "To Create Dark Border / Right Click To Quit",
		       "To Save The Cursor Image, Filename Automatically Determined",
		       "To Clear The Draw Area",
		       "To Set Default Cursor",
		       "To Apply The Cursor",
		       "To Close"},
	     *help2[]={"Open First Saved Cursor File",
		       "Open First/Next Saved Cursor File",
		       "Open Previous Saved Cursor File",
		       "Modify Saved Image By Redrawing"},
	 *defaultHelp={"Left Click To Draw / Right Click To Erase"},
      *colorMeaning[]={"Used For Hot Point & Light Pixel Color",
		       "Used For Hot Point & Dark Pixel Color",
		       "Used For Normal Light Pixel Color",
		       "Used For Normal Dark Pixel Color",
		       "Used For Invisible Pixel"},
	  *fileType[]={"Cursor Files",
		       "Header Files"};

int usedColor[]={12,4,15,8,10};
long number,number2,code[16]={0},mask[16]={0};
int cursor[32]={0},cur[32]={0};
struct ffblk ffblk;
int done=-1,modifyLock=0,lock=0;
char cdStr[16][16],mskStr[16][16];


//====================================|
//********** MAIN FUNCTION ***********|
//====================================|
void main()
{
   int gdriver=DETECT, gmode;
   int i,j,x,y,button;
   initgraph(&gdriver, &gmode, "driver");


setcolor(2);
rectangle(0,0,360,360);
rectangle(10,10,350,350);
setfillstyle(1,2);
floodfill(1,1,2);

setcolor(1);
rectangle(365,0,getmaxx(),365);
rectangle(366,1,getmaxx()-1,364);
line(366,22,getmaxx(),22);
line(366,23,getmaxx(),23);
line(366,40,getmaxx(),40);

line(515,23,515,230);
line(516,23,516,230);

line(366,213,getmaxx(),213);
line(366,230,getmaxx(),230);
line(366,247,getmaxx(),247);
setfillstyle(1,9);
//Binary map
floodfill(377,25,1);
//Code
floodfill(527,25,1);
//Cursor Preview
floodfill(527,235,1);
setfillstyle(1,6);
//Windos Cursor Creator
floodfill(370,5,1);
rectangle(0,365,getmaxx(),getmaxy());

setfillstyle(1,5);
bar(367,214,514,229);
bar(517,214,637,229);

settextstyle(2,0,4);
setcolor(3);
outtextxy(372,215,"Scanning :");
outtextxy(523,215,"Coding :");
BUTTON(430,217,512,227,DOWN,14,1);
BUTTON(569,217,635,227,DOWN,14,1);

setcolor(11);
settextstyle(1,0,3);
outtextxy(373,-5,"Cursor Code Generator");
setcolor(15);
settextstyle(0,0,0);
outtextxy(380,28,"Binary Mapping    Code     Mask");
outtextxy(380,236,"Cursor Preview");
//Clearing Data Area (binary mapping,code,mask)
setfillstyle(1,7);
bar(367,41,514,212);
bar(517,41,637,212);
floodfill(370,250,1);
floodfill(3,370,1);

  for(i=0;i<9;i++)
   BUTTONGRAY(11+i,11+i,349-i,349-i,DOWN,1,0);
  setcolor(7);
  rectangle(20,20,340,340);
  setfillstyle(1,10);
  floodfill(21,21,7);

//Drawing Area
  for(i=20;i<340;i+=20)
   line(20,20+i,340,20+i);
  for(i=20;i<340;i+=20)
   line(20+i,20,20+i,340);
//Keys --- prev,next,select,default
  for(j=0;j<100;j+=25)
  {
    BUTTON(550,252+j,630,273+j,UP,7,1);
    BUTTON(551,253+j,629,272+j,UP,7,1);
    TEXT(554,259+j,menu2[j/25],DEFAULT_FONT,HORIZ_DIR,1,16);
  }
  //cursor preview zone
  BUTTON(371,252,544,348,DOWN,7,1);
  //opened cursor file area
  BUTTON(374,328,540,344,UP,3,1);
  //showing opened filename area
  BUTTON(428,331,536,341,DOWN,11,1);
  TEXT(378,333,"FILE :",DEFAULT_FONT,HORIZ_DIR,1,16);
  //showing cursor preview
  BUTTON(374,255,464,325,UP,2,1);
  BUTTON(377,258,441,322,DOWN,10,1);
  //drawing preview bar
  BUTTON(445,258,460,322,DOWN,14,1);
  //hotX
  BUTTON(467,255,541,272,UP,7,1);
  TEXT(470,260,"HotX:",DEFAULT_FONT,HORIZ_DIR,1,16);
  BUTTON(510,257,539,270,DOWN,8,1);
  //hotY
  BUTTON(467,275,541,292,UP,7,1);
  TEXT(470,280,"HotY:",DEFAULT_FONT,HORIZ_DIR,1,16);
  BUTTON(510,277,539,290,DOWN,8,1);
  //X-Y graph
  BUTTON(467,295,540,325,DOWN,7,1);
  {
  setcolor(15);
  line(471,299,530,299);
  line(471,299,471,320);
  setcolor(8);
  line(472,300,530,300);
  line(472,300,472,320);
  TEXT(529,295,">",SMALL_FONT,HORIZ_DIR,3,15);
  TEXT(530,295,">",SMALL_FONT,HORIZ_DIR,3,8);

  TEXT(467,318,"<",SMALL_FONT,VERT_DIR,3,15);
  TEXT(467,319,"<",SMALL_FONT,VERT_DIR,3,8);

  TEXT(534,295,"X",SMALL_FONT,HORIZ_DIR,3,8);
  TEXT(533,295,"X",SMALL_FONT,HORIZ_DIR,3,15);

  TEXT(476,317,"Y",SMALL_FONT,HORIZ_DIR,3,8);
  TEXT(475,317,"Y",SMALL_FONT,HORIZ_DIR,3,15);

  TEXT(475,300,"(0,0)",SMALL_FONT,HORIZ_DIR,4,8);
  TEXT(476,301,"(0,0)",SMALL_FONT,HORIZ_DIR,4,15);
  }
  //creating the net
  setcolor(2);
  for(i=0;i<60;i+=4)
     line(381+i,259,381+i,321);
   for(j=0;j<60;j+=4)
     line(378,262+j,440,262+j);

  //openning bar area
  BUTTON(371,351,630,362,UP,2,1);
  BUTTON(430,353,628,360,DOWN,14,1);
  TEXT(375,350,"Opening :",SMALL_FONT,HORIZ_DIR,4,10);
//Keys --- generate,hotpoint,save,flash
  settextstyle(0,0,0);
  for(i=0;i<570;i+=79)
   {
    BUTTON(5+i,370,78+i,391,UP,7,1);
    BUTTON(6+i,371,77+i,390,UP,7,1);
    TEXT(10+i,378,menu1[i/79],DEFAULT_FONT,HORIZ_DIR,1,16);
   }
//horizontal line below Genarate,Hotpoint....buttons
{
 setcolor(15);
 line(6,395,630,395);
 setcolor(8);
 line(6,397,630,397);
}
//Showing help area
{
 BUTTON(6,450,630,475,UP,7,1);
 BUTTON(7,451,629,474,UP,7,1);
 BUTTON(8,452,628,473,UP,8,1);
 BUTTON(68,456,624,469,DOWN,16,1);
 TEXT(15,459,"HELP :",DEFAULT_FONT,HORIZ_DIR,1,15);
 showHelp("Welcome To User Defined Mouse Cursor Code Generating Program");
}
//Color Meanings
{
 BUTTON(6,402,200,445,UP,7,1);
 BUTTON(8,415,152,443,DOWN,7,1);
 for(i=0;i<5;i++)
  BUTTON(12+i*28,419,36+i*28,439,UP,usedColor[i],1);
 TEXT(12,405,"Touch This Colors",DEFAULT_FONT,HORIZ_DIR,1,16);
 BUTTON(159,408,195,440,DOWN,7,1);
}
//Show number of generated files at startup
{
 BUTTON(210,402,400,446,UP,1,1);
 BUTTON(212,414,398,444,DOWN,7,1);
 TEXT(219,405,"Files Found At StartUp",DEFAULT_FONT,HORIZ_DIR,1,9);
 for(i=0;i<16;i+=14)
 {
  BUTTON(216,416+i,394,428+i,DOWN,8,1);
  TEXT(220,419+i,fileType[i/13],DEFAULT_FONT,HORIZ_DIR,1,6);
  TEXT(318,419+i,":",DEFAULT_FONT,HORIZ_DIR,1,10);
 }
 //Showing number of output files
 noOfOutputFiles();
}
//SHOW CREDIT, PROGRAMMER NAME,....
{
 for(i=0;i<2;i++)
  BUTTON(410+i,402+i,630-i,445-i,UP,7,1);
 for(i=0;i<2;i++)
  BUTTON(413+i,415+i,627-i,442-i,DOWN,2,1);
 TEXT(495,406,"CREDIT",DEFAULT_FONT,HORIZ_DIR,1,16);
 TEXT(419,420,"Programmer",DEFAULT_FONT,HORIZ_DIR,1,8);
 TEXT(417,418,"Programmer",DEFAULT_FONT,HORIZ_DIR,1,7);
 TEXT(499,420,":",DEFAULT_FONT,HORIZ_DIR,1,8);
 TEXT(497,418,":",DEFAULT_FONT,HORIZ_DIR,1,12);
 TEXT(509,420,"Suman Debnath",DEFAULT_FONT,HORIZ_DIR,1,8);
 TEXT(507,418,"Suman Debnath",DEFAULT_FONT,HORIZ_DIR,1,10);
 TEXT(420,432,"debnath.suman@yahoo.co.in",DEFAULT_FONT,HORIZ_DIR,1,8);
 TEXT(418,430,"debnath.suman@yahoo.co.in",DEFAULT_FONT,HORIZ_DIR,1,14);
}

initmouse();
showmouseptr();

while(1)    // Main while loop
 {
getmousepos(&button,&x,&y);
//printf("%d,%d\b\b\b\b\b\b\b\b\b\b\b\b\b\b",x,y);
  if(kbhit())
   {
      if(getch()==27)//Esc Key
      {
       goto end;
      }
    coder();
   }

  //Touching & Highlighting the buttons
  if(!kbhit() && (button & 1)!=1 && (button & 2)!=2)
   {
    //Generate,hotpoint,border................
    for(i=0;i<570;i+=79)
    {
     if(x>6+i && x<77+i && y>371 && y<390)
      {
       if(getpixel(7+i,372)==7)
	{
	 hidemouseptr();
	 setfillstyle(SOLID_FILL,14);
	 bar(7+i,372,76+i,389);
	 TEXT(10+i,378,menu1[i/79],DEFAULT_FONT,HORIZ_DIR,1,12);
	 showHelp(help1[i/79]);
	 showmouseptr();
	}
      }
     else
     {
      if(getpixel(7+i,372)==14)
	{
	 hidemouseptr();
	 setfillstyle(SOLID_FILL,7);
	 bar(7+i,372,76+i,389);
	 TEXT(10+i,378,menu1[i/79],DEFAULT_FONT,HORIZ_DIR,1,16);
	 showHelp(defaultHelp);
	 showmouseptr();
	}
     }
    }

   //previous,next,current....
   for(j=0;j<100;j+=25)
    {
     if(x>550 && x<630 && y>252+j && y<273+j)
     {
      if(getpixel(552,254+j)==7)
	{
	 hidemouseptr();
	 setfillstyle(SOLID_FILL,10);
	 bar(552,254+j,628,271+j);
	 TEXT(554,259+j,menu2[j/25],DEFAULT_FONT,HORIZ_DIR,1,12);
	 showHelp(help2[j/25]);
	 showmouseptr();
	}
     }
     else
     {
       if(getpixel(552,254+j)==10)
	{
	 hidemouseptr();
	 setfillstyle(SOLID_FILL,7);
	 bar(552,254+j,628,271+j);
	 TEXT(554,259+j,menu2[j/25],DEFAULT_FONT,HORIZ_DIR,1,16);
	 showHelp(defaultHelp);
	 showmouseptr();
	}
     }
    }
   //shows drawing color meanings
    for(i=0;i<5;i++)
    {
     if(x>12+i*28 && x<36+i*28 && y>419 && y<439 )
     {
      if(getpixel(175,425)==7)
      {
       showHelp(colorMeaning[i]);
       BUTTON(159,408,195,440,DOWN,usedColor[i],1);
      }
     }
     else
     {
      if(getpixel(175,425)==usedColor[i])
      {
       showHelp(defaultHelp);
       BUTTON(159,408,195,440,DOWN,7,1);
      }
     }
    }

   }

   //Pressing The Buttons
    if((button & 1)==1)
	{
	  //Selecting The Boxes
	   if(x>=20 && x<=340 && y>=20 && y<=340 && getpixel(x-1,y-1)==10)
	    {
	      hidemouseptr();
	      setfillstyle(1,15);
	      floodfill(x,y,7);
	      showmouseptr();
	    }
    //-------Pressing Keys-------
      //Upper (Prev,next ....)
       for(j=0;j<100;j+=25)
	if(x>550 && x<630 && y>252+j && y<273+j)
	 {
	  BUTTON(550,252+j,630,273+j,DOWN,10,1);
	  BUTTON(551,253+j,629,272+j,DOWN,10,1);
	  TEXT(554+1,259+j+1,menu2[j/25],DEFAULT_FONT,HORIZ_DIR,1,12);
	  delay(150);
	  BUTTON(550,252+j,630,273+j,UP,10,1);
	  BUTTON(551,253+j,629,272+j,UP,10,1);
	  TEXT(554,259+j,menu2[j/25],DEFAULT_FONT,HORIZ_DIR,1,12);

	    switch(j/25)
	     {
	       case 0:findFiles(0);
		      modifyLock=1;
		      break;
	       case 1:findFiles(1);
		      modifyLock=1;
		      break;
	       case 2:findFiles(2);
		      modifyLock=1;
		      break;
	       case 3:if(modifyLock)
		       {
			 modifySavedCursor();
			 coder();
			 gen=1;
		       }
		      break;
	     }
	 }

      //Lower (Generate,Hotpoint .....)
       for(i=0;i<570;i+=79)
	if(x>6+i && x<77+i && y>371 && y<390)
	 {
	  BUTTON(5+i,370,78+i,391,DOWN,14,1);
	  BUTTON(6+i,371,77+i,390,DOWN,14,1);
	  TEXT(10+i+1,378+1,menu1[i/79],DEFAULT_FONT,HORIZ_DIR,1,12);
	  delay(150);
	  BUTTON(5+i,370,78+i,391,UP,14,1);
	  BUTTON(6+i,371,77+i,390,UP,14,1);
	  TEXT(10+i,378,menu1[i/79],DEFAULT_FONT,HORIZ_DIR,1,12);

	    switch(i/79)
	     {
	      case 0 : coder();
		       gen=1;
		       break;
	      case 1 : setHotPoint();         //setting hot point
		       break;
	      case 2 : setBorder();           //set black border
		       break;
	      case 3 : save();                //Saving
		       break;
	      case 4 : flash();               //clearing
		       break;
	      case 5 : previewFile("system\\default.cur");
		       BUTTON(428,331,536,341,DOWN,11,1);
		       modifyLock=1;
		       break;                 //open default cursor file
	      case 6 : hidemouseptr();        //Applying
		       if(gen==1)
			{
			 findHotXHotY();      //find hot point
			 changecursor(cursor,hotX,hotY);//changing cursor
			}
		       showmouseptr();
		       break;
	      case 7 : closegraph();         //exit
		       exit(0);
	     }
	 }
    //----------------------------

	}
    if((button & 2)==2)
	{
	   if(x>=20 && x<=340 && y>=20 && y<=340)
	    {
	      hidemouseptr();
	      setfillstyle(1,10);
	      floodfill(x,y,7);
	      showmouseptr();
	    }
	}
}
end:
closegraph();
exit(0);
}

//-----------------------------------------------|
//------------Gerates Code and Mask--------------|
//-----------------------------------------------|
void coder()
{
char binCode[16],bin2[16],binMask[16],*endptr;
int i,j,k,l,v,x,y,button,cnt;

//Clearing Data Area (binary mapping,code,mask)
setfillstyle(1,7);
bar(367,41,514,212);
bar(517,41,637,212);

settextstyle(2,0,4);
setcolor(11);
outtextxy(372,215,"Scanning :");

strcpy(bin2,"\0");
strcpy(binCode,"\0");
strcpy(binMask,"\0");
settextstyle(0,0,1);

setcolor(15);
settextstyle(0,0,0);
//Creating code
l=0;
for(j=20,k=0;j<340;j+=20,k+=20)
 {
   for(i=20;i<340;i+=20)
   {
     if(getpixel(5+i,5+j)==15 || getpixel(5+i,5+j)==12) //white
      {
	 strcat(binCode,"0");
	 strcat(binMask,"1");
      }
     if(getpixel(5+i,5+j)==8 || getpixel(i+1,j+1)==4) //black
      {
	strcat(binCode,"0");
	strcat(binMask,"0");
      }
     if(getpixel(5+i,5+j)==10) //invisible
      {
	 strcat(binCode,"1");
	 strcat(binMask,"0");
      }
   }

  binCode[16]='\0';
  binMask[16]='\0';
 //Displaying Binary Mapping
  outtextxy(377,40+j/2,binCode);
  l=k/20;
  setfillstyle(1,12);
  bar(432+l*5,219,435+l*5,225);//Moving Bar
  delay(20);

  //convert to code
  number = strtol(binCode, &endptr,2);
  code[k/20]=number;
  //convert to mask
  number2 = strtol(binMask, &endptr,2);
  mask[k/20]=number2;

  strcpy(binCode,"\0");
  strcpy(binMask,"\0");
 } // End of for loop

settextstyle(2,0,4);
setcolor(3);
outtextxy(372,215,"Scanning :");
setcolor(11);
outtextxy(523,215,"Coding :");
//Show code and mask
settextstyle(0,0,0);
for(i=0;i<16;i++)
{
 sprintf(msg,"%X ",code[i]);
 setcolor(4);
 outtextxy(526,50+i*10,msg);
 sprintf(msg,"%X ",mask[i]);
 setcolor(6);
 outtextxy(595,50+i*10,msg);
 setfillstyle(1,12);
 bar(571+i*4,219,573+i*4,225);//Moving bar
 delay(20);
}
delay(100);
setcolor(3);
settextstyle(2,0,4);
outtextxy(523,215,"Coding :");

setfillstyle(1,14);
bar(431,218,511,226);
bar(570,218,634,226);

//Copying To Main Array Cursor
for(i=0;i<16;i++)
{
 cursor[i]=(int)code[i];
 cursor[16+i]=(int)mask[i];
}
//Finding HotPoint
findHotXHotY();
}

//----------------------------------|
//-----------Saves Cursors----------|
//----------------------------------|
void save()
{
FILE *fp,*cur,*creatHeader;
char fname[40],temp[20],ch[5];
int i,j;
unsigned int num=0;

up:
if((fp=fopen("Cursors\\cur.db","rb"))==NULL)
 {
   fclose(fp);
   if(gen==1)
   {
    sound(2000);
    delay(100);
    nosound();
    mkdir("Cursors");
    cur=fopen("Cursors\\cur.db","wb");
      putw(num,cur);
    fclose(cur);
    goto up;
   }
 }
else
 {
  num=getw(fp);
  fclose(fp);
  //Saving
  if(gen==1)
   {
    //printf("\n[%d]",num);
    //changing database
    fp=fopen("Cursors\\cur.db","wb");
      putw(num+1,fp);
    fclose(fp);

    //creating cursor file
    strcpy(fname,"Cursors\\cur");
    //itoa(num,ch, 10);
    sprintf(ch,"%d",num);
    strcat(fname,ch);
    strcat(fname,".cur");
    fp=fopen(fname,"wb");
     putw(hotX,fp);
     putw(hotY,fp);
     putw(hotPointColor,fp);
    for(i=0;i<32;i++)
      putw(cursor[i],fp);
    fclose(fp);

   //creating header file
   strcpy(fname,"\0");
   strcpy(fname,"Cursors\\cur");
   strcat(fname,ch);
   strcat(fname,".h");
   creatHeader=fopen(fname,"wb");
    fprintf(creatHeader,"int cursor%d[32]={",num);
    for(i=0;i<32;i++)
    {
      fprintf(creatHeader,"0x%x",cursor[i]);
      if(i<31)
       fprintf(creatHeader,",");
    }
    fprintf(creatHeader,"};");
    fclose(creatHeader);
   }
 }
 sound(3000);
 delay(200);
 nosound();
 sound(2000);
 delay(200);
 nosound();
}

//---------------------------------------|
//-----------Clear drawing area----------|
//---------------------------------------|
void flash()
{
int i,j;
setfillstyle(1,10);
for(j=20;j<340;j+=20)
 {
   for(i=20;i<340;i+=20)
   {
     floodfill(j+5,i+5,7);
   }
}
//Clearing Data Area (binary mapping,code,mask)
setfillstyle(1,7);
bar(367,41,514,212);
bar(517,41,637,212);
gen=0;
}

//---------------------------------|
//--------Setting hot point--------|
//---------------------------------|
void setHotPoint()
{
int i,j,k,l,x,y,button;

while(1)    // Main while loop
 {
getmousepos(&button,&x,&y);
if((button & 1)==1)
  {
   if(x>=20 && x<=340 && y>=20 && y<=340 && checkExistHotPoint())
   {
    hidemouseptr();
    if(getpixel(x-1,y-1)==8)
     setfillstyle(1,4);
    else
     setfillstyle(1,12);

    floodfill(x,y,7);
    showmouseptr();
   }
   break;
 }
}
}

//-----------------------------------------------|
//--------Check for a existing hot point---------|
//-----------------------------------------------|
int checkExistHotPoint()
{
int i,j;

for(i=20;i<340;i+=20)
 for(j=20;j<340;j+=20)
   if(getpixel(i+1,j+1)==12 || getpixel(i+1,j+1)==4)
    return 0;

return 1;
}

//----------------------------------|
//----------Find hot point----------|
//----------------------------------|
void findHotXHotY()
{
int i,j;

for(i=20;i<340;i+=20)
 for(j=20;j<340;j+=20)
 {
  hotPointColor=getpixel(i+1,j+1);
   if(hotPointColor==12 || hotPointColor==4)
   {
    hotX=i/20 -1;
    hotY=j/20 -1;
    goto end;
   }
 }
hotPointColor=12;
if(getpixel(21,21)==8)
 hotPointColor=4;
end:
}

//----------------------------------|
//----------Setting border----------|
//----------------------------------|
void setBorder()
{
int i,j,k,l,x,y,button;

while(1)    // Main while loop
 {
getmousepos(&button,&x,&y);
if((button & 1)==1)
  {
   if(x>=20 && x<=340 && y>=20 && y<=340)
   {
    hidemouseptr();
    setfillstyle(1,8);
    floodfill(x,y,7);
    showmouseptr();
   }
 }
if((button & 2)==2)
{
 break;
}
}
}

//-------------------------------|
//-----------Find Files----------|
//-------------------------------|
void findFiles(int option)
{
 int i=0;
 static count=0;

//-------------------------
 if(option==0)
 {
  done= findfirst("cursors\\*.cur",&ffblk,0);
  count=0;
 }

 if(option==2)
 {
  done= findfirst("cursors\\*.cur",&ffblk,0);
  count-=2;
  while(i<count)
  {
   done = findnext(&ffblk);
   i++;
  }
 }
//-------------------------

 if(!done)
 {
   showFile(ffblk.ff_name);
   count++;
 }
 else
 {
   done = findfirst("cursors\\*.cur",&ffblk,0);
   showFile(ffblk.ff_name);
   count=1;
 }
 done = findnext(&ffblk);
}

//---------------------------------|
//----------Show filenames---------|
//---------------------------------|
void showFile(char* filename)
{
 previewFile(filename);
 filename[strlen(filename)-4]='\0';
 BUTTON(428,331,536,341,DOWN,11,1);
 TEXT(434,333,filename,DEFAULT_FONT,HORIZ_DIR,1,16);
}

//------------------------------------------------|
//----------Open & Preview cursor files-----------|
//------------------------------------------------|
void previewFile(char* file)
{
 FILE *fp,*output;
 int ch,count=0,i,j,k,code[16],mask[16],len;
 char filename[30]="CURSORS\\";
 char str1[16][4],str2[16][4];
 char codeString[16][16]={"0000000000000000","0000000000000000","0000000000000000","0000000000000000",
			  "0000000000000000","0000000000000000","0000000000000000","0000000000000000",
			  "0000000000000000","0000000000000000","0000000000000000","0000000000000000",
			  "0000000000000000","0000000000000000","0000000000000000","0000000000000000"};


char maskString[16][16]={"0000000000000000","0000000000000000","0000000000000000","0000000000000000",
			  "0000000000000000","0000000000000000","0000000000000000","0000000000000000",
			  "0000000000000000","0000000000000000","0000000000000000","0000000000000000",
			  "0000000000000000","0000000000000000","0000000000000000","0000000000000000"};



 strcat(filename,file);
 //printf("\n[%s] \n",filename);
 if((fp=fopen(filename,"rb"))!=NULL)
 {
  HOTX=getw(fp);
  HOTY=getw(fp);
  COLOR=getw(fp);

  while(count<32)
   {
    ch=getw(fp);
    cur[count]=ch;
    count++;
   }
 }
  fclose(fp);

  //extracting code & mask from file data cur[32]
  for(i=0;i<16;i++)
  {
   code[i]=cur[i];
   mask[i]=cur[i+16];
  }

//######################################
 //****** CODE & MASK GENERATION ******#
 //#####################################
 for(i=0;i<16;i++)
  {
   sprintf(str1[i],"%x",code[i]);
   sprintf(str2[i],"%x",mask[i]);

   str1[i][4]='\0';
   str2[i][4]='\0';

 //--------------------------------------//
 //------ BINARY CODE GENERATION -------//
 //------------------------------------//
   len=strlen(str1[i]);
  //generating binary mapping codeString[16][16]
   for(j=0,k=0;j<15;j=j+4,k=k+4)
    {
    if(j==0) //ensures that switch case occurs for once
     {
      switch(len)
       {
	case 4: j=0;
		break;
	case 3: j=4;
		break;
	case 2: j=8;
		break;
	case 1: j=12;
		break;
       }
      }
      switch(str1[i][k/4])
       {
	 case '0': codeString[i][j+0]='0';
		   codeString[i][j+1]='0';
		   codeString[i][j+2]='0';
		   codeString[i][j+3]='0';
		   break;
	 case '1': codeString[i][j+0]='0';
		   codeString[i][j+1]='0';
		   codeString[i][j+2]='0';
		   codeString[i][j+3]='1';
		   break;
	 case '2': codeString[i][j+0]='0';
		   codeString[i][j+1]='0';
		   codeString[i][j+2]='1';
		   codeString[i][j+3]='0';
		   break;
	 case '3': codeString[i][j+0]='0';
		   codeString[i][j+1]='0';
		   codeString[i][j+2]='1';
		   codeString[i][j+3]='1';
		   break;
	 case '4': codeString[i][j+0]='0';
		   codeString[i][j+1]='1';
		   codeString[i][j+2]='0';
		   codeString[i][j+3]='0';
		   break;
	 case '5': codeString[i][j+0]='0';
		   codeString[i][j+1]='1';
		   codeString[i][j+2]='0';
		   codeString[i][j+3]='1';
		   break;
	 case '6': codeString[i][j+0]='0';
		   codeString[i][j+1]='1';
		   codeString[i][j+2]='1';
		   codeString[i][j+3]='0';
		   break;
	 case '7': codeString[i][j+0]='0';
		   codeString[i][j+1]='1';
		   codeString[i][j+2]='1';
		   codeString[i][j+3]='1';
		   break;
	 case '8': codeString[i][j+0]='1';
		   codeString[i][j+1]='0';
		   codeString[i][j+2]='0';
		   codeString[i][j+3]='0';
		   break;
	 case '9': codeString[i][j+0]='1';
		   codeString[i][j+1]='0';
		   codeString[i][j+2]='0';
		   codeString[i][j+3]='1';
		   break;
	 case 'a': codeString[i][j+0]='1';
		   codeString[i][j+1]='0';
		   codeString[i][j+2]='1';
		   codeString[i][j+3]='0';
		   break;
	 case 'b': codeString[i][j+0]='1';
		   codeString[i][j+1]='0';
		   codeString[i][j+2]='1';
		   codeString[i][j+3]='1';
		   break;
	 case 'c': codeString[i][j+0]='1';
		   codeString[i][j+1]='1';
		   codeString[i][j+2]='0';
		   codeString[i][j+3]='0';
		   break;
	 case 'd': codeString[i][j+0]='1';
		   codeString[i][j+1]='1';
		   codeString[i][j+2]='0';
		   codeString[i][j+3]='1';
		   break;
	 case 'e': codeString[i][j+0]='1';
		   codeString[i][j+1]='1';
		   codeString[i][j+2]='1';
		   codeString[i][j+3]='0';
		   break;
	 case 'f': codeString[i][j+0]='1';
		   codeString[i][j+1]='1';
		   codeString[i][j+2]='1';
		   codeString[i][j+3]='1';
		   break;
       }
   }
 //-------------------------------------//
 //------BINARY MASK GENERATION -------//
 //-----------------------------------//
   len=strlen(str2[i]);
  //generating binary mapping maskString[16][16]
   for(j=0,k=0;j<15;j=j+4,k=k+4)
    {
    if(j==0) //ensures that switch case occurs for once
     {
      switch(len)
       {
	case 4: j=0;
		break;
	case 3: j=4;
		break;
	case 2: j=8;
		break;
	case 1: j=12;
		break;
       }
      }
      switch(str2[i][k/4])
       {
	 case '0': maskString[i][j+0]='0';
		   maskString[i][j+1]='0';
		   maskString[i][j+2]='0';
		   maskString[i][j+3]='0';
		   break;
	 case '1': maskString[i][j+0]='0';
		   maskString[i][j+1]='0';
		   maskString[i][j+2]='0';
		   maskString[i][j+3]='1';
		   break;
	 case '2': maskString[i][j+0]='0';
		   maskString[i][j+1]='0';
		   maskString[i][j+2]='1';
		   maskString[i][j+3]='0';
		   break;
	 case '3': maskString[i][j+0]='0';
		   maskString[i][j+1]='0';
		   maskString[i][j+2]='1';
		   maskString[i][j+3]='1';
		   break;
	 case '4': maskString[i][j+0]='0';
		   maskString[i][j+1]='1';
		   maskString[i][j+2]='0';
		   maskString[i][j+3]='0';
		   break;
	 case '5': maskString[i][j+0]='0';
		   maskString[i][j+1]='1';
		   maskString[i][j+2]='0';
		   maskString[i][j+3]='1';
		   break;
	 case '6': maskString[i][j+0]='0';
		   maskString[i][j+1]='1';
		   maskString[i][j+2]='1';
		   maskString[i][j+3]='0';
		   break;
	 case '7': maskString[i][j+0]='0';
		   maskString[i][j+1]='1';
		   maskString[i][j+2]='1';
		   maskString[i][j+3]='1';
		   break;
	 case '8': maskString[i][j+0]='1';
		   maskString[i][j+1]='0';
		   maskString[i][j+2]='0';
		   maskString[i][j+3]='0';
		   break;
	 case '9': maskString[i][j+0]='1';
		   maskString[i][j+1]='0';
		   maskString[i][j+2]='0';
		   maskString[i][j+3]='1';
		   break;
	 case 'a': maskString[i][j+0]='1';
		   maskString[i][j+1]='0';
		   maskString[i][j+2]='1';
		   maskString[i][j+3]='0';
		   break;
	 case 'b': maskString[i][j+0]='1';
		   maskString[i][j+1]='0';
		   maskString[i][j+2]='1';
		   maskString[i][j+3]='1';
		   break;
	 case 'c': maskString[i][j+0]='1';
		   maskString[i][j+1]='1';
		   maskString[i][j+2]='0';
		   maskString[i][j+3]='0';
		   break;
	 case 'd': maskString[i][j+0]='1';
		   maskString[i][j+1]='1';
		   maskString[i][j+2]='0';
		   maskString[i][j+3]='1';
		   break;
	 case 'e': maskString[i][j+0]='1';
		   maskString[i][j+1]='1';
		   maskString[i][j+2]='1';
		   maskString[i][j+3]='0';
		   break;
	 case 'f': maskString[i][j+0]='1';
		   maskString[i][j+1]='1';
		   maskString[i][j+2]='1';
		   maskString[i][j+3]='1';
		   break;
       }//end of switch
   }
 }

 clearPreview();

 //Drawing starts
  for(i=0;i<64;i+=4)
  {
   for(j=0;j<64;j+=4)
   {
     if(codeString[j/4][i/4]=='0' && maskString[j/4][i/4]=='0')
      setfillstyle(1,8);
     else if(codeString[j/4][i/4]=='0' && maskString[j/4][i/4]=='1')
      setfillstyle(1,15);
     else if(codeString[j/4][i/4]=='1' && maskString[j/4][i/4]=='0')
      setfillstyle(1,10);
     if(i/4==HOTX && j/4==HOTY)
      setfillstyle(1,COLOR);

     bar(378+i,259+j,380+i,261+j);
     setfillstyle(1,12);
     bar(447,319-i,458,321-i);//moving bar
   }
   delay(1);
   }
   setfillstyle(1,14);
   bar(446,259,459,321);
   //hotx & hoty
   {
    sprintf(msg,"%d",HOTX);
    BUTTON(510,257,539,270,DOWN,8,1);
    TEXT(515,260,msg,DEFAULT_FONT,HORIZ_DIR,1,12);
    sprintf(msg,"%d",HOTY);
    BUTTON(510,277,539,290,DOWN,8,1);
    TEXT(515,280,msg,DEFAULT_FONT,HORIZ_DIR,1,12);
   }
   //copying
   for(i=0;i<16;i++)
   {
    for(j=0;j<16;j++)
    {
     cdStr[i][j]=codeString[i][j];
     mskStr[i][j]=maskString[i][j];
    }
   }
}

//To clear preview zone
void clearPreview()
{
int i,j;

setfillstyle(1,15);

for(i=0;i<64;i+=4)
 for(j=0;j<64;j+=4)
   bar(378+i,259+j,380+i,261+j);
}

//To modify saved cursor
void modifySavedCursor()
{
int i,j;

flash();

//clear
setfillstyle(1,14);
bar(431,354,627,359);
 for(i=0;i<320;i+=20)
  for(j=0;j<320;j+=20)
  {
    if(cdStr[j/20][i/20]=='0' && mskStr[j/20][i/20]=='0')
      setfillstyle(1,8);
    else if(cdStr[j/20][i/20]=='0' && mskStr[j/20][i/20]=='1')
      setfillstyle(1,15);
    else if(cdStr[j/20][i/20]=='1' && mskStr[j/20][i/20]=='0')
      setfillstyle(1,10);
    if(i/20==HOTX && j/20==HOTY)
      setfillstyle(1,COLOR);

   bar(21+i,21+j,39+i,39+j);
   setfillstyle(1,12);
   bar(432+(i/20)*6+(j/20)*6,355,436+(i/20)*6+(j/20)*6,358);//moving bar
  }
//clear
hidemouseptr();
setfillstyle(1,14);
bar(431,354,627,359);
showmouseptr();
}

//----------------------------------|
//------------Help Window-----------|
//----------------------------------|
void showHelp(char *str)
{
 BUTTON(68,456,624,469,DOWN,16,1);
 TEXT(72,459,str,DEFAULT_FONT,HORIZ_DIR,1,15);
}

//-------------------------------------|
//----Show number of output files------|
//-------------------------------------|
void noOfOutputFiles()
{
char *msg[2],*type[]={"CURSORS\\*.cur","CURSORS\\*.h"};
int i=0,count,done;
struct ffblk ffblk;


for(i=0;i<2;i++)
{
 done=0;
 count=0;
 done = findfirst(type[i],&ffblk,0);
 while (!done)
  {
   count++;
   done = findnext(&ffblk);
  }
 sprintf(msg[i],"%d",count);

  BUTTON(216,416+i*14,394,428+i*14,DOWN,8,1);
  TEXT(220,419+i*14,fileType[i],DEFAULT_FONT,HORIZ_DIR,1,6);
  TEXT(318,419+i*14,":",DEFAULT_FONT,HORIZ_DIR,1,10);
  TEXT(330,419+i*14,msg[i],DEFAULT_FONT,HORIZ_DIR,1,14);
 }
}

//----------------------------------------------------------------------------|
//-----------------Fuctions for creating buttons & text-----------------------|
//----------------------------------------------------------------------------|
void BUTTONGRAY(int x1,int y1,int x2,int y2,int option,int color, int filltype)
{
  if(option==1)
   {
    setcolor(15);
    rectangle(x1,y1,x2,y2);
    setcolor(8);
    line(x1+1,y2,x2,y2);
    line(x2,y1,x2,y2);
    setfillstyle(filltype,color);
    bar(x1+1,y1+1,x2-1,y2-1);
   }
  else
   {
    setcolor(8);
    rectangle(x1,y1,x2,y2);
    setcolor(15);
    line(x1+1,y2,x2,y2);
    line(x2,y1,x2,y2);
    setfillstyle(filltype,color);
    bar(x1+1,y1+1,x2-1,y2-1);
   }
}

void BUTTON(int x1,int y1,int x2,int y2,int option,int color, int filltype)
{
 if(option==1)
   {
    hidemouseptr();
    setcolor(15);
    rectangle(x1,y1,x2,y2);
    setcolor(16);
    line(x1+1,y2,x2,y2);
    line(x2,y1,x2,y2);
    setfillstyle(filltype,color);
    bar(x1+1,y1+1,x2-1,y2-1);
    showmouseptr();
   }
  else
   {
    hidemouseptr();
    setcolor(16);
    rectangle(x1,y1,x2,y2);
    setcolor(15);
    line(x1+1,y2,x2,y2);
    line(x2,y1,x2,y2);
    setfillstyle(filltype,color);
    bar(x1+1,y1+1,x2-1,y2-1);
    showmouseptr();
   }
}

void TEXT(int x,int y,char *msg,int font,int direction,int charsize,int color)
{
hidemouseptr();
setcolor(color);
settextstyle(font,direction,charsize);
outtextxy(x,y,msg);
showmouseptr();
}
//########################
// MOUSE PROGRAMMING
//########################

union REGS i,o;
struct SREGS s;

initmouse()
  {
   i.x.ax=0;
   int86(0x33,&i,&o);
   return(o.x.ax);
  }

 showmouseptr()
  {
    i.x.ax=1;
    int86(0x33,&i,&o);
    return 0;
  }

 hidemouseptr()
  {
    i.x.ax=2;
    int86(0x33,&i,&o);
    return 0;
  }

 getmousepos(int *button,int *x,int *y)
  {
    i.x.ax=3;
    int86(0x33,&i,&o);
    *button=o.x.bx;
    *x=o.x.cx;
    *y=o.x.dx;
    return 0;
  }
 changecursor(int *shape,int hotX,int hotY)
  {
   i.x.ax=9;
   i.x.bx=hotX;
   i.x.cx=hotY;
   i.x.dx=(unsigned) shape;
   segread(&s);
   s.es=s.ds;
   int86x(0x33,&i,&i,&s);
   return 0;
  }