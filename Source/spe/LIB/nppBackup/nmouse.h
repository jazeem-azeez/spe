                   #include<iostream.h>
                   #include<conio.h>
                   #include<string.h>
                   #include<stdlib.h>
                   #include<graphics.h>
                   #include<stdio.h>
                   #include<math.h>
                   #include<alloc.h>
                   #include<dos.h>


                   union REGS i,o;
                   struct SREGS s;

                   class mouse //mouse services
 {
   public:
          int init_mouse(void);//initialize mouse
          void show_mouseptr(void);//show mousepointer
          void hide_mouseptr(void);//hide mousepointer
          void restrict_mouseptr_movement(int,int,int,int);//restrict mouse pointer's movement
          void get_mouse_pos(int*,int*,int*);//tells the actual mouse pointer's position
          void change_mousepointer_hourglass(void);//changes pointer to hourglass
          void change_mousepointer_hand(void); //changes pointer to hand
          void change_mousepointer_arrow(void);//changes pointer to arrow
          void change_mousepointer_pencil(void);//changes pointer to pencil
          void change_mousepointer_eraser(void);//changes pointer to eraser
          void make_slow_ptr(void);//make slow pointer movement
          void make_fast_ptr(void);//make fast pointer movement
          void make_medium_ptr(void);//make medium pointer movement
                                                        };

          int mouse::init_mouse(void)//initialize mouse if success return 0
    {                                 //else return -1
           i.x.ax=0;
           int86(0x33,&i,&o); return(o.x.ax==0 ? -1:0 );  }
          void mouse::show_mouseptr(void)
    {      i.x.ax=1;
           int86(0x33,&i,&o);       }
          void mouse::hide_mouseptr(void)
    {     i.x.ax=2;
          int86(0x33,&i,&o);
                                             }
          void mouse::restrict_mouseptr_movement(int x1,int y1,int x2,int y2)
    {      i.x.ax=7;
           i.x.cx=x1;
           i.x.dx=x2;
           int86(0x33,&i,&o);
           i.x.ax=8;
           i.x.cx=y1;
           i.x.dx=y2;
           int86(0x33,&i,&o);
                                         }
          void mouse::get_mouse_pos(int* button,int* x,int* y)
    {      i.x.ax=3;
           int86(0x33,&i,&o);
           *button=o.x.bx;
           *x=o.x.cx;
           *y=o.x.dx;
                                   }
          void mouse::change_mousepointer_hourglass(void)
    {      int pointer_hourglass[32]={
                                /*hour-glass screen mask*/
                                0x0000,0x0000,0x0000,0x0000,
                                0x8001,0xc003,0xf00f,0xfc3f,
                                0xfc3f,0xf00f,0xc003,0x8001,
                                0x0000,0x0000,0x0000,0x0000,
                                /*the mouse pointer bitmap*/
                                0xffff,0x8001,0xffff,0x8001,
                                0x4002,0x2004,0x1008,0x0240,
                                0x0240,0x0810,0x2004,0x4002,
                                0x8001,0xffff,0x8001,0xffff,    };
           i.x.ax=9;//service number
           i.x.bx=0;//actual cursor position from left
           i.x.cx=0;//actual cursor position from top
           i.x.dx=(unsigned)pointer_hourglass;//offset address of pointer
           segread(&s);
           s.es=s.ds;//segment address of pointer
           int86x(0x33,&i,&i,&s);                               }

            void mouse::change_mousepointer_hand(void)
    {      int pointer_hand[32]={
                                /*hand-screen mask*/
                                0xe1ff,0xe1ff,0xe1ff,0xe1ff,
                                0xe1ff,0x0000,0x0000,0x0000,
                                0x0000,0x0000,0x0000,0x0000,
                                0x0000,0x0000,0x0000,0x0000,
                                /*mouse pointer bitmap*/
                                0x1e00,0x1200,0x1200,0x1200,
                                0x13ff,0x1249,0x1249,0xf249,
                                0x9001,0x9001,0x9001,0x8001,
                                0x8001,0x8001,0xffff,0x0000,    };
           i.x.ax=9;//service number
           i.x.bx=0;//actual cursor position from left
           i.x.cx=0;//actual cursor position from top
           i.x.dx=(unsigned)pointer_hand;//offset address of pointer
           segread(&s);
           s.es=s.ds;//segment address of pointer
           int86x(0x33,&i,&i,&s);                               }

           void mouse::change_mousepointer_arrow(void)
    {      int pointer_arrow[32]={
                                /*arrow screen mask*/
                                0xffff,0xffff,0xe003,0xf003,
                                0xf803,0xfc03,0xfe03,0xfc03,
                                0xf803,0xf043,0xe0e3,0xc1f3,
                                0x83fb,0x07ff,0x8fff,0xdfff,
                                /*mouse pointer bitmap*/
                                0x0000,0x0000,0x1ffc,0x0804,
                                0x0404,0x0204,0x0104,0x0204,
                                0x0444,0x08a4,0x1114,0x220c,
                                0x4404,0x8800,0x5000,0x2000,    };
           i.x.ax=9;//service number
           i.x.bx=0;//actual cursor position from left
           i.x.cx=0;//actual cursor position from top
           i.x.dx=(unsigned)pointer_arrow;//offset address of pointer
           segread(&s);
           s.es=s.ds;//segment address of pointer
           int86x(0x33,&i,&i,&s);                               }

           void mouse::change_mousepointer_pencil(void)
    {      int pointer_pencil[32]={

                                /*pencil screen mask*/
                                0x00ff,0x007f,0x003f,0x001f,
                                0x0011,0x0007,0x0000,0x0003,
                                0x8001,0xc003,0xe007,0xf00f,
                                0xf81f,0xfc3f,0xfe7f,0xfeff,
                                /*mouse pointer bitmap*/
                                0xff00,0x8100,0x8280,0x8440,
                                0x8820,0x9010,0xa008,0xc005,
                                0x2002,0x1004,0x0808,0x0410,
                                0x0220,0x0140,0x0080,0x0100,
                                                                 };
           i.x.ax=9;//service number
           i.x.bx=0;//actual cursor position from left
           i.x.cx=0;//actual cursor position from top
           i.x.dx=(unsigned)pointer_pencil;//offset address of pointer
           segread(&s);
           s.es=s.ds;//segment address of pointer
           int86x(0x33,&i,&i,&s);                               }

            void mouse::change_mousepointer_eraser(void)
    {      int pointer_eraser[32]={
                                /*eraser screen mask*/
                                0x0000,0x0000,0x0000,0x0000,
                                0x0000,0x0000,0x0000,0x0000,
                                0x0000,0x0000,0x0000,0x0000,
                                0x0000,0x0000,0x0000,0x0000,
                                /*mouse pointer bitmap*/
                                0xffff,0x8001,0x8001,0x8001,
                                0x8001,0x8001,0x8001,0x8001,
                                0x8001,0x8001,0x8001,0x8001,
                                0x8001,0x8001,0x8001,0xffff,
                                                                 };
           i.x.ax=9;//service number
           i.x.bx=0;//actual cursor position from left
           i.x.cx=0;//actual cursor position from top
           i.x.dx=(unsigned)pointer_eraser;//offset address of pointer
           segread(&s);
           s.es=s.ds;//segment address of pointer
           int86x(0x33,&i,&i,&s);                               }

               void mouse::make_slow_ptr(void)
 {         i.x.ax=15;
           i.x.cx=200;
           i.x.dx=400;
           int86(0x33,&i,&o);                                   }

               void mouse::make_fast_ptr(void)
 {         i.x.ax=15;
           i.x.cx=3;
           i.x.dx=3;
           int86(0x33,&i,&o);                                   }

               void mouse::make_medium_ptr(void)
 {         i.x.ax=15;
           i.x.cx=50;
           i.x.dx=50;
           int86(0x33,&i,&o);                                   }
