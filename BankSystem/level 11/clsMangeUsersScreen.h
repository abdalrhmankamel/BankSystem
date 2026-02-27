#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUserListScreen.h"
#include "clsAddUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"


using namespace std;

class clsMangeUsersScreen : protected clsScreen
{
private:

	enum enManageUsersMenueOption
	{
		eUsersList = 1, eAddUser = 2, eDeleteUser = 3,
		eUpdateUser = 4, eFindUser = 5, eMainMenue = 6,
	};

	static short _ReadManageUsersMenueOption()
	{
		cout << "\n" << left << setw(37) << "" << "choose what do you want to do [ 1 to 6 ] ? ";
		short Choice = clsInputValidate::ReadIntNumberBetween(1, 6);
		return Choice;
	}

	static void _GoBackToManageUsersMenue()
	{
		cout << "\n\n\tPress any key to go back to Transactions Menue ...... \n";
		system("pause>0");
		ShowManageUsersScreen();
	}

	static void _ShowUsersListScreen()
	{
		clsUserListScreen::ShowUsersList();
	}

	static void _ShowAddUserScreen()
	{
		clsAddUserScreen::ShowAddUserScreen();
	}

	static void _ShowDeleteUserScreen()
	{
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _ShowUpdateUserScreen()
	{
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _ShowFindUserScreen()
	{
		//cout << "\n Find User Screen will be here on later ......\n";
		clsFindUserScreen::ShowFindUserScreen();
	}
 
	static void _PerformManageUsersMenueOption(enManageUsersMenueOption Option)
	{
		switch (Option)
		{
		case enManageUsersMenueOption::eUsersList:
		{
			system("cls");
			_ShowUsersListScreen();
			_GoBackToManageUsersMenue();
			break;
		}
		case enManageUsersMenueOption::eAddUser:
		{
			system("cls");
			_ShowAddUserScreen();
			_GoBackToManageUsersMenue();
			break;
		}
		case enManageUsersMenueOption::eDeleteUser:
		{
			system("cls");
			_ShowDeleteUserScreen();
			_GoBackToManageUsersMenue();
			break;
		}
		case enManageUsersMenueOption::eUpdateUser:
		{
			system("cls");
			_ShowUpdateUserScreen();
			_GoBackToManageUsersMenue();
			break;
		}
		case enManageUsersMenueOption::eFindUser:
		{
			system("cls");
			_ShowFindUserScreen();
			_GoBackToManageUsersMenue();
			break;
		}

		}
	}

public :

	static void ShowManageUsersScreen()
	{
		if (!_CheckAccessRights(clsUser::enPermissions::pManageUsers))
		{
			return;
		}
		system("cls");
		_DrawScreenHeader("Manage Users Menue");

		cout << "\n" << setw(37) << left << "" << "========================================";
		cout << "\n" << setw(37) << left << "" << "\t\t    Manage Users Menue   ";
		cout << "\n" << setw(37) << left << "" << "========================================";
		cout << "\n" << setw(37) << left << "" << "\t[1] Users list";
		cout << "\n" << setw(37) << left << "" << "\t[2] Add User";
		cout << "\n" << setw(37) << left << "" << "\t[3] Delete User";
		cout << "\n" << setw(37) << left << "" << "\t[4] Update User";
		cout << "\n" << setw(37) << left << "" << "\t[5] Find User";
		cout << "\n" << setw(37) << left << "" << "\t[6] Mian Menue";
		cout << "\n" << setw(37) << left << "" << "========================================";

		_PerformManageUsersMenueOption((enManageUsersMenueOption)_ReadManageUsersMenueOption());
	}




};

