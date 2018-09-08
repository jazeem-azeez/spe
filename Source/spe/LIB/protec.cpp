//**************************************
//     
// Name: ^!A dos based Turbo"C" program 
//     (TSR) to Lock / Unlock Floppy Drivers...
//     .(with full source code)
// Description:Dos based TSR program to 
//     Disable/Enable floppy drives.
//
// Side Effects:Not compatible under windows
//

/*
nofloppy.c written in "Turbo C" for Advance User
TSR program to disable floppy Drives A: & B:

email:	 computer_bazzar@rediffmail.com
(don't send me email for any query,except Bug)
if possible send me a updated or advance version of this program. use can use,modify or redistribute this program freely
PLEASE VOTE for ME !!!!
REMEMBER:
(1)Never change the extension of this program to .cpp. 
(2) this program in meant for DOS (not for windows)
(3) this program will never compile in TC window. You have to use TCC compiler at dos prompt. This tcc.exe file will be present in TC folder. You don't need to copy this file 	from hell
	c:\tc> tcc nofloppy.c
(4)all the ".h" ".obj" files must be present in the current directory
(5)tasm.exe, tlink.exe files must be present in the current directory
(6)you will have to change <> to "" in ur program
for example insted of using <dos.h> u have to use "dos.h" also u have to change this <> to "" in ur dos.h or all calling .h files,simply open dos.h in any text editior and change all <> sign that call other .h files. You have to repeat this method with all ur calling .h files.
(7)it is better to copy all files in current directory c:\tc> copy bin (this will copy all files from c:\tc\bin)c:\tc> copy inlcude (this will copy all files from c:\tc\include)	c:\tc> copy lib (this will copy all files from c:\tc\lib)
*///////////////////////////////////////////////////////////////////
#pragma inline /* dodn't remove this line */
**************************************************/
#include <fcntl.h>
#include <io.h>
#include "dos.h"
#include "stdio.h"
#include "conio.h"
#include <string.h>
#include <process.h>
#define SUCCESS 0XC0FF
#define FAILURE 0XC000
union REGS _i,__o;
void interrupt (*old)();
struct INTERRUPT


    {
    	unsigned bp,di,si,ds,es,dx,cx,bx,ax,ip,cs,fl;
};
void interrupt disk (struct INTERRUPT);
int tsrc;
unsigned our_psp;
void interrupt our_1c();
void interrupt (*prev_1c)();
void interrupt our_2f(struct INTERRUPT);
void interrupt (*prev_2f)();
main(int argc,char *argv[])


    {
    int far *ebptr;
    strupr(argv[1]);
    tsrc=strcmp(argv[1],"UNLOAD");
    if(tsrc!=0)


        		{
        _i.x.ax=0xc000;
        int86(0x2f,&_i,&__o);
        if(__o.x.ax!=SUCCESS)


            			{
            our_psp=getpsp();
            res();
            ebptr=MK_FP(our_psp,0x2c);
            freemem(*ebptr);
            printf("\Nofloppy v(1.0) Installed Successfully....\n");
            keep(0,2500);
            /* if u want to use automatic memory allocation use next line*/
            /*keep(0,(_SS+(_SP/16)-_psp));*/
            			}
            printf("\nfor unloading nofloppy use -> nofloppy unload \n");
            printf("\n Nofloppy v(1.0) already Loaded.....");
        }
        else


            		{
            _i.x.ax=0xc000;
            int86(0x2f,&_i,&__o);
            if(__o.x.ax==SUCCESS)


                {
                _i.x.ax=0xc001;
                int86(0x2f,&_i,&__o);
                if(__o.x.ax==FAILURE)
                printf("\nCannot uninstall Nofloppy v(1.0),another program on top\n");
                else
                printf("\nNofloppy ver(1.0) Uninstalled");
            }
            else
            printf("\nNofloppy ver(1.0) NOT IN MEMORY");
        }
        return 0;
    }
    res()


        {
        prev_1c=getvect(0x1c);
        setvect(0x1c,our_1c);
        prev_2f=getvect(0x2f);
        setvect(0x2f,our_2f);
        old=getvect(0x13);
        setvect(0x13,disk);
        return 0;
    }
    void interrupt disk(struct INTERRUPT r)


        {
        	if (_DL==0 || _DL==1)


            	{
            	asm clc;
            	asm pushf
            	asm pop r.fl
            	return;
            	}
            _ES=r.es;
            _DX=r.dx;
            _CX=r.cx;
            _BX=r.bx;
            _AX=r.ax;
            (*old)();
            asm pushf
            asm pop r.fl;
            r.ax=_AX;
            r.bx=_BX;
            r.cx=_CX;
            r.dx=_DX;
            r.es=_ES;
        }
        void interrupt our_1c()


            {
            (*prev_1c)();
        }
        void interrupt our_2f(struct INTERRUPT r)


            {
            if(r.ax==0xc000)


                {
                r.ax=SUCCESS;
                return;
            }
            if(r.ax==0xc001)


                {
                r.ax=uninstall();
                return;
            }
            asm pop bp
            asm pop di
            asm pop si
            asm pop ds
            asm pop es
            asm pop dx
            asm pop cx
            asm pop bx
            asm pop ax
            asm jmp cs:_prev_2f;
        }
        int uninstall()


            {
            if(our_1c==getvect(0x1c) && our_2f==getvect(0x2f)&&disk==getvect(0x13))


                {
                setvect(0x1c,prev_1c);
                setvect(0x2f,prev_2f);
                setvect(0x13,old);
                freemem(our_psp);
                return(SUCCESS);
            }
            else
            return(FAILURE);
        }
        /**************************************************/

