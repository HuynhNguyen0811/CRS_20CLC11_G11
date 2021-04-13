#include "bigData.h"
#include "struct.h"

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

void readFileStudent(string& path, _student*& pHead) {
	cout << "Please enter the name of the file you want to input: ";
	cin >> path;
	wifstream fileIn;
	fileIn.open(path + ".csv", ios_base::in);
	fileIn.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	if (fileIn.fail())
	{
		cout << "File is not existed " << endl;
		readFileStudent(path, pHead);
	}

	_student* pCur = nullptr;
	wstring temp;
	wchar_t a = ',';
	//getline(fileIn, temp, char(191));
	while (fileIn) {
		if (pHead == nullptr) {
			pHead = new _student;
			pCur = pHead;
		}
		else {
			pCur->pNext = new _student;
			pCur = pCur->pNext;
		}
		getline(fileIn, temp, a);
		pCur->data.No = wstringToInt(temp);
		getline(fileIn, temp, a);
		pCur->data.Student_ID = wstringToLong(temp);

		getline(fileIn, pCur->data.FirstName, a);
		getline(fileIn, pCur->data.LastName, a);
		getline(fileIn, pCur->data.Gender, a);
		getline(fileIn, temp, a);
		pCur->data.Date_Of_Birth = wstringToDate(temp);
		fileIn >> pCur->data.Social_ID;
		pCur->pNext = nullptr;
	}
	fileIn.close();
}

void writeFileStudent(string path, _student* pHead) {
	wofstream fileOut;
	fileOut.open(path, ios_base::out);
	fileOut.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	while (pHead->pNext != nullptr) {
		fileOut << pHead->data.No << L"," << pHead->data.Student_ID << L"," << pHead->data.FirstName << L"," << pHead->data.LastName << L"," << pHead->data.Gender << L"," << pHead->data.Date_Of_Birth.day << wchar_t(47) << pHead->data.Date_Of_Birth.month << wchar_t(47) << pHead->data.Date_Of_Birth.year << L"," << pHead->data.Social_ID << endl;
		pHead = pHead->pNext;
	}
	fileOut.close();
}

void createLogInStudent(string path, _student* pHead, string classname) {
	ofstream fileOut;
	fileOut.open(path + ".csv", ios_base::app);
	while (pHead->pNext != nullptr) {
		fileOut << pHead->data.Student_ID << "," << 1 << "," << classname << endl;
		pHead = pHead->pNext;
	}
	fileOut.close();
}

void deleteListStudent(_student*& pHead) {
	_student* pTmp = pHead;
	while (pHead != nullptr) {
		pHead = pHead->pNext;
		delete pTmp;
		pTmp = pHead;
	}
}