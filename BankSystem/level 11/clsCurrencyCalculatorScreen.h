#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

using namespace std;

class clsCurrencyCalculatorScreen : protected clsScreen
{
private:

    static clsCurrency _GetCurrency(string Massage )
    {
        string CurrencyCode = "";

        cout << "\n" << Massage << endl;         
        CurrencyCode = clsInputValidate::ReadString();
        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency is not found, choose another one: ";
            CurrencyCode = clsInputValidate::ReadString();
        }
        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
        return Currency;
     }

    static float _ReadAmount()
    {
        float Number=0;
        cout << "\n Enter Amount to Exchange : ";
        Number = clsInputValidate::ReadFloutNumber();
        return Number;
    }


    static void _PrintCurrencyCard(clsCurrency Currency , string Title = "Currency Card :")
    {
        cout << "\n______________________";
        cout << "\n" << Title <<"\n";
        cout << "\nCountry      : " << Currency.Country();
        cout << "\nCurrencyCode : " << Currency.CurrencyCode();
        cout << "\nCurrencyName : " << Currency.CurrencyName();
        cout << "\nRate(1$)     : " << Currency.Rate();
        cout << "\n______________________";
    }

    static void _PrintCalculationResults(float Amount ,  clsCurrency Currency1 , clsCurrency Currency2)
    {
        float AmountInUSD = Currency1.ConvertToUSA(Amount);
        _PrintCurrencyCard(Currency1 , "Covert From :");

        cout << " \n\n " << Amount << " " << Currency1.CurrencyCode()
            << " = " << AmountInUSD << " "<<"USD" << endl;

        if (Currency2.CurrencyCode() == "USD")
        {
            return;
        }

        cout << "\nConvert From USD To :\n ";
        _PrintCurrencyCard(Currency2 , "To : ");

        float AmountInCurrency2 = Currency1.ConvertToOtherCurrency(Amount , Currency2);

        cout << " \n\n " << Amount << " " << Currency1.CurrencyCode()
            << " = " << AmountInCurrency2 << " " << Currency2.CurrencyCode() << endl;
    }

public:
    static void ShowCurrencyCalculatorScreen()
    {
        char Continue = 'Y';

        while (Continue == 'y' || Continue == 'Y')
        {
            system("cls");
            _DrawScreenHeader("\tCurrency Calculator");

            clsCurrency Currency1 = _GetCurrency("Enter Currency1 Code : ");
            clsCurrency Currency2 = _GetCurrency("Enter Currency2 Code : ");
            float Amount = _ReadAmount();
            _PrintCalculationResults(Amount , Currency1 , Currency2);

            cout << "\n\nDo you want to perform any calculation : (y/n) ?";
            cin >> Continue;
        }
    }

};