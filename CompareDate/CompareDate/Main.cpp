#include <iostream>
#include <ctime>
#pragma warning(disable : 4996)

using namespace std;

struct Date
{
	int day, month, year;
};

bool operator>= (const Date& a,const Date& b)
{
	if (a.year > b.year)
		return true;
	if (a.year < b.year)
		return false;
	if (a.month > b.month)
		return true;
	if (a.month < b.month)
		return false;
	if (a.day > b.day)
		return true;
	if (a.day < b.day)
		return false;
	return true;
}

bool operator<= (const Date& a, const Date& b)
{
	if (a.year < b.year)
		return true;
	if (a.year > b.year)
		return false;
	if (a.month < b.month)
		return true;
	if (a.month > b.month)
		return false;
	if (a.day < b.day)
		return true;
	if (a.day > b.day)
		return false;
	return true;
}

Date GetSystemDate()
{
	Date a;
	time_t today;
	time(&today);
	tm Today = *localtime(&today);
	a.day = Today.tm_mday;
	a.month = Today.tm_mon + 1;
	a.year = Today.tm_year + 1900;
	return a;
}

int main()
{
	Date a, b;
	a.year = 2021;
	a.month = 5;
	a.day = 1;
	b.year = 2021;
	b.month = 5;
	b.day = 2;
	if (a >= b) cout << "Ngay a sau ngay b";
	else cout << "Ngay a truoc ngay b";
	Date c;
	c = GetSystemDate();
	cout << endl;
	cout << "Ngay:" << c.day << " Thang:" << c.month << " Nam:" << c.year;
}