#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtill.h"
#include <iomanip>
using namespace std;


void ReadUpdatedClientInfo(clsBankClient &Client)
{

    Client.SetFirstName(clsInputValidate::ReadString("\nEnter FirstName : "));

    Client.SetLastName(clsInputValidate::ReadString("\nEnter LastName: "));

    Client.SetEmail(clsInputValidate::ReadString("\nEnter Email: "));

    Client.Setphone(clsInputValidate::ReadString("\nEnter Phone: "));

    Client.SetPinCode(clsInputValidate::ReadString("\nEnter PinCode: "));


}
 void UpdateClient()
 { 

		string AccountNumber = clsInputValidate::ReadString("Please Enter AccountNumber : ");


		while (!(clsBankClient::IsFound(AccountNumber)))
		{

			AccountNumber = clsInputValidate::ReadString("Invalid Account . Please Enter AccountNumber : ");

		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);


		cout << Client.ToString();


		ReadUpdatedClientInfo(Client);
		

		Client.Save();

		cout << Client.ToString();







 }


 void ReadNewClientInfo(clsBankClient& Client)
 {

	 Client.SetFirstName(clsInputValidate::ReadString("\nEnter FirstName : "));

	 Client.SetLastName(clsInputValidate::ReadString("\nEnter LastName: "));

	 Client.SetEmail(clsInputValidate::ReadString("\nEnter Email: "));

	 Client.Setphone(clsInputValidate::ReadString("\nEnter Phone: "));

	 Client.SetPinCode(clsInputValidate::ReadString("\nEnter PinCode: "));

	 Client.SetBalance(clsInputValidate::ReadDoubleNumber("\nEnter balance : "));



 }
 void AddClient()
 {

	 cout << "Adding New Client . \n";


	 string AccountNumber = clsInputValidate::ReadString("Enter account number : ");

	 while (clsBankClient::IsFound(AccountNumber))
	 {
		 AccountNumber = clsInputValidate::ReadString("Account exist , Enter account number : ");
	 }



	 clsBankClient Client = clsBankClient::GetNewClient(AccountNumber);


	 ReadNewClientInfo(Client);


	 clsBankClient::enSaveState SaveResult = Client.Save();


	 switch (SaveResult)
	 {
	 case clsBankClient::Added:
		 cout << "Client added successfully . ";
		 Client.ToString();
		 break;

	 case clsBankClient::svFailed_EmptyClient:
		 cout << "Failed to add client (Empty client).";
		 break;
	 case clsBankClient::svFailed_ClientExists:
		 cout << "Failed to add client (client already exist).";
		 break;

	 default:
		 cout << "Failed to add client .";
		 break;
	 }





 }


 bool DeleteClient()
 {

	 cout << "Delete client . \n";

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
			 cout << "Client deleted successfully .";

			 return true;

		 }
		 else
		 {
			 cout << "Error occured . client was not deleted";
			 return false;

		 }
		 

	 }
	 else
	 {
		 cout << "Delete has been cancelled .";
		 return false;

	 }





 }


 void PrintOneClient(clsBankClient Client)
 {
	 cout << '|' << setw(15) << left << Client.GetAccountNumber()
		  << '|' << setw(22) << left << Client.GetFirstName() + " " + Client.GetLastName()
		  << '|' << setw(14) << left << Client.GetPhone()
		  << '|' << setw(25) << left << Client.GetEmail()
		  << '|' << setw(10) << left << Client.GetPinCode()
		  << '|' << setw(10) << left << Client.GetBalance() << '\n';


 }
 void DisplayClientsList()
 {

	 vector <clsBankClient> vClients = clsBankClient::GetClients();

	 cout << "\t\t\t\t\t Client list (" << vClients.size() << ") client(s) .\n";

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
		 PrintOneClient(Client);
	 }

	 cout << string(110, '-') << '\n';



 }


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




	DisplayBalancesList();




	return 0;

}

