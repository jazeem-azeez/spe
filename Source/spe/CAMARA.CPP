
#define recalc_N() N=crosspdt(V,E)
#define recalc_E() E=crosspdt(N,V)

float scaling_factor = 1;
float inc_scaling_factor = 1.01;

const float d_eye_cent_default = 300;
const float inc_d_eye_cent = 10;
float d_eye_cent = d_eye_cent_default;
const float ang = 0.1;


int xcen, ycen;

vector3 E(1,0,0), N(0,1,0), V(0,0,1);

vector3 EYE (-100,0,0);

float p = 100;

vector3 rot_p_en_v (vector3 X, vector3 U, float w)
{
	U = unit (U);
	float Xu = dotpdt (X,U);
	vector3 Xu_por_U = Xu * U;
	return Xu_por_U + cos(w)*(X-Xu_por_U) + sin(w)*crosspdt(U,X);
}

vector3 normal (vector3 X)
{
	return ((X + (p - dotpdt(V,X))*V));
}

vector3 central (vector3 X)
{
	return (X + ((p - dotpdt(V,X))/dotpdt(V,X-EYE)) * (X-EYE));
}

pointtype pointplotter (vector3 PLANO)
{
	pointtype p;
	p.x = (int) (xcen + scaling_factor*dotpdt(PLANO,E));
	p.y = (int) (ycen - scaling_factor*dotpdt(PLANO,N));
	return p;
}