unsigned char buffer[3];
FILE *fd;
int handle;
fail(char *);
void pass(char *);
main(int argc,char *argv[])


    {
    int n;
    if(argc!=3)


        {
        printf("\nFailpass Utility v1.0 Email: chingpongin@yahoo.co.in");
        printf("\nEnable/Disable .EXE or .COM execution");
        printf("\nsyntex failpass fail <filename.extension>");
        printf("\n		 or");
        printf("\n	 failpass pass <filename.extension>");
        exit(2);
    }
    strupr(argv[1]);
    n=strcmp(argv[1],"FAIL");
    if(n==0)


        {
        fail(argv[2]);
        exit(2);
    }
    n=strcmp(argv[1],"PASS");
    if(n==0)


        {
        pass(argv[2]);
        exit(2);
    }
    return 0;
}
fail(char *fname)


    {
    _chmod(fname,1,FA_ARCH);
    fd=fopen(fname,"rb+");
    if(fd==NULL)


        {
        printf("\nCann't open %s\n\n",fname);
        exit(2);
    }
    fseek(fd,0,SEEK_SET);
    fread(buffer,2,1,fd);
    if(buffer[0]==0xcd)
    if(buffer[1]==0x20)


        {
        fclose(fd);
        printf("\n%s already protected...\n\n",fname);
        exit(2);
    }
    fseek(fd,0,SEEK_END);
    fwrite(buffer,2,1,fd);
    fseek(fd,0,SEEK_SET);
    buffer[0]=0xcd; /* don't take any PANGA with this line */
    buffer[1]=0x20; /* don't take any PANGA with this line */
    fwrite(buffer,2,1,fd);
    fclose(fd);
    return 0;
}
void pass(char *fname)


    {
    int xyz;
    fd=fopen(fname,"rb+");
    if(fd==NULL)


        {
        fclose(fd);
        printf("\nCannot open file %s\n\n",fname);
        exit(2);
    }
    fseek(fd,0,SEEK_SET);
    fread(buffer,2,1,fd);
    if(buffer[0]!=0xcd)
    if(buffer[1]!=0x20)


        {
        fclose(fd);
        printf("\n%s is NOT protected....\n\n",fname);
        exit(2);
    }
    fseek(fd,-2,SEEK_END);
    fread(buffer,2,1,fd);
    fseek(fd,0,SEEK_SET);
    fwrite(buffer,2,1,fd);
    fclose(fd);
    handle=open(fname,O_RDWR);
    chsize(handle,(filelength(handle))-2);
    close(handle);
}
/*******************************/


