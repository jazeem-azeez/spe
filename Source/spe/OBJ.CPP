#// include <gui.h>
# include <3dgfx.cpp>
# include <physics.cpp>





class object

{
	
public:
	//attributes
	int key;   
	object3d gob;
	physics p1;

	//operations
	void load();
	int objupdt();
	int calc();
	int show();
	
	
};

int object :: load(int sl_no)

{	p1.getdata();
	
	svbmp(240,100,400,270,BMPBUFFERIMAGE);
	moveto(240,100);
	
	outtext("Enter the file name \n");
	gcin(msg);

	gob.gfx(msg);

	key=sl_no;

	ldbmp(240,100,BMPBUFFERIMAGE);

}

int object :: show()

{
	gob.maingl(glcase);
}

int object :: calc ()

{  
 p1.update();
}

int object :: objupdt()

{	p1.getdata();
	calc();
}
