// Wladislaw_Czebotarew_JiPP.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "my_interf.h"

int _tmain(int argc, _TCHAR* argv[])
{
	int op; 
	my_interf ifc(1);

	while (ifc.run)
	{
		ifc.menu();

		cin >> op;

		switch (op)
		{
		case my_interf::MY_INTERF_PUSH: //push
			ifc.push();
			break;
		case my_interf::MY_INTERF_POP:	//pop
			ifc.pop();
			break;
		case my_interf::MY_INTERF_DISP:	//display
			ifc.disp();
			break;
		case my_interf::MY_INTERF_SAVE:	//data save
			ifc.save();
			break;
		case my_interf::MY_INTERF_READ:	//data read
			ifc.read();
			break;
		case my_interf::MY_INTERF_FIND:	//find an object
			ifc.find();
			break;
		case my_interf::MY_INTERF_CLRALL: // clear all objects
			ifc.clear_all();
			break;
		case my_interf::MY_INTERF_FINISH: // close the program
			ifc.finish();
			break;
		case my_interf::MY_INTERF_CLROBJ: // delete one object
			ifc.clear_object();
			break;
		case my_interf::MY_INTERF_MODIFI: //modify one object
			ifc.modification();
			break;
		case my_interf::MY_INTERF_INSERT: //insert one object
			ifc.insert_obj();
			break;
		case my_interf::MY_INTERF_INSERT_ARR: // insert array of objects
			ifc.insert_arr();
			break;
		case my_interf::MY_INTERF_EXCEL: // data export to excel and open an excel sheet
			ifc.excel_exp();
			break;
		default:
			ifc.defaul();
			break;
		};
	}

	
	system("pause");
	return 0;
}