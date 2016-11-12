#include "stdafx.h"
#include "node.h"
#include <fstream>


/*Domyslny*/
node::node() : mcoord()
{
	numb = 0;
	sprintf_s(str, "");
}


/*Sparemetrizowany*/
node::node(int nb, char *st, double xx, double yy) : mcoord(xx, yy)
{
	numb = nb;
	sprintf_s(str, 512 * sizeof(char), st);
}


/*Kopii*/
node::node(const node &ob) : mcoord(ob)
{
	//SF Вы это уже сделали в конструкторе копий базового класса. Здесь просто нужно его вызвать и не повторять написанных ранее линий кода
	/*if (ob.pcoord)
	{
		if (!pcoord)
			alloc();
			pcoord[0] = ob.pcoord[0];
			pcoord[1] = ob.pcoord[1];
	}

	else
	{
		if (pcoord)
			delete[] pcoord;
			pcoord = NULL;
	}*/

	
		
	numb = ob.numb;
	strcpy_s(str, 512 * sizeof(char), ob.str);
}






node & node::operator = (const node &ob)
{
	//SF То же самое
	/*if (ob.pcoord)
	{
		if (!pcoord)
			alloc();
		pcoord[0] = ob.pcoord[0];
		pcoord[1] = ob.pcoord[1];
	}
	else
	{
		if (pcoord)
			delete[] pcoord;
			pcoord = NULL;
	}*/


	*(mcoord*)this = *(mcoord*)&ob;
	
	numb = ob.numb;
	strcpy_s(str, 512 * sizeof(char), ob.str);

	return *this;
}

istream & operator >> (istream &strm, node &ob)
{
	cout << "X = ";
	strm >> ob.pcoord[0];

	cout << "Y = ";
	strm >> ob.pcoord[1];

	cout << "NUMBER = ";
	strm >> ob.numb;

	cout << "NAME : ";
	strm >> ob.str;

	return strm;
}

ostream & operator << (ostream &strm, const node &ob)
{
	strm << ob.pcoord[0] << " " << ob.pcoord[1] << " " << ob.numb << " " << ob.str;
	return strm;
}


fstream & operator << (fstream &strm, const node *ob)
{
	//SF moze, tak:
	//strm.write((char*)ob->pcoord, static_cast<streamsize>(2*sizeof(double)));
	//if (strm.bad() || strm.fail()) ....
	//zamiast nastepujacej petli

	
	
	/*for (int i = 0; i < 2; i++)
	{
		double temp = ob->pcoord[i];
		strm.write((char*)(&temp), static_cast<streamsize>(sizeof(double)));
		if (strm.bad() || strm.fail())
			ob->msg.mess(my_mess::ERR_FILE_WRITE);
	}*/


	strm.write((char*)ob->pcoord, static_cast<streamsize>(2 * sizeof(double)));
	if (strm.bad() || strm.fail())
		ob->msg.mess(my_mess::ERR_FILE_WRITE);

	strm.write((char*)(&ob->numb), static_cast<streamsize>(sizeof(int)));
	if (strm.bad() || strm.fail())
		ob->msg.mess(my_mess::ERR_FILE_WRITE);

	strm.write((char*)(&ob->str), static_cast<streamsize>(sizeof(char)* 512));
	if (strm.bad() || strm.fail())
		ob->msg.mess(my_mess::ERR_FILE_WRITE);
	return strm;
}


fstream & operator >> (fstream &strm, node *ob)
{
	for (int i = 0; i < 2; i++)
	{
		double temp;
		strm.read(reinterpret_cast<char *>(&temp), static_cast<streamsize>(sizeof(double)));
		if (strm.bad() || strm.fail() || strm.gcount() != sizeof(double))
			ob->msg.mess(my_mess::ERR_FILE_READ);
		ob->pcoord[i] = temp;
	}

	strm.read(reinterpret_cast<char *>(&ob->numb), static_cast<streamsize>(sizeof(int)));
	if (strm.bad() || strm.fail() || strm.gcount() != sizeof(int))
		ob->msg.mess(my_mess::ERR_FILE_READ);

	strm.read(reinterpret_cast<char *>(&ob->str), static_cast<streamsize>(sizeof(char)* 512));
	if (strm.bad() || strm.fail() || strm.gcount() != sizeof(char)* 512)
		ob->msg.mess(my_mess::ERR_FILE_READ);

	return strm;
}



bool node::operator == (const node & left) const
{
	return(pcoord[0] == left.pcoord[0] &&
		pcoord[1] == left.pcoord[1] &&
		numb == left.numb && (strcmp(str, left.str) == 0));
}