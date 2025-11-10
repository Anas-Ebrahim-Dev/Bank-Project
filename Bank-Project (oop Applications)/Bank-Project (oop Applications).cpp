#include <iostream>
#include <iomanip>
#include "clsUtill.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"

using namespace std;



 void PrintOneClientBalance(clsBankClient Client)
 {
	 cout << '|' << setw(15) << left << Client.GetAccountNumber()
		  << '|' << setw(22) << left << Client.GetFirstName() + " " + Client.GetLastName()
		  << '|' << setw(10) << left << Client.GetBalance() << '\n';

 }
 void DisplayBalancesList()
 {
	 vector <clsBankClient> vClients = clsBankClient::GetClients();

	 cout << "\t\t Client list (" << vClients.size() << ") client(s) .\n";

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




int main()
{




	clsMainScreen::StartBankSystem();







	return 0;

}

