#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;


class clsDepositScreen : protected clsScreen 
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

	static string _ReadAccountNumber()
	{
		string AccountNumber;
		cout << "\nPlease enter Account Number :\n";
		cin >> AccountNumber;
		return AccountNumber;
	}
	 

public:

	static void ShowDepositScreen()
	{
		_DrawScreenHeader("Deposit Screen");

		string AccountNumber = _ReadAccountNumber();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
			AccountNumber = _ReadAccountNumber();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClientInfo(Client);

		double Amount = 0;
		char Answer = 'n';
	 
		cout << "\nPlease enter deposit amount : ";
		Amount =  clsInputValidate::ReadPositaveNumber();

		cout << "\nAre you sure you want perform this transaction : (y/n) ?";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Client.Deposit(Amount);
			cout << "\nDone Successfully , New balance is : ";
			cout << Client.AccountBalance ;
		}
		else
		{
			cout << "\nOperation was cancelled.\n";
		}
			
		 
	}



	

};

