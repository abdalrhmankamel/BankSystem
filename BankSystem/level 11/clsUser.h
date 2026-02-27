#pragma once

#include<iostream>
#include<string>
#include<vector>
#include"clsPerson.h"
#include"clsString.h"
#include<fstream>
#include "clsDate.h"
#include "clsUtil.h"

using namespace std;


class clsUser : public clsPerson 
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	enMode _Mode;
	string _UserName;
	string _Password;
	int    _Permission;

	bool _MarkForDelete = false;

	struct stLoginRegisterRecord;

	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string seperator = "#//#")
	{
		stLoginRegisterRecord LoginRegisterRecord;

		vector <string> LoginRegisterDataLine = clsString::Split(Line , seperator);
		LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
		LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
		LoginRegisterRecord.Password =  clsUtil::DecryptText( LoginRegisterDataLine[2]);
		LoginRegisterRecord.Permission = stoi(LoginRegisterDataLine[3]);

		return LoginRegisterRecord;
	}

	static clsUser _ConvertLineToUserObject(string line, string sperator = "#//#")
	{
		vector <string> vUsersData;
		vUsersData = clsString::Split(line, sperator);


		return clsUser (enMode::UpdateMode, vUsersData[0], vUsersData[1], vUsersData[2],
			vUsersData[3], vUsersData[4],clsUtil::DecryptText( vUsersData[5]), stof(vUsersData[6]));
	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser (enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static string _ConvertUserObjectToLine(clsUser User, string Sperater = "#//#")
	{
		string Line;
		Line = User.FirstName + Sperater;
		Line = Line + User.LastName + Sperater;
		Line = Line + User.Email + Sperater;
		Line = Line + User.Phone + Sperater;
		Line = Line + User.UserName + Sperater;
		Line = Line + clsUtil::EncryptText (User.Password ) + Sperater;
		Line = Line + to_string(User.Permission);
		return Line;
	}

	static vector <clsUser>  _LoadUsersFromFile()
	{
		fstream MyFile;
		vector <clsUser> vUsers;

		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				vUsers.push_back(User);
			}
			MyFile.close();
		}
		return vUsers;
	}

	static void _SaveUsersObjectOnFile(vector <clsUser> vUsers)
	{
		fstream MyFile;

		MyFile.open("Users.txt", ios::out);

		if (MyFile.is_open())
		{
			string Line;
			for (clsUser& U : vUsers)
			{
				if (U._MarkForDelete == false)
				{
					Line = _ConvertUserObjectToLine(U);
					MyFile << Line << endl;
				}
			}

			MyFile.close();
		}

	}

	void  _Update()
	{
		vector < clsUser> vUsers;
		vUsers = _LoadUsersFromFile();
		for (clsUser& User : vUsers)
		{
			if (User.UserName  == _UserName)
			{
				User = *this;
				break;
			}
		}
		_SaveUsersObjectOnFile(vUsers);

	}

	void _AddDateUserToFile(string DataUser)
	{
		fstream MyFile;

		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << DataUser<< endl;
			MyFile.close();
		}
	}

	void _AddNewuser()
	{
		_AddDateUserToFile(_ConvertUserObjectToLine(*this));
	}

	string _PrepareLogInRecord(string Seperator = "#//#")
	{
		string LoginRecord = "";
		LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
		LoginRecord += UserName + Seperator;
		LoginRecord += clsUtil::EncryptText ( Password)  + Seperator;
		LoginRecord += to_string(Permission);
		return LoginRecord;
	}

public :

	enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64
		, pLoginRegister = 128 , pCurrency = 256
	};

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone,
		string UserName, string PassWord,  int Permission) :
		clsPerson (FirstName , LastName , Email , Phone )
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = PassWord;
		_Permission = Permission;
	}

	struct stLoginRegisterRecord 
	{
		string DateTime;
		string UserName;
		string Password;
		int Permission;
	};

	bool IsEmpty()
	{
		return (enMode::EmptyMode == _Mode);
	}
 
	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}

	string  GetUserName()
	{
		return _UserName;
	}

	_declspec(property (get = GetUserName, put = SetUserName)) string UserName;

	void SetPassword( string PassWord )
	{
		_Password = PassWord;
	}

	string GetPassword()
	{
		return _Password;
	}

	_declspec(property (get = GetPassword, put = SetPassword)) string Password;

	void SetPermission(int Permission)
	{
		_Permission = Permission;
	}

	int GetPermission()
	{
		return _Permission;
	}

	_declspec(property (get = GetPermission, put = SetPermission)) int  Permission;


	static clsUser  Find(string UserName)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName)
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
			return _GetEmptyUserObject();
		}
	}

	static clsUser Find(string  UserName, string Password)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open())
		{
			string line;
			while (getline(MyFile, line))
			{
				clsUser User = _ConvertLineToUserObject(line);
				if ((User.UserName == UserName) && (User.Password == Password))
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
			return _GetEmptyUserObject();
		}
	}

	static bool IsUserExist(string UserName)
	{
		clsUser User = clsUser::Find(UserName);
		return (!User.IsEmpty());
	}

	enum enSaveResult { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserNameExists = 2 };

	enSaveResult Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			return enSaveResult::svFaildEmptyObject;
		}
		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResult::svSucceeded;
			break;
		}
		case enMode::AddNewMode:
		{
			if (IsUserExist(_UserName))
			{
				return enSaveResult::svFaildUserNameExists;
				break;
			}
			else
			{
				_AddNewuser();
				_Mode = enMode::UpdateMode;
				return enSaveResult::svSucceeded;
				break;
			}

		}
		}
	}

	bool  Delete()
	{
		vector <clsUser> vUser = _LoadUsersFromFile();

		for (clsUser & U : vUser)
		{
			if (U.UserName ==  _UserName )
			{
				U._MarkForDelete = true;
				break;
			}
		}
		_SaveUsersObjectOnFile(vUser);
		*this = _GetEmptyUserObject();
		return true;

	}

	static clsUser GetNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	static vector <clsUser> GetUsersList()
	{
		return _LoadUsersFromFile();
	}

	bool CheckAccessPermission(enPermissions Permission)
	{
		if (this->Permission == enPermissions::eAll)
			return true;
		if ((Permission & this-> Permission ) == Permission)
			return true;
		else
			return false;

	}

	void RegisterLogIn()
	{
			string Line;
			Line = _PrepareLogInRecord();

		fstream MyFile;
		MyFile.open("LogRegister.txt", ios::out | ios::app);
		if (MyFile.is_open())
		{
			MyFile << Line << endl;
			MyFile.close();
		}
	}

	static vector <stLoginRegisterRecord> GetLoginRegisterList()
	{
		vector <stLoginRegisterRecord> vLoginRegisterRecord;

		fstream MyFile;
		MyFile.open("LogRegister.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;

			stLoginRegisterRecord LoginRegisterRecord;

			while (getline(MyFile, Line))
			{

				LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);

				vLoginRegisterRecord.push_back(LoginRegisterRecord);

			}

			MyFile.close();

		}

		return vLoginRegisterRecord;

	}

};

