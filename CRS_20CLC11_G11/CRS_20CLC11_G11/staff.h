#ifndef _STAFF_H_
#define _STAFF_H_

#include "struct.h"
#include "bigData.h"

void menuStaff();

void deleteListClass(_Class*& pHead);
void loadClassName(string className, _Class*& pHeadClass);

void AtTheBeginningOfSchoolYear();
void AtTheBeginningOfSemester();

void deleteListCourse(_course*& pHead);

void inputFromKeyboardCourse(_course*& pHead);
void readCourseFile(string path, _course*& pHead);
void writeCourseFile(string path, _course* pHead);
void writeIndividualCourseFile(string path, course pHead);
void writeAllIndividualCourseFile(string path, _course* pHead);
void addCourseListFile(string path, course pHead);
void addIndividualCourseFile(string path, course pHead);
void displayCourseConsole(_course* pHead);

course findCourse(unsigned long long ID, _course* pHead);

void createCourseFromKeyboard();
void createCourseFromFile();
void editCourse();

void createCourse();

#endif