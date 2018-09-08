/*PARTS
=====
1. Create a dynamic data base that can be used along with SPE
:Which returns data related to a particular object
2.A seperate exe file which works one a dbf file
:has the ability to modify the database
Employes A Calculator(SIMPLE )
*/

//headers
#include <stdio.h>
#include <conio.h>
#include <string.h>

typedef char string[32];
string general_index[16];
class database
{
public:
	struct records
	{
	string value[16];
	struct record *ptr;
	};
	
	};
	database()
	{
	}
	~database()
	{
	delete records;
	}

};
int database :: database(char *str)
{
FILE *in;
int no_of_records,
in=fopen(str,"r+")
while (!feof(in))
{
//putchar(fgetc(in));
for
}


}


int check_file()
{
return -1;
}

void main()
{
check_file ();
database_init();
}