#ifndef _STUDENT_H_
#define _STUDENT_H_

#include "bigData.h"
#include "struct.h"

student findInfoStudent(unsigned long long ID, string className);
student findStudent(unsigned long long ID, string className);

void printInfoStudent(student stu);
void printScoreboard(student stu);

void editFilePassword(string path, unsigned long long ID, string className, string newPassword);
void changePassword(unsigned long long ID, string className);

bool checkLogin(string path, unsigned long long ID, string password, string& className);

void login(unsigned long long& ID, string& className);

void createStudentFile(student stu, string className);
void createStudentFileWithout1Course(student stu, string className, unsigned long long course_ID);

int countEnrolledCourse(student stu);

bool checkEnrollCourse(unsigned long long tempID, _course* pHeadCourse, student stu);
bool checkConflictCourse(student stu, course course);

void deleteTimeTable(student& stu);
void createTimetable(student& stu, _course* pHeadCourse);
void displayTimetable(student stu);

void addEnrolledCourse(student stu, string className, unsigned long long course_ID);
void addStudentToCourse(unsigned long long student_ID, unsigned long long course_ID);

_score* takeTailEnrollCourse(student stu);

void enrollCourse(student& stu, string className, _course* pHeadCourse);
void viewEnrollCourse(student stu, _course* pHeadCourse);
void removeEnrollCourse(student& stu, string className, _course* pHeadCourse);

void menuManageCourseStudent(student stu, string className);
void menuStudent(unsigned long long ID, string className);

#endif