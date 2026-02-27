#pragma once

#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidate.h" 
#include "clsScreen.h"

using namespace std;


 
class clsUpdateClientScreen : protected clsScreen 
{
private :

    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter FirstName : \n";
        Client.FirstName = clsInputValidate::ReadString();
        cout << "\nEnter LastName : \n";
        Client.LastName = clsInputValidate::ReadString();
        cout << "\nEnter Email : \n";
        Client.Email = clsInputValidate::ReadString();
        cout << "\nEnter Phone : \n";
        Client.Phone = clsInputValidate::ReadString();
        cout << "\nEnter PinCode : \n";
        Client.PinCode = clsInputValidate::ReadString();
        cout << "\nEnter AccountBalance : \n";
        Client.AccountBalance = stof(clsInputValidate::ReadString());

    }

    static void _PrintClientInfo(clsBankClient Client)
    {
        cout << "\n   Client card     : \n";
        cout << "\n___________________";
        cout << "\nFirstName          : " << Client.FirstName;
        cout << "\nLastNaem           : " << Client.LastName;
        cout << "\nEmail              : " << Client.Email;
        cout << "\nPhone              : " << Client.Phone;
        cout << "\nAccountNumber      : " << Client.GetAccountNumber();
        cout << "\nPinCode            : " << Client.PinCode;
        cout << "\nAccountBalance     : " << Client.AccountBalance;
        cout << "\n___________________";
    }
                 

public:

   static void ShowUpdateClientScreen()
    {
       if (!_CheckAccessRights(clsUser::enPermissions::pUpdateClients))
       {
           return;
       }

       _DrawScreenHeader("\n Update Client Screen ");

        string AccountNumber;
        cout << "\nPlease , enter AccountNumber : \n";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "The Account Number is not Exist , choose anther one : \n";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClientInfo(Client);

        char Answer = 'N';
        cout << "\nAre you sure do you want to Update info Client ? (Y/N) ? \n";
        cin >> Answer;


        if (Answer == 'Y' || Answer == 'y')
        {
            cout << "\n Update Client info  : ";
            cout << "\n__________________________\n";
            _ReadClientInfo(Client);

            switch (Client.Save())
            {
            case clsBankClient::enSaveResult::svFaildEmptyObject:
            {
                cout << "\n\nFaild procces !!!\n\n";
                break;
            }
            case clsBankClient::enSaveResult::svSucceeded:
            {
                cout << "Account Updated successfully \n";
                _PrintClientInfo(Client);
                break;
            }
           }
        }
         
    }



};

