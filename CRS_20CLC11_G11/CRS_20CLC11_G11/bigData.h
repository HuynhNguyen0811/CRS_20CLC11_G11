#include "struct.h"

#include <iostream>
#include <stdio.h>
#include <Windows.h>

#include <time.h>  
#include <string>
#include <fstream>
#include <filesystem>

#include<io.h>
#include <fcntl.h>

#include<locale>
#include<codecvt>

using namespace std;

void _LText();
void _SText();

int stringToInt(string str);
unsigned long long stringToLong(string str);
Date stringToDate(string str);

int wstringToInt(wstring str);
unsigned long long wstringToLong(wstring str);
Date wstringToDate(wstring str);