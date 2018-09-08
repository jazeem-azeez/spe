
#include <math.h>
#include <fstream.h>
#include <stdio.h>

#define DAX_PI 3.141592653589793238462643383279
#define PiOver180	(DAX_PI/180)
#define d180OverPi (180/DAX_PI)


/*===========3Dimensional Vector Class======================*/
class vec3d
   {
   public:
      double x;
      double y;
      double z;

      vec3d();
      vec3d(double, double, double);
      vec3d(const vec3d&);
      virtual ~vec3d();

      vec3d& operator= (const vec3d&);
      friend ostream& operator<< (ostream&, const vec3d&);
      friend int operator== (const vec3d&, const vec3d&);
      friend int operator!= (const vec3d&, const vec3d&);
      friend vec3d operator+ (const vec3d&, const vec3d&);
      friend vec3d operator- (const vec3d&, const vec3d&);
      friend vec3d operator- (const vec3d&);
      friend vec3d operator* (const double&, const vec3d&);
      friend vec3d operator* (const vec3d&, const double&);
      friend vec3d operator/ (const vec3d&, const double&);
      vec3d& operator+= (const vec3d&);
      vec3d& operator-= (const vec3d&);
      vec3d& operator*= (const double&);
      vec3d& operator/= (const double&);

      friend double dotP(const vec3d&, const vec3d&);
      friend vec3d crossP(const vec3d&, const vec3d&);
      friend double distanceBetween(const vec3d&, const vec3d&);
      friend double angleBetweenRad(vec3d, vec3d);
      friend double angleBetweenDeg(vec3d, vec3d);
      friend double angleFromPlaneRad(vec3d);
      friend double angleFromPlaneDeg(vec3d);
      friend vec3d perpProjection(const vec3d&, const vec3d&);
      friend vec3d rotateAboutX_Deg(const vec3d&, const double);
      friend vec3d rotateAboutY_Deg(const vec3d&, const double);
      friend vec3d rotateAboutZ_Deg(const vec3d&, const double);
      friend vec3d rotate_Deg (const vec3d&, const double,const double ,const double );
      friend vec3d rotateAboutX_Rad(const vec3d&, const double);
      friend vec3d rotateAboutY_Rad(const vec3d&, const double);
      friend vec3d rotateAboutZ_Rad(const vec3d&, const double);

      void normalize();
      double length();
   };
      const vec3d Zero3d       (0.0, 0.0, 0.0);
      const vec3d UnitX3d      (1.0, 0.0, 0.0);
      const vec3d UnitY3d      (0.0, 1.0, 0.0);
      const vec3d UnitZ3d      (0.0, 0.0, 1.0);
      const vec3d Unit_Vector  (1.0, 1.0, 1.0);
vec3d::vec3d()
{
x = 0.0;
y = 0.0;
z = 0.0;
}

vec3d::vec3d(double _x, double _y, double _z)
{
x = _x;
y = _y;
z = _z;
}

vec3d::vec3d(const vec3d& _Vec)
{
x = _Vec.x;
y = _Vec.y;
z = _Vec.z;
}

vec3d::~vec3d()
{}

vec3d& vec3d::operator= (const vec3d& _Vec)
{
if(this == &_Vec) 
   return (*this);
else
   x = _Vec.x;
   y = _Vec.y;
   z = _Vec.z;
   return (*this);
}

ostream& operator<< (ostream& os, const vec3d& _Vec)
{ 
os << "(( " << _Vec.x << ", " << _Vec.y << ", " << _Vec.z << " ))" << endl;
return os ;
}


int operator== (const vec3d& _Vec1, const vec3d& _Vec2)
{
if((_Vec1.x == _Vec2.x) && (_Vec1.y == _Vec2.y) && (_Vec1.z == _Vec2.z))
   return (1);
else
   return (0);
}

int operator!= (const vec3d& _Vec1, const vec3d& _Vec2)
{
if((_Vec1.x != _Vec2.x) || (_Vec1.y != _Vec2.y) || (_Vec1.z != _Vec2.z))
   return (1);
else
   return (0);
}

