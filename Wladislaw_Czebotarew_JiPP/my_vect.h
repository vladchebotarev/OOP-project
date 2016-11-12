#pragma once

#include "my_mess.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

template <class T> class my_vect
{
	T *dat;										//wskaznik do danych typu ogolnego
	size_t ndim;								//rozmiar tablicy, na ktory pozostala zaalokowana
	size_t last;								//wskazuje na pierwsza pusta pozycje w tablice
	my_mess msg;
	fstream flinp;
	char filename[FILENAME_MAX];
	bool alloc();
	bool my_realloc();
	char* conv_to_excel(stringstream & strm);

public:
	my_vect(size_t dm);							//konstruktor - alokuje pamiec dla tablicy typu T na dm elementow
	my_vect() { dat = NULL; ndim = last = 0; }
	~my_vect();
	void init(size_t dm);						//alokuje pamiec o dm elementow, jesli dat = NULL
	T *get_begin();								//zwraca wskaznik na poczatek
	T *get_end();								//zwraca wskaznik na koniec
	void disp();								//wyswietla tablice
	void push(const T &ob);						//dodaje element typu T do pierwszej wolnej pozycji w tablice
	T *pop();									//zwraca wskaznik do ostatniego elementu tablicy i usuwa jego, lub NULL (tablica pusta)
	T & operator [] (const size_t ind); 
	void remove(size_t ind);					//usuwa element tablicy o indeksie ind, kompresuje tablicu
	void insert(const T &ob, size_t ind);		//wstawia element ob w tablicê odrazu po elemencie dat[ind]
	void insert(const T &ob, size_t ind, size_t numb);  // wstawia tablice elementow "ob" (o rozmiarze numb) w tablice "dat" po elemencie "dat[ind]"
	void clear_all();							//usuniêcie wszystkich elementów tablicy
	bool Prep_excel();							//wyprowadzenie danych formacie Excel (*.csv)
	bool save();
	bool read();
	void modify(size_t ind, const T & ob);
	bool is_empty();


};

template <class T>
my_vect<T> ::my_vect(size_t dm)
{
	ndim = dm;
	if (!alloc())
		msg.mess(my_mess::ERR_ALLOC_MEM);
	else
		last = dm;
}


template<class T>
my_vect<T>::~my_vect()
{
	delete[] dat;
}



template<class T>
bool my_vect<T>::alloc()
{
	try
	{
		dat = new T[ndim];
		return 1;
	}
	catch (bad_alloc)
	{
		return 0;
	}
}


template<class T>
void my_vect<T>::init(size_t dm)
{
	if (!dat)
	{
		ndim = dm;
		if (!alloc())
			msg.mess(my_mess::ERR_ALLOC_MEM);
		else
			last = 0;
		sprintf_s(filename, "plik.dat");
	}
	else
		return;
}


template<class T>
T * my_vect<T>::get_begin()
{
	return dat;
}

template<class T>
T * my_vect<T>::get_end()
{
	return &dat[last];
}

template<class T>
void my_vect<T>::disp()
{
	if (last > 0)
	{
		size_t it;
		for (it = 0; it < last; it++)
		{
			cout << "it = " << it << " :  " << dat[it] << endl;
		}
	}
	else
		msg.mess(my_mess::WARN_ARR_EMPT);
}


template<class T>
void my_vect<T>::push(const T &ob)
{
	if (last >= ndim)
	{
		msg.mess(my_mess::WARN_ARR_FULL);
		if (!my_realloc())
			msg.mess(my_mess::ERR_ALLOC_MEM);
	}
	dat[last] = ob;
	last++;
}



template<class T>
T * my_vect<T>::pop()
{
	if (last > 0)
	{
		last--;
		return &dat[last];
	}
	else
	{
		return NULL;
	}
}



template<class T>
T & my_vect<T>::operator [] (const size_t ind)
{
	if (!dat || ind < 0 || ind >= last)
	{
		msg.mess(my_mess::ERR_ARR_POINTER);
	}
	return dat[ind];
}


template<class T>
void my_vect<T>::remove(size_t ind)
{
	if (last == 0)
	{
		msg.mess(my_mess::WARN_ARR_EMPT);
		return;
	}

	if (ind < 0 || ind >= last)
	{
		msg.mess(my_mess::ERR_ARR_POINTER);
		return;
	}


	for (int i = ind; i < last; ++i){
		if (ind != last - 1){
			dat[i] = dat[i + 1]; //SF jesli ind == last-1, wtedy i+1 = last - pierwszy element poza zakresem danych umieszczonych w tablice    ???
		}
	}
	last--;
}


template<class T>
bool my_vect<T>::my_realloc()
{
	ndim += 20;
	T* temp;

	try
	{
		temp = new T[ndim];
	}

	catch (bad_alloc)
	{
		return 0;
	}

	for (int i = 0; i < last; i++)
		temp[i] = dat[i];
	delete[] dat;

	dat = temp;
	return 1;
}




