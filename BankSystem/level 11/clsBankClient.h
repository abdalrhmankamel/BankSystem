#pragma once

#include<iostream>
#include<string>
#include<vector>
#include"clsPerson.h"
#include"clsString.h"
#include<fstream>

using namespace std;
 
class clsBankClient : public clsPerson
{

private:
	  
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewClient = 2    };

	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkForDelete = false;

	struct stTransferLogRegister;

	static clsBankClient _ConvertLineToClientObject(string line , string sperator = "#//#")
	{
		vector <string> vClientData;
		vClientData = clsString::Split(line, sperator);

		 
		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], vClientData[5], stof(vClientData[6]));
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	 }

	static string _ConvertClientObjectToLine( clsBankClient  Client , string Sperater = "#//#")
	{
		string Line;
		Line = Client.FirstName + Sperater;
		Line = Line + Client.LastName +Sperater;
		Line = Line + Client.Email+ Sperater;
		Line = Line + Client.Phone + Sperater;
		Line = Line + Client.GetAccountNumber() + Sperater;
		Line = Line + Client.PinCode + Sperater;
		Line = Line + to_string(Client.AccountBalance) ;
		return Line;
	}

	static vector <clsBankClient>  _LoadClientFromFile()
	{
		fstream MyFile;
		vector <clsBankClient> vClient;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				vClient.push_back(Client);
			}
			MyFile.close();
		}
		return vClient;
	}

	static void _SaveClientsObjectOnFile(vector <clsBankClient> vClient)
	{
		fstream MyFile;
		 
		MyFile.open("Clients.txt", ios::out);

		if (MyFile.is_open())
		{
			string Line;
			for (clsBankClient& C : vClient)
			{
				if (C._MarkForDelete == false)
				{
					Line = _ConvertClientObjectToLine(C);
					MyFile << Line << endl;
				}
			}

			MyFile.close();
		}
	 
	}

	void  _Update()
	{
		vector < clsBankClient> vClient;
		vClient = _LoadClientFromFile();
		for (clsBankClient& Client : vClient)
		{
			if (Client.GetAccountNumber() == _AccountNumber)
			{
				Client = *this;
				break;
			}
		}
		_SaveClientsObjectOnFile(vClient);

	}

	void _AddDateClientToFile(string DataClient)
	{
		fstream MyFile;

		MyFile.open("Clients.txt", ios::out | ios::app );

		if (MyFile.is_open())
		{ 
			MyFile << DataClient << endl;
			MyFile.close();
		}
	}

	void _AddNewClient()
	{
		_AddDateClientToFile(_ConvertClientObjectToLine(*this));
	}

	  string _PrepareTransferLogRecord(  clsBankClient DistentionClient,
		double Amount ,string UserName , string Seperator = "#//#")
	{
		string TransferLine = "";
		TransferLine += clsDate::GetSystemDateTimeString() + Seperator;
		TransferLine += _AccountNumber + Seperator;
		TransferLine += to_string(Amount) + Seperator;
		TransferLine += to_string(AccountBalance) + Seperator;
		TransferLine += to_string(DistentionClient.AccountBalance) + Seperator;
		TransferLine +=   UserName;
		return TransferLine;
	}

	  void _RegisterTransferLog(double Amount, clsBankClient DestinationClient, string UserName)
	  {

		  string stDataLine = _PrepareTransferLogRecord(  DestinationClient , Amount , UserName);

		  fstream MyFile;
		  MyFile.open("TransferLog.txt", ios::out | ios::app);

		  if (MyFile.is_open())
		  {

			  MyFile << stDataLine << endl;

			  MyFile.close();
		  }

	  }

	static  stTransferLogRegister _ConvertTransferLineToRecord(string Line , string Seprator = "#//#")
	  {
		  stTransferLogRegister Record;
		  vector <string> vRecord;
		  vRecord = clsString::Split(Line, Seprator );
		  Record.Date = vRecord[0];
		  Record.SClient = vRecord[1];
		  Record.DClient = vRecord[2];
		  Record.Amount = stod(vRecord[3]);
		  Record.SBalance = stod(vRecord[4]);
		  Record.DBalance = stod(vRecord[5]);
		  Record.UserName = vRecord[6];
		  return Record;
	 }

