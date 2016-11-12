#pragma once

#include "my_mess.h"
#include <iostream>

using namespace std;

class mcoord
{
protected:
	double *pcoord;  //pcoord[0] -x ; pcoord[1] - y
	my_mess msg;
	void alloc();
public:
	mcoord() { alloc(); pcoord[0] = pcoord[1] = 0; }     //konsruktor domyslny	
	mcoord(double x, double y);							//sparametryzowany
	mcoord(const mcoord & ob);
	~mcoord();
	mcoord & operator = (const mcoord &ob);
	friend istream & operator >> (istream &strm, mcoord &ob);
	friend ostream & operator << (ostream &strm, const mcoord &ob);
	friend fstream & operator << (fstream &strm, const mcoord *ob);
	friend fstream & operator >> (fstream &strm, mcoord *ob);
	bool operator == (const mcoord & left) const;

};




