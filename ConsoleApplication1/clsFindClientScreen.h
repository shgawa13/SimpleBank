#pragma once
#include <iostream>
#include "clsBankClient.h";
#include "clsInputValidate.h";
#include "clsScreen.h"
class clsFindClientScreen:protected clsScreen
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
  static void ShowFindClientScreen()
  {
    if (!CheckAccessRight(clsUser::enPermissions::pFindClient))
    {
      return;
    }
    _DrawScreenHeader(" Find Clinet Screen");

    string AccountNumber = "";
    cout << "\nPlease Enter Account Number: ";
    AccountNumber = clsInputValidate::ReadString();

    while (!clsBankClient::IsClientExist(AccountNumber))
    {
      cout << "Sorry,this Account doesn't Exist,\nPlease Enter Different Account Number: ";
      AccountNumber = clsInputValidate::ReadString();
    }

    clsBankClient Client = clsBankClient::Find(AccountNumber);
    
    if (!Client.IsEmpty())
    {
      cout << "\nClient Was Found\n";
    }
    else
    {
      cout << "\nSorry Client Was not  Found\n";

    }
    _PrintClient(Client);
  }
};

