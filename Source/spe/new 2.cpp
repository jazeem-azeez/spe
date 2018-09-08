
void transresolver()

{	

}

void rotresolver()

{	

}

int resolve_collition(particle &p)
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
vel =vel+p.vel;
omega=omega+p.omega;
update();
}