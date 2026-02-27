#pragma once

#include <iostream>
#include < iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"

using namespace std;

class clsDeleteUserScreen : protected clsScreen 
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

    static void ShowDeleteUserScreen()
    {
        _DrawScreenHeader("Delete User Screen ");

        string UserName;
        cout << "\nPlease enter UserName : \n ";
         UserName = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nError the UserName is exist ,Please Try anthor one  : \n ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(UserName);

        _PrintUser(User);

        char Answer = 'n';
        cout << "\nAre you sure do you wnat to delete this User ? ( Y/N ) : \n";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            if (User.Delete())
            {
                cout << "\nUser Deleted  successfully \n";
                _PrintUser(User);
            }
            else
                cout << "\n Error User was not deleted \n";
        }


    }



};

