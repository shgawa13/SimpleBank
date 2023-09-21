#include <iostream>
#include "clsMainScreen.h";
#include "clsLoginScreen.h";
#include "clsDate.h";
using namespace std;


int main()
{


  while (true)
  {
   clsLoginScreen::ShowLoginScreen();
  }
  clsDate::GetSystemDate();
  system("pause>0");
  return 0;
}

