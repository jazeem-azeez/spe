/* Sample program that initializes the SuperVGA driver */

#include <stdio.h>
#include <conio.h>
#include <graphics.h>

#include "c:\spe\lib\svgautil.h"
#include "c:\spe\lib\svga16.h"
#include "c:\spe\lib\twk16.h"
#include "c:\spe\lib\twk256.h"
#include "c:\spe\lib\svga256.h"
#include "c:\spe\lib\svga32k.h"
#include "c:\spe\lib\svga64k.h"
#include "c:\spe\lib\svgatc.h"
#include "c:\spe\lib\svgas3.h"

/* Returns the color for white */
long WhitePixel()
{
  switch(getmaxcolor()) {
    case 32768: return 0x7fffL;
    case 65535: return 0xffffL;
    case 16777: return 0xffffffL;
    default   : return 15;
  };
}

int huge DetectVGA256()
{
  int Vid;

  printf("Which video mode would you like to use? \n");
  printf("  0) 320x200x256\n");
  printf("  1) 640x400x256\n");
  printf("  2) 640x480x256\n");
  printf("  3) 800x600x256\n");
  printf("  4) 1024x768x256\n");
  printf("  5) 640x480x256\n");
  printf("  6) 1280x1024x256\n");
  printf("\n> ");
  scanf("%d",&Vid);
  return Vid;
}

int huge DetectVGAS3()
{
  int Vid;

  printf("Which video mode would you like to use?\n");
  printf("  0) 640x480x256\n");
  printf("  1) 800x600x256\n");
  printf("  2) 1024x768x256\n");
  printf("  3) 800x600x16\n");
  printf("  4) 1024x768x16\n");
  printf("  5) 1280x960x16\n");
  printf("  6) 1280x1024x16\n");
  printf("  7) 640x480x32768\n");
  printf("> ");
  scanf("%d",&Vid);
  return Vid;
}
int huge DetectVGA64k()
{
  int Vid;

  printf("Which video mode would you like to use? \n");
  printf("  0) 320x200x65536\n");
  printf("  1) 640x350x65536\n");
  printf("  2) 640x400x65536\n");
  printf("  3) 640x480x65536\n");
  printf("  4) 800x600x65536\n");
  printf("  5) 1024x768x65536\n");
  printf("  6) 1280x1024x65536\n");
  printf("\n> ");
  scanf("%d",&Vid);
  return Vid;
}

int huge DetectVGA24bit()
{
  int Vid;

  printf("Which video mode would you like to use? \n");
  printf("  0) 320x200x24-bit\n");
  printf("  1) 640x350x24-bit\n");
  printf("  2) 640x400x24-bit\n");
  printf("  3) 640x480x24-bit\n");
  printf("  4) 800x600x24-bit\n");
  printf("  5) 1024x768x24-bit\n");
  printf("  6) 1280x1024x24-bit\n");
  printf("\n> ");
  scanf("%d",&Vid);
  return Vid;
}

int huge DetectVGA32k()
{
  int Vid;

  printf("Which video mode would you like to use? \n");
  printf("  0) 320x200x32768\n");
  printf("  1) 640x350x32768\n");
  printf("  2) 640x400x32768\n");
  printf("  3) 640x480x32768\n");
  printf("  4) 800x600x32768\n");
  printf("  5) 1024x768x32768\n");
  printf("  6) 1280x1024x32768\n");
  printf("\n> ");
  scanf("%d",&Vid);
  return Vid;
}

int huge DetectVGA16()
{
  int Vid;

  printf("Which video mode would you like to use? \n");
  printf("  0) 320x200x16\n");
  printf("  1) 640x200x16\n");
  printf("  2) 640x350x16\n");
  printf("  3) 640x480x256\n");
  printf("  4) 800x600x16\n");
  printf("  5) 1024x768x16\n");
  printf("  6) 1280x1024x16\n");
  printf("\n> ");
  scanf("%d",&Vid);
  return Vid;
}

int huge DetectTwk16()
{
  int Vid;

  printf("Which video mode would you like to use? \n");
  printf("  0) 704x528x16\n");
  printf("  1) 720x540x16\n");
  printf("  2) 736x552x16\n");
  printf("  3) 752x564x16\n");
  printf("  4) 768x576x16\n");
  printf("  5) 784x588x16\n");
  printf("  6) 800x600x16\n");
  printf("\n> ");
  scanf("%d",&Vid);
  return Vid;
};

int huge DetectTwk256()
{
  int Vid;

  printf("Which video mode would you like to use? \n");
  printf("  0) 320x400x256\n");
  printf("  1) 320x480x256\n");
  printf("  2) 360x480x256\n");
  printf("  3) 376x564x256\n");
  printf("  4) 400x564x256\n");
  printf("  5) 400x600x256\n");
  printf("  6) 320x240x256\n");
  printf("\n> ");
  scanf("%d",&Vid);
  return Vid;
};
   int huge DetectBGIVGA256()
{
 int Vid;
 /*
  printf("Which video mode would you like to use? \n");
  printf("  0) 320x200x256\n");
  printf("  1) 640x400x256\n");
  printf("  2) 640x480x256\n");
  printf("  3) 800x600x256\n");
  printf("  4) 1024x768x256\n");
  printf("  5) 640x480x256\n");
  printf("  6) 1280x1024x256\n");
  printf("\n> ");
  scanf("%d",&Vid);
  return Vid;*/
  return 3;
}

struct palettetype far *pal=(void *) 0;
struct palettetype initpal;

void initsvga()
{
  int  Gd = DETECT, Gm;
  int  Drv;
  char GrErr;
 installuserdriver("BGI256v2",DetectBGIVGA256);

 initgraph(&Gd,&Gm,"");

 GrErr = graphresult();
 if (GrErr != grOk)
 {
      printf("Graphics error: %s\n",grapherrormsg(GrErr));
      exit(1);
  }

pal=getdefaultpalette();

setcolor((WhitePixel()));
}
