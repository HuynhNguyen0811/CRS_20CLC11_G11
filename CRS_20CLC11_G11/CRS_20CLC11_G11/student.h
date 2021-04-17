#ifndef _STUDENT_H_
#define _STUDENT_H_

#include "bigData.h"
#include "struct.h"

void menuStudent(unsigned long long ID, string className);
void login(unsigned long long& ID, string& className);
bool checkLogin(string path, unsigned long long ID, string password, string& className);
void printInfoStudent(student stu);
void findAndPrintStudent(unsigned long long ID, string className);
void changePassword(unsigned long long ID, string className);
void editFilePassword(string path, unsigned long long ID, string className, string newPassword);

#endif