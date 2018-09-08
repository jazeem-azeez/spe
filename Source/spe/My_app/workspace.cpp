//1.include and debug headers
//list of headers
# include "headerli.cpp"
void main()
{
	Graphinit();
	ldbmp(0,0,"test.bmp");
	m.initmouse();
	m.showmouseptr();
	m.restrictmouseptr(0,0,640,480);
	getch();
}