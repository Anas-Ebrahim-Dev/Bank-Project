#pragma once
#include<iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
using namespace std;

class clsUpdateClientScreen : public clsScreen
{



private:

	static void _ReadUpdatedClientInfo(clsBankClient& Client)
	{

		Client.SetFirstName(clsInputValidate::ReadString("\nEnter FirstName : "));

		Client.SetLastName(clsInputValidate::ReadString("\nEnter LastName: "));

		Client.SetEmail(clsInputValidate::ReadString("\nEnter Email: "));

		Client.Setphone(clsInputValidate::ReadString("\nEnter Phone: "));

		Client.SetPinCode(clsInputValidate::ReadString("\nEnter PinCode: "));


	}


public:


	static bool UpdateClient()
	{

		DrawScreenHeader("Update Client Screen");

		string AccountNumber = clsInputValidate::ReadString("Please Enter AccountNumber : ");


		while (!(clsBankClient::IsClientFound(AccountNumber)))
		{

			AccountNumber = clsInputValidate::ReadString("Invalid Account . Please Enter AccountNumber : ");

		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);


		cout << Client.ToString();

		char Confirm = clsInputValidate::ReadChar("\nAre you sure to Update this client (Y/N) ? ");

		if (Confirm == 'Y' || Confirm == 'y')
		{
			_ReadUpdatedClientInfo(Client);
			clsBankClient::enSaveState SaveResult = Client.Save();
			switch (SaveResult)
			{
			case clsBankClient::Updated:
				cout << "\nClient Updated successfully . \n";
				cout << Client.ToString();
				return true;

			case clsBankClient::svFailed_EmptyClient:

				cout << "Failed to Update client (Empty client).";
				return false;

			case clsBankClient::svFailed_ClientNotExist:

				cout << "Failed to Update client (client Not exist).";
				return false;


			default:

				cout << "Failed to Update client .";
				return false;

			}

		}
		else
		{
			cout << "Update has been cancelled .\n";
			return false;

		}

		


		

		







	}




};

