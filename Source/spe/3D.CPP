//PROGRAMA VISUALIZADOR DE OBJETOS 3D
//Elaborador por Diego Andres Alvarez Marín (diegoandresalvarez@gmx.net)
//El programa muestra el objeto con una vista en perspectiva
//Utilice las flechas para mover el objeto
// + para alejar la c mara (haciendo una proyeccion mas ortogonal
// - para alejar la camara (haciendo una proyeccion mas en perspectiva
// < y > para hacer zoom
// Home para volver al estado inicial
// Ctrl+ flecha izq y Ctrl + flecha der para girar el objeto
// alrededor del plano normal a la pantalla

#include <iostream.h>
#include <stdlib.h>
#include "camara.cpp"
#include "objeto.cpp"
#include "teclado.cpp"

int maxx, maxy;
const float ang = 0.1;

pointtype *ppant;

inicializar_modo_grafico()
{
   int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "");
   errorcode = graphresult();
   if (errorcode != grOk)
   {
	  cout << "Graphics error: " << grapherrormsg(errorcode) << endl;
	  cout << "Press any key to halt:";
	  getch();
	  exit(1);
   }
	maxx = getmaxx();	maxy = getmaxy();
   xcen = maxx/2;		ycen = maxy/2;
   return 0;
}


int main()
{
	int i;
	int t; //teclado
	inicializar_modo_grafico();
	definir_objeto();
	ppant = new pointtype[cubo.nv];
	setbkcolor (BLACK);
	do {
		t = leertecla();
		for (i=0; i<cubo.na; i++)
		{
			setcolor (BLACK);
			line (ppant[cubo.la[i].p1].x, ppant[cubo.la[i].p1].y,
				  ppant[cubo.la[i].p2].x, ppant[cubo.la[i].p2].y);
			setcolor (WHITE);
		}
		switch (t) {
			case F_ARR:	V = rot_p_en_v (V,E,-ang); recalc_N(); break;
			case F_ABA:	V = rot_p_en_v (V,E,ang); recalc_N(); break;
			case F_DER: V = rot_p_en_v (V,N,ang); recalc_E(); break;
			case F_IZQ: V = rot_p_en_v (V,N,-ang); recalc_E(); break;
			case CTRL_F_DER: N = rot_p_en_v (N,V,-ang); recalc_E(); break;
			case CTRL_F_IZQ: N = rot_p_en_v (N,V,ang); recalc_E(); break;
			case '>': scaling_factor *= inc_scaling_factor; break;
			case '<': scaling_factor /= inc_scaling_factor; break;
			case '+': d_eye_cent += inc_d_eye_cent; break;
			case '-': if (d_eye_cent>1) d_eye_cent -= inc_d_eye_cent; break;
			case HOME:
					E = ii; N = jj; V = kk;
					scaling_factor = 1;
					d_eye_cent = d_eye_cent_defecto;
				break;
		};
		EYE = d_eye_cent*V;
		for (i=0; i<cubo.nv; i++)
			ppant[i] = plano_a_pantalla(proy_central(cubo.lv[i]));
		for (i=0; i<cubo.na; i++)
			line (ppant[cubo.la[i].p1].x, ppant[cubo.la[i].p1].y,
				  ppant[cubo.la[i].p2].x, ppant[cubo.la[i].p2].y);
	} while (t!=ESCAPE);
	closegraph();
	delete ppant;
	return 0;
}
