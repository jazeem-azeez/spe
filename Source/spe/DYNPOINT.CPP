// Borland C++ - (C) Copyright 1991 by Borland International

// DPOINT.CPP -- exercise in Getting Started

#include <iostream.h>
#include <graphics.h>
#include <conio.h>
#include "figures.h"

int main()
{
// Assign pointer to dynamically allocated object; call constructor
Point *APoint = new Point(50, 100);

// initialize the graphics system
int graphdriver = DETECT, graphmode;
initgraph(&graphdriver, &graphmode, "..\\bgi");

// Demonstrate the new object
APoint->Show();
cout << "Note pixel at (50,100). Now, hit any key...";
getch();
delete APoint;
closegraph();
return(0);
}
