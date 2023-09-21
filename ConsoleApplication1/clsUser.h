#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include <vector>
#include <fstream>

using namespace std;
class clsUser : public clsPerson
{
private:
 

  enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
  enMode _Mode;
  string _UserName;
  string _Password;
  int _Permissions;

  bool _MarkedForDelete = false;

  static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
  {
    vector<string> vUserData;
    vUserData = clsString::Split(Line, Seperator);

    return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
      vUserData[3], vUserData[4], vUserData[5], stoi(vUserData[6]));

  }

  static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
  {

    string UserRecord = "";
    UserRecord += User.FirstName + Seperator;
    UserRecord += User.LastName + Seperator;
    UserRecord += User.Email + Seperator;
    UserRecord += User.Phone + Seperator;
    UserRecord += User.UserName + Seperator;
    UserRecord += User.Password + Seperator;
    UserRecord += to_string(User.Permissions);

    return UserRecord;

  }

 
  static  vector <clsUser> _LoadUsersDataFromFile()
  {

    vector <clsUser> vUsers;

    fstream MyFile;
    MyFile.open("Users.txt", ios::in);//read Mode

    if (MyFile.is_open())
    {

      string Line;


      while (getline(MyFile, Line))
      {

        clsUser User = _ConvertLinetoUserObject(Line);

        vUsers.push_back(User);
      }

      MyFile.close();

    }

    return vUsers;

  }

  static void _SaveUsersDataToFile(vector <clsUser> vUsers)
  {

    fstream MyFile;
    MyFile.open("Users.txt", ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {

      for (clsUser U : vUsers)
      {
        if (U.MarkedForDeleted() == false)
        {
          //we only write records that are not marked for delete.  
          DataLine = _ConverUserObjectToLine(U);
          MyFile << DataLine << endl;

        }

      }

      MyFile.close();

    }

  }

  void _Update()
  {
    vector <clsUser> _vUsers;
    _vUsers = _LoadUsersDataFromFile();

    for (clsUser& U : _vUsers)
    {
      if (U.UserName == UserName)
      {
        U = *this;
        break;
      }

    }

    _SaveUsersDataToFile(_vUsers);

  }

  void _AddNew()
  {

    _AddDataLineToFile(_ConverUserObjectToLine(*this));
  }

  void _AddDataLineToFile(string  stDataLine)
  {
    fstream MyFile;
    MyFile.open("Users.txt", ios::out | ios::app);

    if (MyFile.is_open())
    {

      MyFile << stDataLine << endl;

      MyFile.close();
    }

  }

  static clsUser _GetEmptyUserObject()
  {
    return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
  }
  
  
  string _PrepareLogInRecord(string Seperator = "#//#")
  {
    string LoginRecord = "";
    LoginRecord += clsDate::GetSystemTimeString() + Seperator;
    LoginRecord += UserName + Seperator;
    LoginRecord += Password + Seperator;
    LoginRecord += to_string(Permissions);
    return LoginRecord;
  }
  struct  stLogUsers;
  static stLogUsers _ConvertLogsLineToObj(string Line,string Seprater="#//#")
  {
    vector<string> vLogs = clsString::Split(Line,Seprater);
    stLogUsers LogUsers;

    LogUsers.DateTime = vLogs[0];
    LogUsers.UserName = vLogs[1];
    LogUsers.Password = vLogs[2];
    LogUsers.Permissions = stoi(vLogs[3]);

    return LogUsers;
  }

public:
  enum enPermissions {
    eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
    pUpdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64,
    pViewLog=128, pCurrencyExchange = 256
  };

  // this only for logsUsers
  struct stLogUsers
  {
    string DateTime;
    string UserName;
    string Password;
    int Permissions;
  };

  clsUser(enMode Mode, string FirstName, string LastName,
    string Email, string Phone, string UserName, string Password,
    int Permissions) :
    clsPerson(FirstName, LastName, Email, Phone)

  {
    _Mode = Mode;
    _UserName = UserName;
    _Password = Password;
    _Permissions = Permissions;
  }

  bool IsEmpty()
  {
    return (_Mode == enMode::EmptyMode);
  }

  bool MarkedForDeleted()
  {
    return _MarkedForDelete;
  }

  string GetUserName()
  {
    return _UserName;
  }

  void SetUserName(string UserName)
  {
    _UserName = UserName;
  }

  __declspec(property(get = GetUserName, put = SetUserName)) string UserName;

  void SetPassword(string Password)
  {
    _Password = Password;
  }

  string GetPassword()
  {
    return _Password;
  }
  __declspec(property(get = GetPassword, put = SetPassword)) string Password;

  void SetPermissions(int Permissions)
  {
    _Permissions = Permissions;
  }

  int GetPermissions()
  {
    return _Permissions;
  }
  __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

  static clsUser Find(string UserName)
  {
    fstream MyFile;
    MyFile.open("Users.txt", ios::in);//read Mode

    if (MyFile.is_open())
    {
      string Line;
      while (getline(MyFile, Line))
      {
        clsUser User = _ConvertLinetoUserObject(Line);
        if (User.UserName == UserName)
        {
          MyFile.close();
          return User;
        }
      }

      MyFile.close();

    }

    return _GetEmptyUserObject();
  }

  static clsUser Find(string UserName, string Password)
  {

    fstream MyFile;
    MyFile.open("Users.txt", ios::in);//read Mode

    if (MyFile.is_open())
    {
      string Line;
      while (getline(MyFile, Line))
      {
        clsUser User = _ConvertLinetoUserObject(Line);
        if (User.UserName == UserName && User.Password == Password)
        {
          MyFile.close();
          return User;
        }

      }

      MyFile.close();

    }
    return _GetEmptyUserObject();
  }

  enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

  enSaveResults Save()
  {

    switch (_Mode)
    {
    case enMode::EmptyMode:
    {
      if (IsEmpty())
      {
        return enSaveResults::svFaildEmptyObject;
      }
    }

    case enMode::UpdateMode:
    {
      _Update();
      return enSaveResults::svSucceeded;

      break;
    }

    case enMode::AddNewMode:
    {
      //This will add new record to file or database
      if (clsUser::IsUserExist(_UserName))
      {
        return enSaveResults::svFaildUserExists;
      }
      else
      {
        _AddNew();
        //We need to set the mode to update after add new
        _Mode = enMode::UpdateMode;
        return enSaveResults::svSucceeded;
      }

      break;
    }
    }

  }

  static bool IsUserExist(string UserName)
  {

    clsUser User = clsUser::Find(UserName);
    return (!User.IsEmpty());
  }

  bool Delete()
  {
    vector <clsUser> _vUsers;
    _vUsers = _LoadUsersDataFromFile();

    for (clsUser& U : _vUsers)
    {
      if (U.UserName == _UserName)
      {
        U._MarkedForDelete = true;
        break;
      }

    }

    _SaveUsersDataToFile(_vUsers);

    *this = _GetEmptyUserObject();

    return true;

  }


  static clsUser GetAddNewUserObject(string UserName)
  {
    return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
  }

  static vector <clsUser> GetUsersList()
  {
    return _LoadUsersDataFromFile();
  }

   bool CheckAccessPermission(enPermissions Permissions)
  {
    if (this->Permissions == enPermissions::eAll) return true;

    if ((Permissions & this->Permissions) == Permissions)
    {
      return true;
    }
    else {
      return false;
    }
    
  }
   
   
   void RegisterLogIn()
   {
     fstream MyFile;
     string stDataLine = _PrepareLogInRecord();
     MyFile.open("LogUsers.txt", ios::out | ios::app);

     if (MyFile.is_open())
     {

       MyFile << stDataLine << endl;

       MyFile.close();
     }

   }
   // only for logs file;
   static vector<stLogUsers> GetLogsUsersList()
   {
      vector <stLogUsers> vLogs;
     fstream Myfile;

     Myfile.open("LogUsers.txt", ios::in);
     if (Myfile.is_open())
     {
       string Line;
       stLogUsers stLog;
      while (getline(Myfile,Line))
      {
        stLog = _ConvertLogsLineToObj(Line);
        vLogs.push_back(stLog);
      }
      Myfile.close();
     }
     return vLogs;
   }
   
};