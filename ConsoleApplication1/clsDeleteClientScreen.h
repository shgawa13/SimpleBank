#pragma once
#include <iostream>
#include "clsBankClient.h";
#include "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;

class clsDeleteClientScreen:protected clsScreen
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
	static void ShowDeleteClientScreen()
	{
    if (!CheckAccessRight(clsUser::enPermissions::pDeleteClient))
    {
      return;
    }
    _DrawScreenHeader("   Delete Client Screen");
    string AccountNumber = "";
    cout << "\nPlease Enter Account Number: ";
    AccountNumber = clsInputValidate::ReadString();

    while (!clsBankClient::IsClientExist(AccountNumber))
    {
      cout << "\nError, Account number is not Exist\nPlease Enter Account Number: ";
      AccountNumber = clsInputValidate::ReadString();
    }
    clsBankClient Clinet = clsBankClient::Find(AccountNumber);
    _PrintClient(Clinet);

    cout << "\nAre you sure to Delete this Client? (y/n) : ";
    char Answer = 'n';
    cin >> Answer;

    if (tolower(Answer) == 'y')
    {
      if (Clinet.Delete())
      {
        cout << "\nClient Has been Deleted Successfully\n";
        _PrintClient(Clinet);
      }
      else
      {
        cout << "Error Client was not Deleted";
      }
    }
	}
};

