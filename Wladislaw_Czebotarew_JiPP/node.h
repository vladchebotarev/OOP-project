#pragma once
#include "mcoord.h"

class node : public mcoord
{
	int numb;       //numer wierzcho³ku
	char str[512];  //nazwa wierzcho³ku
public:
	node(int nb, char *st, double xx, double yy);
	node();
	node(const node & ob);
	node & operator = (const node &ob);
	friend istream & operator >> (istream &strm, node &ob);
	friend ostream & operator << (ostream &strm, const node &ob);
	friend fstream & operator << (fstream &strm, const node *ob);
	friend fstream & operator >> (fstream &strm, node *ob);
	bool operator == (const node & left) const;
};