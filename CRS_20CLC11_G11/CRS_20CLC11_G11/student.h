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

void addEnrolledCourse(student stu, string className, unsigned long long course_ID);

void enrollCourse(student& stu, string className, _course* pHeadCourse);
void viewEnrollCourse(student stu, _course* pHeadCourse);

void menuManageCourseStudent(student stu, string className);
void menuStudent(unsigned long long ID, string className);

#endif