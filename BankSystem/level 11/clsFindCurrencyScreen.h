#pragma once


#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsCurrency.h"


using namespace std;

class clsFindCurrencyScreen : protected clsScreen
{
private:

	static void _PrintCurrencyCard(clsCurrency Currency)
	{
		cout << "\n______________________";
		cout << "\nCurrency Card :";
		cout << "\nCountry      : " << Currency.Country();
		cout << "\nCurrencyCode : " << Currency.CurrencyCode();
		cout << "\nCurrencyName : " << Currency.CurrencyName();
		cout << "\nRate(1$)     : " << Currency.Rate();
		cout << "\n______________________";
	}

	static void _ShowResults(clsCurrency Currency)
	{
		if (!Currency.IsEmpty())
		{
			cout << "\n Currency Found :-) " << endl;
			_PrintCurrencyCard(Currency);
		}
		else
		{
			cout << "\n Currency Was Not Found :(- " << endl;
		}
	}

public:

	static void  ShowFindCurrencyScreen()
	{         
        string Title = "\tFind Currencies Screen";      
        _DrawScreenHeader(Title);
        
		cout << "\nFind By : [1] Code  , [2] Country : ";
		short answer = clsInputValidate::ReadIntNumberBetween(1,2);
		if (answer == 1)
		{
			cout << "\n Enter Currency Code : ";
			 string Code = clsInputValidate::ReadString();			  
			clsCurrency Currency = clsCurrency::FindByCode(Code);
			_ShowResults(Currency);
		}
		else
		{
			cout << "\n Enter Country Name  : ";
			string Country = clsInputValidate::ReadString();	
			clsCurrency Currency = clsCurrency::FindByCountry(Country);
			_ShowResults(Currency);
		}
	}

};

