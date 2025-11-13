#pragma once
#include <iostream>
using namespace std;

class clsScreen
{

protected:


	static void DrawScreenHeader(string Tittle ,string SubTittle = "")
	{

		cout << "-------------------------------------------\n";
		cout << "               " << Tittle << '\n';
		if (SubTittle != "")
		{
			cout << "           " << SubTittle << '\n';
		}
		cout << "-------------------------------------------\n\n";



	}



};

