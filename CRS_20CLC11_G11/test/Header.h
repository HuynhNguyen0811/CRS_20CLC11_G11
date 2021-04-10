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

struct session {
	std::string dayOfWeek;
	std::string hour;
};
struct _session {
	session data;
	_session* pNext, * pPrevious;
};

struct course {
	unsigned long long courseId;
	std::wstring courseName;
	std::wstring teacherName;
	int credit;
	int maxStu = 50;
	_session* session;
};
struct _course {
	course data;
	_course* pNext, * pPrevious;
};