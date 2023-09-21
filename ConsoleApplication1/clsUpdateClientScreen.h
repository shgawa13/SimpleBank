#pragma once
#include <iostream>
#include "clsScreen.h";
#include "clsBankClient.h";
#include "clsInputValidate.h";
using namespace std;

class clsUpdateClientScreen:protected clsScreen
{
private:
  static void _ReadClientInfo(clsBankClient& Client)
  {
    cout << "\nEnter FirstName: ";
    Client.FirstName = clsInputValidate::ReadString();

    cout << "\nEnter LastName: ";
    Client.LastName = clsInputValidate::ReadString();

    cout << "\nEnter Email: ";
    Client.Email = clsInputValidate::ReadString();

    cout << "\nEnter Phone: ";
    Client.Phone = clsInputValidate::ReadString();

    cout << "\nEnter PinCode: ";
    Client.PinCode = clsInputValidate::ReadString();

    cout << "\nEnter Account Balance: ";
    Client.AccountBalance = clsInputValidate::ReadFloatNumber();
  } 

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

	static void ShowUpdateClientScreen()
	{
    if (!CheckAccessRight(clsUser::enPermissions::pUpdateClient))
    {
      return;
    }
    _DrawScreenHeader("Update Client Screen");
    
    string AccountNumber = "";
    cout << "\nPlease Enter Account Number: ";
    AccountNumber = clsInputValidate::ReadString();

    while (!clsBankClient::IsClientExist(AccountNumber))
    {
      cout << "\Error, Account Number is not Exist\nPlease Enter Different Account Number: ";
      AccountNumber = clsInputValidate::ReadString();
    }

    clsBankClient Client = clsBankClient::Find(AccountNumber);
    _PrintClient(Client);

    cout << "\nUpdate Client Info: \n";
    cout << "_______________________\n";
    _ReadClientInfo(Client);

    clsBankClient::enSaveResults SaveResult;
    SaveResult = Client.Save();

    switch (SaveResult)
    {
    case clsBankClient::svSucceeded:
    {
      cout << "\n Account Saved Successfully (^_^)\n";
      _PrintClient(Client);
      break;
    }
    case clsBankClient::svFaildEmptyObject:
    {
      cout << "\Error Account was not save because it's Empty!\n";
      break;
    }

    }

	}
};

