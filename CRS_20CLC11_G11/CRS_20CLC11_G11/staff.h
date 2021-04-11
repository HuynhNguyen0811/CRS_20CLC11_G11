#ifndef _STAFF_H_
#define _STAFF_H_

#include "struct.h"
#include "bigData.h"

void menuStaff();
void deleteListClass(_Class*& pHead);
void loadClassName(string className, _Class*& pHeadClass);
void AtTheBeginningOfSchoolYear();
void AtTheBeginningOfSemester();

void readCourseFile(_course*& pHead);
void writeCourseFile(_course* pHead);
void createCourse();

#endif