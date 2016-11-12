#include "stdafx.h"
#include <iostream>
#include "my_mess.h"

using namespace std;

char *my_mess::strtab[] =
{
	"E  MEMORY ALLOC ERROR",          
	"W  ARRAY IS FULL",               
	"W  ARRAY IS EMPTY",              
	"W  INCORRECT OPERATION CODE",
	"W  ARRAY IS SMALL",
	"E  FAULTY POINTER TO ARRAY",
	"E	OPEN FILE ERROR",
	"E	READ FILE ERROR",
	"E  SAVE FILE ERROR",
	"W  EXPORT TO EXCEL ERROR",
	"W  FAULTY FILE TYPE",
	"W  CIN ERROR"
};

void my_mess::mess(enum MY_MESSAGE ms) const
{
	if (strtab[ms][0] == 'E')
	{
		cout << "ERROR: " << &strtab[ms][1] << endl;
		system("pause");
		exit(1);
	}
	else if (strtab[ms][0] == 'W')
	{
		cout << "WARNING: " << &strtab[ms][1] << endl;
	}
}