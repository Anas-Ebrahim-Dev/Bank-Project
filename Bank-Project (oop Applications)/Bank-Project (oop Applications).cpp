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




int main()
{







	return 0;

}

