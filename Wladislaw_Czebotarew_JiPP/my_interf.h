#pragma once

#include "my_vect.h"
#include "mcoord.h"
#include "node.h"


typedef node variable; //a variable in container vect

class my_interf
{
public:
	enum MY_INTERF
	{
		MY_INTERF_PUSH,
		MY_INTERF_POP,
		MY_INTERF_CLROBJ,
		MY_INTERF_CLRALL,
		MY_INTERF_MODIFI,
		MY_INTERF_INSERT,
		MY_INTERF_INSERT_ARR,
		MY_INTERF_FIND,
		MY_INTERF_SAVE,
		MY_INTERF_READ,
		MY_INTERF_DISP,
		MY_INTERF_EXCEL,
		MY_INTERF_FINISH,
		MY_INTERF_TOT
	};
private:
	my_vect<variable> vect;
	char str_interf[MY_INTERF_TOT][512];  //komunikaty
	my_mess msg;

public:
	bool run;

	my_interf();
	my_interf(size_t dim);
	void menu();
	void push();
	void pop();
	void disp();
	void find();
	void save();
	void read();
	void finish();
	void defaul();
	void clear_all();
	void clear_object();
	void modification();
	void insert_obj();
	void insert_arr();
	void excel_exp();
};



template <typename T, typename K>
T* my_find(const T* p_begin, const T* p_end, const K &key)
{
	T* tmp = const_cast <T*> (p_begin);
	for (; tmp != p_end; ++tmp)
	if (*tmp == key)
		return tmp;
	return NULL;
}