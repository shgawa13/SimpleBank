#pragma warning(disable : 4996)

#include <iostream>

using namespace std;
enum enDays { Sun, Mon, Tus, When, Thir, Fri, Satr };
enum enDateCompare { Before = -1, Equal = 0, After = 1 };
bool IsLeapYear(short Year)
{
  return (Year % 4 == 0 && Year % 100 != 0 || Year % 400 == 0);
}
short ReadYear()
{
  int Number = 0;
  cout << "please Enter Number of Year: ";
  cin >> Number;
  return Number;
}
short ReadMonth() {
  short Month = 0;
  cout << "\nPlease Enter Number of month: ";
  cin >> Month;
  return Month;
}
short ReadDay()
{
  short Day = 0;
  cout << "please Enter Number of Day: ";
  cin >> Day;
  return Day;
}
short ReadAddDays()
{
  short Days = 0;
  cout << "How many Days you want to add? ";
  cin >> Days;
  return Days;
}
struct sDate
{
  short Year;
  short Month;
  short Days;
};
string DaysShortname(short Index)
{
  string DaysOfWeek[7] = { "Sun","Mon","Tus","When","Thir","Fri","Satr" };
  return DaysOfWeek[Index];
}
string MonthShortName(short Month)
{
  string MonthName[12] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Des" };
  return MonthName[Month - 1];
}
short NumbersOfDaysInYear(short Year)
{
  return IsLeapYear(Year) ? 366 : 365;
}
short NumbersOfDaysInMonth(short Year, short Month)
{
  if (Month < 1 || Month > 12) return 0;

  short DaysOfMonths[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

  return  (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : DaysOfMonths[Month - 1];
}
int NumbersOfHoursInYear(short Year, short Month) {
  return NumbersOfDaysInMonth(Year, Month) * 24;
}
int NumberOfMintusInYear(short Year, short Month)
{
  return NumbersOfHoursInYear(Year, Month) * 60;
}
int NumberOfSecondesInYear(short Year, short Month)
{
  return NumberOfMintusInYear(Year, Month) * 60;
}

short DaysOfWeekOrder(short Year, short Month, short Day)
{
  int a = (14 - Month) / 12;
  int y = Year - a;
  int m = Month + (12 * a) - 2;
  int d = (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
  return d;
}

void ShowMonth(short Month, short Year)
{
  short NumberOfDays;
  int current = DaysOfWeekOrder(Year, Month, 1);
  NumberOfDays = NumbersOfDaysInMonth(Year, Month);

  printf("\n  _______________%s_______________\n\n", MonthShortName(Month).c_str());
  printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
  short i;
  for (i = 0; i < current; i++)  printf("     ");

  for (short j = 1; j <= NumberOfDays; j++) {

    printf("%5d", j);

    if (++i == 7)
    {
      i = 0;
      printf("\n");
    }
  }

  cout << "\n  _________________________________\n";

}
void ShowCalander(short Year)
{
  cout << "-------------------------------------\n";
  cout << "\tCalneder of Year: " << Year << "\n";
  cout << "-------------------------------------\n";
  for (short i = 1; i <= 12; i++)
  {
    //short DaysOfWeek = DaysOfWeekOrder(Year, i, 1);

    ShowMonth(i, Year);
  }
}
short ShowTotalNumberFromBeginig(short Year, short Month, short Days)
{
  short TotalOfDays = 0;

  for (short i = 1; i <= Month - 1; i++)
  {
    TotalOfDays += NumbersOfDaysInMonth(Year, i);

  }
  TotalOfDays += Days;
  return TotalOfDays;
}
sDate GetDateFromOrderDays(short RemaingDaysInYear, short Year)
{
  sDate Date;
  short MonthDays = 0;
  short RemaingDays = RemaingDaysInYear;

  Date.Month = 1;
  Date.Year = Year;

  while (true)
  {
    MonthDays = NumbersOfDaysInMonth(Date.Year, Date.Month);
    if (RemaingDays > MonthDays)
    {
      RemaingDays -= MonthDays;
      Date.Month++;
    }
    else
    {
      Date.Days = RemaingDays;
      break;
    }
  }
  return Date;
}
sDate AddDaysToDate(sDate Date, short DaysToAdd)
{

  short RemaingDays = DaysToAdd + ShowTotalNumberFromBeginig(Date.Year, Date.Month, Date.Days);
  short MonthDays = 0;

  Date.Month = 1;
  while (true)
  {
    MonthDays = NumbersOfDaysInMonth(Date.Year, Date.Month);
    if (RemaingDays > MonthDays)
    {
      RemaingDays -= MonthDays;
      Date.Month++;
      if (Date.Month > 12)
      {
        Date.Month = 1;
        Date.Year++;
      }
    }
    else
    {
      Date.Days = RemaingDays;
      break;
    }
  }
  return Date;
}
sDate ReadFullDate()
{
  sDate Date;
  Date.Days = ReadDay();
  Date.Month = ReadMonth();
  Date.Year = ReadYear();

  return Date;
}
struct sPeriod {
  sDate Start;
  sDate End;
};
sPeriod ReadPriod()
{
  sPeriod Priod;
  cout << "Start Priod\n";
  Priod.Start = ReadFullDate();
  cout << "\nEnd Priod\n";
  Priod.End = ReadFullDate();

  return Priod;
}
bool IsDate1BeforeDate2(sDate Date1, sDate Date2)
{

  return (Date1.Year < Date2.Year) ? true
    : ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true
      : (Date1.Month < Date2.Month ? true
        : (Date1.Month == Date2.Month ? Date1.Days < Date2.Days : false))) : false);
}
bool IsDateEqual(sDate Date1, sDate Date2)
{
  return (Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month) ? ((Date1.Days == Date2.Days) ? true : false) : false) : false;
}
bool IsLastDayInMonth(sDate Date)
{
  short TotalDaysInMonth = NumbersOfDaysInMonth(Date.Year, Date.Month);
  return (TotalDaysInMonth == Date.Days);
}
bool IsLastMonthInYear(sDate Date)
{
  return (Date.Month == 12);
}
bool IsWeekEnd(sDate Date)
{
  short DayIndex = DaysOfWeekOrder(Date.Year, Date.Month, Date.Days);
  return (DayIndex == 5 || DayIndex == 6);
}
bool IsBusinessDay(sDate Date)
{
  return !IsWeekEnd(Date);
}
bool IsDate1AferDate2(sDate Date1, sDate Date2)
{
  return (!IsDate1BeforeDate2(Date1, Date2) && !IsDateEqual(Date1, Date2));
}
sDate IncreaseDateByoneDay(sDate Date1)
{
  if (IsLastDayInMonth(Date1))
  {
    if (IsLastMonthInYear(Date1))
    {
      Date1.Days = 1;
      Date1.Month = 1;
      Date1.Year++;
    }
    else
    {
      Date1.Days = 1;
      Date1.Month++;
    }
  }
  else {
    Date1.Days++;
  }
  return Date1;
}
int ShowTheDiffrent(sDate Date1, sDate Date2, bool IncludeEndDay = false)
{
  int Days = 0;

  while (IsDate1BeforeDate2(Date1, Date2))
  {
    Days++;
    Date1 = IncreaseDateByoneDay(Date1);
  }

  return IncludeEndDay ? ++Days : Days;
}
sDate GetSystemDate()
{
  sDate Date;
  time_t t = time(0);
  tm* now = localtime(&t);

  Date.Year = now->tm_year + 1900;
  Date.Month = now->tm_mon + 1;
  Date.Days = now->tm_mday;
  return Date;
}
sDate IncreaseDateByXDays(sDate& Date1, short Days)
{


  for (short i = 1; i <= Days; i++) {
    Date1 = IncreaseDateByoneDay(Date1);
  }

  return Date1;
}
sDate IncreaseDateByOneWeek(sDate& Date1)
{
  for (short i = 1; i <= 7; i++)
  {
    Date1 = IncreaseDateByoneDay(Date1);
  }
  return Date1;
}
sDate IncreaseDateByXWeeks(sDate& Date1, short Weeks)
{
  for (short i = 1; i <= Weeks; i++)
  {
    Date1 = IncreaseDateByOneWeek(Date1);
  }
  return Date1;
}
sDate IncreaseDateByOneMonth(sDate& Date1)
{
  if (Date1.Month == 12) {
    Date1.Month = 1;
    Date1.Year++;
  }
  else {
    Date1.Month++;
  }

  short DaysInMonth = NumbersOfDaysInMonth(Date1.Year, Date1.Month);

  if (Date1.Days > DaysInMonth) {
    Date1.Month = DaysInMonth;
  }
  return Date1;
}
enDateCompare CompareDates(sDate Date1, sDate Date2)
{
  if (IsDate1BeforeDate2(Date1, Date2)) return enDateCompare::Before;

  if (IsDateEqual(Date1, Date2)) return enDateCompare::Equal;
  /* if (IsDate1AfterDate2(Date1,Date2))
  return enDateCompare::After;*/
  //this is

  return enDateCompare::After;
}
bool IsOverLap(sPeriod Date1, sPeriod Date2)
{
  if (
    CompareDates(Date2.End, Date1.Start) == enDateCompare::Before
    ||
    CompareDates(Date2.Start, Date1.End) == enDateCompare::After
    )
    return false;
  else
    return true;
}
sDate IncreaseDateByXMonth(sDate& Date1, short Monthes)
{
  for (short i = 1; i <= Monthes; i++)
  {
    IncreaseDateByOneMonth(Date1);
  }
  return Date1;
}
sDate IncreaseDateByOneYear(sDate& Date1)
{
  Date1.Year++;
  return Date1;
}
short GetTotalVecationDays(sDate DateFrom, sDate DateTo)
{
  short DaysCount = 0;
  while (IsDate1BeforeDate2(DateFrom, DateTo))
  {
    if (IsBusinessDay(DateFrom)) DaysCount++;
    DateFrom = IncreaseDateByoneDay(DateFrom);
  }
  return DaysCount;
}
sDate VecationReturnDate(sDate& Date1, short VecationDays)
{
  while (VecationDays > 0)
  {
    if (IsBusinessDay(Date1)) {
      VecationDays--;
    }
    Date1 = IncreaseDateByoneDay(Date1);
  }

  return Date1;
}
void  ShowInformation(sDate OriginalDate)
{
  sDate Date;
  Date = IncreaseDateByoneDay(OriginalDate);
  cout << "\n01 - Increase Date by one day: " << Date.Year << "/" << Date.Month << "/" << Date.Days;
  Date = IncreaseDateByXDays(Date, 10);
  cout << "\n02 - Increase Date by X days: " << Date.Year << "/" << Date.Month << "/" << Date.Days;
  Date = IncreaseDateByOneWeek(Date);
  cout << "\n03 - Increase Date by One Week: " << Date.Year << "/" << Date.Month << "/" << Date.Days;
  Date = IncreaseDateByXWeeks(Date, 10);
  cout << "\n04 - Increase Date by 10 Week: " << Date.Year << "/" << Date.Month << "/" << Date.Days;
  Date = IncreaseDateByOneMonth(Date);
  cout << "\n05 - Increase Date by One Month " << Date.Year << "/" << Date.Month << "/" << Date.Days;
  Date = IncreaseDateByXMonth(Date, 10);
  cout << "\n06 - Increase Date by 10 Month " << Date.Year << "/" << Date.Month << "/" << Date.Days;
  Date = IncreaseDateByOneYear(Date);
  cout << "\n06 - Increase Date by One Year " << Date.Year << "/" << Date.Month << "/" << Date.Days;

}
