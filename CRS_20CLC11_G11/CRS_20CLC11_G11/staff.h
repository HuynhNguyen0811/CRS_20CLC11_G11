#ifndef _STAFF_H_
#define _STAFF_H_

#include "struct.h"
#include "bigData.h"

void menuStaff();

void deleteListCourse(_course*& pHead);
void deleteListClass(_Class*& pHead);
void deleteListStudentAttend(_studentRegis* pHead);

void readStuInClass(string path, _student*& pHead);
void readClassName(string path, _Class*& pHeadClass);
void displayClassName(_Class* pHead);

void AtTheBeginningOfSchoolYear();
void AtTheBeginningOfSemester();
void displayClassAndStudent();

void inputFromKeyboardCourse(_course*& pHead);

_studentRegis* takeTailStudentRegis(_studentRegis* pHead);

void readCourseFile(string path, _course*& pHead);
void readAllIndividualCourseFile(string path, _course* pHead);
void readIndividualCourseFile(string path, _course* pHead); //read student attend
void readAccount(string path, _account*& pHead); //read ID, pass, class name of every student

void writeCourseFile(string path, _course* pHead);
void writeCourseFileWithout1Course(string path, _course* pHead, unsigned long long tempID);
void writeIndividualCourseFile(string path, course pHead);
void writeAllIndividualCourseFile(string path, _course* pHead);
void writeIndividualCourseFileWithout1Student(string path, course pHead, unsigned long long student_ID);

void addCourseListFile(string path, course pHead);
void addIndividualCourseFile(string path, course pHead);

void displayCourseConsole(_course* pHead);
void displayIndividualCourseConsole(course pHead);

void displayStudentAttendIndividualCourse(_studentRegis* pHead);

_course* findCourse(unsigned long long ID, _course* pHead);

void createCourseFromKeyboard();
void createCourseFromFile();
void editCourse();
void removeCourse();
void viewAttendStudent();
void writeAttendStudent();

void createCourse(); //menu manage course

#endif