#pragma once

class my_mess
{
public:
	enum MY_MESSAGE
	{
		ERR_ALLOC_MEM,     
		WARN_ARR_FULL,     
		WARN_ARR_EMPT,     
		WARN_ARR_UNKN,     
		WARN_ARR_SMALL,
		ERR_ARR_POINTER,
		ERR_FILE_OPEN,
		ERR_FILE_READ,
		ERR_FILE_WRITE,
		WARN_EXCEL_WRITE,
		WARN_FILE_READ_TYPE,
		WARN_CIN_FAIL,
		TOT_NUMB                 
	};

	static char *strtab[TOT_NUMB]; 

public:
	void mess(enum MY_MESSAGE ms)const;    
};