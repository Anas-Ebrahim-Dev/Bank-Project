#pragma once
#include "clsScreen.h"
#include<iostream>
#include "clsInputValidate.h"
#include "clsBankUser.h"
using namespace std;

class clsFindUserScreen :public clsScreen
{



public:




	static bool FindUser()
	{

		DrawScreenHeader("Find User Screen");

		string UserName = clsInputValidate::ReadString("Please Enter UserName : ");


		while (!(clsBankUser::IsUserFound(UserName)))
		{

			UserName = clsInputValidate::ReadString("Invalid UserName . Please Enter UserName : ");

		}

		clsBankUser User = clsBankUser::Find(UserName);



		if (User.IsActive())
		{
			cout << "\nUser is found .\n";
			cout << User.ToString();
			return true;
		}
		else
		{
			cout << "User is Empty .\n";
			return false;

		}



	}


};

