# include <dos.h>
# include <graphics.h>
# include <stdio.h>
# include <stdlib.h>
# include <conio.h>
# include <fstream.h>
# include <string.h>
# include <bmpimage.h>
# include <mymouse.h>



class console

{
public: 
	//data members
	char name[16];
	char *txt[][8];
	unsigned int no;
	int *sx,*sy,*ex,*ey;
	int stx,sty;
	char imagename[16];
	// member functions
	console()
	{
		name[0]=NULL;
		no=0;
		txt[0][0]=NULL;
	}
	~console()
	{
	delete sx,sy,ex,ey;
		delete txt;
	}

	console (char filename [16]);
	int   choice();
	moveconsole();
	void show()
	{  		ldbmp(stx,sty,imagename);
	}

};

int console :: choice()
	{
	int i;
	char str[4];
	for(;;)
	for (i=0;i<no;i++)
		{

		if (m.click(sx[i],sy[i],ex[i],ey[i])==1)
		return i;
		if(!kbhit()==0)
			return 0;
		}
	}



console :: console (char filename [16])

{
	FILE *datas;
	char bmpname[16];
	int i;
	//strcpy(bmpname,filename);
	datas = fopen(filename,"rt");
	if (datas==NULL)
	printf("Error opening file");
	/*for(int i=0;bmpname[i]!='\n';i++)
	bmpname[i]=getc(datas);
	bmpname[i]='\0';
	printf("%s",bmpname);
	getch();*/
	flushall();
	stx=-1,sty=-1;
	fscanf(datas,"%d %d",&stx,&sty);
	no=0;
	//printf("%d,%d",stx,sty);
	fscanf(datas,"%d",&no);
	sx= (int *)     new int [no];
	sy= (int *)	new int [no];
	ex= (int *)	new int [no];
	ey= (int *)	new int [no];
	txt[0][0]=(char*)	new char [no][8];
	//printf("%d",no);
	for (i=0;i<=no;i++)
	{
	fscanf(datas,"%d %d %d %d",&sx[i],&sy[i],&ex[i],&ey[i]);
	}
	fclose(datas);

	for(i=0;filename[i]!='.'&&filename[i]!='\0';i++);
	filename[i+1]='b',filename[i+2]='m',filename[i+3]='p',filename[i+4]='\0';
	//m.hidemouseptr();
	ldbmp(stx,sty,filename);
	strcpy(imagename,filename);
}
/*
void main()
{
int gdriver = DETECT, gmode, errorcode;
int x, y;

initgraph(&gdriver, &gmode, "");


console c1("main.con");
m.initmouse();
m.showmouseptr();
c1.choice();
getch();
closegraph();
}
  */