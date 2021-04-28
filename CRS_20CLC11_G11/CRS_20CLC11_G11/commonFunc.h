#ifndef _COMMON_H_
#define _COMMON_H_

#include "struct.h"

#include <Windows.h>
#include <string>

#include <fstream>

#include <cmath>

#include<io.h> //utf
#include <fcntl.h>

#include <conio.h> //getch

using namespace std;

void GotoXY(int x, int y);
void ShowCur(bool CursorVisibility);
void textColor(int k);

void _LText();
void _SText();

int stringToInt(string str);
unsigned long long stringToLong(string str);
Date stringToDate(string str);

int wstringToInt(wstring str);
unsigned long long wstringToLong(wstring str);
Date wstringToDate(wstring str);

void wstringToWchar(wchar_t* destination, wstring source);
void stringToChar(char* destination, string source);

int countLine(string path);

#endif