#ifndef _STAFF_H_
#define _STAFF_H_

#include "struct.h"
#include "bigData.h"

void deleteListStudent(_student*& pHead);
void deleteListCourse(_course*& pHead);
void deleteListClass(_Class*& pHead);
void deleteListStudentAttend(_studentRegis* &pHead);

void create_chooseSem(Date& start, Date& end);
void applyStartEndRegis(_course* pHead, Date start, Date end);

//class / student
void readStuInClass(string path, _student*& pHead);
void readClassName(string path, _Class*& pHeadClass);

void readFileStudent(string& path, _student*& pHead);
void createClassListFile(string path, string className);
void createLogInStudent(string path, _student* pHead, string classname);
void writeFileStudent(string path, _student* pHead);

void displayClassName(_Class* pHead);

void inputClass();

//course
void inputFromKeyboardCourseInSem(_course*& pHead, Date, Date);

_studentRegis* takeTailStudentRegis(_studentRegis* pHead);

void readCourseFile(string path, _course*& pHead);
void readForInputCourseFileInSem(string path, _course*& pHead, Date start, Date end);
void readAllIndividualCourseFile(string path, _course* pHead);
void readIndividualCourseFile(string path, _course* pHead); //read student attend
void readAccount(string path, _account*& pHead); //read ID, pass, class name of every student

void writeCourseFile(string path, _course* pHead);
void writeCourseFileWithout1Course(string path, _course* pHead, unsigned long long tempID);
void writeIndividualCourseFile(string path, course pHead);
void writeAllIndividualCourseFile(_course* pHead);
void writeIndividualCourseFileWithout1Student(string path, course pHead, unsigned long long student_ID);

void addCourseFile(string path, _course* pHead);
void addIndividualCourseFile(string path, course pHead);

void displayCourseConsole(_course* pHead);
void displayIndividualCourseConsole(course pHead);

void displayStudentAttendIndividualCourse(_studentRegis* pHead);

_course* findCourse(unsigned long long ID, _course* pHead);

void createCourseFromKeyboardInSem(Date start, Date end); 
void createCourseFromFileInSem(Date start, Date end);  
void editCourseInSem(Date start, Date end); 
void removeCourseInSem(Date start, Date end); 
void viewAttendStudentInSem(Date start, Date end); 
void writeAttendStudentInSem(Date start, Date end); 

//score
void readScoreboard(string path, _course*& course);

void writeScoreboardAllIndividualStu(_course* course);

void displayScoreboardConsole(_course* course);

void inputScoreboardInSem(Date start, Date end); 
void viewScoreboardCourseInSem(Date start, Date end); 
void viewScoreboardClassInSem(Date start, Date end); 
void editScoreFromCourseInSem(Date start, Date end); 

//sub menu
void menuManageStudent();
void menuManageCourse(); 
void menuManageScore(); 

//main menu
void menuStaff();

#endif