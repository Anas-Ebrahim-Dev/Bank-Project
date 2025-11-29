#pragma once
#include "clsScreen.h"
#include "clsBankUser.h"
#include "clsInputValidate.h"
#include<iostream>
using namespace std;

class clsAddNewUserScreen :public clsScreen
{




private:



	static int _ReadPermissions()
	{

		cout << "(Permissions)\n\n";

		int Permission = 0;

		char Confirm = clsInputValidate::ReadChar("\n Do you want to give full access (Y/N) ? ");


		if (Confirm == 'Y' || Confirm == 'y')
		{
			return int(clsBankUser::enPermissions::All);
		}

		Confirm = clsInputValidate::ReadChar("\n Show Client List (Y/N) ? ");

		if (Confirm == 'Y' || Confirm == 'y')
		{
			Permission += int(clsBankUser::enPermissions::ListClients);
		}

		Confirm = clsInputValidate::ReadChar("\n Add New Client (Y/N) ? ");

		if (Confirm == 'Y' || Confirm == 'y')
		{
			Permission += int(clsBankUser::enPermissions::AddNewClient);
		}

		Confirm = clsInputValidate::ReadChar("\n Delete Client (Y/N) ? ");

		if (Confirm == 'Y' || Confirm == 'y')
		{
			Permission += int(clsBankUser::enPermissions::DeleteClient);
		}


		Confirm = clsInputValidate::ReadChar("\n Update Client (Y/N) ? ");

		if (Confirm == 'Y' || Confirm == 'y')
		{
			Permission += int(clsBankUser::enPermissions::UpdateClient);
		}

		Confirm = clsInputValidate::ReadChar("\n Find Client (Y/N) ? ");

		if (Confirm == 'Y' || Confirm == 'y')
		{
			Permission += int(clsBankUser::enPermissions::FindClient);
		}

		Confirm = clsInputValidate::ReadChar("\n Tranactions (Y/N) ? ");

		if (Confirm == 'Y' || Confirm == 'y')
		{
			Permission += int(clsBankUser::enPermissions::Tranactions);
		}

		Confirm = clsInputValidate::ReadChar("\n Mange Users (Y/N) ? ");

		if (Confirm == 'Y' || Confirm == 'y')
		{
			Permission += int(clsBankUser::enPermissions::ManageUsers);
		}


		if (Permission == int(clsBankUser::enPermissions::Total))
		{
			return int(clsBankUser::enPermissions::All);
		}

		return Permission;



	}


	static void _ReadUserInfo(clsBankUser& User)
	{
		User.SetFirstName(clsInputValidate::ReadString("\nEnter FirstName : "));
																								 
		User.SetLastName(clsInputValidate::ReadString("\nEnter LastName: "));					 
																								 
		User.SetEmail(clsInputValidate::ReadString("\nEnter Email: "));							 
																								 
		User.Setphone(clsInputValidate::ReadString("\nEnter Phone: "));							 
																								 
		User.SetPassword(clsInputValidate::ReadString("\nEnter Password: "));					 
																								 
		User.SetPermission(_ReadPermissions());

	}


public:


	static bool AddUser()
	{

		DrawScreenHeader("Adding New User");


		string UserName = clsInputValidate::ReadString("Enter UserName  : ");

		while (clsBankUser::IsUserFound(UserName))
		{
			UserName = clsInputValidate::ReadString("UserName exist , Enter UserName  : ");
		}


		clsBankUser User = clsBankUser::GetNewUser(UserName);

		_ReadUserInfo(User);

		clsBankUser::enSaveResult SaveResult = User.Save();

		switch (SaveResult)
		{
		case clsBankUser::enSaveResult::svSucceeded:
			cout << "\nUser added successfully . \n";
			cout << User.ToString();
			return true;

		case clsBankUser::enSaveResult::svFailed_EmptyUser:
			cout << "Failed to add User (Empty User).";
			return false;

		case clsBankUser::enSaveResult::svFailed_UserExists:
			cout << "Failed to add User (User already exist).";
			return false;

		default:
			cout << "Failed to add User .";
			return false;
		}



	}


};

