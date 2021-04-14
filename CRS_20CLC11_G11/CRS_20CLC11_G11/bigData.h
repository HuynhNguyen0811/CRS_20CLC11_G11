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

#include <direct.h> //create folder

#include<io.h>
#include <fcntl.h>

#include<locale> //imbue
#include<codecvt>

using namespace std;

void readFileStudent(string& path, _student*& pHead);
void writeFileStudent(string path, _student* pHead);
void createLogInStudent(string path, _student* pHead, string classname);
void deleteListStudent(_student*& pHead);

void loadClassName(string className, _Class*& pHeadClass);

#endif