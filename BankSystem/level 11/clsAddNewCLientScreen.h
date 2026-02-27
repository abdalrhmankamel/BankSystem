#pragma once


#include <iostream>
#include < iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
 

using namespace std;

 
class clsAddNewCLientScreen : protected clsScreen
{
private:

    static void _ReadClientInfo(clsBankClient & Client)
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

    static void PrintClientInfo(clsBankClient Client)
    {
        cout << "\n   Client card     : \n";
        cout << "\nFirstName          : " << Client.FirstName;
        cout << "\nLastNaem           : " << Client.LastName;
        cout << "\nEmail              : " << Client.Email;
        cout << "\nPhone              : " << Client.Phone;
        cout << "\nAccountNumber      : " << Client.GetAccountNumber();
        cout << "\nPinCode            : " << Client.PinCode;
        cout << "\nAccountBalance     : " << Client.AccountBalance;
    }

public:


  static  void AddNewClient()
    {
      if (!_CheckAccessRights(clsUser::enPermissions::pAddNewClient))
      {
          return;
      }


      _DrawScreenHeader("Add new client Screen ");

        string AccountNumber;
        cout << "\nPlease , enter AccountNumber : \n";
        AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "The AccountNumber is   Exist , choose anther one : \n";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::GetNewClientObject(AccountNumber);
        cout << "\n\t\tAdd new client : \n\n";
        _ReadClientInfo(Client);

        clsBankClient::enSaveResult SaveResult;

        SaveResult = Client.Save();

        switch (SaveResult)
        {
        case  clsBankClient::enSaveResult::svSucceeded:
        {
            cout << "\nAccount Addeded Successfully :-)\n";
             PrintClientInfo(Client);
            break;
        }
        case clsBankClient::enSaveResult::svFaildEmptyObject:
        {
            cout << "\nError account was not saved because it's Empty";
            break;

        }
        case clsBankClient::enSaveResult::svFaildAccountNumberExists:
        {
            cout << "\nError account was not saved because account number is used!\n";
            break;

        }
        }
    }


};

