#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"


using namespace std;





class clsTransferScreen : protected clsScreen
{

private:

	static void _PrintClientInfo(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFullName   : " << Client.FullName();		 
		cout << "\nAcc. Number : " << Client.GetAccountNumber();		 
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";
	}


	static string _ReadAccountNumber()
	{
		string AccountNumber;
		cout << "\nPlease Enter Account Number to Transfer From: ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		return AccountNumber;
	}

	static double _ReadAmount(clsBankClient Client1)
	{
		double Amount = 0;
	
		cout << "\nPlease enter  amount to transfer : ";
		Amount = clsInputValidate::ReadPositaveNumber();

		while (Client1.AccountBalance < Amount)
		{
			cout << "\n\nAmount exceeds the available balance , Enter another amount :";
			cin >> Amount;
		}
		return Amount;
	}

public:

	static void ShowTransferScreen()
	{
		_DrawScreenHeader("Transfer Screen");

		clsBankClient Client1 = clsBankClient::Find(_ReadAccountNumber());

		_PrintClientInfo(Client1);
	 
		clsBankClient Client2 = clsBankClient::Find(_ReadAccountNumber());

		_PrintClientInfo(Client2);

		double Amount = _ReadAmount(Client1);

		char Answer = 'n';
		cout << "\nAre you sure you want perform this Operation ? (y/n) ?";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			if (Client1.Transfer(Amount, Client2 , CurrentUser.UserName))
			{
				cout << "\nTransfer Done Successfully. ";
			}
			else
			{
				cout << "\nTransfer faild .\n";
			}
		}
		_PrintClientInfo(Client1);
		_PrintClientInfo(Client2);
	}


};

