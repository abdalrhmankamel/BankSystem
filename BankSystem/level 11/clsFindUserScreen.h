#pragma once
#include <iostream>
#include < iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"

using namespace std;

class clsFindUserScreen : public clsScreen
{
        static void _PrintUser(clsUser User)
        {
            cout << "\nUser Card:";
            cout << "\n___________________";
            cout << "\nFirstName   : " << User.FirstName;
            cout << "\nLastName    : " << User.LastName;
            cout << "\nFull Name   : " << User.FullName();
            cout << "\nEmail       : " << User.Email;
            cout << "\nPhone       : " << User.Phone;
            cout << "\nUser Name   : " << User.UserName;
            cout << "\nPassword    : " << User.Password;
            cout << "\nPermissions : " << User.Permission;
            cout << "\n___________________\n";

        }

public :

    static void ShowFindUserScreen()
    {
        _DrawScreenHeader("Find User Screen");

        string UserName;
        cout << "\nPlease enter UserName : \n ";
        UserName = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nError the UserName not found ,choose anthor one  : \n ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(UserName);

        if (User.IsEmpty())
            cout << "\nUser was not found .\n";
        else
            cout << "\n User Found .\n\n\n";

        _PrintUser(User);




    }

};

