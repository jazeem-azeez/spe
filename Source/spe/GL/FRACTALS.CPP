struct complex {float x;float y;};
complex complexsquare(complex c)
{
    complex csq;
    csq.x= c.x*c.x-c.y*c.y;
    csq.y=2*c.x*c.y;
    return (csq);
}

int iterate (complex zinit, int maxiter)
{
    complex z=zinit;
    int cnt=0;
    while((z.x*z.x+z.y*z.y<=4.0)&&(cnt<maxiter))
    {
    z=complexsquare(z);
    z.x+=zinit.x;
    z.y+=zinit.y;
    cnt++;
    }
    return (cnt);
}

void mandelbrot(int xwmin,int ywmin,int nx,int ny,int maxiter,float realmin,float realmax,float imagmin,float imagmax)
{
float realinc=(realmax-realmin)/nx;
float imaginc=(imagmax-imagmin)/ny;
complex z;
int x,y;
int clr ,cnt;
for(x=0,z.x=realmin;x<nx;x++,z.x+=realinc)
    for(y=0,z.y=imagmin;y<ny;y++,z.y+=imaginc)
    {
	cnt =iterate(z,maxiter);
	if(cnt==maxiter)
	    clr=0;
	else
	    clr=cnt;
	PutPixel(xwmin+x,ywmin+y,clr);
    }
}
