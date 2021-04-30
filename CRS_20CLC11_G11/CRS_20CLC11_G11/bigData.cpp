#include "bigData.h"
#include "struct.h"
#include "commonFunc.h"


void readFileStudent(string& path, _student*& pHead) {
	wifstream fileIn;
	do {
		cout << "Please enter the name of the file you want to input: ";
		cin >> path;
		
		fileIn.open(path + ".csv", ios_base::in);
		fileIn.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

		if (fileIn.fail())
		{
			cout << "File is not existed " << endl;
		}
	} while (fileIn.fail());

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
	string pass, zero = "0";
	while (pHead->pNext != nullptr) {
		fileOut << pHead->data.Student_ID << ",";
		 
		if (pHead->data.Date_Of_Birth.day < 10) pass = zero + to_string(pHead->data.Date_Of_Birth.day);
		else pass = to_string(pHead->data.Date_Of_Birth.day);
		if (pHead->data.Date_Of_Birth.month < 10) pass += zero + to_string(pHead->data.Date_Of_Birth.month);
		else pass += to_string(pHead->data.Date_Of_Birth.month);
		pass += to_string(pHead->data.Date_Of_Birth.year);

		fileOut << pass << ",";
		fileOut << classname << endl;

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