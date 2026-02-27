#pragma once

#include <iostream>
#include < iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"

using namespace std;






class clsAddUserScreen : public clsScreen 
{

private:

    static void _ReadUserInfo(clsUser & User)
    {
        cout << "\nEnter FirstName : \n";
        User.FirstName = clsInputValidate::ReadString();
        cout << "\nEnter LastName : \n";
        User.LastName = clsInputValidate::ReadString();
        cout << "\nEnter Email : \n";
        User.Email = clsInputValidate::ReadString();
        cout << "\nEnter Phone : \n";
        User.Phone = clsInputValidate::ReadString();
        cout << "\nEnter Password : \n";
        User.Password = clsInputValidate::ReadString();
        cout << "\nEnter Permission : \n";
        User.Permission =  _ReadPermissionsToSet();

    }

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

    static int _ReadPermissionsToSet()
    {

        int Permissions = 0;
        char Answer = 'n';


        cout << "\nDo you want to give full access? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }

        cout << "\nDo you want to give access to : \n ";

        cout << "\nShow Client List? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pListClients;
        }

        cout << "\nAdd New Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }

        cout << "\nDelete Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pUpdateClients;
        }

        cout << "\nFind Client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pFindClient;
        }

        cout << "\nTransactions? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pTranactions;
        }

        cout << "\nManage Users? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pManageUsers;
        }

        cout << "\Login Register? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pLoginRegister;
        }

        return Permissions;

    }


public:
	

	static void ShowAddUserScreen()
	{

        _DrawScreenHeader("Add New User ");

        string UserName; 
        cout << "\nPlease enter UserName : \n ";
        UserName = clsInputValidate::ReadString();
            while (clsUser::IsUserExist(UserName))
            {
                cout << "\nError the UserName is exist ,Please Try anthor one  : \n ";
                UserName = clsInputValidate::ReadString();
            }

            clsUser User = clsUser::GetNewUserObject(UserName);

            _ReadUserInfo(User);

            clsUser::enSaveResult SaveResult;

            SaveResult = User.Save();

            switch (SaveResult)
            {
            case  clsUser::enSaveResult::svSucceeded:
            {
                cout << "\nUser Addeded Successfully :-)\n";
                _PrintUser(User);
                break;
            }
            case clsUser::enSaveResult::svFaildEmptyObject:
            {
                cout << "\nError User was not saved because it's Empty";
                break;

            }
            case clsUser::enSaveResult::svFaildUserNameExists:
            {
                cout << "\nError User was not saved because UserName is used!\n";
                break;

            }
            }

	}
};

