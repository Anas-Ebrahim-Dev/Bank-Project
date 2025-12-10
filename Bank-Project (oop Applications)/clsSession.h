#pragma once
#include <iostream>
#include "clsBankUser.h"
using namespace std;

class clsSession
{


private:


	inline static clsBankUser _LoggedInUser = clsBankUser::GetEmptyUser();


public:


	static void StartSession(clsBankUser User)
	{
		_LoggedInUser = User;
	}

	static clsBankUser GetSessionUser()
	{
		return _LoggedInUser;
	}

	static void EndSession()
	{
		_LoggedInUser = clsBankUser::GetEmptyUser();
	}

	static bool CheckUserPermission(clsBankUser::enPermissions OperationPermission)
	{
		return clsBankUser::DoesUserHavePermission(OperationPermission, _LoggedInUser.GetPermission());
	}


};

