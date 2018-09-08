//#include <headerli.cpp>
int selectcolor()
{
int x,y,clr;
Xldbmp(1,300,"rgb16.bmp");
screen_target_select(x,y);
Xldbmp(1,300,"rgb16.bmp");
return (getpixel(x,y));
}

float distanceBetween(const point3d & _Vec1, const point3d & _Vec2)
{
double Distance = sqrt(pow((_Vec2.x - _Vec1.x),2) + pow((_Vec2.y - _Vec1.y),2) + pow((_Vec2.z - _Vec1.z),2));
return ((float)Distance);
}
vec3d _G,_wind;

void setupreactor()
{
	glprintf("Enter the scale ratios data:(1meter = XX pixels) ->");
	X_glscanf(3,"%lf %lf %lf",&_xscale,&_yscale,&_zscale);
	glprintf("Enter the Force Field data: Wind ->");
	X_glscanf(3,"%lf %lf %lf",&_wind.x,&_wind.y,&_wind.z);
	glprintf("Enter the no of objects:-> ");

  //	_G.x=0*xscale,_G.y=-.9*yscale,_G.z=0*zscale;
}
class sim_body
	{
	public:
	char name[16];
	int color;
	byte collitionstate;
	gllineobject o;
	particle p,pext;

	vec3d point_of_impact;
	void showdetails();
	int changeproperty();
	void create_body();

	friend drawobj(gllineobject *o,int color);
	friend readobj(gllineobject *o,char *path);

	void drawbody()
	{
	drawobj(o,color);
	}
	void updatephy()
	{
		 p.update();
//		 p.vel=p.vel+_G+_wind;

	}
	void updategl()
	{
	aotrans(o,p.vel.x,p.vel.y,p.vel.z);
	aorot(o,p.theta.x,p.theta.y,p.theta.z);
	}

	int did_collide_with(gllineobject &i);
	int is_point_inside_object(point3d &p1);
	void resolve_collition(particle &c);
	void update_box_info();
	friend  reactor_engine_link();

	void preprocesscollition(particle pexternal)
	{
	collitionstate=1;
	vec3d u1=p.vel,u2=pexternal.vel;
	float m1=p.mass,m2=pexternal.mass;
	pext=p;
	pext.vel=(((m1-m2)/(m1+m2))*u1)+(((2*m2)/(m1+m2))*u2);

//	temp=pexternal.mass*pexternal.vel*cos(angleBetweenRad(pext.pos,point_of_impact));
  //	pext.vel=(temp*pext._e);
//	pext.vel+=_G;
	}
	void processcollition()
	{
	collitionstate=0;
	p=pext;
	}
	sim_body *ptr,*prev;
	}*simbody1;


void sim_body ::resolve_collition(particle & c)
{
/*
Really Im confused
float avg_e=((_e+p._e)/2);
if(avg_e>1.0)
	avg_e=1;
if(avg_e<0.0)
	avg_e=0;
double anglebw=anglebetween(vel,p.vel);
float mu1cos=(mass*(vel.length()* cos(angle]),mu2cos=(p.mass*(p.vel.length()* cos(angle));
float MVf=(avg_e*(mu1cos+mu2cos));
*/

}

	//void sim_body :: resolve_collition(particle &p)	{}
	int sim_body :: did_collide_with(gllineobject &i)
	{

	for(int j=0,k=0 ;j<i.no;j++)
	{
		for(k=0;k<o.no;k++)
		{
		if(distanceBetween(o.p[j],i.p[k])<=0.5)
			{
			point_of_impact.x=o.p[j].x,point_of_impact.y=o.p[j].y,point_of_impact.z=o.p[j].z;
			return 0;
			}
		}
	}
	return 1;
	}

	int sim_body::is_point_inside_object(point3d &p1)
	{
	//troubles
	for(int i=0,flag=-1;i<o.no;i++)
	{
	//if(distanceBetween(p1,o.p[i])==0.0f)
	  //	return (1);

	if(p1.x <=o.cr.x && o.p[i].x <=o.cr.x && p1.x >= o.p[i].x )
		if(p1.y <=o.cr.y &&o.p[i].y <=o.cr.y && p1.y >= o.p[i].y )
			if(p1.z <=o.cr.z  && o.p[i].z <=o.cr.z && p1.z >= o.p[i].z)
			{
			flag++;
			}

	if(p1.x >=o.cr.x && o.p[i].x >=o.cr.x && p1.x <= o.p[i].x)
		if( p1.y >=o.cr.y && o.p[i].y >=o.cr.y && p1.y <= o.p[i].y)
			if( p1.z >=o.cr.z && o.p[i].z >=o.cr.z && p1.z <= o.p[i].z)
			{
			flag++;
			}
	}
	if(flag<1)
	return (-1);
	else
	return flag;

	}

	void sim_body::create_body()
	{
	HideMouse();
	for(;;)
	{
	cleardevice();
	msg_n_gin(0,0,"Enter name of sim body: -> ");
	glnextline();
	outtext("trying to open associated files");
	msg[0]=changefileext(msg,"gld");
	if(readobj(msg,o)!=-1)
		{
		glprintf("Sucessfully loaded");
		delay(250);
		break;
		}
	else
	{
		outtext(" Sorry File not Found");
		getch();
		   //	goto   LABEL;
	}
	}

	strcpy(name,msg);
	clearviewport();
	p.getdata();
	aotrans(o,p.pos.x-o.cr.x,p.pos.y-o.cr.y,p.pos.z-o.cr.z);
	color=6;
	glprintf("%d ",color);
	delay(128);
	return ;
	//showdetails();
	//changeproperty();
	}
	void sim_body:: showdetails()
	{
	/*
	byte done=0;
point3d cam1,zoom1;
cam1.x=0,cam1.y=0,cam1.z=0;
//trans1.x=0,trans1.y=0,trans1.z=0;
zoom1.x=1,zoom1.y=1,zoom1.z=1;
setcamzoom(&zoom1);
setcamera(&cam1);
//setcamtrans(&trans1);
camera_rot_on=TURN_ON;
camera_zoom_on=TURN_ON ;
camera_trans_on=TURN_ON;
	clearviewport();
	setwritemode(XOR_PUT);
	outtext(name);
	glnextline();
	p.putdata();
	HideMouse();
	for(;done!=1;)
		{
		drawobj(o,color);
		delay(62);
		showtime;
		drawobj(o,color);
		if(kbhit())
			{
			done=getch();
			if(done=='z')
				aoscale(o,0.9,0.9,0.9);
			else if(done=='Z')
				aoscale(o,1.1,1.1,1.1);
			else
				done=1;
			}

rotcamera(&cam1,0,2,2);
		}
	clearviewport();
	ShowMouse();
	glouttext("Press any key to continue...");
	getch();         */

	}

int sim_body:: changeproperty()
	{
	return 1;
	}

static int MAX_SIM_BODY;/*
void main()
{
sim_body s[2];
glprintf("Executed");
}                         */