#ifndef _STUDENT_H_
#define _STUDENT_H_

#include "bigData.h"
#include "struct.h"

void deleteListScore(student& stu);

student findInfoStudent(unsigned long long ID, std::string className);
student findStudent(unsigned long long ID, std::string className);

void printInfoStudent(student stu);
void printScoreboardInSem(student stu, _course* pHeadCourse, Date, Date);

void editFilePassword(std::string path, unsigned long long ID, std::string className, std::string newPassword);
void changePassword(unsigned long long ID, std::string className);

bool checkLoginStudent(std::string path, unsigned long long ID, std::string password, std::string & className);
bool checkLoginStaff(std::string path, std::string ID, std::string password);

void login();

//after login
void createStudentFile(student stu, std::string className);
void createStudentFileWithout1Course(student stu, std::string className, unsigned long long course_ID);

int countEnrolledCourse(student stu);

bool checkEnrollCourse(unsigned long long tempID, _course* pHeadCourse, student stu);
bool checkConflictCourse(student stu, course course);
bool checkRegisTime(Date);
void defineStartEndRegis(Date& start, Date& end, Date);

void deleteTimeTable(student& stu);
void createTimetable(student& stu, _course* pHeadCourse, Date);
void displayTimetable(student stu);

void addEnrolledCourse(student stu, std::string className, unsigned long long course_ID);
void addStudentToCourse(unsigned long long student_ID, unsigned long long course_ID);

_score* takeTailEnrollCourse(student stu);

void enrollCourse(student& stu, std::string className, _course* pHeadCourse, Date);
void viewEnrollCourse(student stu, _course* pHeadCourse, Date);
void removeEnrollCourse(student& stu, std::string className, _course* pHeadCourse, Date);

void menuManageCourseStudent(student stu, std::string className);
void menuStudent(unsigned long long ID, std::string className);

#endif