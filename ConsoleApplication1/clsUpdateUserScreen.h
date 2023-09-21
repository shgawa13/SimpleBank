#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
using namespace std;

class clsUpdateUserScreen:protected clsScreen
{
private:

  static void _ReadUserInfo(clsUser& User)
  {
    cout << "\nEnter FirstName: ";
    User.FirstName = clsInputValidate::ReadString();

    cout << "\nEnter LastName: ";
    User.LastName = clsInputValidate::ReadString();

    cout << "\nEnter Email: ";
    User.Email = clsInputValidate::ReadString();

    cout << "\nEnter Phone: ";
    User.Phone = clsInputValidate::ReadString();

    cout << "\nEnter Password: ";
    User.Password = clsInputValidate::ReadString();

    cout << "\nEnter Permissons: ";
    User.Permissions = _ReadPermissionsToSet();
  }

  static void _PrintUser(clsUser User)
  {
    cout << "\nUser Card:";
    cout << "\n___________________";
    cout << "\nFirstName   : " << User.FirstName;
    cout << "\nLastName    : " << User.LastName;
    cout << "\nFull Name   : " << User.FullName();
    cout << "\nEmail       : " << User.Email;
    cout << "\nPhone       : " << User.Phone;
    cout << "\nUser Name   : " << User.UserName;
    cout << "\nPassword    : " << User.Password;
    cout << "\nPermissions : " << User.Permissions;
    cout << "\n___________________\n";
  }

  static int _ReadPermissionsToSet()
  {
    int Permissions = 0;
    char Answer = 'n';

    cout << "\n Do You want to give Full access (y/n): ";
    cin >> Answer;
    if (tolower(Answer) == 'y')
    {
      return -1;
    }

    cout << "\n Do you want to give access to: ";
    cout << "\n Show Client List (y/n): ";
    cin >> Answer;
    if (tolower(Answer) == 'y')
    {
      Permissions += clsUser::enPermissions::pListClients;
    }

    cout << "\n Add New Client (y/n): ";
    cin >> Answer;
    if (tolower(Answer) == 'y')
    {
      Permissions += clsUser::enPermissions::pAddNewClient;
    }

    cout << "\n Delete Client (y/n): ";
    cin >> Answer;
    if (tolower(Answer) == 'y')
    {
      Permissions += clsUser::enPermissions::pDeleteClient;
    }

    cout << "\n Update Client (y/n): ";
    cin >> Answer;
    if (tolower(Answer) == 'y')
    {
      Permissions += clsUser::enPermissions::pUpdateClient;
    }

    cout << "\n Find Client (y/n): ";
    cin >> Answer;
    if (tolower(Answer) == 'y')
    {
      Permissions += clsUser::enPermissions::pFindClient;
    }

    cout << "\n Add New Client (y/n): ";
    cin >> Answer;
    if (tolower(Answer) == 'y')
    {
      Permissions += clsUser::enPermissions::pAddNewClient;
    }

    cout << "\n Transaction (y/n): ";
    cin >> Answer;
    if (tolower(Answer) == 'y')
    {
      Permissions += clsUser::enPermissions::pTransactions;
    }

    cout << "\n Manage Users (y/n): ";
    cin >> Answer;
    if (tolower(Answer) == 'y')
    {
      Permissions += clsUser::enPermissions::pManageUsers;
    }

    cout << "\n View UsersLogs (y/n): ";
    cin >> Answer;
    if (tolower(Answer) == 'y')
    {
      Permissions += clsUser::enPermissions::pViewLog;
    }
    return Permissions;
  }

public:

	static void ShowUpdateUserScreen()
	{
		_DrawScreenHeader("\t Update User");

		string UserName = "";
		cout << "\nPlease Enter UserName: ";
		UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\n Sorry, UserName is not Exist,\n Please Enter UserName: ";
	  	UserName = clsInputValidate::ReadString();
		}
		
		clsUser User1 = clsUser::Find(UserName);
		_PrintUser(User1);

    char Answer = 'n';
    cout << "\n Are you sure to Update this user (y/n): ";
    cin >> Answer; 

    if (tolower(Answer) == 'y')
    {

      cout << "\nUpdate Client Info: \n";
      cout << "_______________________\n";
      _ReadUserInfo(User1);

      clsUser::enSaveResults SaveResult;
      SaveResult = User1.Save();

      switch (SaveResult)
      {
        case  clsUser::enSaveResults::svSucceeded:
        {
          cout << "\nUser Updated Successfully\n";

          _PrintUser(User1);
          break;
        }
        case clsUser::enSaveResults::svFaildEmptyObject:
        {
          cout << "\nError User was not saved because it's Empty";
          break;

        }

      }
    }


	}

};

