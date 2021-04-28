#include "commonFunc.h"

void GotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConCurInf;

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = CursorVisibility;

	SetConsoleCursorInfo(handle, &ConCurInf);
}

void textColor(int k) {
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, k);
}

void _LText() //chuyen sang tieng viet
{
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);
}
void _SText() { // tat tieng viet
	_setmode(_fileno(stdin), _O_TEXT);
	_setmode(_fileno(stdout), _O_TEXT);
}

int stringToInt(string str) {
	int sum = 0;
	for (int i = 0; i < str.size(); i++) {
		if ((int)(str[i] - 48) >= 0 && (int)(str[i] - 48) <= 9) {
			sum *= 10;
			sum += (int)(str[i] - 48);
		}
	}
	return sum;
}

unsigned long long stringToLong(string str) {
	unsigned long long sum = 0;
	for (int i = 0; i < str.size(); i++) {
		if ((unsigned long long)(str[i] - 48) >= 0 && (unsigned long long)(str[i] - 48) <= 9) {
			sum *= 10;
			sum += (unsigned long long)(str[i] - 48);
		}
	}
	return sum;
}

Date stringToDate(string str) {
	int day = 0, month = 0, year = 0;
	int i = 0;
	while (i < str.size() && (int)str[i] != 47) {
		day *= 10;
		day += (int)(str[i] - 48);
		i++;
	}
	i++;
	while (i < str.size() && (int)str[i] != 47) {
		month *= 10;
		month += (int)(str[i] - 48);
		i++;
	}
	i++;
	while (i < str.size()) {
		year *= 10;
		year += (int)(str[i] - 48);
		i++;
	}
	return { day, month, year };
}

int wstringToInt(wstring str) {
	int sum = 0;
	for (int i = 0; i < str.size(); i++) {
		if ((int)(str[i] - 48) >= 0 && (int)(str[i] - 48) <= 9) {
			sum *= 10;
			sum += (int)(str[i] - 48);
		}
	}
	return sum;
}

unsigned long long wstringToLong(wstring str) {
	unsigned long long sum = 0;
	for (int i = 0; i < str.size(); i++) {
		if ((unsigned long long)(str[i] - 48) >= 0 && (unsigned long long)(str[i] - 48) <= 9) {
			sum *= 10;
			sum += (unsigned long long)(str[i] - 48);
		}
	}
	return sum;
}

Date wstringToDate(wstring str) {
	int day = 0, month = 0, year = 0;
	int i = 0;
	while (i < str.size() && (int)str[i] != 47) {
		day *= 10;
		day += (int)(str[i] - 48);
		i++;
	}
	i++;
	while (i < str.size() && (int)str[i] != 47) {
		month *= 10;
		month += (int)(str[i] - 48);
		i++;
	}
	i++;
	while (i < str.size()) {
		year *= 10;
		year += (int)(str[i] - 48);
		i++;
	}
	return { day, month, year };
}

void wstringToWchar(wchar_t* destination, wstring source) {
	for (int i = 0; i < source.size() + 1; i++) {
		destination[i] = source[i];
	}
}

void stringToChar(char* destination, string source) {
	for (int i = 0; i < source.size() + 1; i++) {
		destination[i] = source[i];
	}
}

int countLine(string path) {
	ifstream fileIn;
	string temp;
	int line;
	fileIn.open(path);
	for (line = 0; getline(fileIn, temp); line++);
	return line;
}