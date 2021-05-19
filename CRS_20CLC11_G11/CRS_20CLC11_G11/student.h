#ifndef _STUDENT_H_
#define _STUDENT_H_

#include "bigData.h"
#include "struct.h"

void deleteListScore(student& stu);

student findInfoStudent(unsigned long long ID, string className);
student findStudent(unsigned long long ID, string className);

void printInfoStudent(student stu);
void printScoreboardInSem(student stu, _course* pHeadCourse, Date, Date);

void editFilePassword(string path, unsigned long long ID, string className, string newPassword);
void changePassword(unsigned long long ID, string className);

bool checkLoginStudent(string path, unsigned long long ID, string password, string & className);
bool checkLoginStaff(string path, string ID, string password);

void login();

//after login
void createStudentFile(student stu, string className);
void createStudentFileWithout1Course(student stu, string className, unsigned long long course_ID);

int countEnrolledCourse(student stu);

bool checkEnrollCourse(unsigned long long tempID, _course* pHeadCourse, student stu);
bool checkConflictCourse(student stu, course course);
bool checkRegisTime(Date);
void defineStartEndRegis(Date& start, Date& end, Date);

void deleteTimeTable(student& stu);
void createTimetable(student& stu, _course* pHeadCourse, Date);
void displayTimetable(student stu);

void addEnrolledCourse(student stu, string className, unsigned long long course_ID);
void addStudentToCourse(unsigned long long student_ID, unsigned long long course_ID);

_score* takeTailEnrollCourse(student stu);

void enrollCourse(student& stu, string className, _course* pHeadCourse, Date);
void viewEnrollCourse(student stu, _course* pHeadCourse, Date);
void removeEnrollCourse(student& stu, string className, _course* pHeadCourse, Date);

void menuManageCourseStudent(student stu, string className);
void menuStudent(unsigned long long ID, string className);

#endif