//1.include and debug headers
//list of headers
# include "headerli.cpp"
void main()
{
	initsvga();
	SetMode(0x103,0);
//	Xldbmp(0,0,"test.bmp");
	Xldbmp(0,0,"test256.bmp");
	m.initmouse();
	setcolor(0);
	line (0,0,800,600);
	getch();
	textmode(0x03);
	cleardevice();
	closegraph();
	exit(1);
}