template <class T>
bool my_vect<T>::read()
{
	
	char tmpstr[512];
	size_t tmplast;
	flinp.open(filename, ios::in | ios::binary);
	if (!flinp.is_open())
		msg.mess(my_mess::ERR_FILE_OPEN);
	T tmp;
	last = 0;

	flinp.read(tmpstr, static_cast<streamsize>(sizeof(char)* 512));
	if (flinp.bad() || flinp.fail() || flinp.gcount() != sizeof(char)* 512)
		msg.mess(my_mess::ERR_FILE_READ);

	
	if ((strcmp(tmpstr, typeid(tmp).name())) != 0)
	{
		msg.mess(my_mess::WARN_FILE_READ_TYPE);
		return false;
	}

	flinp.read(reinterpret_cast<char *>(&tmplast), static_cast<streamsize>(sizeof(size_t)));
	if (flinp.bad() || flinp.fail() || flinp.gcount() != sizeof(size_t))
		msg.mess(my_mess::ERR_FILE_READ);

	for (size_t i = 0; i < tmplast && !flinp.eof(); ++i)
	{
		flinp >> &tmp;
		if (flinp.eof())
			break;
		push(tmp);
	}
	flinp.close();
	return true;
}



template <class T>
bool my_vect<T>::save()
{
	if (last == 0)
	{
		msg.mess(my_mess::WARN_ARR_EMPT);
		return 0;
	}
	flinp.open(filename, ios::out | ios::binary | ios::trunc); //SF ios::trunc, plik moze juz istniec i zawierac wiecej rekordow od tych, ktore stworza nasze dane przy zapisie.

	if (!flinp.is_open())
		msg.mess(my_mess::ERR_FILE_OPEN);

	char temp[512];
	sprintf_s(temp, typeid(T).name());

	flinp.write(temp, static_cast<streamsize>(sizeof(char)* 512));	
	if (flinp.bad() || flinp.fail())
		msg.mess(my_mess::ERR_FILE_WRITE);

	

	flinp.write(reinterpret_cast<char *>(&last), static_cast<streamsize>(sizeof(size_t)));	
	if (flinp.bad() || flinp.fail())
		msg.mess(my_mess::ERR_FILE_WRITE);

	for (int i = 0; i < last; ++i)
	{
		flinp << &dat[i];
		
	}
	flinp.close();
	return true;
}



template <class T>
void my_vect<T>::clear_all()
{
	delete[] dat;
	dat = NULL;
	init(ndim);
}



template <class T>
void my_vect<T>::modify(size_t ind, const T & ob)
{
	dat[ind] = ob;
}



template <class T>
void my_vect<T>::insert(const T &ob, size_t ind)
{
	if (ind == last + 1) push(ob);
	else if (ind > last + 1)
		msg.mess(my_mess::WARN_ARR_SMALL);
	else
	{
		if (last + 1 >= ndim)
		{
			msg.mess(my_mess::WARN_ARR_FULL);
			if (!my_realloc())
				msg.mess(my_mess::ERR_ALLOC_MEM);
		}

		
		last++;
		for (int i = last; i > ind; i--)
			dat[i] = dat[i - 1];
		dat[ind] = ob;

	}
}

template <class T>
void my_vect<T>::insert(const T &ob, size_t ind, size_t numb)
{
	

	if (ind > last + 1)
		msg.mess(my_mess::WARN_ARR_SMALL);
	else
	{
		if ((last + numb) >= ndim)
		{
			msg.mess(my_mess::WARN_ARR_FULL);
			if (!my_realloc())
				msg.mess(my_mess::ERR_ALLOC_MEM);
		}


		size_t i;

		for (i = (last); i > ind; i--)
			dat[i + numb - 1] = dat[i - 1];
		for (i = 0; i<numb; i++)
			dat[i + ind] = (&ob)[i];

		last += numb;
	}

}

template <class T>
bool my_vect<T>::Prep_excel()
{
	if (last == 0)
	{
		msg.mess(my_mess::WARN_ARR_EMPT);
		return 0;
	}
	fstream flinp;
	stringstream tmpStream;
	tmpStream.clear();
	flinp.open("excel_export.csv", ios::out);
	if (!flinp.good())
		msg.mess(my_mess::ERR_FILE_OPEN);

	for (int i = 0; i < last; ++i)
	{
		tmpStream << dat[i];
		if (i != last - 1)
			tmpStream << endl;
	}
	flinp << typeid(T).name() << endl;
	flinp << conv_to_excel(tmpStream);
	flinp.close();
	string openString = "start excel_export.csv"; 

	system(openString.c_str()); 

	return true;
}


template <class T>
char* my_vect<T>::conv_to_excel(stringstream & strm)
{
	string tmpString;
	char* tmpChar = NULL;
	size_t len;

	tmpString = strm.str();
	len = tmpString.length() + 1;

	try
	{
		tmpChar = new char[len];
	}
	catch (bad_alloc)
	{
		msg.mess(my_mess::ERR_ALLOC_MEM);
	}

	memcpy((void*)tmpChar, (void*)tmpString.c_str(), len);

	for (size_t i = 0; i < len; ++i)
	if (tmpChar[i] == ' ')
		tmpChar[i] = ';';

	return tmpChar;
}


template <class T>
bool my_vect<T>::is_empty()
{
	if (last == 0) return 1;
	else return 0;
}