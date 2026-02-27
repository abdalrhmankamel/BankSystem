#pragma once

#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h" 

using namespace std;




class clsFindClientScreen : protected clsScreen 
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

     static void ShowFindClientScreen()
     {
         if (!_CheckAccessRights(clsUser::enPermissions::pFindClient))
         {
             return;
         }

         _DrawScreenHeader("\nFind Client Screen");

         string AccountNumber;
         cout << "\nPlease enter Account Number :\n";
         AccountNumber = clsInputValidate::ReadString();
         while (!clsBankClient::IsClientExist(AccountNumber))
         {
             cout << "\n Account Number is not valid , please enter another one : ";
             AccountNumber = clsInputValidate::ReadString();
         }

         clsBankClient Client = clsBankClient::Find(AccountNumber);

         if (Client.IsEmpty())
             cout << "\nClient was not found .\n";             
         else
             cout << "\n Client Found \n\n\n";

         _PrintClientInfo(Client);


     }
	  
};

