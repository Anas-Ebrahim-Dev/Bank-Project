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


		if (!(clsSession::CheckUserPermission(clsBankUser::enPermissions::FindClient)))
		{
			clsMessages::ShowAccessDeniedMessage();
			return false;
		}



		DrawScreenHeader("Find Client Screen");

		string AccountNumber = clsInputValidate::ReadString("Please Enter AccountNumber : ");


		while (!(clsBankClient::IsClientFound(AccountNumber)))
		{

			AccountNumber = clsInputValidate::ReadString("Invalid Account . Please Enter AccountNumber : ");

		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);



		if (Client.IsActive())
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

