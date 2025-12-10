#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "clsUtil.h"
#include "clsPerson.h"
#include "clsString.h"
#include "clsInputValidate.h"

using namespace std;

const string ClientsFile = "BankClients.txt";



class clsBankClient : public clsPerson
{


public:

	enum enState { Empty = 0, Update = 1, Add = 2 };


private:

	string _AccountNumber = "";
	string _PinCode = "";
	double _Balance = 0;
	enState _State = Empty;
	bool _MarkForDelete = false;


private:

	static clsBankClient _ConvertLineToClient(string Line)
	{
		vector <string> vFelids;

		vFelids = clsString::vSplit(Line, "#//#");


		return  clsBankClient(enState::Update, vFelids[0], vFelids[1], vFelids[2], vFelids[3], vFelids[4], vFelids[5], stod(vFelids[6]));

	}



	string _ConvertToLine()
	{
		string Delemeter = "#//#";

		return GetFirstName() + Delemeter + GetLastName() + Delemeter + GetEmail() + Delemeter + GetPhone() + Delemeter 
			+ _AccountNumber + Delemeter+ _PinCode + Delemeter + to_string(_Balance);
	}

	static vector <clsBankClient> _LoadDataFromFileToVector()
	{
		vector <clsBankClient> vClients;
		fstream File;
		string Line = "";

		File.open(ClientsFile, ios::in);

		if (File.is_open())
		{
			while (getline(File, Line))
			{
				vClients.push_back(_ConvertLineToClient(Line));

			}
		}
		File.close();

		return vClients;

	}

	static void _SaveVectorToFile(vector <clsBankClient> &vClients)
	{
		fstream File;

		File.open(ClientsFile, ios::out);

		if (File.is_open())
		{
			for (clsBankClient& Client : vClients)
			{
				if (Client._MarkForDelete == false)
				{
					File << Client._ConvertToLine() << endl;

				}

			}
			File.close();

		}


	}

	void _UpdateInVector(vector <clsBankClient> &vClients)
	{

		for (clsBankClient& Client : vClients)
		{
			if (Client.GetAccountNumber() == _AccountNumber)
			{
				Client = (*this);
				break;
			}
		}

	}

	void _Update()
	{
		vector <clsBankClient> vClients = _LoadDataFromFileToVector();

		_UpdateInVector(vClients);

		_SaveVectorToFile(vClients);

	}

	bool _AddNew()
	{

		string ClientAsLine = (*this)._ConvertToLine();

		
		if (clsUtill::AddLineToFile(ClientAsLine, ClientsFile))
		{
			_State = enState::Update;
			return true;
		}

		return false;

	}

	static void _MarkForDeleteInVector(vector <clsBankClient>& vClients , string AccountNumber)
	{

		for (clsBankClient& Client : vClients)
		{
			if (Client.GetAccountNumber() == AccountNumber)
			{
				Client._MarkForDelete = true;
				break;
			}

		}

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

	void SetBalance(double Balance)
	{
		_Balance = Balance;
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


	string ToString()
	{
		string ClientCard = "";

		ClientCard += "\n----------------------------------";
		ClientCard += "\nFirstName   : " + GetFirstName();
		ClientCard += "\nLastName    : " + GetLastName();
		ClientCard += "\nFull Name   : " + GetFirstName() + " " + GetLastName();
		ClientCard += "\nEmail       : " + GetEmail();
		ClientCard += "\nPhone       : " + GetPhone();
		ClientCard += "\nAcc. Number : " + _AccountNumber;
		ClientCard += "\nPassword    : " + _PinCode;
		ClientCard += "\nBalance     : " + to_string(_Balance);
		ClientCard += "\n----------------------------------\n";

		return ClientCard;

	}



public:




	static clsBankClient Find(string AccountNumber)
	{

		fstream File;
		string Line = "";


		File.open(ClientsFile, ios::in);



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

			return clsBankClient::GetEmptyClient();
		}



	}

	bool IsActive()
	{
		return (_State == enState::Update);
	}

	static bool IsClientFound(string AccountNumber)
	{
		clsBankClient Client = Find(AccountNumber);

		return Client.IsActive();

	}

	static clsBankClient GetEmptyClient()
	{
		return clsBankClient(enState::Empty, "", "", "", "", "", "", 0);
	}

	static clsBankClient GetNewClient(string AccountNumber)
	{
		return clsBankClient(enState::Add, "", "", "", "", AccountNumber, "", 0);
	}

	enum enSaveState { Updated, Added, svFailed_EmptyClient, svFailed_ClientNotExist, svFailed_ClientExists };

	bool IsEmpty()
	{
		return (_State == enState::Empty);
	}

	enSaveState Save()
	{

		switch (_State)
		{
		case clsBankClient::Empty:

			return enSaveState::svFailed_EmptyClient;

		case clsBankClient::Update:
			if (IsClientFound(_AccountNumber))
			{
				_Update();
				return enSaveState::Updated;

			}
			else
			{
				return  enSaveState::svFailed_ClientNotExist;
			}

		case clsBankClient::Add:
			if (!(IsClientFound(_AccountNumber)))
			{
				_AddNew();
				return enSaveState::Added;

			}
			else
			{
				return enSaveState::svFailed_ClientExists;
			}


		default:

			return enSaveState::svFailed_EmptyClient;

		}

	}

	static bool Delete(string AccountNumber)
	{
		if (IsClientFound(AccountNumber))
		{
			vector<clsBankClient> vClients = _LoadDataFromFileToVector();

			_MarkForDeleteInVector(vClients, AccountNumber);

			_SaveVectorToFile(vClients);

			return true;
		}
		else
		{
			return false;
		}


	}

	static vector <clsBankClient> GetClients()
	{
		return _LoadDataFromFileToVector();

	}

	static double GetTotalBalances()
	{
		vector <clsBankClient> vClients = _LoadDataFromFileToVector();

		double TotalBalances = 0;

		for (clsBankClient& Client : vClients)
		{
			TotalBalances += Client.GetBalance();
		}

		return TotalBalances;

	}

	bool Deposit(double Amount)
	{
		if (Amount > 0)
		{
			_Balance += Amount;
			return true;
		}

		return false;

	}

	bool Withdrwa(double Amount)
	{
		if (Amount <= 0)
		{
			return false;
		}

		if (Amount <= _Balance)
		{
			_Balance -= Amount;
			return true;
		}
		else
		{
			return false;

		}

	}


	
};

