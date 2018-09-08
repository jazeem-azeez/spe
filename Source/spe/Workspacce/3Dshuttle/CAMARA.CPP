/*
UNIDAD PARA EL MANEJO DE LAS TRANSFORMACIONES Y PROYECCIONES 3D
*/

#include <graphics.h>
#include "vector3.cpp"

#define recalc_N() N=prod_cruz(V,E)
#define recalc_E() E=prod_cruz(N,V)

float scaling_factor = 1;
float inc_scaling_factor = 1.01;

const float d_eye_cent_defecto = 300;
const float inc_d_eye_cent = 10;
float d_eye_cent = d_eye_cent_defecto;


int xcen, ycen;
// (xcen,ycen) son las coordenadas del punto central de la pantalla;

vector3 E(1,0,0), N(0,1,0), V(0,0,1);
/*
N y E son los vectores que definen el plano de proyecci¢n
V es el vector3 normal al plano de proyeccion
los tres son vectores unitarios
*/

vector3 EYE (-100,0,0);
//en la proteccion central representa la posicion del OJO observador

float p = 100;
//p es la distancia del punto (0,0,0) al plano

vector3 rot_p_en_v (vector3 X, vector3 U, float w)
{
//	w -> angulo			X -> punto			U -> vector
	U = unitario (U);
	float Xu = prod_punto (X,U);
	vector3 Xu_por_U = Xu * U;
	return Xu_por_U + cos(w)*(X-Xu_por_U) + sin(w)*prod_cruz(U,X);
}

vector3 proy_normal (vector3 X)
{
	return (X + (p - prod_punto(V,X))*V);
}

vector3 proy_central (vector3 X)
{
	return (X + ((p - prod_punto(V,X))/prod_punto(V,X-EYE)) * (X-EYE));
}

pointtype plano_a_pantalla (vector3 PLANO)
{
	pointtype pantalla;
	pantalla.x = (int) (xcen + scaling_factor*prod_punto(PLANO,E));
	pantalla.y = (int) (ycen - scaling_factor*prod_punto(PLANO,N));
	return pantalla;
}



