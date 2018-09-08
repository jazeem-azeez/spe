
//# include <gui.h>
# include <vec3d.h>

# define ONCOL			0
# define ONREST			1

struct collisionstatus

{	short int colstatus,motstatus;
};

class phy

{

public :
	//attributes
	float mass,distance, momentum,acc,velocity,angacc,angvel,_e;
	vec3d pos,tradir,prevpos,force,torque,rotdir;
	 //friction
	double changed_dir,rotchanged_dir;
	collition_status c1;
	
	clock_t start, end;

	//methods
	int update();
	void getdata();
	int restore()

{	pos=prevpos;
	start=clock();
	return 0;
}

	friend  void collisionresolver(phy &p1);

};

int phy ::update()

{
 end=clock();
 double time =((end -start) / CLK_TCK);	//difftime 
 velocity = acc*time;
 angvel=angacc*time;
 
 prevpos=pos;								
 pos +=tradir*(velocity *time);	   //  delta distance
 
 distance +=(velocity *time);
 
 momentum=mass*velocity;

 return 0;

}




void phy ::getdata()

{				 
	svbmp(240,160,maxx,maxy,"buff.bmp");
	moveto(240,160);
	outtext("Enter the Physics details of the current object \n");

	outtext("\nMass :");
	mass=gcin(msg);

	outtext("\nVelocity :");
	vel=gcin(msg);

	momentum=vel*mass;

	outtext("\nEnter the position vector ");
	pos=vec3d((double)gcin(msg),(double)gcin(msg),(double)gcin(msg));

	outtext("\nEnter the direction vector ");
	dir=vec3d((double)gcin(msg),(double)gcin(msg),(double)gcin(msg));
	
	outtext("\nEnter the force vector ");
	force=vec3d((double)gcin(msg),(double)gcin(msg),(double)gcin(msg));

	acc=length(force)/mass;

	outtext("\nEnter the torque vector ");
	torque=vec3d((double)gcin(msg),(double)gcin(msg),(double)gcin(msg));

	outtext("\ndone");
	ldbmp(240,160,"buff.bmp");
}

void transresolver(vec3d &p1, float e)

{	

	double alpha,theta,distance,v_cos_theta,v_sin_theta;

	e=(e+_e)/2;	


	  	alpha=angleBetweenang(p1,dir);
		
		
		v_cos_theta = e*vel*dcos(alpha);
		v_sin_theta = e*vel*dsin(alpha);
		changed_direction=datan((v_sin_theta/v_cos_theta));

		vel=(v_cos_theta/dcos(changed_direction));

		dir= rotateAboutZ_Deg(dir,changed_direction);
		dir= rotateAboutY_Deg(dir,changed_direction);
		dir= rotateAboutX_Deg(dir,changed_direction);



}

void rotresolver(vec3d &p1, float e)

{	

	double alpha,v_cos_theta,v_sin_theta;

	e=(e+_e)/2;	


	  	alpha=angleBetweenang(p1,rotdir);
		
		
		v_cos_theta = e*vel*dcos(alpha);
		v_sin_theta = e*vel*dsin(alpha);
		rotchanged_dir =datan((v_sin_theta/v_cos_theta));

		angvel=(v_cos_theta/dcos(rotchanged_dir ));

		rotdir= rotateAboutZ_Deg(rotdir,rotchanged_dir );
		rotdir= rotateAboutY_Deg(rotdir,rotchanged_dir );
		rotdir= rotateAboutX_Deg(rotdir,rotchanged_dir );



}

int collitionresolver(vec3d &p1, float e)

{	if (c1.colstatus==ONCOL&&c1.motstatus!=ONREST)
	{rotresolver(vec3d &p1, float e),transresolver(vec3d &p1, float e);
	return 0;}
	return 1;
}
