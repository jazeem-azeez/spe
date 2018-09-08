char help_index[][16]={"HELPsim.bmp","HELPdb.bmp","Helpcfg.bmp"};

int helpnavigator(char filename[16])
{
int c;
//cleardevice();
bcm B;
B.initiate(filename);
//for(i=0;filename[i]!='.'||filename[i]!='\0';i++);
//filename[i+1]='H',filename[i+2]='I',filename[i+3]='F';
//load_help_index(filename);
for(;;)
{
	B.show();
	c=B.choice();
	//clearviewport();
	if(c==0)
	  return 0;
	else
	{Xldbmp(0,0,help_index[c-1]);
	 getch();
	 }


}
//return -1;

}
