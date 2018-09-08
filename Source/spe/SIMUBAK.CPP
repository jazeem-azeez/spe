//#include <headerli.cpp>
class sim_body
	{
	public:
	char name[16];
	int color;
	gllineobject o;
	particle p;

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
	void update()
	{
		 p.update();
	}
	int did_collide_with(gllineobject &i);
	int is_point_inside_object(point3d &p1);
	void resolve_collition(particle &c);
	friend  reactor_engine_link();
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
p.vel =c.vel+p.vel;
p.omega=c.omega+p.omega;
update();
}

	//void sim_body :: resolve_collition(particle &p)	{}
	int sim_body :: did_collide_with(gllineobject &i)
	{
		for(int j=0;j<o.no;j++)
		{
		if(is_point_inside_object(i.p[j])!=-1)
			{
			point_of_impact.x=i.p[j].x,point_of_impact.y=i.p[j].y,point_of_impact.z=i.p[j].z;
			return 1;
			}
		}
	return -1;
	}

	int sim_body::is_point_inside_object(point3d &p1)
	{

	for(int i=0,flag=0;i<o.no;i++)
	{
	if(p1.x >= obj1.p[i].x&&p1.y >= obj1.p[i].y&&p1.z >= obj1.p[i].z)
		{
		flag++;
		break;
		}
	}
	for(i=0;i<o.no;i++)
	{
	if(p1.x <= obj1.p[i].x&&p1.y <= obj1.p[i].y&&p1.z <= obj1.p[i].z)
		{
		flag++;
		break;
		}
	}
	if (flag==0)
		flag=-1;
	return flag;
	}

	void sim_body::create_body()
	{
	for(;;)
	{
	clearviewport();
	msg_n_gin(0,0,"Enter name of sim body: -> ");
	outtext("trying to open associated files");
	msg[0]=changefileext(msg,"gld");
	if(readobj(msg,o)!=-1)
		{outtext("Sucessfully loaded");
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
	color=LIGHTGREEN;//selectcolor();
	clearviewport();
	p.getdata();
//	aotrans(o,p.pos.x-o.cr.x,p.pos.y-o.cr.y,p.pos.z-o.cr.z);
	showdetails();
	//changeproperty();
	}
	void sim_body:: showdetails()
	{
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
	getch();
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