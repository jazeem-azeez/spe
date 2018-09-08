/*

# include<iostream.h>
# include<conio.h>
# include<graphics.h>
# include<dos.h>
# include<string.h>

# include<stdlib.h>
# include <stdio.h>
*/
# include <gui.cpp>
# include<math.h>
#define MAXPARTICLES 2300

// using namespace io ;
float color;

class Atom
{
	public:
		float x;
		float y;
		float vv;
		float hv;
		float theta;

		void setrest(int h)
		{
			float temp;
			temp=rand()%1000;
			theta = ((rand()%h))*3.14/180;
			vv=((temp)*sin(theta));
			hv=((temp)*cos(theta));

		}

		void setxy(float a,float b)
		{
			x = a;
			y = getmaxy()-b;
		}

		float getx()
		{
			return x;
		}
		float gety()
		{
			return getmaxy()-y;
		}

		void show(int l)
		{
			if(l)
				putpixel(x,y,color);
			else
				putpixel(x,y,0);
		}
};


Atom atomArray[MAXPARTICLES];
float g = -980;

void setAtoms()
{
	float x = rand()%getmaxx();
	float y = rand()%getmaxy();
	int flag=0;

	Atom first;
	first.setxy(rand()%getmaxx(),0);
	first.theta=((rand()%60)+60)*3.14/180;
	float temp=rand()%500+500;
	first.vv = temp*sin(first.theta);
	first.hv = temp*cos(first.theta);
	temp=rand()%500;
	for(int u = 0;u<temp;u++)
	{
		setcolor(BLACK);
		setfillstyle(SOLID_FILL,BLACK);
		circle(first.x,first.y,3);
		fillellipse(first.x,first.y,3,3);
		first.setxy(first.x+first.hv*(0.01),first.gety()+first.vv*(0.01) + g/2*(0.01)*(0.01));
		first.vv = first.vv + g*(0.01);
		setcolor(color);
		setfillstyle(SOLID_FILL,color);

		circle(first.x,first.y,3);
		fillellipse(first.x,first.y,3,3);
		if(first.x>=getmaxx() || first.x<=0 || first.y>=getmaxy() || first.y<=0)
		{
			flag=1;
			goto end;
		}
		delay(10);
	}
	end:
		x=first.x;
		y=first.gety();

	if(flag)
	{
		if(x>=getmaxx()/2)
			x=x-10;
		else
			x=x+10;
		if(y>=getmaxy()/2)
			y=y-5;
		else
			y=y+5;
	}

	for(int i=0;i<MAXPARTICLES;i++)
	{
		atomArray[i].setxy(x,y);
		atomArray[i].setrest(360);
	}
}

void moveAtoms(int maxX )
{
	for(int k=0;k<MAXPARTICLES;k++)
	{
		atomArray[k].show(0);
		atomArray[k].setxy(atomArray[k].getx()+atomArray[k].hv*(0.01),atomArray[k].gety()+atomArray[k].vv*(0.01) + g/2*(0.01)*(0.01));
		atomArray[k].vv = atomArray[k].vv + g*(0.01) ;
		if(atomArray[k].x>=maxX || atomArray[k].x<=0)
		atomArray[k].hv = -(atomArray[k].hv);
		if(atomArray[k].y<=0)
		atomArray[k].vv = -(atomArray[k].vv);
		else
		if(atomArray[k].y>=maxX)
		atomArray[k].vv = -(atomArray[k].vv)-(rand()%500);
		atomArray[k].show(1);
	}
}




void aniexpo()
{
       /*
       int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "");
	errorcode = graphresult();
	if (errorcode != grOk)  /* an error occurred */
	/*
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1); /* terminate with an error code */
		/*
	}
		  */
	char ch=0;
	int j=0;
		cleardevice();
		color = rand()%24+8;
		setAtoms();
		while(j<500)
		{
			j++;
			moveAtoms(getmaxx());
		}
	cleardevice();

	closegraph();

}

int main()

{
	aniexpo();
	return 1;
}



