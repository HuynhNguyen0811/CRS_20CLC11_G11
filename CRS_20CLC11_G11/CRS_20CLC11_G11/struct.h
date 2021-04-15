#ifndef _STRUCT_H_
#define _STRUCT_H_

#include <iostream>

struct student;
struct _student;
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
	_course* course = nullptr;

	double GPA = 0;
};
struct _student {
	student data;
	_student* pNext, * pPrevious;
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
	wchar_t* dayOfWeek;
	wchar_t* hour;
};
struct course {
	unsigned long long courseId;
	std::wstring courseName;
	std::wstring teacherName;
	int credit;
	int maxStu = 50;
	session* session;
};
struct _course {
	course data;
	_course* pNext, * pPrevious;
};

struct score {
	course data;
	double mark;
};
struct _score {
	score data;
	_score* pNext, * pPrevious;
};

struct account {
	unsigned long long Student_ID;
	std::string password;
};
struct _account {
	account data;
	_account* pNext, * pPrevious;
}; 

#endif