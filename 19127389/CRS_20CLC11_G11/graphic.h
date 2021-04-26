#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

#include "struct.h"
#include "bigData.h"

void designMenuLogin(int x, int y);
void designMenuStaff(int x, int y);
void designMenuStudent(int x, int y);

void drawChoosingOutlineStu(int x, int y);
void drawOutlineStu(int x, int y);
void drawChoosingOutlineStaff(int x, int y);
void drawOutlineStaff(int x, int y);
void writeMenuLogin(int x, int y);

void designMenuManageCourseStaff(int x, int y);
void designMenuManageStudentStaff(int x, int y);
void designMenuManageSystemStaff(int x, int y);

void designMenuManageCourseStudent(int x, int y);

#endif