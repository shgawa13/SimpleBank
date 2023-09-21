#pragma once
#include <iostream>;
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;

class clsDepositScreen:protected clsScreen
{
private:
	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";

	}
public:

	static void ShowDepositScreen()
	{
		_DrawScreenHeader("  Deposit Screen");
		string AccountNumber = "";

		cout << "\nPlease Enter AccountNumber: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nSorry Account Number is not Exist,lease Enter AccountNumber: ";
	   	AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);


		float DepositAmount = 0;
		cout << "\nPlease Enter Deposit Amont: ";
		DepositAmount = clsInputValidate::ReadFloatNumber();

		char Answer = 'n';
		cout << "\nAre you Sure To preform this Transaction (y/n): ";
		cin >> Answer; 

		if (tolower(Answer) == 'y')
		{
			Client.Deposit(DepositAmount);
			cout << "\nAmout Deposit Successfully";
			cout << "\nYour new Balance is : " << Client.AccountBalance;
		}
		else
		{
			cout << "\nTransaction was Cancled";
		}
		
	}
};

