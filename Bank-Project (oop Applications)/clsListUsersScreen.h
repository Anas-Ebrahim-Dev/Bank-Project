#pragma once
#include "clsScreen.h"
#include "clsBankUser.h"
#include <iostream>
#include<iomanip>
using namespace std;

class clsListUsersScreen :public clsScreen
{

private:

	static void _PrintOneUser(clsBankUser User)
	{
		cout << '|' << setw(15) << left << User.GetUserName()
			<< '|' << setw(22) << left << User.GetFirstName() + " " + User.GetLastName()
			<< '|' << setw(14) << left << User.GetPhone()
			<< '|' << setw(25) << left << User.GetEmail()
			<< '|' << setw(10) << left << User.GetPassword()
			<< '|' << setw(14) << left << User.GetPermission() << '\n';


	}



public:


	static void DisplayUserList()
	{
		vector <clsBankUser> vUsers = clsBankUser::GetUsers();

		string Tittle = "User List ";
		string SubTittle = " User list (" + to_string(vUsers.size()) + ") User(s) .";

		DrawScreenHeader(Tittle, SubTittle);


		cout << string(110, '-') << '\n';

		cout << '|' << setw(15) << left << "User Name"
			 << '|' << setw(22) << left << "Full Name"
			 << '|' << setw(14) << left << "Phone Number"
			 << '|' << setw(25) << left << "Email"
			 << '|' << setw(10) << left << "Password"
			 << '|' << setw(14) << left << "Permission" << '\n';

		cout << string(110, '-') << '\n';

		if (vUsers.size() == 0)
		{
			cout << "\t\t\t\t\tNo Users found . ";
			cout << string(110, '-') << '\n';
			return;
		}

		for (clsBankUser& User : vUsers)
		{
			_PrintOneUser(User);
		}

		cout << string(110, '-') << '\n';



	}

};

