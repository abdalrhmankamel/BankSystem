#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "clsGlobal.h"
#include "clsInputValidate.h"
using namespace std;

class clsLoginScreen : protected clsScreen 
{
private:

	static bool  _Login()
	{
		bool LoginFaild = false  ;
		string UserName, Password;
		short FaildLoginCount = 0  ;
		do {

			if (LoginFaild)
			{
				FaildLoginCount++;
				cout << "\nInvlaid UserName/Password!";
				cout << "\nYou have " << ( 3 - FaildLoginCount )  << " Trail(s) to login \n\n";
			}

			if (FaildLoginCount == 3)
			{
				cout << "\n You are locked after 3 failed trails \n\n";
				return false;
			}

			cout << "\nEnter UserName : \n";
			UserName = clsInputValidate::ReadString();
			
			cout << "\nEnter password : \n";
			Password  = clsInputValidate::ReadString();

			CurrentUser = clsUser::Find(UserName , Password );

			LoginFaild = CurrentUser.IsEmpty();

		}while (LoginFaild);
		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenue();
	}

public :

	static bool ShowLoginScreen()
	{
		
		system("cls");
		_DrawScreenHeader(" Login Screen ");
		return _Login();
	}



};

