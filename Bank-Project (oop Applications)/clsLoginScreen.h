#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iostream>
#include "clsBankUser.h"
#include "clsSession.h"
#include "clsMainScreen.h"
using namespace std;

class clsLoginScreen :public clsScreen
{



private:




public:



	static void Login()
	{


			system("cls");
			DrawScreenHeader("Loging Screen");

			clsBankUser User = User.GetEmptyUser();
			string UserName = "";
			string Password = "";
			bool IsUserNotValid = true;

			do
			{



				UserName = clsInputValidate::ReadString("Enter UserName : ");

				Password = clsInputValidate::ReadString("Enter Passwore : ");

				User = clsBankUser::Find(UserName, Password);

				IsUserNotValid = User.IsEmpty();

				if (IsUserNotValid)
				{

					cout << "Invalid UserName - Password \n\n";

				}



			} while (IsUserNotValid);

			system("cls");
			clsSession::StartSession(User);




	}



};

