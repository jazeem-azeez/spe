# include <gui.cpp>
# include <stdlib.h>

int animate(char filename [16]);
void main()
{
	m.initmouse();
	initgui();
	m.hidemouseptr();
	animate("logox.bmp");
}

int animate(char filename[16])

{			int i,j;
	wait();
		ldbmp(0,0,filename);
	while(!kbhit())

	{
		for(i=0;i<15;i++)
		{
		setrgbpalette(i,rand()%256,rand()%256,rand()%256);
		wait();
		}

	}
	closegraph();

}
