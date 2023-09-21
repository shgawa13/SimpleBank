#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;

class clsTransferScreen:protected clsScreen
{
private:

	static void _PrintClientCard(clsBankClient Client)
	{
    cout << "\nClient Card:";
    cout << "\n___________________\n";
		cout << "\nFull Name   : " << Client.FullName();
    cout << "\nAcc. Number : " << Client.AccountNumber();
    cout << "\nBalance     : " << Client.AccountBalance;
    cout << "\n___________________\n";
	}

	static string _GetAccountNumber()
	{
		string AccountNumber = "";
		AccountNumber = clsInputValidate::ReadString();

		if (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\n Sorry, this Account doesn't";
			cout << "\n Please Enter Account Number You want Transfer From: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		return AccountNumber;
	}

	static float _GetAmount(clsBankClient SourceClient)
	{
		float Amount = 0;
		cout << "\nPlease Enter the Amount You want to Treansfer: ";
		Amount = clsInputValidate::ReadFloatNumber();

		while (Amount > SourceClient.AccountBalance)
		{
			cout << "Amont Exceed the Available blance, Please Enter Another Amount ";
			Amount = clsInputValidate::ReadFloatNumber();
		}
		return Amount;
	}

public: 

	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\tTransfer Screen");

		// here is the source Account
	
		cout << "\nPlease Enter Account Number You want Transfer From: ";
		clsBankClient SourceClient = clsBankClient::Find( _GetAccountNumber());
		_PrintClientCard(SourceClient);


		// Here is the destionation Account
		string AccountNumberTo = "";
		cout << "\n Please Enter AccountNumber that you want transfer to: ";
		AccountNumberTo = _GetAccountNumber();
		clsBankClient ClientTo= clsBankClient::Find(AccountNumberTo);

		float Amount = _GetAmount(SourceClient);
	
		char Answer = 'n';
		cout << "\n Are you sure to preform this Transactio (y/n): ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			if (SourceClient.Transfer(Amount, ClientTo))
			{
				cout << "\n Transfer Done Successfully";

			}
			else
			{
				cout << "\ Sorry Transfer Faild";
			}
	   _PrintClientCard(SourceClient);
		 _PrintClientCard(ClientTo);
		}
		

	}

};

