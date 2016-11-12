#include "stdafx.h"
#include "mcoord.h"
#include <fstream>


/*Alokowanie pamieci*/
void mcoord::alloc()
{
	try
	{
		pcoord = new double[2];
	}
	catch (bad_alloc)
	{
		msg.mess(my_mess::ERR_ALLOC_MEM);
	}
}


/*Konstruktor sparametryzowany*/
mcoord::mcoord(double x, double y)
{
	alloc();

	pcoord[0] = x;
	pcoord[1] = y;
}


/*Konstruktor kopii*/
mcoord::mcoord(const mcoord & ob)
{	
	
	if (ob.pcoord){
		alloc();
		pcoord[0] = ob.pcoord[0];
		pcoord[1] = ob.pcoord[1];
	}

	else{
		pcoord[0] = pcoord[1] = 0;
	}
}


/*Destruktor*/
mcoord::~mcoord()
{
	if (pcoord){
		delete[] pcoord;
		pcoord = NULL;
	}
}



mcoord & mcoord::operator = (const mcoord &ob)
{

	
	if (ob.pcoord)
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
	}
	
	return *this;
}



istream & operator >> (istream &strm, mcoord &ob)
{
	cout << "X = ";
	strm >> ob.pcoord[0];

	cout << "Y = ";
	strm >> ob.pcoord[1];
	return strm;
}



ostream & operator << (ostream &strm, const mcoord &ob)
{
	strm << ob.pcoord[0] << " " << ob.pcoord[1];
	return strm;
}




fstream & operator << (fstream &strm, const mcoord *ob)
{
	for (int i = 0; i < 2; i++)
	{
		double temp = ob->pcoord[i];
		strm.write((char*)(&temp), sizeof(double));
		if (strm.bad() || strm.fail())
		{
			cout << "ERROR!!!";
		}
	}
	return strm;
}



fstream & operator >> (fstream &strm, mcoord *ob)
{
	for (int i = 0; i < 2; i++)
	{
		double temp;
		strm.read((char*)(&temp), sizeof(double));
		if (strm.bad() || strm.fail() || strm.gcount() != sizeof(double))
		{
			cout << "ERROR!!!";
		}
		ob->pcoord[i] = temp;
	}
	return strm;
}



bool mcoord::operator == (const mcoord & left) const
{
	return(pcoord[0] == left.pcoord[0] && pcoord[1] == left.pcoord[1]);
}