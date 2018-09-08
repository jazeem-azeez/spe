//UNIDAD PARA EL MANEJO DE VECTORES EN R3

#include <math.h>
#include <iostream.h>

class vector3 {
public:
	float x,y,z;
	vector3 (float xx=0, float yy=0, float zz=0) {x=xx; y=yy; z=zz;};
	vector3 operator + (vector3 b);
	vector3 operator - (vector3 b);
	vector3 operator = (vector3 vec);
	friend vector3 prod_cruz (vector3 a,vector3 b);
	friend float prod_punto (vector3 a,vector3 b);
	friend float norma (vector3 b);
	friend vector3 unitario (vector3 b);
	friend vector3 operator * (float esc, vector3 b);
	friend vector3 operator * (vector3 b, float esc);
	imprimir() { cout << x << "  " << y << "  " << z << endl; return 0; };
};


vector3 vector3::operator + (vector3 b)
{
	vector3 suma;
	suma.x = x+b.x;
	suma.y = y+b.y;
	suma.z = z+b.z;
	return suma;
}

vector3 vector3::operator - (vector3 b)
{
	vector3 resta;
	resta.x = x-b.x;
	resta.y = y-b.y;
	resta.z = z-b.z;
	return resta;
}

vector3 vector3::operator = (vector3 b)
{
	x = b.x;
	y = b.y;
	z = b.z;
	return *this;
}

vector3 prod_cruz (vector3 a,vector3 b)
{
//	r = a x b
	vector3 r;
	r.x = a.y*b.z - a.z*b.y;
	r.y = a.z*b.x - a.x*b.z;
	r.z = a.x*b.y - a.y*b.x;
	return r;
};

float prod_punto (vector3 a,vector3 b)
{
	return (a.x*b.x + a.y*b.y + a.z*b.z);
}

float norma (vector3 b)
{
	return sqrt(b.x*b.x + b.y*b.y + b.z*b.z);
}

vector3 unitario (vector3 b)
{
	float escalar = norma(b);
	vector3 unit;
	unit.x = b.x/escalar;
	unit.y = b.y/escalar;
	unit.z = b.z/escalar;
	return unit;
}


vector3 operator * (float esc, vector3 b)
{
	vector3 nv;
	nv.x = esc * b.x;
	nv.y = esc * b.y;
	nv.z = esc * b.z;
	return nv;
}

vector3 operator * (vector3 b, float esc)
{
	vector3 nv;
	nv.x = esc * b.x;
	nv.y = esc * b.y;
	nv.z = esc * b.z;
	return nv;
}


float dist_punto_vector3 (vector3 P, vector3 V)
{
	return norma(P - (prod_punto(P,V) * V));
};

vector3 ii(1,0,0), jj(0,1,0), kk(0,0,1);


/*#include <conio.h>

main()
{
	clrscr();
	vector3 x(10,-2,3), u(2,4,-3), r,q;
	return 0;

}
*/