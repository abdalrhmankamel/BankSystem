#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
 

using namespace std;


class clsDeleteClientScreen : protected clsScreen
{

private:

    static void _PrintClientInfo(clsBankClient Client)
    {

        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.GetAccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }

public:

   static void ShowDeleteClientScreen()
    {
       if (!_CheckAccessRights(clsUser::enPermissions::pDeleteClient))
       {
           return;
       }

       _DrawScreenHeader("Delete Client Screen ");

        string AccountNumber;
        cout << "\nPlease , enter AccountNumber : \n";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "The AccountNumber is not Exist , choose anther one : \n";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClientInfo( Client);

        char Answer =  'n';
        cout << "\nAre you sure do you wnat to delete your account ? ( Y/N ) : \n";
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            if (Client.Delete())
            {
                cout << "\nClient Deleted Successfully  :-)\n";
                _PrintClientInfo(Client);
            }
            else
            {
                 cout << "\nError Client Was not Deleted\n";
            }
        }
    }


};

