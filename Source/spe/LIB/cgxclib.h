/*****************************************
 * CGX Console Library			 *
 *****************************************
 * HELP ?
 * ======
 * sorry , The code can only compile in turbo c. If you write the
 * same for other compilers , please mail me.
 * 
 * A LIST OF FEW FUNCTIONS
 * -----------------------
 *  	void cgx_setcursorshape(int start,int end);
 *	___________________________________________
 * 
 *	sets the cursor shape. start is the starting point for
 *	the cursor and 'end' the end. I still don't know how the
 *	start and end works , but you can use the various #defintions
 *	...
 *	1. cgx_setnocursor 	: no cursor at all.
 *	2. cgx_setsolidcursor	: a solid cursor.
 *	3. cgx_setthincursor	: a thin cursor.
 *	4. cgx_setthickcursor	: a thick but not solid cursor
 *	5. cgx_settopcursor	: a cursor which is on top (this is cool!).
 *	6. cgx_setnormalcursor	: normal cursor
 *	___________________________________________
 *
 *	void cgx_gotoxy(int x,int y);
 *		
 *	Just like the gotoxy in conio.h file. (1,1) to (80,25)
 *	___________________________________________
 *
 *	int color(int backround,int foreground);
 *	
 *	returns the number code for a background and
 *	foreground. You can use the number codes
 *	defined in conio.h
 *	___________________________________________
 *
 *	void cgx_getcursorpos(int &x,int &y,int page=0);
 *	
 *	gets the cursor position and stores it in x and y.
 *	Note that the default page is 0 , but you can specify
 *	other page numbers too.
 *	___________________________________________
 *
 *	void cgx_setpage(int page=0);
 *
 *	Set the page number. Default page = 0.
 *	___________________________________________
 *
 *	void cgx_scrollup
 *		(int l = 0 , 
 *		 int ULx = 1  , int ULy = 1 , 
 *		 int LRx = 80 , int LRy = 25 , 
 *		 int attrib = color(BLACK,CYAN))
 *
 *	l = number of lines to scroll up. If l = 0 the function
 *	clears the whole thing.
 *
 *	ULx = The upper left x co-ord.
 *	ULy = The upper left y co-ord.
 *
 *	LRx = The lower right x co-ord.
 *	LRy = The lower right y co-ord.
 *
 *	attrib = attribute to set for the scrolled area.
 *	__________________________________________
 *
 *	void cgx_scrolldown(...)	
 *
 *	Does the same thing but downwards.
 *	__________________________________________
 *
 *	void cgx_getcharat(int x,int y,char &c , int &a , int page = 0)
 *
 *	Gets the character at position x,y of the screen and stores it int
 *	c along with its attributes in a. Page number by default is 0.
 *	__________________________________________
 *
 *	void cgx_putcharat(int x,int y,
 *		char c,int a=color(BLACK,CYAN),int page = 0)
 *
 *	Puts the char c at the position x,y with color a in page 0
 *	__________________________________________
 *
 *	void cgx_drawbox(int x1,int y1,int x2,int y2,
 *		int attrib=color(BLACK,CYAN))
 *
 *	Draws a box with a single border.
 *	__________________________________________
 *
 *	And many more for which no explanation is needed..
 *
 ******************************************************************************/
# include <stdio.h>
# include <conio.h>
# include <dos.h>

# define INT0x10	geninterrupt(0x10)

void cgx_setcursorshape(int start,int end){
	_AH = 0x1    ;	_CH = start  ;
	_CL = end    ;	INT0x10	     ;
}

#define cgx_setnocursor		cgx_setcursorshape(20,0)
#define cgx_setsolidcursor      cgx_setcursorshape(0,20)
#define cgx_setthincursor	cgx_setcursorshape(4,4 )
#define cgx_setthickcursor	cgx_setcursorshape(4,8 )
#define cgx_settopcursor	cgx_setcursorshape(3,3 )
#define cgx_setnormalcursor	cgx_setcursorshape(5,5 )

int color(int background,int foreground){
	return background*16+foreground;
}

/* (1,1) to (80,25) */

