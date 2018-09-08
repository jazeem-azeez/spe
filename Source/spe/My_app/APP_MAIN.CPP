
//list of headers
float _xscale=1.0,_yscale=1.0,_zscale=1.0;// check when optimizing is done
# include "headerli.cpp"
# include "c:\spe\my_app\app_lin.cpp"

int setup_platform();
int setdown_platfrom();
int Application();

 void main()
{
	int i=0;
	setup_platform();
	cleardevice();
	if(glsetup(0)==0)
		if(Application()!=0)
		{
		setdown_platfrom();
		printf("\nSome bug caused the program to abort the operation");
		printf("\n\t plase contact your administrator");
		printf("\nTrying to restart platform\n");
		for(i=0;i<79;i++,delay(62))
			cout<<".";
		_cexit();
		printf("\n Do tou Want to Try [y] :");

		if(getch()=='y')
			main();
		exit(3);
		}

	exit(setdown_platfrom());
}
setdown_platfrom()
{
	textmode(0x3);
	restorecrtmode();
	printf("Exiting \n returned to textmode");
	closegraph();
	printf("\n\tThank you\n\t Press any key to exit");
	getch();
	return 0;
}
setup_platform()
{
	directvideo=1;
	textbackground(BLUE);
	textcolor(LIGHTGREEN);
	highvideo();
	clrscr();
	printf("\n\tStarting : ");

	delay(500);
	printf("\nPlease check prerequesties\n\nSearching for files: \n");
	printf("\nName\t->\tSize");
	delay(500);
//	Show_files("*.gld");
//	Show_files("*.exe");
//	Show_files("*.bcm");
	delay(500);

	printf("\n\nInstalling & Setting up Devices and Handlers");
//	printf("\nSound device is being setup 0x220\t");
//	delay(500);
//	if (ResetDSP(0x220)==1)
//		printf("\Found and Reset");
///	else
//		printf("FAILED\n");
//	printf("\nSound device is being setup 0x330\t");
//	delay(500);
//	if (ResetDSP(0x330)==1)
//		printf("\nFound and Reset");
//	else
//		printf("FAILED\n");
//
	printf("\nInitiating BGI graphics Mode....  ");
	sleep(1);
	initsvga();
	InitMouse();
	setcolor(LIGHTGREEN);
	cleardevice();
	glprintf("\n\t\t\t\t\t\t\t\t\tPreparing Graphics (GL)\n Initializing VESA 800X600 MODE\n");
	glnextline();
	SetMode(_800x600,1);
	clearviewport();
//	sysinfo();
	delay(500);
	glprintf("\n\nSetting up 8087 Error Handler...\t\t\t");
	setup_float_exception();
	delay(500);
	glprintf("\tDone");
	delay(1000);
	clearviewport();
	setcolor(YELLOW);
	glprintf("\n\n\nNow Your Platform Has Been Sucessfully Initialized.");
	glprintf("\n\n\n\nWarnning!.. there is chance of havng Domain Errors/Hardware burnouts\n\t in Pentium 4 based processors");
	glprintf("\n\n\nSo Please backup all your data for your safety\\(pentium is not recommended-{pentium flaws})");
	sleep(5);
	return 0;
}
