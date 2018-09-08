//the main vector,point part


class vector3 {
public:
	float x,y,z;
	vector3 (float xx=0, float yy=0, float zz=0) {x=xx; y=yy; z=zz;};
	vector3 operator + (vector3 b);
	vector3 operator - (vector3 b);
	vector3 operator = (vector3 vec);
	friend vector3 crosspdt (vector3 a,vector3 b);
	friend float dotpdt (vector3 a,vector3 b);
	friend float normal (vector3 b);
	friend vector3 unit (vector3 b);
	friend vector3 operator * (float esc, vector3 b);
	friend vector3 operator * (vector3 b, float esc);
	imp() { cout << x << "  " << y << "  " << z << endl; return 0; };
};


vector3 vector3::operator + (vector3 b)
{
	vector3 sum;
	sum.x = x+b.x;
	sum.y = y+b.y;
	sum.z = z+b.z;
	return sum;
}

vector3 vector3::operator - (vector3 b)
{
	vector3 diff;
	diff.x = x-b.x;
	diff.y = y-b.y;
	diff.z = z-b.z;
	return diff;
}

vector3 vector3::operator = (vector3 b)
{
	x = b.x;
	y = b.y;
	z = b.z;
	return *this;
}

vector3 crosspdt (vector3 a,vector3 b)
{
//	r = a x b
	vector3 r;
	r.x = a.y*b.z - a.z*b.y;
	r.y = a.z*b.x - a.x*b.z;
	r.z = a.x*b.y - a.y*b.x;
	return r;
};

float dotpdt (vector3 a,vector3 b)
{
	return (a.x*b.x + a.y*b.y + a.z*b.z);
}

float normal (vector3 b)
{
	return sqrt(b.x*b.x + b.y*b.y + b.z*b.z);
}

vector3 unit (vector3 b)
{
	float escalar = normal(b);
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


float dist_point_vector3 (vector3 P, vector3 V)
{
	return normal(P - (dotpdt(P,V) * V));
};

vector3 ii(1,0,0), jj(0,1,0), kk(0,0,1);
