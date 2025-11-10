#pragma once
#include<iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
using namespace std;


class clsFindClientScreen : public clsScreen
{


public:

	static bool FindClient()
	{

		DrawScreenHeader("Find Client Screen");

		string AccountNumber = clsInputValidate::ReadString("Please Enter AccountNumber : ");


		while (!(clsBankClient::IsFound(AccountNumber)))
		{

			AccountNumber = clsInputValidate::ReadString("Invalid Account . Please Enter AccountNumber : ");

		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);



		if (!(Client.IsEmpty()))
		{
			cout << "\nClient is found .\n";
			cout << Client.ToString();
			return true;
		}
		else
		{
			cout << "Client is Empty .\n";
			return false;

		}


	}





};

