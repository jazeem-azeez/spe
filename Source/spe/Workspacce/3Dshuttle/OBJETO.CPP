//#include "vector3.cpp"

typedef struct arista {int p1, p2;};

class objeto3D {
public:
	int nv;        int na;
   vector3 *lv;   arista *la;
   objeto3D (int nvertices, int naristas);
   ~objeto3D () {delete lv; delete la;};
};

objeto3D::objeto3D (int nvertices, int naristas)
{
	nv = nvertices;         na = naristas;
	lv = new vector3[nv];   la = new arista[na];
};


/*objeto3D cubo (8,12);   //8 vertices, 12 aristas

definir_objeto()
{
	cubo.lv[0].x = -75;     cubo.lv[0].y = -75;     cubo.lv[0].z = -75;
	cubo.lv[1].x = -75;  cubo.lv[1].y = -75;  cubo.lv[1].z = 75;
	cubo.lv[2].x = -75;  cubo.lv[2].y = 75;      cubo.lv[2].z = 75;
	cubo.lv[3].x = -75;  cubo.lv[3].y = 75;   cubo.lv[3].z = -75;
	cubo.lv[4].x = 75;   cubo.lv[4].y = -75;     cubo.lv[4].z = -75;
	cubo.lv[5].x = 75;   cubo.lv[5].y = -75;     cubo.lv[5].z = 75;
	cubo.lv[6].x = 75;   cubo.lv[6].y = 75;      cubo.lv[6].z = 75;
	cubo.lv[7].x = 75;   cubo.lv[7].y = 75;      cubo.lv[7].z = -75;

	cubo.la[0].p1 = 0;      cubo.la[0].p2 = 1;
	cubo.la[1].p1 = 1;      cubo.la[1].p2 = 2;
	cubo.la[2].p1 = 2;      cubo.la[2].p2 = 3;
	cubo.la[3].p1 = 4;      cubo.la[3].p2 = 5;
	cubo.la[4].p1 = 5;      cubo.la[4].p2 = 6;
	cubo.la[5].p1 = 6;      cubo.la[5].p2 = 7;
	cubo.la[6].p1 = 0;      cubo.la[6].p2 = 4;
	cubo.la[7].p1 = 3;      cubo.la[7].p2 = 0;
	cubo.la[8].p1 = 4;      cubo.la[8].p2 = 7;
	cubo.la[9].p1 = 1;      cubo.la[9].p2 = 5;
	cubo.la[10].p1 = 2;     cubo.la[10].p2 = 6;
	cubo.la[11].p1 = 3;     cubo.la[11].p2 = 7;
	return 0;
}
*/

#include <stdio.h>
objeto3D cubo(522,890);

definir_objeto(){
	FILE *datos;
	int npuntos, naristas, i, x, y, z;
	datos = fopen("shuttle.txt","rt");
	fscanf(datos,"%d",&npuntos);

	for (i=0; i<npuntos; i++){
		fscanf(datos,"%d %d %d",&x, &y, &z);
		cubo.lv[i].x = x/80;
		cubo.lv[i].y = y/80;
		cubo.lv[i].z = z/80;
	}
	fscanf(datos,"%d",&naristas);
	for (i=0; i<naristas; i++){
		fscanf(datos,"%d %d",&x,&y);
		cubo.la[i].p1 = x-1;
		cubo.la[i].p2 = y-1;
	}
	fclose(datos);
}
