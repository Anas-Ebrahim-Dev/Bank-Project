#pragma once
#include<iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
using namespace std;

class clsDeleteClientScreen : public clsScreen
{



public:

	static bool DeleteClient()
	{

		DrawScreenHeader("Delete Client Screen ");

		string AccountNumber = clsInputValidate::ReadString("Enter account number : ");

		while (!(clsBankClient::IsFound(AccountNumber)))
		{
			AccountNumber = clsInputValidate::ReadString("Client dosen't exist . Enter account number : ");
		}


		clsBankClient Client = clsBankClient::Find(AccountNumber);

		cout << Client.ToString();


		char Confirm = clsInputValidate::ReadChar("\nAre you sure to delete this client (Y/N) ? ");



		if (Confirm == 'Y' || Confirm == 'y')
		{
			if (clsBankClient::Delete(AccountNumber))
			{
				cout << "Client deleted successfully .\n";

				return true;

			}
			else
			{
				cout << "Error occured . client was not deleted\n";
				return false;

			}


		}
		else
		{
			cout << "Delete has been cancelled .";
			return false;

		}





	}


};

