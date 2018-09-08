# include <graphics.h>
# include <dos.h>
# include <stdio.h>
# include <iostream.h>
# include <conio.h>
# include <math.h>
const char UP = 72;// arrow keys
const char LEFT = 75;
const char RIGHT = 77;
const char DOWN = 80;
int dist(int x,int y,int x1,int y1) // for calculating distance between circles


    {
    int dis=sqrt((x1-x)*(x1-x)+(y1-y)*(y1-y));
    return dis;
}
int main()


    {
    clrscr();
    char key = 0;
    int d=DETECT,mode;
    int x=319,y=180,r,i,midx,midy,x1,y1;
    initgraph(&d,&mode,"");
    midx=getmaxx()/2; // mid co-ordinates of screen
    midy=getmaxy()/2;
    x1=midx;
    y1=midy;
    circle(x,y,10);
    while(key!=27) // Execute till Escape is pressed


        	{
        	circle(x1,y1,10);
        	key = getch();
        	switch(key) // To control circle through arrow keys


            	{
            	case UP:
            	y--;
            	circle(x,y,10);
            	break;
            	case DOWN:
            	y++;
            	circle(x,y,10);
            	break;
            	case LEFT:
            	x--;
            	circle(x,y,10);
            	break;
            	case RIGHT:
            	x++;
            	circle(x,y,10);
            	break;
            	}
            	delay(10);
            	cleardevice();
            	circle(x,y,10);
		if(dist(x,y,x1,y1)<=20)//if circles HIT


                	 {
                	 outtextxy(midx,10,"HIT");
                	 if(y==y1) // To change circle position


                    	 {
                    		 if(x<x1)
                    		x1++;
                    		 if(x>x1)
                    		x1--;
                    	 }
                    	 if(x==x1)


                        	{
                        		if(y<y1)
                        		y1++;
                        		else
                        		y1--;
                        	}
                        	 else if(x<x1 && y<y1)


                            	 {
                            		 x1++;
                            		 y1++;
                            	 }
                            	 else if(x>x1 && y>y1)


                                	{
                                		 x1--;
                                		 y1--;
                                	}
                                	else if(x>x1 && y<y1)


                                    	{
                                    		 x1--;
                                    		 y1++;
                                    	}
                                    	else if(x<x1 && y>y1)


                                        	 {
                                        		 x1++;
                                        		 y1--;
                                        	 }
                                        	 }
                                        	gotoxy(1,3);
                                        	cout<<"Distance:"<<dist(x,y,x1,y1);
                                        	cout<<"\n X:"<<x<<"\n Y:"<<y;
                                        	cout<<"\n X1:"<<x1<<"\n Y1:"<<y1;
                                        	cout<<"\n Press Escape to Exit";
                                    }
                                    return 0;
                                }
