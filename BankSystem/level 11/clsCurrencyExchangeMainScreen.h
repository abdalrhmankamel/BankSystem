#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

class clsCurrencyExchangeMainScreen : protected clsScreen
{
private:

	enum enCurrencyOptions
	{
		eCurrenciesList = 1, eFindCurrency = 2,
		eUpdateCurrencyRate = 3, eCurrencyCalculator = 4,
		  eExit = 5
	};

	static short _ReadCurrencyOption()
	{
		cout << "\n" << left << setw(37) << "" << "choose what do you want to do [ 1 to 5 ] ? ";
		short Choice = clsInputValidate::ReadIntNumberBetween(1, 5);
		return Choice;
	}

	static void _GoBackToCurrency()
	{
		cout << "\n\n\tPress any key to go back to Currencies Menu ...... \n";
		system("pause>0");
		ShowCurrencyMenue();
	}

	static void _ShowCurrenciesListScreen()
	{
		clsCurrenciesListScreen::ShowCurrenciesListScreen();

	}	 

	static void _ShowFindCurrencyScreen()
	{
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void _ShowUpdateCurrencyRateScreen()
	{
		clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
	}

	static void _ShowCurrencyCalculatorScreen()
	{
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}

	static void _PerformCurrencyOption(enCurrencyOptions Option)
	{
		switch (Option)
		{
		case enCurrencyOptions::eCurrenciesList:
		{
			system("cls");
			_ShowCurrenciesListScreen();
			_GoBackToCurrency();
			break;
		}
		case enCurrencyOptions::eFindCurrency:
		{
			system("cls");
			_ShowFindCurrencyScreen();
			_GoBackToCurrency();
			break;
		}
		case enCurrencyOptions::eUpdateCurrencyRate:
		{
			system("cls");
			_ShowUpdateCurrencyRateScreen();
			_GoBackToCurrency();
			break;
		}
		case enCurrencyOptions::eCurrencyCalculator:
		{
			system("cls");
			_ShowCurrencyCalculatorScreen();
			_GoBackToCurrency();
			break;
		}
		}
	}

public:

	static void ShowCurrencyMenue()
	{
		system("cls");
		_DrawScreenHeader("\tCurrency Menue");

		cout << "\n" << setw(37) << left << "" << "========================================";
		cout << "\n" << setw(37) << left << "" << "\t\t    Main Menue   ";
		cout << "\n" << setw(37) << left << "" << "========================================";
		cout << "\n" << setw(37) << left << "" << "\t[1] Currency List";
		cout << "\n" << setw(37) << left << "" << "\t[2] Find Currency";
		cout << "\n" << setw(37) << left << "" << "\t[3] Update Rate";
		cout << "\n" << setw(37) << left << "" << "\t[4] Currency Calculator";
		cout << "\n" << setw(37) << left << "" << "\t[5] Main";		 
		cout << "\n" << setw(37) << left << "" << "========================================";

		_PerformCurrencyOption((enCurrencyOptions)_ReadCurrencyOption());
	}






};