void cgx_gotoxy(int x,int y,int page=0){
	x-- ; y -- ;
	_AH = 0x02 ;
	_BH = page ; _DH = y    ;
	_DL = x    ; INT0x10	;
}

/* (1,1) to (80,25) */

void cgx_getcursorpos(int &x,int &y,int page=0){
	_AH = 0x03 ;	_BH = page ;
	INT0x10	   ;
	y = _DH	   ;	x = _DL    ;
	y ++	   ;	x ++	   ;
}

void cgx_setpage(int page=0){
	_AH = 0x05 ;	_AL = page ;
	INT0x10	   ;
}

void cgx_scrollup(int l = 0 , int ULx = 1  , int ULy = 1 , int LRx = 80 , int LRy = 25 , int attrib = color(BLACK,CYAN)){
	ULx-- ; ULy--; LRx--; LRy--;
	_AH = 0x06 ; _AL = l	; _BH = attrib;
	_CL = ULx  ; _CH = ULy  ;
	_DL = LRx  ; _DH = LRy  ;
	INT0x10	   ;
}

void cgx_scrolldown(int l = 0 , int ULx = 1  , int ULy = 1 , int LRx = 80 , int LRy = 25 , int attrib = color(BLACK,CYAN)){
	ULx-- ; ULy--; LRx--; LRy--;
	_AH = 0x07 ; _AL = l	; _BH = attrib;
	_CL = ULx  ; _CH = ULy  ;
	_DL = LRx  ; _DH = LRy  ;
	INT0x10	   ;
}

void cgx_clear(int ULx = 1 , int ULy = 1 , int LRx = 80 , int LRy = 25 , int attrib = color(BLACK,CYAN)){
	cgx_scrollup(0,ULx,ULy,LRx,LRy,attrib);
}

void cgx_getcharat(int x,int y,char &c , int &a , int page = 0){
	cgx_gotoxy(x,y) ;
	_AH = 0x08 ;	_BH = page ;
	INT0x10    ;	c = _AL	   ;
	a = _AH	   ;
}

void cgx_char(int c,int nor=1,int attrib=color(BLACK,CYAN),int page=0){
	_AH = 0x09 ;	_AL = c    ;
	_BL = attrib ;	_BH = page ;
	_CX = nor  ;
	INT0x10    ;
}

void cgx_putcharat(int x,int y,char c,int a=color(BLACK,CYAN),int page = 0){
	cgx_gotoxy(x,y) ;
	cgx_char(c,1,a,page);
}

void cgx_putscrchar(int c,int page = 0){
	_AH = 0x0A ;	_AL = c	   ;
	_BH = page ;	INT0x10	   ;
}

void cgx_textbordercolor(int color){
	_AH = 0xB  ;
	_BH = 0	   ;
	_BL = color;
}

void cgx_putchar(int c,int page=0){
	_AH = 0xE  ; _AL = c ;
	_BH = page ; _BL = 4 ; INT0x10 ;

}

const char horiz_line = 'Ä';
const char vert_line  = '³';
const char ul_corner  = 'Ú';
const char ur_corner  = '¿';
const char ll_corner  = 'À';
const char lr_corner  = 'Ù';

 void cgx_drawbox(int x1,int y1,int x2,int y2,int attrib=color(BLACK,CYAN)){
	cgx_setnocursor;
	cgx_gotoxy(x1,y1);
	for(int j=y1;j<=y2;++j)
		for(int i=x1;i<=x2;++i){
			     if(i==x1&&j==y1)   cgx_putcharat(i,j,ul_corner,attrib);
			else if(i==x1&&j==y2)   cgx_putcharat(i,j,ll_corner,attrib);
			else if(i==x2&&j==y1)   cgx_putcharat(i,j,ur_corner,attrib);
			else if(i==x2&&j==y2)   cgx_putcharat(i,j,lr_corner,attrib);
			else if(i==x1||i==x2)   cgx_putcharat(i,j,vert_line,attrib);
			else if(j==y1||j==y2)   cgx_putcharat(i,j,horiz_line,attrib);
			else			cgx_putcharat(i,j,' ',attrib);
		}
		cgx_setnormalcursor;
 }

