#include "staff.h"
void deleteListStudent(_student*& pHead) {
	_student* pTemp = pHead;
	while (pHead != nullptr) {
		pHead = pHead->pNext;
		delete pTemp;
		pTemp = pHead;
	}
	pHead = nullptr;
}

void deleteListClass(_Class*& pHead) {
	_Class* pTemp = pHead;
	while (pHead != nullptr) {
		pHead = pHead->pNext;
		delete pTemp;
		pTemp = pHead;
	}
	pHead = nullptr;
}

void deleteListCourse(_course*& pHead) {
	_course* pTemp = pHead;
	while (pHead != nullptr) {
		delete[] pHead->data.session;
		pHead = pHead->pNext;
		deleteListStudentAttend(pTemp->data.studentID);
		delete pTemp;
		pTemp = pHead;
	}
	pHead = nullptr;
}

void deleteListStudentAttend(_studentRegis*& pHead) {
	_studentRegis* pTemp = pHead;
	while (pHead != nullptr) {
		pHead = pHead->pNext;
		delete pTemp;
		pTemp = pHead;
	}
	pHead = nullptr;
}

void deleteListAccount(_account*& pHead) {
	_account* pTemp = pHead;
	while (pHead != nullptr) {
		pHead = pHead->pNext;
		delete pTemp;
		pTemp = pHead;
	}
	pHead = nullptr;
}

//return start end regis
void create_chooseSem(Date& start, Date& end) {
	//choose school year
	int year;
	cout << "Choose school year: ";
	cin >> year;

	//choose sem
	//chon 1 trong 3
	int sem;
	do {
		cout << "Choose semester: ";
		cin >> sem;
	} while (sem != 1 && sem != 2 && sem != 3);
	switch (sem) {
	case 1: //ngay 1 thang 9 nam year den ngay 15 thang 12 nam year
		start = { 16, 8, year };
		end = { 1, 9, year };
		break;
	case 2: //ngay 1 thang 1 nam year + 1 den 15 thang 4 nam year + 1
		start = { 16, 12, year };
		end = { 1, 1, year + 1 };
		break;
	case 3: //ngay 1 thang 5 nam year + 1 den 15 thang 8 nam year + 1
		start = { 16, 5, year + 1 };
		end = { 1, 6, year + 1 };
		break;
	}
}

void applyStartEndRegis(_course* pHead, Date start, Date end) {
	while (pHead != nullptr && pHead->pNext != nullptr) {
		pHead->data.startRegis = start;
		pHead->data.endRegis = end;
		pHead = pHead->pNext;
	}
}
void displayClassAndStudent() {
	//read class list
	string path;
	_Class* pHeadClass = nullptr;

	path = folderDir + folderClassDir + classListDir;
	readClassName(path, pHeadClass);

	//display class list
	cout << "Class list: " << endl;
	displayClassName(pHeadClass);

	//loop
	int temp = 1;
	string choose;
	_student* pHeadStu = nullptr;

	while (temp != 0) {
		//choose class
		cout << "Enter class name you want to display student list: ";
		cin >> choose;

		//read class
		path = folderDir + folderClassDir + choose + csvFormat;
		readStuInClass(path, pHeadStu);

		//display class
		displayStuInClassConsole(pHeadStu);

		//delete student list
		deleteListStudent(pHeadStu);

		pHeadStu = nullptr;
		cout << "Enter 0 to escape: ";
		cin >> temp;
	}
	deleteListClass(pHeadClass);
}
