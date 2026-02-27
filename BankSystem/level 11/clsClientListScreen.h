#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

using namespace std;



class clsClientListScreen : protected clsScreen 
{
private:


   static void _PrintClientRecordLine(clsBankClient Client)
    {
        cout << setw(8) << "" << "|" << left << setw(15) << Client.FirstName <<
            "|" << left << setw(15) << Client.LastName <<
            "|" << left << setw(20) << Client.Email <<
            "|" << left << setw(15) << Client.Phone <<
            "|" << left << setw(15) << Client.GetAccountNumber() <<
            "|" << left << setw(10) << Client.PinCode <<
            "|" << left << setw(15) << Client.AccountBalance << endl;
    }

public:


  static  void ShowClientList()
    {
      if (!_CheckAccessRights(clsUser::enPermissions::pListClients))
      {
          return;
      }
        vector <clsBankClient> vClients = clsBankClient::GetClientList();

        string title = "Clients list Screen ";
        string subtitle = "  (" + to_string(vClients.size()) + ") Clients ";

        clsScreen::_DrawScreenHeader(title, subtitle);
         
        cout << setw(8) << "" << "________________________________________________________________________________________________________________\n" << endl;
        cout << setw(8) << "" << "|" << left << setw(15) << "FirstName" <<
            "|" << left << setw(15) << "LastName" <<
            "|" << left << setw(20) << "Email" <<
            "|" << left << setw(15) << "Phone" <<
            "|" << left << setw(15) << "AccountNumber" <<
            "|" << left << setw(10) << "PinCode" <<
            "|" << left << setw(15) << "AccountBalance" << endl;
        cout << setw(8) << "" << "________________________________________________________________________________________________________________\n" << endl;

        if (vClients.size() == 0)
            cout << setw(8) << "" << "\nNo clients available in the system " << endl;
        else
            for (clsBankClient& Client : vClients)
            {
                _PrintClientRecordLine(Client);
            }

        cout << setw(8) << "" << "________________________________________________________________________________________________________________" << endl;
    }


};

