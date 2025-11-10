#pragma once
#include "clsScreen.h"
#include <iostream>
#include"clsBankClient.h"
#include <iomanip>

using namespace std;

class clsListClientsScreen : public clsScreen
{

private:


	static void _PrintOneClient(clsBankClient Client)
	{
		cout << '|' << setw(15) << left << Client.GetAccountNumber()
			<< '|' << setw(22) << left << Client.GetFirstName() + " " + Client.GetLastName()
			<< '|' << setw(14) << left << Client.GetPhone()
			<< '|' << setw(25) << left << Client.GetEmail()
			<< '|' << setw(10) << left << Client.GetPinCode()
			<< '|' << setw(10) << left << Client.GetBalance() << '\n';


	}


public:



	static void DisplayClientsList()
	{

		vector <clsBankClient> vClients = clsBankClient::GetClients();

		string Tittle = "Clients List ";
		string SubTittle = " Client list (" + to_string(vClients.size()) + ") client(s) .";

		DrawScreenHeader(Tittle, SubTittle);
		 

		cout << string(110, '-') << '\n';

		cout << '|' << setw(15) << left << "Account Number"
			 << '|' << setw(22) << left << "Client Name"
			 << '|' << setw(14) << left << "Phone Number"
			 << '|' << setw(25) << left << "Email"
			 << '|' << setw(10) << left << "Pin Code"
			 << '|' << setw(10) << left << "Balance" << '\n';

		cout << string(110, '-') << '\n';


		if (vClients.size() == 0)
		{
			cout << "\t\t\t\t\tNo clients found . ";
			cout << string(110, '-') << '\n';
			return;
		}



		for (clsBankClient& Client : vClients)
		{
			_PrintOneClient(Client);
		}

		cout << string(110, '-') << '\n';



	}





};