vec3d operator+ (const vec3d& _Vec1, const vec3d& _Vec2)
{
vec3d _Vec0;

_Vec0.x = _Vec1.x + _Vec2.x;
_Vec0.y = _Vec1.y + _Vec2.y;
_Vec0.z = _Vec1.z + _Vec2.z;
return (_Vec0);
}

vec3d operator- (const vec3d& _Vec1, const vec3d& _Vec2)
{
vec3d _Vec0;

_Vec0.x = _Vec1.x - _Vec2.x;
_Vec0.y = _Vec1.y - _Vec2.y;
_Vec0.z = _Vec1.z - _Vec2.z;
return (_Vec0);
}

vec3d operator- (const vec3d& _Vec)
{
vec3d _Vec0;

if(_Vec.x != 0)
   _Vec0.x = (_Vec.x * (-1));
if(_Vec.y != 0)
   _Vec0.y = (_Vec.y * (-1));
if(_Vec.z != 0)
   _Vec0.z = (_Vec.z * (-1));
return (_Vec0);
}

vec3d operator* (const double& X, const vec3d& _Vec1)
{
vec3d _Vec0;

_Vec0.x = (X * _Vec1.x);
_Vec0.y = (X * _Vec1.y);
_Vec0.z = (X * _Vec1.z);
return (_Vec0);
}

vec3d operator* (const vec3d& _Vec1, const double& X)
{
vec3d _Vec0;

_Vec0.x = (X * _Vec1.x);
_Vec0.y = (X * _Vec1.y);
_Vec0.z = (X * _Vec1.z);
return (_Vec0);
}

vec3d operator/ (const vec3d& _Vec1, const double& X)
{
vec3d _Vec0;

_Vec0.x = (_Vec1.x / X);
_Vec0.y = (_Vec1.y / X); 
_Vec0.z = (_Vec1.z / X);    
return (_Vec0);
}

vec3d& vec3d::operator+= (const vec3d& _Vec)
{
x += _Vec.x;
y += _Vec.y;
z += _Vec.z;
return (*this);
}

vec3d& vec3d::operator-= (const vec3d& _Vec)
{
x -= _Vec.x;
y -= _Vec.y;
z -= _Vec.z;
return (*this);
}

vec3d& vec3d::operator*= (const double& X)
{
x *= X;
y *= X;
z *= X;
return (*this);
}

vec3d& vec3d::operator/= (const double& X)
{
x /= X;
y /= X;
z /= X;
return (*this);
}

void vec3d::normalize()
{
double Length = length();
if(Length!=0)
{x = x / Length;
y = y / Length;
z = z / Length;}
else
{
x = x / 0.0000001;
y = y / 0.0000001;
z = z / 0.0000001;
}

}

double vec3d::length()
{
double Length =  sqrt((x * x) + (y * y) + (z * z));
return (Length);
}

double dotP(const vec3d& _Vec1, const vec3d& _Vec2)
{
double X = ((_Vec1.x * _Vec2.x) + (_Vec1.y * _Vec2.y) + (_Vec1.z * _Vec2.z));
return (X);
}

vec3d crossP(const vec3d& _Vec1, const vec3d& _Vec2)
{
vec3d _Vec0;
_Vec0.x =   _Vec1.y * _Vec2.z - _Vec1.z * _Vec2.y;
_Vec0.y = - _Vec1.x * _Vec2.z + _Vec1.z * _Vec2.x;
_Vec0.z =   _Vec1.x * _Vec2.y - _Vec1.y * _Vec2.x;
return (_Vec0);
}

double distanceBetween(const vec3d& _Vec1, const vec3d& _Vec2)
{
double Distance = sqrt(pow((_Vec2.x - _Vec1.x),2) + pow((_Vec2.y - _Vec1.y),2) + pow((_Vec2.z - _Vec1.z),2));
return (Distance);
}

