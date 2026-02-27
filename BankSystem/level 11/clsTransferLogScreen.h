#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsTransferLogScreen : protected clsScreen
{
private:

	static void _PrintTransferLogRecord(clsBankClient::stTransferLogRegister  Record)
	{
		cout << setw(8) << left << "" << "| " << left << setw(30) << Record.Date;	
		cout << "| " << left << setw(10) << Record.SClient;
		cout << "| " << left << setw(10) << Record.DClient;
		cout << "| " << left << setw(10) << Record.Amount;
		cout << "| " << left << setw(10) << Record.SBalance;
		cout << "| " << left << setw(10) << Record.DBalance ;
		cout << "| " << left << setw(10) << Record.UserName;
	}

public : 

	static void ShowTransferLogScreen()
	{
		vector <clsBankClient::stTransferLogRegister> vRecords = clsBankClient::GetTransferLogList();

		string Title = "Transfer Register List Screen";
		string SubTitle = "\t(" + to_string(vRecords.size()) + ") Record(s).";

		_DrawScreenHeader(Title , SubTitle);

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "___________________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(30) << "Date/Time";
		cout << "| " << left << setw(10) << "S.Client";
		cout << "| " << left << setw(10) << "D.Client";
		cout << "| " << left << setw(10) << "Amount";
		cout << "| " << left << setw(10) << "S.Balance";
		cout << "| " << left << setw(10) << "D.Balance";
		cout << "| " << left << setw(10) << "UserName";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "___________________________________________________\n" << endl;

		if (vRecords.size() == 0)
			cout << "\t\t\t\t No Records Available in the system !!!\n\n";

		for (clsBankClient::stTransferLogRegister& Record : vRecords)
		{
			_PrintTransferLogRecord(Record);
			cout << endl;
		}
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "___________________________________________________\n" << endl;
	}


};

