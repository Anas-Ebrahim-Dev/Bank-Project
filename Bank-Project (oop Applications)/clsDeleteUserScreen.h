#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankUser.h"
#include "clsInputValidate.h"
using namespace std;

class clsDeleteUserScreen :public clsScreen
{

	

public:

	static bool DeleteUser()
	{

		DrawScreenHeader("Delete User Screen ");

		string UserName = clsInputValidate::ReadString("Enter User Name : ");

		while (!(clsBankUser::IsUserFound(UserName)))
		{
			UserName = clsInputValidate::ReadString("User dosen't exist . Enter UserName : ");
		}


		clsBankUser User = clsBankUser::Find(UserName);

		cout << User.ToString();


		char Confirm = clsInputValidate::ReadChar("\nAre you sure to delete this User (Y/N) ? ");



		if (Confirm == 'Y' || Confirm == 'y')
		{
			if (clsBankUser::Delete(UserName))
			{
				cout << "user deleted successfully .\n";
				return true;

			}
			else
			{
				cout << "Error occured . User was not deleted\n";
				return false;

			}


		}
		else
		{
			cout << "Delete has been cancelled .";
			return false;

		}


	}





};

