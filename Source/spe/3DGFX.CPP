//#include <gui.cpp>
#include <vector3.cpp>
#include <camara.cpp>

	struct edge 
{
	int p1, p2;
};


class object3d {
public:

   pointtype *ppant;
   int nv;        int ne;
   vector3 *lv;   edge *la;
   object3d (int nvertices, int nedges);
   ~object3d () {delete lv; delete la; delete ppant};
   void load_obj(char file[]);
   int maingl(int t);

};

object3d::object3d (int nvertices, int nedges)
{
	nv = nvertices;         ne = nedges;
	lv = new vector3[nv];   la = new edge[ne];
		ppant = new pointtype[nv];
};



void object3d :: load_obj(char file[])
{
	FILE *datas;
	int npuntos, nedges, i, x, y, z;
	datas = fopen(file,"rt");
	fscanf(datas,"%d",&npuntos);

	for (i=0; i<npuntos; i++){
		fscanf(datas,"%d %d %d",&x, &y, &z);
		lv[i].x = x/80;
		lv[i].y = y/80;
		lv[i].z = z/80;
	}
	fscanf(datas,"%d",&nedges);
	for (i=0; i<nedges; i++){
		fscanf(datas,"%d %d",&x,&y);
		la[i].p1 = x-1;
		la[i].p2 = y-1;
	}
	fclose(datas);
}


int object3d :: maingl(int t)
{
	int i;
	setbkcolor (BLACK);
	do {
		t = letter();
		for (i=0; i<ne; i++)
		{
			setcolor (BLACK);

			line (ppant[la[i].p1].x, ppant[la[i].p1].y,
				  ppant[la[i].p2].x, ppant[la[i].p2].y);
			setcolor (WHITE);
		}
		switch (t) {
			case 'w'  ://moveup

				   for (i=0;i<nv;i++)
					lv[i].y++;
				
					break;

			case 's'  ://movedown();
				for (i=0;i<nv;i++)
					lv[i].y--;
					
					break;
			case 'a'  ://moveright();	
				for (i=0;i<nv;i++)
				 		lv[i].x--;
				

					break;
			case 'd'  ://moveleft
				for (i=0;i<nv;i++)
					 	lv[i].x++;
					
					break;
			case 'z'   ://move deeper
				for (i=0;i<nv;i++)
						lv[i].z--;
						
					break;
			case 'Z'   ://movehigher
				for (i=0;i<nv;i++)
							lv[i].z++;
					
					break;
			case UPKEY:	V = rot_p_en_v (V,E,-ang); recalc_N(); break;
			case DOWNKEY:	V = rot_p_en_v (V,E,ang); recalc_N(); break;
			case RIGHTKEY: V = rot_p_en_v (V,N,ang); recalc_E(); break;
			case LEFTKEY: V = rot_p_en_v (V,N,-ang); recalc_E(); break;
			case CTRL_RIGHT: N = rot_p_en_v (N,V,-ang); recalc_E(); break;
			case CTRL_LEFT: N = rot_p_en_v (N,V,ang); recalc_E(); break;
			case '>': scaling_factor *= inc_scaling_factor; break;
			case '<': scaling_factor /= inc_scaling_factor; break;
			case '+': d_eye_cent += inc_d_eye_cent; break;
			case '-': if (d_eye_cent>1) d_eye_cent -= inc_d_eye_cent; break;
			case HOME:	E = ii; N = jj; V = kk;
					scaling_factor = 1;
					d_eye_cent = d_eye_cent_default;
				break;
		};
		EYE = d_eye_cent*V;
		for (i=0; i<nv; i++)
			ppant[i] = pointplotter(central(lv[i]));
		for (i=0; i<ne; i++)
			line (ppant[la[i].p1].x, ppant[la[i].p1].y,
				  ppant[la[i].p2].x, ppant[la[i].p2].y);
	} while (t!=ESC);
	getch();
	return 0;
};
