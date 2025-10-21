#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
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



	 clsBankClient Client(clsBankClient::enState::Add, "", "", "", "", AccountNumber, "", 0);


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



int main()
{

	AddClient();






	return 0;

}

