#ifndef _STUDENT_H_
#define _STUDENT_H_

#include "bigData.h"
#include "struct.h"

void deleteLastScore(student stu);

student findInfoStudent(unsigned long long ID, string className);
student findStudent(unsigned long long ID, string className);

void printInfoStudent(student stu);
void printScoreboard(student stu);

void editFilePassword(string path, unsigned long long ID, string className, string newPassword);
void changePassword(unsigned long long ID, string className);

bool checkLogin(string path, unsigned long long ID, string password, string& className);

void login(unsigned long long& ID, string& className);

void menuManageStudent(student stu, string className);
void menuStudent(unsigned long long ID, string className);

#endif