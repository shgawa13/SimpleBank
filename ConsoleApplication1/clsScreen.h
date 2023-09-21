#pragma once
#include <iostream>;
#include "Global.h"
#include "clsDate.h"
#include <string>
using namespace std;
class clsScreen
{
protected:

	static void _DrawScreenHeader(string Title, string SubTitle = "")
	{
		cout << "\t\t\t\t ---------------------------------------------------------"<<endl;
		cout << "\t\t\t\t\t\t" << Title << endl;

		if (SubTitle != "")
		{
			cout <<"\n\t\t\t\t\t"<< SubTitle << endl;
		}

		cout << "\t\t\t\t ---------------------------------------------------------"<<endl;

		cout << "\t\t\t\t\t\t\tUser:" << CurrentUser.GetUserName();
		cout << "\n\t\t\t\t\t\t\t" << clsDate::DateToString(clsDate())<<endl;
	}

	static  bool CheckAccessRight(clsUser::enPermissions Permissions)
	{
		if (!CurrentUser.CheckAccessPermission(Permissions))
		{
			cout << "\t\t\t\t\t______________________________________";
			cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
			cout << "\n\t\t\t\t\t______________________________________\n\n";
			return false;
		}
		else
		{
			return true;
		}
	}
};

