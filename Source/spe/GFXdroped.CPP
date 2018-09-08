# include <vector3d.cpp>
# include <gui.cpp>
# include <algo3d.h>



class gfx

{
public:
	//attributes
	tri3d *t;
	unsigned int no_tri;
	unsigned int key;
	//methods
	void rotate(double degx,double degy,double degz);
	void move(int dx,int dy,int dy);
	void draw();
	gfx(int no,fstream file);
	~gfx();

};

void gfx :: rotate (int degx,int  degy,int degz)

{	
	for(int i=0;i<no_tri;i++)
	 atrot(t[i], degx, degy, degz);

}

void gfx :: move(double dx,double dy,double dy);

{	
	for(int i=0;i<no_tri;i++)
	 attrans(t[i], degx, degy, degz);

}

void gfx :: draw ()

{	
	for(int i=0;i<no_tri;i++)
	 drawtriangle(t[i],WHITE);

}

gfx :: gfx(char fn)

{
	int no;
	file.open(fn,ios::in);
	if(!file){display_err("ERROR openning file");}
		file>>no;
	no_tri=no;
	t=new triangle3d [no]
	for(int i=0;i<no_tri;i++)
		file>>t[i].x>>t[i].y>>t[i].z;
}
gfx :: ~gfx ()

{
	delete t;
}