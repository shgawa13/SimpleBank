#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrencyListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
using namespace std;

class clsCurrencyExchangeMenu:protected clsScreen
{
private:
	enum enCurrencyExchangeOpations {eListCurrency=1,eFindCurrency=2,
       eUpdateRate=3,eCurrencyCalculator=4,eMainMenue=5};

  static short ReadCurrencyExChangeOption()
  {
    cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
    short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5? ");
    return Choice;
  }

  static void _GoBackToCurrencyMenue()
  {
    cout << "\n\nPress any key to go back to Manage Users Menue...";
    system("pause>0");
    ShowCurrencyExChangeMenue();
  }

  static void _ShowListCurrencyScreen()
  {
    //cout << "\n Currency Screen will be here\n";
    clsCurrencyListScreen::ShowCurrencyListScreen();
  }

  static void _ShowFindCurrencyScreen()
  {
    //cout << "\n Find Currency Screen will be here\n";
    clsFindCurrencyScreen::ShowFindCurrencyScreen();
  }

  static void _ShowUpdateRateScreen()
  {
   // cout << "\n UpdateRate Screen will be here\n";
    clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
  }

  static void _ShowCurrencyCalculatorScreen()
  {
   // cout << "\n Currency Calculator Screen";
    clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
  }
  static void _PerformCurrencyExchangeMenueOption(enCurrencyExchangeOpations CurrencyExOption)

  {
    switch (CurrencyExOption)
    {
    case enCurrencyExchangeOpations::eListCurrency:
      system("cls");
      _ShowListCurrencyScreen();
      _GoBackToCurrencyMenue();
      break;
    case enCurrencyExchangeOpations::eFindCurrency:
      system("cls");
      _ShowFindCurrencyScreen();
      _GoBackToCurrencyMenue();
      break;
    case enCurrencyExchangeOpations::eUpdateRate:
      system("cls");
      _ShowUpdateRateScreen();
      _GoBackToCurrencyMenue();
      break;
    case enCurrencyExchangeOpations::eCurrencyCalculator:
      system("cls");
      _ShowCurrencyCalculatorScreen();
      _GoBackToCurrencyMenue();
      break;
    case clsCurrencyExchangeMenu::eMainMenue:
    {

    }
    }
  }

public:

  
	static void ShowCurrencyExChangeMenue()
	{
    system("cls");
		_DrawScreenHeader("Currency Exchange Screen");

    cout << setw(37) << left << "" << "===========================================\n";
    cout << setw(37) << left << "" << "\t\t  Currency Exchange Menue\n";
    cout << setw(37) << left << "" << "===========================================\n";
    cout << setw(37) << left << "" << "\t[1] List Currency.\n";
    cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
    cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
    cout << setw(37) << left << "" << "\t[4] Currency calculator.\n";
    cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
    cout << setw(37) << left << "" << "===========================================\n";
    _PerformCurrencyExchangeMenueOption((enCurrencyExchangeOpations)ReadCurrencyExChangeOption());
	}

};

