#include <stdio.h>
#include <math.h>
#include <dos.h>
#include <conio.h>
//#include <c:\spe\pr\vector.h>
//#include <c:\spe\pr\particleX.cpp>
/*
on the basis of

*/
struct force 
{
float x,y,z;
}f[30],gravity;

setupPR()
{
//run the basics step to set the engine run

}

class particle
{
public:

float x,y,z;
float vel,mass,e;
float KE ;

};

float acceleration(float vel,float time)
{
if(time==0)
return 0.0;
else
return (vel/time);
}

float kinetic_energy(float mass,float vel)
{
return(0.5*mass*vel);
}

float force(float mass ,float acce)
{
return (mass*acce);
}

float momentum(float mass,float vel)
{
return (mass*vel);
}

float work(float force,float disp)
{
return (force*disp);
}

