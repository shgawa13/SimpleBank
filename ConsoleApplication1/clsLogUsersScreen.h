#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsString.h"
#include "clsUser.h"
#include <vector>
#include <iomanip>
using namespace std;

class clsLogUsersScreen:protected clsScreen
{
private:
  
  static void PrintUserRecordLine(clsUser::stLogUsers User)
  {

    cout << setw(8) << left << "" << "| " << setw(45) << left << User.DateTime;
    cout << "| " << setw(20) << left << User.UserName;
    cout << "| " << setw(12) << left << User.Password;
    cout << "| " << setw(10) << left << User.Permissions;

  }

public:



	static void ShowLogUsersScreen()
	{
    if (!CheckAccessRight(clsUser::enPermissions::pManageUsers))
    {
      return;
    }

    vector<clsUser::stLogUsers> vUsers = clsUser::GetLogsUsersList();
    string Title = "    Log Users Screen";
    string SupTitle = "\t     (" + to_string(vUsers.size()) + ") Log(s).";
    _DrawScreenHeader(Title,SupTitle);

    cout << setw(8) << left << "" << "\n\t_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << setw(8) << left << "" << "| " << left << setw(45) << "Date/Time";
    cout << "| " << left << setw(20) << "UserName";
    cout << "| " << left << setw(12) << "Password";
    cout << "| " << left << setw(10) << "Permissions";
    cout << setw(8) << left << "" << "\n\t_______________________________________________________";
    cout << "_________________________________________\n" << endl;

   

      for (clsUser::stLogUsers User: vUsers)
      {

        PrintUserRecordLine(User);
        cout << endl;
      }

    cout << setw(8) << left << "" << "\n\t_______________________________________________________";
    cout << "_________________________________________\n" << endl;

	}
};

