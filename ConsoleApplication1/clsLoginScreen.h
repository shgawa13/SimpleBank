#pragma once
#include <iostream>
#include "clsMainScreen.h"
#include "clsScreen.h"
#include "Global.h" // here we store the current User.

class clsLoginScreen:protected clsScreen
{
private:

	static void _Login()
	{
		bool LoginFiled = false;
		short Trils = 2;

		do {
			string UserName, Password;

			if (LoginFiled)
			{
				cout << "\nInvalid UserName and Password,";
				cout << "\nYou Have: " << Trils-- << " left";
			}

			cout << "\nPlease Enter UserName: ";
			cin >> UserName;

			cout << "\nPlease Enter Password: ";
			cin >> Password;

			CurrentUser = clsUser::Find(UserName, Password);
			LoginFiled = CurrentUser.IsEmpty();
			
			if (Trils ==0) {
				cout << "\nYour Account is locked";
				exit(0);
			}

		} while (LoginFiled);
	
		CurrentUser.RegisterLogIn();
		// if login Successeded  we show main menu
		clsMainScreen::ShowMainMenue();
	}
public:

	static void ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\tLogin Screen");
		_Login();

	}
};

