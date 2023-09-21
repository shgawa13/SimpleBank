#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h";
using namespace std;

class clsShowWithdrawScreen:protected clsScreen
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

  static void ShowWithdrawScreen()
  {
    _DrawScreenHeader(" Withdraw Screen");
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

    float WithdrawAmount = 0;
    cout << "\nPlease Enter Withdraw Amont: ";
    WithdrawAmount = clsInputValidate::ReadFloatNumber();

    if (Client.Withdraw(WithdrawAmount)) {

      char Answer = 'n';
      cout << "\nAre you Sure To preform this Transaction (y/n): ";
      cin >> Answer;

      if (tolower(Answer) == 'y')
      {
        
        cout << "\nAmout  WithdrawAmount Successfully";
        cout << "\nYour new Balance is : " << Client.AccountBalance;
      }
      else
      {
      cout << "\nTransaction was Cancled";
      }
    }
    else
    {
      cout << "Sorry Your Amount is lower than: " << WithdrawAmount;
    }

  }
};

