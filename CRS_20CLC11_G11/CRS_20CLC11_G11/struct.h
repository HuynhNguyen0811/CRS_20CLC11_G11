#ifndef _STRUCT_H_
#define _STRUCT_H_

#include <iostream>

struct student;
struct _student;
struct _studentRegis;
struct Class;
struct _Class;
struct semester;
struct _semester;
struct session;
struct course;
struct _course;
struct score;
struct _score;
struct account;
struct _account;

struct Date {
	int day, month, year;
};

struct student {
	int No;
	unsigned long long Student_ID;
	std::wstring FirstName;
	std::wstring LastName;
	std::wstring Gender;
	Date Date_Of_Birth;
	unsigned long long Social_ID;

	_score* score = nullptr;
	//_course* course = nullptr;
	int** timeTable = nullptr;
};
struct _student {
	student data;
	_student* pNext;
};

struct _studentRegis {
	int no;
	unsigned long long data;
	std::wstring name;
	double total = 0, final = 0, mid = 0, other = 0, gpa = 0;
	_studentRegis* pNext;
};

struct Class {
	std::string name;
	_student* student;
};
struct _Class {
	Class data;
	_Class* pNext, * pPrevious;
};

struct semester {
	Date startDay, endDate;
};
struct _semester {
	semester data;
	_semester* pNext, * pPrevious;
};

struct session {
	std::wstring dayOfWeek;
	std::wstring hour;
};
struct course {
	unsigned long long courseId;
	std::wstring courseName;
	std::wstring teacherName;
	int credit;
	int maxStu = 50;
	session* session;
	_studentRegis* studentID = nullptr;
	Date startRegis = { 0, 0, 0 }, endRegis = { 0, 0, 0 };
};
struct _course {
	course data;
	_course* pNext;
};

struct score {
	unsigned long long course_ID;
	double total = 0, final = 0, mid = 0, other = 0, gpa = 0;
};

struct _score {
	score data;
	_score* pNext;
};

struct account {
	unsigned long long Student_ID;
	std::string password;
	std::string className;
};
struct _account {
	account data;
	_account* pNext;
}; 

#endif