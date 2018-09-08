//1.include and debug headers
//list of headers
# include "headerli.cpp"
# include "c:\spe\my_app\app_lin.cpp"
int setup_platform();
int setdown_platfrom();
int Application();

int Show_files(void);

 void main()
{
RESTART:
setup_platform();
cleardevice();
Enlarge(400,300,"DONE");
Reduce(400,300,"DONE");
delay(500);
cleardevice();
if(Application()!=0)
{
printf("\nSome bug caused the program to abort the operation");
printf("\n\t plase contact your administrator");
if('y'==getche())
{
_cexit();
setdown_platfrom();
exit(1);
}
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
playwav("thanku.wav");
getch();
return 0;
}
setup_platform()
{
textbackground(BLUE);
textcolor(LIGHTGREEN);
highvideo();
clrscr();
printf("\n\tStarting : ");
sleep(1);
printf("\nPlease check prerequesties\n\nShowing available files list in the current active directory: \n");
printf("\nName\t\tSize");
sleep(1);
//Show_files();
sleep(1);
printf("\n\tPlease Wait ...");
sleep(1);
printf("\nInstalling & setup Devices and Handlers");
sleep(1);
setup_float_exception();
printf("\nSound device is being setup 0x220\t");
sleep(1);
if (ResetDSP(0x220)==1)
printf("\Found and Reset");
else
printf("FAILED\n");
sleep(1);
printf("\nSound device is being setup 0x240\t");
sleep(1);
if (ResetDSP(0x240)==1)
printf("\nFound and Reset");
else
printf("FAILED\n");
sleep(1);
playwav("init.wav");
initsvga();
InitMouse();
printf("\n\t\t\t\tPreparing Graphics (GL)\n Initializing VESA 800X600 MODE\n");
delay(2000);
SetMode(_800x600,0);
sleep(1);
return 0;
}
int Show_files(void)
{
  struct find_t ffblk;
  int done;
  done = _dos_findfirst("*.*",_A_NORMAL,&ffblk);
  while (!done) {
  if(!kbhit())
    {
    printf("\nFilename_> %s\n\t\t\tSize = %ld -bytes,\tdate stamp  = 0x%x\n",ffblk.name,ffblk.size,ffblk.wr_time);
    delay(100);
    done = _dos_findnext(&ffblk);
    }
    else
    {
    getch();
    printf("Press any key to continue");
    getch();
    }
  }
  return 0;
}
