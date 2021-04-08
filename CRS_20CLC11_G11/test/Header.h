#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <time.h>  
#include <string>
#include <fstream>
#include <filesystem>

#include<io.h>
#include <fcntl.h>

#include<locale>
#include<codecvt>
using namespace std;

struct Date {
	int Day, Month, Year;
};

struct Student {
	int No;
	unsigned long long Student_ID;
	string FirstName;
	string LastName;
	string Gender;
	Date Date_Of_Birth;
	unsigned long long Social_ID;

	double GPA = 0;
};
struct WStudent {
	int No;
	unsigned long long Student_ID;
	wstring FirstName;
	wstring LastName;
	wstring Gender;
	Date Date_Of_Birth;
	unsigned long long Social_ID;

	double GPA = 0;
};

struct NodeStudent {
	Student data;
	NodeStudent* pNext;
};

struct SchoolYear {
	int x;
	int y;
};

struct Course {
	string Course_ID;
	string Course_Name;
	string Teacher_Name;
	int Number_Of_Credits;
	int MaxStu;
};