double angleBetweenRad(vec3d _Vec1, vec3d _Vec2)
{
_Vec1.normalize();
_Vec2.normalize();
double dP, angle;
dP = dotP(_Vec1, _Vec2);
angle = acos(dP);
return (angle);
}

double angleBetweenDeg(vec3d _Vec1, vec3d _Vec2)
{
_Vec1.normalize();
_Vec2.normalize();
double dP, angle;
dP = dotP(_Vec1, _Vec2);
angle = acos(dP);
angle = angle * d180OverPi;
return (angle);
}

double angleFromPlaneRad(vec3d _Vec1)
{
_Vec1.normalize();
double dP, angle;
dP = dotP(_Vec1, UnitX3d);
angle = acos(dP);
return (angle);
}

double angleFromPlaneDeg(vec3d _Vec1)
{
_Vec1.normalize();
double dP, angle;
dP = dotP(_Vec1, UnitX3d);
angle = acos(dP);
angle = angle * d180OverPi;
return (angle);
}

vec3d perpProjection(const vec3d& _Vec1, const vec3d& _Vec2)
{
vec3d _Vec0;
_Vec0 = (dotP(_Vec1, _Vec2) / (dotP(_Vec2, _Vec2))) * _Vec2;
return (_Vec0);
}

vec3d rotateAboutX_Deg(const vec3d& _Vec1, const double _Angle)
{
vec3d _Vec0;
double sinCalc = (double)sin(_Angle * PiOver180);
double cosCalc = (double)cos(_Angle * PiOver180);

_Vec0.x = _Vec1.x;
_Vec0.y = (_Vec1.y * cosCalc) - (_Vec1.z * sinCalc);
//if((_Vec0.y < .00000000001) && (_Vec0.y > -.00000000001))
  // _Vec0.y = 0.0;
_Vec0.z = (_Vec1.y * sinCalc) + (_Vec1.z * cosCalc);
//if((_Vec0.z < .00000000001) && (_Vec0.z > -.00000000001))
//   _Vec0.z = 0.0;
return (_Vec0);
}

vec3d rotateAboutY_Deg(const vec3d& _Vec1, const double _Angle)
{
vec3d _Vec0;
double sinCalc = (double)sin(_Angle * PiOver180);
double cosCalc = (double)cos(_Angle * PiOver180);

_Vec0.x = (_Vec1.x * cosCalc) + (_Vec1.z * sinCalc);
//if((_Vec0.x < .00000000001) && (_Vec0.x > -.00000000001))
  // _Vec0.x = 0.0;
_Vec0.y = _Vec1.y;
_Vec0.z = (_Vec1.z * cosCalc) - (_Vec1.x * sinCalc);
//if((_Vec0.z < .00000000001) && (_Vec0.z > -.00000000001))
  // _Vec0.z = 0.0;
return (_Vec0);
}

vec3d rotateAboutZ_Deg(const vec3d& _Vec1, const double _Angle)
{
vec3d _Vec0;
double sinCalc = (double)sin(_Angle * PiOver180);
double cosCalc = (double)cos(_Angle * PiOver180);

_Vec0.x = (_Vec1.x * cosCalc) - (_Vec1.y * sinCalc);
//if((_Vec0.x < .00000000001) && (_Vec0.x > -.00000000001))
  // _Vec0.x = 0.0;
_Vec0.y = (_Vec1.y * cosCalc) + (_Vec1.x * sinCalc);
//if((_Vec0.y < .00000000001) && (_Vec0.y > -.00000000001))
  // _Vec0.y = 0.0;
_Vec0.z = _Vec1.z;
return (_Vec0);
}

