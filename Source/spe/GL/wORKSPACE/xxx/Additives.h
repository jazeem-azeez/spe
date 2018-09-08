# include <bcm.h> // bitmaop image class supported bits 2,4,8 (256)
# include <button.h>
# include <mssgebox.h>
# include <shade&lightalg.cpp>
# include <vector.cpp>
# include <gui.h>

void effect(int sx,int sy,int ex,int ey)
{
	char c;
       //	m.hidemouseptr();

	for(int i=sx,j=sy;j<=ey;j++)
		for(i=sx;i<=ex;i++)
		{
			c=getpixel(i,j);
			putpixel(i,j,c-8);
		}
	for(;(m.moving()==9););
	for(i=sx,j=sy;j<=ey;j++)
		for(i=sx;i<=ex;i++)
		{
			c=getpixel(i,j);
			putpixel(i,j,c+8);
		}
       //m.showmouseptr();
}

int fliptext(char word[64])


    {
    outtextxy(10, 1, word);
    for(x=10; x < 4 * 8 * strlen(word) + 8; x++)


        	{
        	for(y=0; y<30; y++)


            		{
            		col = getpixel(x, y);
            		if(col > 0)


                			{
                			putpixel(x, 60 - y, 3);
                			}
                		}
                	}
                	getch();
            }
			
byte page=0;
void pageflip()
{
setvisualpage(page);
setactivepage(1-page);
page=1-page;
}