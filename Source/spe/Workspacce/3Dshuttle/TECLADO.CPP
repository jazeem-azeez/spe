#include <conio.h>

int INSERTAR=1;
#define NORMAL 0
#define EXTENDIDO 1


#define NOKEY		0

#define ESCAPE		27
#define BACKSPACE	8
#define ENTER		13
#define TAB			9
#define SHIFT_TAB	0x0F00
#define INSERT		0x5200
#define DELETE		0x5300
#define HOME		0x4700
#define END			0x4F00
#define F_IZQ		0x4B00
#define F_DER		0x4D00
#define F_ARR		0x4800
#define F_ABA		0x5000
#define CTRL_F_IZQ	0x7300
#define CTRL_F_DER	0x7400



int leertecla(void)
{
	union {
		unsigned int tecla;
		unsigned char caracter[2];
	};

	tecla = NOKEY;
	caracter[NORMAL] = (char)getch();
	if (!caracter[NORMAL]) caracter[EXTENDIDO] = (char) getch();

	return tecla;
}