#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"

using namespace std;

const string FileName = "BankClients.txt";

class clsBankClient : public clsPerson
{


public:

	enum enState { Empty = 0, Loded = 1 };


private:

	string _AccountNumber;
	string _PinCode;
	double _Balance;
	enState _State;


private:

	static clsBankClient _ConvertLineToClient(string Line)
	{
		vector <string> vFelids;

		vFelids = clsString::vSplit(Line, "#//#");


		return  clsBankClient(enState::Loded, vFelids[0], vFelids[1], vFelids[2], vFelids[3], vFelids[4], vFelids[5], stod(vFelids[6]));

	}

	static clsBankClient _EmptyClient()
	{
		return clsBankClient(enState::Empty, "", "", "", "", "", "", 0);
	}


public:


	clsBankClient(enState State , string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, double Balance) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_Balance = Balance;
		_State = State;
	}


	string GetAccountNumber()
	{
		return _AccountNumber;
	}


	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;

	}
	string GetPinCode()
	{
		return _PinCode;
	}


	double GetBalance()
	{
		return _Balance;
	}


	void SetState(enState State)
	{
		_State = State;

	}
	enState GetState()
	{
		return _State;

	}

	void Print()
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << GetFirstName();
		cout << "\nLastName    : " << GetLastName();
		cout << "\nFull Name   : " << GetFirstName() + " " + GetLastName();
		cout << "\nEmail       : " << GetEmail();
		cout << "\nPhone       : " << GetPhone();
		cout << "\nAcc. Number : " << _AccountNumber;
		cout << "\nPassword    : " << _PinCode;
		cout << "\nBalance     : " << _Balance;
		cout << "\n___________________\n";

	}




public:


	static clsBankClient Find(string AccountNumber)
	{

		fstream File;
		string Line = "";


		File.open(FileName, ios::in);



		if (File.is_open())
		{
			while (getline(File, Line))
			{
				clsBankClient BankClient = _ConvertLineToClient(Line);
					
				if (BankClient._AccountNumber == AccountNumber)
				{
					File.close();
					return BankClient;
				}

				

			}

			File.close();
			return _EmptyClient();
		}



	}

	bool IsFound()
	{
		return (_State != Empty);

	}

	static bool IsFound(string AccountNumber)
	{
		clsBankClient Client = Find(AccountNumber);

		return Client.IsFound();
	}


};

