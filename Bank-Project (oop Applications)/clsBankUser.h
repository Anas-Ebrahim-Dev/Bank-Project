#pragma once
#include<iostream>
#include <vector>
#include <fstream>
#include <string>
#include "clsUtil.h"
#include "clsPerson.h"
#include "clsString.h"

using namespace std;


const string UsersFile = "BankUsers.txt";


class clsBankUser : public clsPerson
{

public:

    enum class enState { Empty = 0, Update = 1, Add = 2 };

    enum class enPermissions
    {
        None = 0, All = -1, ListClients = 1, AddNewClient = 2, DeleteClient = 4,
        UpdateClient = 8, FindClient = 16, Tranactions = 32, ManageUsers = 64 , Total = 127
    };

private:

	string _UserName;
	string _Password;
	int _Permission;
    enState _State;
    bool _MarkForDelete;

private:

    string _ConvertToLine()
    {
        string Delemeter = "#//#";

        return GetFirstName() + Delemeter + GetLastName() + Delemeter + GetEmail() + Delemeter + GetPhone() + Delemeter
            + _UserName + Delemeter + _Password + Delemeter + to_string(_Permission);
    }

    static clsBankUser _ConvertLineToUser(string Line)
    {
        vector <string> vFelids;

        vFelids = clsString::vSplit(Line, "#//#");


        return  clsBankUser(enState::Update, vFelids[0], vFelids[1], vFelids[2], vFelids[3], vFelids[4], vFelids[5], stoi(vFelids[6]));

    }

    static vector <clsBankUser> _LoadUsersFromFileToVector()
    {
        vector <clsBankUser> vUsers;
        fstream File;
        string Line = "";

        File.open(UsersFile, ios::in);

        if (File.is_open())
        {
            while (getline(File, Line))
            {
                vUsers.push_back(_ConvertLineToUser(Line));

            }
        }
        File.close();

        return vUsers;

    }


    bool _UpdateUserInVector(vector <clsBankUser>& vUsers)
    {

        for (clsBankUser& User : vUsers)
        {
            if (User.GetUserName() == _UserName)
            {
                User = (*this);
                return true;
            }
        }

        return false;

    }

    static bool _SaveVectorToFile(vector <clsBankUser>& vUsers)
    {
        fstream File;

        File.open(UsersFile, ios::out);

        if (File.is_open())
        {
            for (clsBankUser& User : vUsers)
            {
                if (User._MarkForDelete == false)
                {
                    File << User._ConvertToLine() << endl;

                }

            }

            File.close();
            return true;
        }    
        return false;


    }

    bool _Update()
    {
        vector <clsBankUser> vUsers = _LoadUsersFromFileToVector();

        if (_UpdateUserInVector(vUsers))
        {
            _SaveVectorToFile(vUsers);
            return true;

        }

        return false;


    }

    bool _AddNew()
    {
        string UserAsLine = (*this)._ConvertToLine();

        if (clsUtill::AddLineToFile(UserAsLine, UsersFile))
        {
            _State = enState::Update;
            return true;
        }

        return false;

    }

    static bool _MarkForDeleteInVector(vector <clsBankUser>& vUsers, string UserName)
    {
        for (clsBankUser& User : vUsers)
        {
            if (User.GetUserName() == UserName)
            {
                User._MarkForDelete = true;
                return true;
            }
        }

        return false;
    }



public:


	clsBankUser(enState State ,string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Permission)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_UserName = UserName;
		_Password = Password;
		_Permission = Permission;
        _State = State;
        _MarkForDelete = false;

	}


    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }
    string GetUserName()
    {
        return _UserName;
    }


    void SetPassword(string Password)
    {
        _Password = Password;
    }
    string GetPassword()
    {
        return _Password;
    }


    void SetPermission(int Permission)
    {
        _Permission = Permission;
    }
    int GetPermission()
    {
        return _Permission;
    }


    void SetState(enState State)
    {
        _State = State;
    }
    enState GetState()
    {
        return _State;
    }




public:


    static clsBankUser Find(string UserName)
    {
        fstream File;
        string Line = "";


        File.open(UsersFile, ios::in);



        if (File.is_open())
        {
            while (getline(File, Line))
            {
                clsBankUser BankUser = _ConvertLineToUser(Line);

                if (BankUser._UserName == UserName)
                {
                    File.close();
                    return BankUser;
                }



            }

            File.close();

        }    

        return clsBankUser::GetEmptyUser();

    }


    static clsBankUser Find(string UserName,string Password)
    {
        fstream File;
        string Line = "";


        File.open(UsersFile, ios::in);



        if (File.is_open())
        {
            while (getline(File, Line))
            {
                clsBankUser BankUser = _ConvertLineToUser(Line);

                if (BankUser._UserName == UserName && BankUser._Password == Password)
                {
                    File.close();
                    return BankUser;
                }



            }

            File.close();

        }    

        return clsBankUser::GetEmptyUser();

    }



    static bool IsUserFound(string UserName)
    {

        clsBankUser User = Find(UserName);

        return User.IsActive();

    }

    bool IsActive()
    {
        return (_State == enState::Update);
    }

    bool IsEmpty()
    {
        return (_State == enState::Empty);
    }

    enum class enSaveResult {svSucceeded , svFailed_EmptyUser , svFailed_UserNotExists , svFailed_UserExists  };

    enSaveResult Save()
    {
        switch (_State)
        {
        case clsBankUser::enState::Empty:

            return enSaveResult::svFailed_EmptyUser;

        case clsBankUser::enState::Update:
            if (IsUserFound(_UserName))
            {
                _Update();
                return enSaveResult::svSucceeded;
            }
            else
            {
                return enSaveResult::svFailed_UserNotExists;
            }

        case clsBankUser::enState::Add:

            if (!(IsUserFound(_UserName)))
            {
                _AddNew();
                return enSaveResult::svSucceeded;
            }
            else
            {
                return enSaveResult::svFailed_UserExists;
            }


        default:

            return  enSaveResult::svFailed_EmptyUser;

        }
    }

    static bool Delete(string UserName)
    {
        vector <clsBankUser> vUsers = _LoadUsersFromFileToVector();

        if (_MarkForDeleteInVector(vUsers, UserName))
        {
            _SaveVectorToFile(vUsers);
            return true;
        }
        
        return false;

    }

    static vector <clsBankUser> GetUsers()
    {
        return _LoadUsersFromFileToVector();
    }

    static clsBankUser GetNewUser(string UserName)
    {
        return clsBankUser(enState::Add, "", "", "", "", UserName, "", 0);
    }

    string ToString()
    {
        string UserCard = "";

        UserCard += "\n----------------------------------";
        UserCard += "\nFirstName      : " + GetFirstName();
        UserCard += "\nLastName       : " + GetLastName();
        UserCard += "\nFull Name      : " + GetFirstName() + " " + GetLastName();
        UserCard += "\nEmail          : " + GetEmail();
        UserCard += "\nPhone          : " + GetPhone();
        UserCard += "\nUser Name      : " + _UserName;
        UserCard += "\nPassword       : " + _Password;
        UserCard += "\nPermission     : " + to_string(_Permission);
        UserCard += "\n----------------------------------\n";

        return UserCard;

    }

    static clsBankUser GetEmptyUser()
    {
        return clsBankUser(enState::Empty, "", "", "", "", "", "", 0);
    }


};

