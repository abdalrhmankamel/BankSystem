#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include "clsClientListScreen.h"
#include "clsAddNewCLientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFIndClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsMangeUsersScreen.h"
#include "clsGlobal.h"
#include "clsUser.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeMainScreen.h"

class clsMainScreen : protected clsScreen 
{
private:

	enum enMainMenueOptions
	{
		eListClients = 1 , eAddNewClient = 2 ,
		eUpdateClient = 3 , eDeletedClient = 4 , 
		eFindClient = 5 , eShowTransactionsMenue = 6 ,
		eManageUsers = 7 ,eLoginRegister = 8 ,
		eCurrency = 9 ,eExit = 10 
	};

	static short _ReadMainMenueOption()
	{
		cout <<"\n" << left << setw(37) << "" << "choose what do you want to do [ 1 to 10 ] ? ";
		short Choice = clsInputValidate::ReadIntNumberBetween(1, 10);
		return Choice;
	}

	static void _GoBackToMainMenue()
	{
		cout <<  "\n\n\tPress any key to go back to Main Menue ...... \n";
		system("pause>0");
		ShowMainMenue();
	}

	static void _ShowAllClientsScreen()
	{
		clsClientListScreen::ShowClientList();

	}

	static void _ShowAddNewClientScreen()
	{
		clsAddNewCLientScreen::AddNewClient();
	}

	static void _ShowDeleteClientScreen()
	{
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _ShowUpdateClientScreen()
	{
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void _ShowFindClientScreen()
	{
		clsFindClientScreen::ShowFindClientScreen();
	}

	static void _ShowTransactionsMenue()
	{
		clsTransactionsScreen::ShowTransactionsMenue();
	 }

	static void _ShowManageUsersScreen()
	{
		clsMangeUsersScreen::ShowManageUsersScreen();
	}

	static void _ShowCurrencyScreen()
	{
		clsCurrencyExchangeMainScreen::ShowCurrencyMenue();
	}

	static void _ShowLoginRegisterScreen()
	{
		clsLoginRegisterScreen::ShowLoginRegisterScreen();
	}

	static void _Logout()
	{
		CurrentUser =  clsUser::Find("","");
	}

	static void _PerformMainMenueOption(enMainMenueOptions Option)
	{
		switch (Option)
		{
		case enMainMenueOptions::eListClients:
		{
			system("cls");
			_ShowAllClientsScreen();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOptions::eAddNewClient:
		{
			system("cls");
			_ShowAddNewClientScreen();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOptions::eUpdateClient:
		{
			system("cls");
			_ShowUpdateClientScreen();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOptions::eDeletedClient:
		{
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOptions::eFindClient:
		{
			system("cls");
			_ShowFindClientScreen();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOptions::eShowTransactionsMenue:
		{
			system("cls");
			_ShowTransactionsMenue();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOptions::eManageUsers:
		{
			system("cls");
			_ShowManageUsersScreen();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOptions::eLoginRegister:
		{
			system("cls");
			_ShowLoginRegisterScreen();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOptions::eCurrency:
		{
			system("cls");
			_ShowCurrencyScreen();
			_GoBackToMainMenue();
			break;
		}
		case enMainMenueOptions::eExit:
		{
			system("cls");
			_Logout();
			break;
		}
		}
	}


public :

	static void ShowMainMenue()
	{
		system("cls");
		_DrawScreenHeader("\tMain Menue");

		cout << "\n" << setw(37) << left << "" << "========================================";
		cout << "\n" << setw(37) << left << "" << "\t\t    Main Menue   ";
		cout << "\n" << setw(37) << left << "" << "========================================";
		cout << "\n" << setw(37) << left << "" << "\t[1] Show Clint List";
		cout << "\n" << setw(37) << left << "" << "\t[2] Add New Client";
		cout << "\n" << setw(37) << left << "" << "\t[3] Update Client info";
		cout << "\n" << setw(37) << left << "" << "\t[4] Delete Client";
		cout << "\n" << setw(37) << left << "" << "\t[5] Find Client";
		cout << "\n" << setw(37) << left << "" << "\t[6] TransAction";
		cout << "\n" << setw(37) << left << "" << "\t[7] ManageUsers";
		cout << "\n" << setw(37) << left << "" << "\t[8] Login Register";
		cout << "\n" << setw(37) << left << "" << "\t[9] Currency";
		cout << "\n" << setw(37) << left << "" << "\t[10] Logout";
		cout << "\n" << setw(37) << left << "" << "========================================";

		_PerformMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
	}

};


 
