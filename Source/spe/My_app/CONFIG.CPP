void command(char para[32])
{
restorecrtmode();
textmode(0x3);
HideMouse();
system(para);

getch();
SetMode(_800x600,1);
setgraphmode(getgraphmode());
}
int Configure()
{
clearviewport();
glprintf("Command:-");
strcpy(msg," ");
gin();
if(strcmp(msg,"help")==0||strcmp(msg,"\?")==0)
	glprintf("sysinfo - system enviornment info");
else if(strcmp(msg,"sysinfo")==0)
	sysinfo();
else
	command(msg);
getch();
return 0;
}
