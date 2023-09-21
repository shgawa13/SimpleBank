#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsScreen.h"
class clsDeleteUserScreen:protected clsScreen
{
private:
	static void _PrintUser(clsUser& User)
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

public:

	static void ShowDeleteUserScreen()
	{
		string UserName = "";
		_DrawScreenHeader("\t Delete User Screen");

		cout << "\nPlease Enter UserName: ";
		cin >> UserName;
		// this can handle it
		if (UserName =="Admin")
		{
			cout << "\nSorry you can't delete this user";
			return;
		}
	
		while (!clsUser::IsUserExist(UserName))
		{
			cout <<"\n Sorry, UserName is not Exist,\n Please Enter Another UserName: ";
	  	cin >> UserName;
		}

		clsUser User1 = clsUser::Find(UserName);
		_PrintUser(User1);

		char Answer = 'n';
		cout << "\n Are you sure you want to delete this User (y/n): ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			if (User1.Delete())
			{
				cout << "\n User " << UserName << " Has been Deleted Successfully";
				_PrintUser(User1);
			}
			else
			{
				cout << "\nError User Was not Deleted\n";
			}
		}
	}
};