public: 

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone,
		string AccountNumber, string PinCode, float AccountBalance)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
       _Mode = Mode ;
       _AccountNumber = AccountNumber;
       _PinCode  = PinCode ;
	   _AccountBalance = AccountBalance;
	}

	struct stTransferLogRegister
	{
		string Date;
		string SClient;
		string DClient;
		double Amount;
		double SBalance;
		double DBalance;
		string UserName;
	};


	bool IsEmpty()
	{
		return (enMode::EmptyMode == _Mode);
	}

	 string GetAccountNumber()
	 {
		 return _AccountNumber;
	 }

	 void SetPinCode(string PinCode)
	 {
		 _PinCode = PinCode;
	 }

	 string GetPinCode() 
	 {
		 return _PinCode;
	 }
	  
	 __declspec(property (get = GetPinCode, put = SetPinCode ))string PinCode;

	 void SetAccountBalance(float AccBa)
	 {
		 _AccountBalance = AccBa;
	 }

	 float GetAccoutBalance()
	 {
		 return _AccountBalance;
	 }

	 __declspec(property (get = GetAccoutBalance, put = SetAccountBalance))float AccountBalance;

	  

	 static clsBankClient  Find  (string AccountNumber)
	 {
		 fstream MyFile;
		 MyFile.open("Clients.txt", ios::in);
		 if (MyFile.is_open())
		 {
			 string Line;
			 while (getline(MyFile, Line))
			 {
				 clsBankClient Client = _ConvertLineToClientObject(Line);
				 if (Client.GetAccountNumber() == AccountNumber)
				 { 
					 MyFile.close();
					 return Client;
				 }
			 }
				 MyFile.close();
				 return _GetEmptyClientObject();
		 }
	 }
	    
	 static clsBankClient Find(string  AccountNumber, string PinCode)
	 {
		 fstream MyFile;
		 MyFile.open("Clients.txt", ios::in);
		 if (MyFile.is_open())
		 {
			 string line;
			 while (getline(MyFile, line))
			 {
				 clsBankClient Client = _ConvertLineToClientObject(line);
				 if ((Client.GetAccountNumber() == AccountNumber) &&( Client.GetPinCode() == PinCode))
				 {
					 MyFile.close();
					 return Client;
				 }
			 }
			 MyFile.close();
			 return _GetEmptyClientObject();
		 }
	 }

	 static bool IsClientExist(string AccountNumber)
	 {
		 clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		 return (! Client1.IsEmpty());
	 }
	  
	 enum enSaveResult { svFaildEmptyObject  = 0 , svSucceeded = 1 , svFaildAccountNumberExists= 2 };

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
		 case enMode::AddNewClient :
		 {
			 if (IsClientExist(_AccountNumber))
			 {
				 return enSaveResult::svFaildAccountNumberExists;
				 break;
			 }
			 else
			 {
				 _AddNewClient();
				 _Mode = enMode::UpdateMode;
				 return enSaveResult::svSucceeded;
				 break;
			 }
			 
			}
		 }
	 }

	 bool  Delete()
	 {
		 vector <clsBankClient> vClients = _LoadClientFromFile();

		 for (clsBankClient& C : vClients)
		 {
			 if (C.GetAccountNumber() == _AccountNumber)
			 {
				 C._MarkForDelete = true;
				 break;
			 }
		}
		 _SaveClientsObjectOnFile(vClients);
		 *this = _GetEmptyClientObject();
		 return true; 

	 }

	 static clsBankClient GetNewClientObject(string AccountNumber )
	 {
		 return clsBankClient (enMode::AddNewClient , "","","","",AccountNumber,"",0);
	 }

	 static vector <clsBankClient> GetClientList()
	 {
		 return _LoadClientFromFile();
	 }

	 static double GetTotalBalance()
	 {
		 vector <clsBankClient> vClients = _LoadClientFromFile();
		 double Total = 0 ;
		 for (clsBankClient& Client : vClients)
		 {
			 Total = Total + Client.AccountBalance;
		 }
		 return Total;
	 }
 
	 void Deposit(double Amount)
	 {
		 _AccountBalance += Amount;
		 Save();
		}

	 bool  WithDraw(double Amount)
	 {
		 if (Amount > AccountBalance)
		 {
			 return false;
		 }
		 else
		 {
		 _AccountBalance -= Amount;
			 Save();
			 return true;
		 }
	 }

	 bool Transfer(double Amount , clsBankClient & DistentionClient , string UserName) 
	 {
		 if (Amount > AccountBalance)
		 {
			 return false;
		 }
		 WithDraw(Amount);
		 DistentionClient.Deposit(Amount);
		 _RegisterTransferLog( Amount  , DistentionClient ,  UserName );
		 return true;
	 }

	static  vector < stTransferLogRegister> GetTransferLogList()
	 {
		 fstream MyFile;
		 string Line;
		 stTransferLogRegister Record;
		 vector <stTransferLogRegister> vRecords;
		 MyFile.open("TransferLog.txt" , ios::in );
		 if (MyFile.is_open())
		 {
			 while (getline(MyFile, Line))
			 {
				 Record = _ConvertTransferLineToRecord(Line);
				 vRecords.push_back(Record);
			 }
			 MyFile.close();
		 }
		 return vRecords;
	 }
};




