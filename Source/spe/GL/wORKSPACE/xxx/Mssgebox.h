 #include"button.h"

		  class Mssgbox //base class for creating Message Box
    {	protected:int L,T,R,B;
		   void* imgptr;
		   char* mssgstring;

	   public: Mssgbox() { L=T=R=B=0; }
		   Mssgbox(int left,int top,int right,int bottom,char* s);
		   void Display_Mssgbox(void);
		   void Display_Mssg(char* );
		   ~Mssgbox(){free(imgptr);free(mssgstring); }
				    };

     Mssgbox::Mssgbox(int left,int top,int right,int bottom,char* s)
 {   L=left;T=top;R=right;B=bottom;
     strcpy(mssgstring,s);
     int area=imagesize(L,T,R,B);
     imgptr=(int*)malloc(area);
     if(imgptr==NULL)
 {   closegraph();restorecrtmode();
     cout<<"\n\tMemory allocation error";
     cout<<"\n\tPress any key to continue";
     getch();exit(1);	}
     getimage(L,T,R,B,imgptr);		  }

     void Mssgbox::Display_Mssgbox(void)
 {   putimage(L,T,imgptr,XOR_PUT);
     setfillstyle(SOLID_FILL,LIGHTGRAY);bar(L,T,R,B);
     setfillstyle(SOLID_FILL,BLUE);bar(L,T,R,T+20);
     setcolor(WHITE);outtextxy(L+4,T+3,mssgstring);
     setlinestyle(SOLID_LINE,1,1);
     setcolor(WHITE);line(L,T,R,T);line(L,T,L,B);
     setcolor(DARKGRAY);line(R,T,R,B);line(R,B,L,B);
     }
     void Mssgbox::Display_Mssg(char* bs)
 {   setcolor(BLACK);
 int i=0,xpos=L+4,ypos=T+24,n=strlen(bs);char outstring[2];outstring[1]='\0';
	   while(i!=n)
 {    outstring[0]=bs[i];
      outtextxy(xpos,ypos,outstring);
      xpos+=textwidth(outstring)+2;i++;
	   if(xpos>=R)
 {    xpos=L+4;ypos+=textheight(outstring)+2;	 }
      }

	   }
//***************************************************************************
//		derived classes for various massagebox..self explanatory
//***************************************************************************
	      class Mssgbox_with_crossbutton:public Mssgbox
 {
  public:
  Mssgbox_with_crossbutton(int left,int top,int right,int bottom,char* s):Mssgbox(left,top,right,bottom,s) { }
  void Display_Mssgbox_with_crossbutton(Crossbutton);
  void restore(void){putimage(L,T,imgptr,COPY_PUT); }
       };

    void Mssgbox_with_crossbutton::Display_Mssgbox_with_crossbutton(Crossbutton crb)
 {  Display_Mssgbox();
    crb.displaybt();	 }


