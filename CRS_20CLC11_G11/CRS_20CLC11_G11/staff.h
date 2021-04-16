#ifndef _STAFF_H_
#define _STAFF_H_

#include "struct.h"
#include "bigData.h"

void menuStaff();

void deleteListCourse(_course*& pHead);
void deleteListClass(_Class*& pHead);
void deleteListStudentAttend(_studentRegis* pHead);

void loadClassName(string className, _Class*& pHeadClass);

void AtTheBeginningOfSchoolYear();
void AtTheBeginningOfSemester();

void inputFromKeyboardCourse(_course*& pHead);

void readCourseFile(string path, _course*& pHead);
void readAllIndividualCourseFile(string path, _course* pHead);
void readIndividualCourseFile(string path, _course* pHead); //read student attend

void writeCourseFile(string path, _course* pHead);
void writeIndividualCourseFile(string path, course pHead);
void writeAllIndividualCourseFile(string path, _course* pHead);

void addCourseListFile(string path, course pHead);
void addIndividualCourseFile(string path, course pHead);

void displayCourseConsole(_course* pHead);
void displayIndividualCourseConsole(course pHead);

void displayStudentAttendIndividualCourse(_studentRegis* pHead);

_course* findCourse(unsigned long long ID, _course* pHead);

void createCourseFromKeyboard();
void createCourseFromFile();
void editCourse();

void createCourse();

#endif