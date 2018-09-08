//bitmap console manager
class bcm

{
public:
	//data members
	char name[16];
	int no;
	int *sx,*sy,*ex,*ey;
	int stx,sty;
	char imagename[16];
	// member functions
	int check_name(char *str)
	{
	return strcmpi(name,str);
	}

	bcm()
	{
		name[0]='\0';
		no=0;
		txt=NULL;
	}

	~bcm()
	{
	delete sx,sy,ex,ey;
	delete txt;
	}
	void initiate (char filename [16]);

	bcm(char filename [16])
	{
	initiate (filename);
	}

	int   choice();

	int movebcm(int x,int y);

	void show()
	{  		ldbmp(stx,sty,imagename);
	}
};

int bcm :: movebcm(int x,int y)

	{
	for (int i=0;i<no;i++)
		sx[i]+=x,sy[i]+=y,ex[i]+=x,ey[i]+=y;
	stx+=x,sty+=y;
	show();
	return 0;
	}

int bcm :: choice()
	{
	int i;
	char str[4];
	for(;;)
	for (i=0;i<no;i++)
		{
		 if (m.ismouse(sx[i],sy[i],ex[i],ey[i])==1)
			effect(sx[i],sy[i],ex[i],ey[i]);

		if (m.click(sx[i],sy[i],ex[i],ey[i])==1)
		{
	      //	setcolor(BLACK);
	      //	outtextxy(600,400,"Clicked");
			return i;
		}
		if(!kbhit()==0)
			return getch();
		}
	}



void bcm :: initiate (char filename [16])

{
	FILE *datas;
	char bmpname[16];
	int i;
	
	flushall();
	datas = fopen(filename,"rt");
	flushall();
	if (datas==NULL)
	{printf("Error opening file");
	exit(0);
	}
	flushall();
	stx=-1,sty=-1;
	fscanf(datas,"%d	%d",&stx,&sty);
	no=0;
	
	fscanf(datas,"%d",&no);
	sx= (int *) new int [no];
	sy= (int *)	new int [no];
	ex= (int *)	new int [no];
	ey= (int *)	new int [no];
	
	for (i=0;i<=no;i++)
	{
	fscanf(datas,"%d	%d	%d	%d",&sx[i],&sy[i],&ex[i],&ey[i]);
	}
	fclose(datas);

	for(i=0;filename[i]!='.'&&filename[i]!='\0';i++);

	filename[i+1]='b',filename[i+2]='m',filename[i+3]='p',filename[i+4]='\0';
	strcpy(imagename,filename);
	strncpy(name,filename,i);
	name[i]='\0';
	
	
}
