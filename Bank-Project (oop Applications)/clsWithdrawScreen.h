#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
using namespace std;

class clsWithdrawScreen :public clsScreen
{




public:


	static bool Withdraw()
	{

		DrawScreenHeader("WithDraw Screen ");

		string AccountNumber = clsInputValidate::ReadString("Enter account number : ");

		while (!(clsBankClient::IsFound(AccountNumber)))
		{
			AccountNumber = clsInputValidate::ReadString("Client dosen't exist . Enter account number : ");
		}


		clsBankClient Client = clsBankClient::Find(AccountNumber);

		cout << Client.ToString();


		double Amount = clsInputValidate::ReadDoubleNumber("Please Enter Withdraw Amount : ");

		char Confirm = clsInputValidate::ReadChar("\nAre you sure You Want Perform this Transaction (Y/N) ? ");



		if (Confirm == 'Y' || Confirm == 'y')
		{
			if (Client.Withdrwa(Amount))
			{
				cout << "The Transaction was completed successfully. \n";
				cout << "New balance is :" << Client.GetBalance() << '\n';
				Client.Save();
				return true;

			}
			else
			{
				cout << " Transaction Failed .\n";
				return false;

			}


		}
		else
		{
			cout << "Transaction has been cancelled .\n";
			return false;

		}




	}

};

