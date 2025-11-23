#pragma once
#include <iostream>
#include "clsScreen.h"
using namespace std;

class clsMangeUsersScreen :public clsScreen
{

private:

	enum class _enManageUsersMenuOptions
	{
		ListUsers = 1, AddNewUser = 2, DeleteUser = 3, UpdateUser = 4, FindUser = 5, MainMenu = 6
	};



private:


	static void _DrawMangeUsersMenu()
	{
		DrawScreenHeader("MangeUsers Menu");

		cout << "===========================================\n";
		cout << "           Manage Users Menu\n";
		cout << "===========================================\n";
		cout << "\t[1] List Users.\n";
		cout << "\t[2] Add New User.\n";
		cout << "\t[3] Delete User.\n";
		cout << "\t[4] Update User.\n";
		cout << "\t[5] Find User.\n";
		cout << "\t[6] Main Menu.\n";
		cout << "===========================================\n";


	}

	static _enManageUsersMenuOptions _ReadMangeUsersMenuOption()
	{
		int Choice = clsInputValidate::ReadIntNumberBetween("Choose what do you want to do? [1 to 6]? ", 1, 6);

		return _enManageUsersMenuOptions(Choice);

	}

	static void _ListUsers()
	{
		DrawScreenHeader("list Users");
	}

	static bool _AddNewUser()
	{
		DrawScreenHeader("Add New User");
		return true;
	}

	static bool _DeleteUser()
	{
		DrawScreenHeader("Delete User");
		return true;

	}

	static bool _UpdateUser()
	{
		DrawScreenHeader("Update User");
		return true;

	}

	static bool _FindUser()
	{
		DrawScreenHeader("Find User");
		return true;

	}

	static void _PerformMangeUsersOperation(_enManageUsersMenuOptions Choice)
	{

		switch (Choice)
		{
		case clsMangeUsersScreen::_enManageUsersMenuOptions::ListUsers:
			_ListUsers();
			break;
		case clsMangeUsersScreen::_enManageUsersMenuOptions::AddNewUser:
			_AddNewUser();
			break;
		case clsMangeUsersScreen::_enManageUsersMenuOptions::DeleteUser:
			_DeleteUser();
			break;
		case clsMangeUsersScreen::_enManageUsersMenuOptions::UpdateUser:
			_UpdateUser();
			break;
		case clsMangeUsersScreen::_enManageUsersMenuOptions::FindUser:
			_FindUser();
			break;

		default:

			return;

		}
	}


public:


	static void StartMangeUsersMenu()
	{


		while (true)
		{

			_DrawMangeUsersMenu();

			_enManageUsersMenuOptions Choice = _ReadMangeUsersMenuOption();

			if (Choice == _enManageUsersMenuOptions::MainMenu)
			{
				return;
			}

			system("cls");


			_PerformMangeUsersOperation(Choice);


			system("pause=0");

			system("cls");



		}

	}


};

