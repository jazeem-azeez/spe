#include"mouse.h"
/********************************************************************************************
 NOTE:-change the path where the mouse.h is residing,for e.g.,it may be-
                                   #include"d:\tc\bin\gui\mouse.h>
********************************************************************************************
ALSO REMEMBER THE BUTTON OBJECTS ARE MEMORY HUNGRY...SO TO MAINTAIN PROPER MEMORY MANAGEMENT
YOU SHOULDN'T USE MANY BUTTONS ON YOUR PROGRAM,IT MIGHT SHOW MEMORY ALLOCATION ERROR.
*******************************************************************************************/
		   enum buttonstatus { unpushed,pushed };
		   enum boolean { FALSE,TRUE };


		   class button//base class for drawing 3D buttons
   {  protected:
		int L,T,R,B;
		buttonstatus bstatus;

      public:   button(int x1,int y1,int x2,int y2);
		virtual void displaybt(void);//display the 3D button
		boolean onmouseover(int,int,int,mouse);//returns true if pointer is on the button
		boolean onmouseover_click(int,int,int,mouse);//returns true if pointer is on the button and mouse is clicked
								      };
	     button::button(int x1,int y1,int x2,int y2)
   {
	     L=x1;T=y1;R=x2;B=y2;
	     bstatus=unpushed;
				     }

		       void button::displaybt(void)
   {
	 setfillstyle(SOLID_FILL,LIGHTGRAY);bar(L,T,R,B);
		if(bstatus==unpushed)
   {     setlinestyle(SOLID_LINE,1,1);
         setcolor(WHITE);line(L,T,R,T);line(L,T,L,B);
         setcolor(DARKGRAY);line(R,T,R,B);line(R,B,L,B);
                         }
                else if(bstatus==pushed)
   {     setlinestyle(SOLID_LINE,1,1);
         setcolor(DARKGRAY);line(L,T,R,T);line(L,T,L,B);
         setcolor(WHITE);line(R,T,R,B);line(R,B,L,B);
         }                                                  }

             boolean button:: onmouseover(int x,int y,int bt,mouse m)
   {
         m.get_mouse_pos(&bt,&x,&y);
         if(x>=L&&x<=R&&y>=T&&y<=B)
         return TRUE;
         else
         return FALSE;                 }

                boolean button::onmouseover_click(int x,int y,int bt,mouse m)
   {
	 m.get_mouse_pos(&bt,&x,&y);
              if((bt & 1)==1)
    {    if(x>=L&&x<=R&&y>=T&&y<=B)
    {    m.hide_mouseptr();
         return TRUE;     }
         else
         return FALSE;       }            }


/*******************************************************************************************
 NOTE:-following sections shows how to derive various subclasses from the base button class
 TUTORIAL:-1>derive a class which can show an icon/a picture on the button's face
           2>derive a class which displays two consicutive buttons,if any one is pressed
             it'll remain pressed untill the other button is not pressed
           3>derive a class which displays a button,the button changes its color whenever
             the mouse pointer goes on it
           4>derive a class which displays a button and a text on it, the button changes
             the text color whenever the mouse pointer goes on it
*******************************************************************************************/


               class Textbutton:public button//derived class which shows text on it
{       private:char s[10];
                int textcolor;
        public:
        Textbutton(int x1,int y1,int x2,int y2,char* ss,int tcolor):button(x1,y1,x2,y2)
     {  strcpy(s,ss); textcolor=tcolor;         }

                void displaybt(void)
     {         button::displaybt();
               setcolor(textcolor);
               outtextxy(L+6,T+8,s);         }

               void btclick(void)
   {     bstatus=pushed;
         Textbutton::displaybt();delay(500);
         bstatus=unpushed;
         Textbutton::displaybt();
                                                       }
               };


               class Numberbutton:public button//derived class which shows number on it
{       private:int num,nc;
        public:
        Numberbutton(int x1,int y1,int x2,int y2,int number,int numbercolor):button(x1,y1,x2,y2)
     {  num=number;nc=numbercolor;                      }

                void displaybt(void)
      { button::displaybt();
        setcolor(nc);char temp[2];
        itoa(num,temp,10);
        outtextxy(L+6,T+8,temp);             }

        void btclick(void)
   {     bstatus=pushed;
         Numberbutton::displaybt();delay(500);
         bstatus=unpushed;
         Numberbutton::displaybt();
                                                       }
	};


	       class Colorbutton:public button//derived class which shows color on it
{       private:int color;
	public:Colorbutton(int x1,int y1,int x2,int y2,int c):button(x1,y1,x2,y2)
     {  color=c;                                        }

		void displaybt(void)
{       button::displaybt();
	setfillstyle(SOLID_FILL,color);
	bar(L+5,T+5,R-5,B-5);        }

		void btclick(void)
   {     bstatus=pushed;
	 Colorbutton::displaybt();delay(500);
	 bstatus=unpushed;
	 Colorbutton::displaybt();
						       }
	};


	class Crossbutton:public button//derived class which shows a cross on it
{       private:int color;
	public:Crossbutton(int x1,int y1,int x2,int y2,int c):button(x1,y1,x2,y2)
     {  color=c;                                        }

	       void displaybt(void)
{       button::displaybt();
	setlinestyle(SOLID_LINE,0,1);setcolor(color);
	line(L+1,T+1,R-1,B-1);line(L+1,B-1,R-1,T+1);        }

	       void btclick(void)
   {     bstatus=pushed;
	 Crossbutton::displaybt();delay(500);
	 bstatus=unpushed;
	 Crossbutton::displaybt();
                                                       }
        };

