#pragma once
#include"clsScreen.h"
#include "clsBankClient.h"
#include<iostream>
using namespace std;

class clsAddNewClientScreen : public clsScreen
{


private:

	static void _ReadNewClientInfo(clsBankClient& Client)
	{

		Client.SetFirstName(clsInputValidate::ReadString("\nEnter FirstName : "));

		Client.SetLastName(clsInputValidate::ReadString("\nEnter LastName: "));

		Client.SetEmail(clsInputValidate::ReadString("\nEnter Email: "));

		Client.Setphone(clsInputValidate::ReadString("\nEnter Phone: "));

		Client.SetPinCode(clsInputValidate::ReadString("\nEnter PinCode: "));

		Client.SetBalance(clsInputValidate::ReadDoubleNumber("\nEnter balance : "));



	}


public:


	static bool AddClient()
	{

		if (!(clsSession::CheckUserPermission(clsBankUser::enPermissions::AddNewClient)))
		{
			clsMessages::ShowAccessDeniedMessage();
			return false;
		}


		DrawScreenHeader("Adding New Client");


		string AccountNumber = clsInputValidate::ReadString("Enter account number : ");

		while (clsBankClient::IsClientFound(AccountNumber))
		{
			AccountNumber = clsInputValidate::ReadString("Account exist , Enter account number : ");
		}



		clsBankClient Client = clsBankClient::GetNewClient(AccountNumber);


		_ReadNewClientInfo(Client);


		clsBankClient::enSaveState SaveResult = Client.Save();


		switch (SaveResult)
		{
		case clsBankClient::Added:
			cout << "\nClient added successfully . \n";
			cout << Client.ToString();
			return true;

		case clsBankClient::svFailed_EmptyClient:
			cout << "Failed to add client (Empty client).";
			return false;
			
		case clsBankClient::svFailed_ClientExists:
			cout << "Failed to add client (client already exist).";
			return false;

		default:
			cout << "Failed to add client .";
			return false;
			
		}





	}




};

