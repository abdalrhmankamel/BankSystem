#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"

using namespace std;


class clsTotalBalanceScreen : protected clsScreen 
{
private:

	static void _PrintClientBalanceRecordLine(clsBankClient Client)
	{
		cout << "|" << left << setw(15) << Client.GetAccountNumber() <<
			"|" << left << setw(40) << Client.FirstName <<
			"|" << left << setw(15) << Client.AccountBalance << endl;
	}


public:


	static void ShowTotalBalanceScreen()
	{
		vector <clsBankClient> vClients = clsBankClient::GetClientList();
		cout << "\n\t\t\t\t   Balance List " << vClients.size() << " Client(s) " << endl;
		cout << "________________________________________________________________________________________________________________" << endl;
		cout <<
			"|" << left << setw(15) << "AccountNumber" <<
			"|" << left << setw(40) << "Client Name" <<
			"|" << left << setw(15) << "AccountBalance" << endl;
		cout << "________________________________________________________________________________________________________________" << endl;

		if (vClients.size() == 0)
			cout << "\nNo clients available in the system " << endl;
		else
			for (clsBankClient& Client : vClients)
			{
				_PrintClientBalanceRecordLine(Client);
			}

		cout << "________________________________________________________________________________________________________________" << endl;
		double Total = clsBankClient::GetTotalBalance();
		cout << "\n\t\t\t\t\t   Total Balance : " << Total << endl;
		cout << "\n\t\t\t\t\t ( " << clsUtil::NumberToText(Total) << ")" << endl;
	}

};

