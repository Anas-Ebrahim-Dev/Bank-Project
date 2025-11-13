#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsUtil.h"
#include <iomanip>

using namespace std;

class clsTotalBalancesScreen :public clsScreen
{




private:

	static void PrintOneClientBalance(clsBankClient Client)
	{
		cout << '|' << setw(15) << left << Client.GetAccountNumber()
			<< '|' << setw(22) << left << Client.GetFirstName() + " " + Client.GetLastName()
			<< '|' << setw(10) << left << Client.GetBalance() << '\n';

	}


public:


	static void DisplayBalancesList()
	{

		vector <clsBankClient> vClients = clsBankClient::GetClients();


		string Tittle = "Balances List ";
		string SubTittle = " Client list (" + to_string(vClients.size()) + ") client(s) .";

		DrawScreenHeader(Tittle, SubTittle);

		cout << string(60, '-') << '\n';

		cout << '|' << setw(15) << left << "Account Number"
			 << '|' << setw(22) << left << "Client Name"
			 << '|' << setw(10) << left << "Balance" << '\n';

		cout << string(60, '-') << '\n';


		if (vClients.size() == 0)
		{
			cout << "\t\t\t\t\tNo clients found . ";
			cout << string(60, '-') << '\n';
			return;
		}



		for (clsBankClient& Client : vClients)
		{
			PrintOneClientBalance(Client);
		}

		cout << string(60, '-') << '\n';

		double TotalBalances = clsBankClient::GetTotalBalances();

		cout << "\t\t Total Balances = " << TotalBalances << '\n';
		cout << "\t\t" << clsUtill::NumberToWords(TotalBalances) << '\n';



	}



};

