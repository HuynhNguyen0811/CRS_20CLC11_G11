#ifndef _DATA_H_
#define _DATA_H_

#include "struct.h"

#include <iostream>
#include <stdio.h>
#include <Windows.h>

#include <time.h>  //take time

#include <string> 
#include <fstream>
#include <filesystem>
#include <sstream>

#include<io.h>
#include <fcntl.h>

#include<locale> //imbue
#include<codecvt>

using namespace std;

const string folderDir = "Data\\";
const string folderClassDir = "Classes\\";
const string folderCourseDir = "Course\\";
const string classListDir = "Class_Name.csv";
const string courseListDir = "Course.csv";
const string passStaffDir = "passStaff.csv";
const string passStudentDir = "passStudent.csv";
const string csvFormat = ".csv";
const string txtFormat = ".txt";

#endif