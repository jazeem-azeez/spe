#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <c:\spe\pr\vector.h>
#include <c:\spe\gl\mathd.h>

#define ismoving	1
#define isrotating	1

enum collition_type {penetrating=-1,just_on_collition=0,not_on_colltion,dont_even_imagine};

clock_t start, end,lasttimestamp,delta_t,time_of_execution;

typedef	vec3d	force;
typedef	vec3d	plane;

force	gravity;


int reactor_engine_link(particle& p,ved3d pointfimpact,double kineticE,collition_type col_type)
{
//timestamp generator;
end=clock();
delta_t=(end-start+time_of_execution)/CLK_TCK;
//here i think is the pace to update the object with the time and to perform operations related to collition
/*
we have
(1). kinetic energy of the other object with which collition occoured
(2).pointfimpact
(3) the type of collition whether the collition was a penetrating one and else things
*/
return 0;
}


int init_reactor()

{
gravity .x=0;
gravity .y=-9.8;
gravity .z=0;
start=clock();
return 0;
}

struct boundary
{
vec3d [2][4];
};

class particle
{
public:
	vec3d pos,lpos,vel,omega,distance,Rpos,LRpos,theta;
	float acc,trq,mass,TKE,RKE,_e;

    boundary cube;

	void getdata()
	{
	cout<<"Position Vector details\n" ;
	cin>>pos.x>>pos.y>>pos.z>>Rpos.x>>Rpos.y>>Rpos.z;
	cout<<"\nVelocity vector";
	cin>>vel.x>>vel.y>>vel.z;
	cout<<"\nTheta vector";
	cin>>theta.x>>theta.y>>theta.z;
	}
	void 	changeposition(vec3d v1,vec3d v2)
	{
	pos=v1;
	Rpos=v2;
	}

	void 	changevel(vec3d v1)
	{
	vel=v1;
	}

	void 	changeomega(vec3d v1)
	{
	omega=v1;
	}

	void	changeacc(float a)
	{
	acc=a;
	}

	void 	changemass(float a)
	{
	mass=a;
	}

	void 	changetorque(float a)
	{
	trq=a;
	}

	void	updateposition()
	{
	lpos=pos;
	distance=vel*delta_t;
	pos=pos+distance;
	LRpos=Rpos;
	theta=omega*delta_t;
	Rpos=rotateAboutX_Deg(Rpos,theta.x);
	Rpos=rotateAboutY_Deg(Rpos,theta.y);
	Rpos=rotateAboutZ_Deg(Rpos,theta.z);
	}

	void 	update_vel_AND_omega()
	{
	vel.normalize();
	vel=vel*acc*(end-start);//velocity=accelaration*total time
	omega.normalize();
	omega=omega*trq*(end-start);
	}

	void 	updateKE()
	{
	TKE=0.5*mass*(vel.length()*vel.length());
	RKE=0.5*mass*(omega.length()*omega.length());
	}

	void	update()
	{
	update_vel_AND_omega();
	updateKE();
	updateposition();
	}
	void draw()
	{
	point3d  p;
	p.x=pos.x;
	p.y=pos.y;
	p.z=pos.z;
	drawpoint(p,15);
    //	line3d l;
//	l.p1.x=Rpos.x,l.p2.x=LRpos.x,l.p1.y=Rpos.y,l.p2.y=LRpos.x,l.p1.z=Rpos.z,l.p2.z=Rpos.x;

  //	drawline(line3d,15);
	}
	friend  reactor_engine_link();
}p1;          /*


