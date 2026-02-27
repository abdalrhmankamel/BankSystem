#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include "clsDepositScreen.h"
#include "clsWithDrawScreen.h"
#include "clsTotalBalanceScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
using namespace std;



class clsTransactionsScreen : protected clsScreen 
{
private:

	enum enTransactionsMenueOption
	{
		eDeposit = 1 , eWithDraw = 2 , eTotalBalance = 3 , eTransfer = 4
		, eTransferLog ,eMainMenue = 6
	};

	static short _ReadTransActionsMenueOption()
	{
		cout << "\n" << left << setw(37) << "" << "choose what do you want to do [ 1 to 6 ] ? ";
		short Choice = clsInputValidate::ReadIntNumberBetween(1, 6);
		return Choice;
	}

	static void _GoBackToTransActionsMenue()
	{
		cout << "\n\n\tPress any key to go back to Transactions Menue ...... \n";
		system("pause>0");
		ShowTransactionsMenue();
	}

	static void _ShowDepositScreen()
	{
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithDrawScreen()
	{
		clsWithDrawScreen::ShowWithDrawScreen();
	}

	static void _ShowTotalBalance()
	{
		clsTotalBalanceScreen::ShowTotalBalanceScreen();
	}

	static void _ShowTransfer()
	{
		clsTransferScreen::ShowTransferScreen();
	}

	static void _ShowTransferLogScreen()
	{
		clsTransferLogScreen::ShowTransferLogScreen();
	}

	static void _PerformMainMenueOption(enTransactionsMenueOption Option)
	{
		switch (Option)
		{
		case enTransactionsMenueOption::eDeposit:
		{
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransActionsMenue();
			break;
		}
		case enTransactionsMenueOption::eWithDraw:
		{
			system("cls");
			_ShowWithDrawScreen();
			_GoBackToTransActionsMenue();
			break;
		}
		case enTransactionsMenueOption::eTotalBalance:
		{
			 system("cls");
			 _ShowTotalBalance();
			 _GoBackToTransActionsMenue();
			break;
		}
		case enTransactionsMenueOption::eTransfer:
		{
			system("cls");
			_ShowTransfer();
			_GoBackToTransActionsMenue();
			break;
		}
		case enTransactionsMenueOption::eTransferLog:
		{
			system("cls");
			_ShowTransferLogScreen();
			_GoBackToTransActionsMenue();
			break;
		}
		}
	}

public:

	static void ShowTransactionsMenue()
	{
		if (!_CheckAccessRights(clsUser::enPermissions::pTranactions))
		{
			return;
		}

		system("cls");
		_DrawScreenHeader("Transactions Menue");


		cout << "\n" << setw(37) << left << "" << "========================================";
		cout << "\n" << setw(37) << left << "" << "\t\t    Transaction Menue   ";
		cout << "\n" << setw(37) << left << "" << "========================================";
		cout << "\n" << setw(37) << left << "" << "\t[1] Deposit";
		cout << "\n" << setw(37) << left << "" << "\t[2] WithDraw";
		cout << "\n" << setw(37) << left << "" << "\t[3] TotalBalance";
		cout << "\n" << setw(37) << left << "" << "\t[4] Transfer ";
		cout << "\n" << setw(37) << left << "" << "\t[5] Transfer Log ";
		cout << "\n" << setw(37) << left << "" << "\t[6] Mian Menue";
		cout << "\n" << setw(37) << left << "" << "========================================";

		_PerformMainMenueOption((enTransactionsMenueOption)_ReadTransActionsMenueOption());
	}


};

