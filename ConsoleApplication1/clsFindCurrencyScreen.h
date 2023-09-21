#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
class clsFindCurrencyScreen:clsScreen
{
private:

	static void _PrintCurrencyCard(clsCurrency Currency)
	{
		cout << "\nCurrency Card:\n";
		cout << "_____________________________\n";
		cout << "\nCountry    : " << Currency.Country();
		cout << "\nCode       : " << Currency.CurrencyCode();
		cout << "\nName       : " << Currency.CurrencyName();
		cout << "\nRate(1$) = : " << Currency.Rate();

		cout << "\n_____________________________\n";
	}
	static short _ReadCurrencyOption()
	{
		short Number = 0;
		cout << "\nFind by: [1] Code or [2] Country: ";
		Number = clsInputValidate::ReadIntNumberBetween(1, 2);
		return Number;
	}

	

public:

	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader(" Find Currency Screen\n");
		short Option = _ReadCurrencyOption();
		string stFind = "";

		switch (Option)
		{
		case 1:
		{
			cout << "\nPlease Enter Currency Code: ";
			stFind = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCode(stFind);
			_PrintCurrencyCard(Currency);
			break;
		}
		
		case 2: 
		{
			cout << "\nPlease Enter Country Name: ";
			stFind = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCountry(stFind);
			_PrintCurrencyCard(Currency);
			break;
		}
		}
	}
};