vec3d rotate_Deg(const vec3d& _Vec1, const double x_Angle,const double y_Angle,const double z_Angle)
{
vec3d _Vec0;

double sinCalc = (double)sin(x_Angle * PiOver180);
double cosCalc = (double)cos(x_Angle * PiOver180);

_Vec0.y = (_Vec1.y * cosCalc) - (_Vec1.z * sinCalc);
if((_Vec0.y < .00000000001) && (_Vec0.y > -.00000000001))
  _Vec0.y = 0.0;
_Vec0.z = (_Vec1.y * sinCalc) + (_Vec1.z * cosCalc);
if((_Vec0.z < .00000000001) && (_Vec0.z > -.00000000001))
   _Vec0.z = 0.0;


sinCalc = (double)sin(y_Angle * PiOver180);
cosCalc = (double)cos(y_Angle * PiOver180);

_Vec0.x = (_Vec1.x * cosCalc) + (_Vec1.z * sinCalc);
if((_Vec0.x < .00000000001) && (_Vec0.x > -.00000000001))
   _Vec0.x = 0.0;
_Vec0.z = (_Vec1.z * cosCalc) - (_Vec1.x * sinCalc);
if((_Vec0.z < .00000000001) && (_Vec0.z > -.00000000001))
   _Vec0.z = 0.0;

sinCalc = (double)sin(z_Angle * PiOver180);
cosCalc = (double)cos(z_Angle * PiOver180);

_Vec0.x = (_Vec1.x * cosCalc) - (_Vec1.y * sinCalc);
if((_Vec0.x < .00000000001) && (_Vec0.x > -.00000000001))
   _Vec0.x = 0.0;
_Vec0.y = (_Vec1.y * cosCalc) + (_Vec1.x * sinCalc);
if((_Vec0.y < .00000000001) && (_Vec0.y > -.00000000001))
   _Vec0.y = 0.0;

return (_Vec0);
}

vec3d rotateAboutX_Rad(const vec3d& _Vec1, const double _Angle)
{
vec3d _Vec0;
double sinCalc = (double)sin(_Angle);
double cosCalc = (double)cos(_Angle);

_Vec0.x = _Vec1.x;
_Vec0.y = (_Vec1.y * cosCalc) - (_Vec1.z * sinCalc);
if((_Vec0.y < .00000000001) && (_Vec0.y > -.00000000001))
   _Vec0.y = 0.0;
_Vec0.z = (_Vec1.y * sinCalc) + (_Vec1.z * cosCalc);
if((_Vec0.z < .00000000001) && (_Vec0.z > -.00000000001))
   _Vec0.z = 0.0;
return (_Vec0);
}

vec3d rotateAboutY_Rad(const vec3d& _Vec1, const double _Angle)
{
vec3d _Vec0;
double sinCalc = (double)sin(_Angle);
double cosCalc = (double)cos(_Angle);

_Vec0.x = (_Vec1.x * cosCalc) + (_Vec1.z * sinCalc);
if((_Vec0.x < .00000000001) && (_Vec0.x > -.00000000001))
   _Vec0.x = 0.0;
_Vec0.y = _Vec1.y;
_Vec0.z = (_Vec1.z * cosCalc) - (_Vec1.x * sinCalc);
if((_Vec0.z < .00000000001) && (_Vec0.z > -.00000000001))
   _Vec0.z = 0.0;
return (_Vec0);
}

vec3d rotateAboutZ_Rad(const vec3d& _Vec1, const double _Angle)
{
vec3d _Vec0;
double sinCalc = (double)sin(_Angle);
double cosCalc = (double)cos(_Angle);

_Vec0.x = (_Vec1.x * cosCalc) - (_Vec1.y * sinCalc);
if((_Vec0.x < .00000000001) && (_Vec0.x > -.00000000001))
   _Vec0.x = 0.0;
_Vec0.y = (_Vec1.y * cosCalc) + (_Vec1.x * sinCalc);
if((_Vec0.y < .00000000001) && (_Vec0.y > -.00000000001))
   _Vec0.y = 0.0;
_Vec0.z = _Vec1.z;
return (_Vec0);
}

 /*
void copyto(vec3d v2,vector3 v1)

{
	v2.z=(double) v1.z,v2.y=(double) v1.y,v2.x=(double) v1.x;
}
   */