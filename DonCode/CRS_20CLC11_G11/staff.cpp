#include "staff.h"
#include "student.h"
#include "commonFunc.h"
#include "bigData.h"

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

void deleteListStudentAttend(_studentRegis* &pHead) {
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
void create_chooseSem(Date &start, Date& end) {
	//choose school year
	int year;
	cout << "Choose/Create school year: ";
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

void readStuInClass(string path, _student* &pHead) {
	wifstream fileIn;
	fileIn.open(path, ios_base::in);
	fileIn.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
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

void readClassName(string path, _Class*& pHeadClass) {
	ifstream fileIn;
	fileIn.open(path, ios_base::in);
	_Class* pCurClass = nullptr;
	while (fileIn) {
		if (pHeadClass == nullptr) {
			pHeadClass = new _Class;
			pCurClass = pHeadClass;
		}
		else {
			pCurClass->pNext = new _Class;
			pCurClass = pCurClass->pNext;
		}
		getline(fileIn, pCurClass->data.name, '\n');
		pCurClass->pNext = nullptr;
	}

	fileIn.close();
}

void displayStuInClassConsole(_student* pHead) {
	_LText();
	
	while (pHead != nullptr && pHead->pNext != nullptr) {
		wcout << pHead->data.No << L"," << pHead->data.Student_ID << L"," << pHead->data.FirstName << L"," << pHead->data.LastName << L"," << pHead->data.Gender << L"," << pHead->data.Date_Of_Birth.day << wchar_t(47) << pHead->data.Date_Of_Birth.month << wchar_t(47) << pHead->data.Date_Of_Birth.year << L"," << pHead->data.Social_ID << endl;
		pHead = pHead->pNext;
	}

	_SText();
}

void displayClassName(_Class* pHead) {
	while (pHead != nullptr && pHead->pNext != nullptr) {
		cout << pHead->data.name << endl;
		pHead = pHead->pNext;
	}
}

void createClassListFile(string path, string className) {
	ofstream fileOut;
	fileOut.open(path, ios_base::app);

	fileOut << className << endl;

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

//doi lai ten ham 
void inputClass() {
	system("CLS");
	_student* pHead = nullptr;
	
	_Class* pHeadClass = nullptr;

	_mkdir("Data");
	_mkdir("Data\\Classes");

	string path, newPath; //duong dan cua file input class
	string className;
	int flag;
	cout << "Choose method to input class name\n1.From keyboard\n2.From a file\n0.Escape";
	cin >> flag;
	switch (flag) {
	case 1:
		while (true) {
			cout << "Creating a class:\nPlease enter class name: ";
			cin >> className;

			newPath = folderDir + folderClassDir + classListDir;
			createClassListFile(newPath, className);

			readFileStudent(path, pHead);

			newPath = folderDir + passStudentDir;
			createLogInStudent(newPath, pHead, className);

			newPath = folderDir + folderClassDir + className + csvFormat;
			writeFileStudent(newPath, pHead);

			deleteListStudent(pHead);
			int temp;
			cout << "Input '0' if you want to escape: ";
			cin >> temp;
			if (temp == 0) {
				system("CLS");
				break;
			}
		}
		break;
	case 2:
		cout << "Please enter file name that contains class name: ";
		cin >> className;
		readClassName(className, pHeadClass);
		if (pHeadClass == nullptr) menuStaff();
		while (pHeadClass->pNext != nullptr) {

			newPath = folderDir + folderClassDir + classListDir;
			createClassListFile(newPath, pHeadClass->data.name);

			pHeadClass->data.student = nullptr;
			readFileStudent(path, pHeadClass->data.student);

			newPath = folderDir + passStudentDir;
			createLogInStudent(newPath, pHeadClass->data.student, pHeadClass->data.name);

			
			newPath = folderDir + folderClassDir + pHeadClass->data.name + csvFormat;
			writeFileStudent(newPath, pHeadClass->data.student);

			deleteListStudent(pHeadClass->data.student);
			pHeadClass = pHeadClass->pNext;
		}
		deleteListClass(pHeadClass);
		menuStaff();
		break;
	default:
		break;
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

//----------------------------------------------------------

void inputFromKeyboardCourseInSem(_course*& pHead, Date start, Date end) {
	_course* pCur = nullptr;
	int temp = -1, check;
	wchar_t a = '\n';
	while (temp != 0) {
		if (pHead == nullptr) {
			pHead = new _course;
			pCur = pHead;
		}
		else {
			pCur->pNext = new _course;
			pCur = pCur->pNext;
		}

		cout << "Course's ID: ";
		cin >> pCur->data.courseId;

		cin.ignore(1000, '\n');

		_LText();

		wcout << "Course's name: ";
		std::getline(wcin, pCur->data.courseName, L'\n');
		wcout << "Teacher's name: ";
		std::getline(wcin, pCur->data.teacherName, L'\n');

		_SText();
		cout << "Number of credits: ";
		cin >> pCur->data.credit;
		cout << "Do you want to change course's max student (default as 50, enter 1 to change): ";
		cin >> check;
		if (check == 1) {
			cout << "Credit: ";
			cin >> pCur->data.credit;
		}

		pCur->data.session = new session[2];

		for (int i = 0; i < 2; i++) {
			cout << "Day of week " << i + 1 << " of the course will performed (MON / TUE / WED / THU / FRI / SAT): ";
			wcin >> pCur->data.session[i].dayOfWeek;
			cout << "The session " << i + 1 << " of the course will performed (S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30)): ";
			wcin >> pCur->data.session[i].hour;
		}
		pCur->data.startRegis = start;
		pCur->data.endRegis = end;

		pCur->pNext = nullptr;

		cout << "Enter 0 to stop: ";
		cin >> temp;
	}

	pCur->pNext = new _course;
	pCur = pCur->pNext;
	pCur->data.session = new session[2];
	pCur->pNext = nullptr;
}

void readCourseFile(string path, _course*& pHead) {
	wifstream fileIn;
	fileIn.open(path, ios_base::in);
	fileIn.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	if (fileIn.fail())
	{
		cout << "File is not existed " << endl;
		return;
	}

	_course* pCur = nullptr;
	wstring temp;
	wchar_t a = ',', b = '\n';
	while (fileIn) {
		if (pHead == nullptr) {
			pHead = new _course;
			pCur = pHead;
		}
		else {
			pCur->pNext = new _course;
			pCur = pCur->pNext;
		}
		getline(fileIn, temp, a);
		pCur->data.courseId = wstringToLong(temp);
		getline(fileIn, pCur->data.courseName, a);
		getline(fileIn, pCur->data.teacherName, a);
		getline(fileIn, temp, a);
		pCur->data.credit = wstringToInt(temp);
		getline(fileIn, temp, a);
		pCur->data.maxStu = wstringToInt(temp);

		pCur->data.session = new session[2];

		getline(fileIn, pCur->data.session[0].dayOfWeek, a);
		getline(fileIn, pCur->data.session[0].hour, a);

		getline(fileIn, pCur->data.session[1].dayOfWeek, a);
		getline(fileIn, pCur->data.session[1].hour, a);
		getline(fileIn, temp, a);
		pCur->data.startRegis = wstringToDate(temp);
		getline(fileIn, temp, b);
		pCur->data.endRegis = wstringToDate(temp);

		pCur->pNext = nullptr;
	}
	fileIn.close();
}

void readForInputCourseFileInSem(string path, _course*& pHead, Date start, Date end) {
	wifstream fileIn;
	fileIn.open(path, ios_base::in);
	fileIn.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	if (fileIn.fail())
	{
		cout << "File is not existed " << endl;
		return;
	}

	_course* pCur = nullptr;
	wstring temp;
	wchar_t a = ',', b = '\n';
	while (fileIn) {
		if (pHead == nullptr) {
			pHead = new _course;
			pCur = pHead;
		}
		else {
			pCur->pNext = new _course;
			pCur = pCur->pNext;
		}
		getline(fileIn, temp, a);
		pCur->data.courseId = wstringToLong(temp);
		getline(fileIn, pCur->data.courseName, a);
		getline(fileIn, pCur->data.teacherName, a);
		getline(fileIn, temp, a);
		pCur->data.credit = wstringToInt(temp);
		getline(fileIn, temp, a);
		pCur->data.maxStu = wstringToInt(temp);

		pCur->data.session = new session[2];

		getline(fileIn, pCur->data.session[0].dayOfWeek, a);
		getline(fileIn, pCur->data.session[0].hour, a);

		getline(fileIn, pCur->data.session[1].dayOfWeek, a);
		getline(fileIn, pCur->data.session[1].hour, b);

		pCur->data.startRegis = start;
		pCur->data.endRegis = end;

		pCur->pNext = nullptr;
	}
	fileIn.close();
}

void readAllIndividualCourseFile(string path, _course* pHead) {
	while (pHead != nullptr && pHead->pNext != nullptr) {
		readIndividualCourseFile(path + to_string(pHead->data.courseId) + csvFormat, pHead);
		pHead = pHead->pNext;
	}
}

_studentRegis* takeTailStudentRegis(_studentRegis* pHead) {
	_studentRegis* pCur = pHead;
	while (pCur != nullptr && pCur->pNext != nullptr) pCur = pCur->pNext;
	return pCur;
}

void readIndividualCourseFile(string path, _course* pHead) {
	wifstream fileIn;
	fileIn.open(path, ios_base::in);
	fileIn.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	wstring temp;
	_studentRegis* pCur = takeTailStudentRegis(pHead->data.studentID);
	wchar_t a = ',';
	fileIn.ignore(1000, '\n');
	while (fileIn) {
		if (pHead->data.studentID == nullptr) {
			pHead->data.studentID = new _studentRegis;
			pCur = pHead->data.studentID;
		}
		else {
			pCur->pNext = new _studentRegis;
			pCur = pCur->pNext;
		}

		getline(fileIn, temp, L',');
		pCur->data = wstringToLong(temp);
		fileIn >> pCur->total >> a;
		fileIn >> pCur->final >> a;
		fileIn >> pCur->mid >> a;
		fileIn >> pCur->other >> a;
		fileIn >> pCur->gpa >> a;

		fileIn.ignore(1000, '\n');

		pCur->pNext = nullptr;
	}
	
	fileIn.close();
}

void readAccount(string path, _account* &pHead) {
	ifstream fileIn;
	fileIn.open(path, ios_base::in);

	_account* pCur = nullptr;
	string tempID;
	while (fileIn) {
		if (pHead == nullptr) {
			pHead = new _account;
			pCur = pHead;
		}
		else {
			pCur->pNext = new _account;
			pCur = pCur->pNext;
		}
		getline(fileIn, tempID, ',');
		pCur->data.Student_ID = stringToLong(tempID);
		getline(fileIn, pCur->data.password, ',');
		getline(fileIn, pCur->data.className, '\n');
		pCur->pNext = nullptr;
	}
}

void writeCourseFile(string path, _course* pHead) {
	wofstream fileOut;
	fileOut.open(path, ios_base::out);
	fileOut.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	
	while (pHead != nullptr && pHead->pNext != nullptr) {
		fileOut << pHead->data.courseId << "," << pHead->data.courseName << "," << pHead->data.teacherName << "," << pHead->data.credit << "," << pHead->data.maxStu << ",";
		fileOut << pHead->data.session[0].dayOfWeek << "," << pHead->data.session[0].hour << ",";
		fileOut	 << pHead->data.session[1].dayOfWeek << "," << pHead->data.session[1].hour << ",";
		fileOut << pHead->data.startRegis.day << L"/" << pHead->data.startRegis.month << L"/" << pHead->data.startRegis.year << ",";
		fileOut << pHead->data.endRegis.day << L"/" << pHead->data.endRegis.month << L"/" << pHead->data.endRegis.year << endl;
		pHead = pHead->pNext;
	}

	fileOut.close();
}

void addCourseFile(string path, _course* pHead) {
	wofstream fileOut;
	fileOut.open(path, ios_base::app);
	fileOut.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	while (pHead != nullptr && pHead->pNext != nullptr) {
		fileOut << pHead->data.courseId << "," << pHead->data.courseName << "," << pHead->data.teacherName << "," << pHead->data.credit << "," << pHead->data.maxStu << ",";
		fileOut << pHead->data.session[0].dayOfWeek << "," << pHead->data.session[0].hour << ",";
		fileOut << pHead->data.session[1].dayOfWeek << "," << pHead->data.session[1].hour << ",";
		fileOut << pHead->data.startRegis.day << L"/" << pHead->data.startRegis.month << L"/" << pHead->data.startRegis.year << ",";
		fileOut << pHead->data.endRegis.day << L"/" << pHead->data.endRegis.month << L"/" << pHead->data.endRegis.year << endl;
		pHead = pHead->pNext;
	}

	fileOut.close();
}

void writeCourseFileWithout1Course(string path, _course* pHead, unsigned long long tempID) {
	wofstream fileOut;
	fileOut.open(path, ios_base::out);
	fileOut.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	while (pHead != nullptr && pHead->pNext != nullptr) {
		if (tempID != pHead->data.courseId) {
			fileOut << pHead->data.courseId << "," << pHead->data.courseName << "," << pHead->data.teacherName << "," << pHead->data.credit << "," << pHead->data.maxStu << ",";
			fileOut << pHead->data.session[0].dayOfWeek << "," << pHead->data.session[0].hour << ",";
			fileOut << pHead->data.session[1].dayOfWeek << "," << pHead->data.session[1].hour << ",";
			fileOut << pHead->data.startRegis.day << L"/" << pHead->data.startRegis.month << L"/" << pHead->data.startRegis.year << ",";
			fileOut << pHead->data.endRegis.day << L"/" << pHead->data.endRegis.month << L"/" << pHead->data.endRegis.year << endl;
		}
		pHead = pHead->pNext;
	}

	fileOut.close();
}

void writeIndividualCourseFile(string path, course pHead) {
	wofstream fileOut;
	fileOut.open(path, ios_base::out);
	fileOut.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	fileOut << pHead.courseId << "," << pHead.courseName << "," << pHead.teacherName << "," << pHead.credit << "," << pHead.maxStu << ",";
	fileOut << pHead.session[0].dayOfWeek << "," << pHead.session[0].hour << ",";
	fileOut << pHead.session[1].dayOfWeek << "," << pHead.session[1].hour << ",";
	fileOut << pHead.startRegis.day << L"/" << pHead.startRegis.month << L"/" << pHead.startRegis.year << ",";
	fileOut << pHead.endRegis.day << L"/" << pHead.endRegis.month << L"/" << pHead.endRegis.year << endl;

	_studentRegis* pCur = pHead.studentID;
	while (pCur != nullptr && pCur->pNext != nullptr) {
		fileOut << pCur->data << "," << pCur->total << "," << pCur->final << "," << pCur->mid << "," << pCur->other << "," << pCur->gpa << ",,,,," << endl;
		pCur = pCur->pNext;
	}

	fileOut.close();
}

void writeIndividualCourseFileWithout1Student(string path, course pHead, unsigned long long student_ID) {
	wofstream fileOut;
	fileOut.open(path, ios_base::out);
	fileOut.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	fileOut << pHead.courseId << "," << pHead.courseName << "," << pHead.teacherName << "," << pHead.credit << "," << pHead.maxStu << ",";
	fileOut << pHead.session[0].dayOfWeek << "," << pHead.session[0].hour << ",";
	fileOut << pHead.session[1].dayOfWeek << "," << pHead.session[1].hour << ",";
	fileOut << pHead.startRegis.day << L"/" << pHead.startRegis.month << L"/" << pHead.startRegis.year << ",";
	fileOut << pHead.endRegis.day << L"/" << pHead.endRegis.month << L"/" << pHead.endRegis.year << endl;

	_studentRegis* pCur = pHead.studentID;
	while (pCur != nullptr && pCur->pNext != nullptr) {
		if (pCur->data != student_ID) {
			fileOut << pCur->data << "," << pCur->total << "," << pCur->final << "," << pCur->mid << "," << pCur->other << "," << pCur->gpa << endl;
		}
		pCur = pCur->pNext;
	}

	fileOut.close();
}

void addIndividualCourseFile(string path, course pHead) {
	wofstream fileOut;
	fileOut.open(path, ios_base::app);
	fileOut.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	fileOut << pHead.courseId << "," << pHead.courseName << "," << pHead.teacherName << "," << pHead.credit << "," << pHead.maxStu << ",";
	fileOut << pHead.session[0].dayOfWeek << "," << pHead.session[0].hour << ",";
	fileOut << pHead.session[1].dayOfWeek << "," << pHead.session[1].hour << ",";
	fileOut << pHead.startRegis.day << L"/" << pHead.startRegis.month << L"/" << pHead.startRegis.year << ",";
	fileOut << pHead.endRegis.day << L"/" << pHead.endRegis.month << L"/" << pHead.endRegis.year << endl;

	fileOut.close();
}

void writeAllIndividualCourseFile(_course* pHead) {

	while (pHead != nullptr && pHead->pNext != nullptr) {
		writeIndividualCourseFile(folderDir + folderCourseDir + to_string(pHead->data.courseId) + csvFormat, pHead->data);
		pHead = pHead->pNext;
	}

}

void displayCourseConsole(_course* pHead) {
	_LText();

	while (pHead != nullptr && pHead->pNext != nullptr) {
		wcout << pHead->data.courseId << " ";
		wcout << pHead->data.courseName << " ";
		wcout << pHead->data.teacherName << " ";
		wcout << pHead->data.credit << " ";
		wcout << pHead->data.maxStu << " ";
		wcout << pHead->data.session[0].dayOfWeek << "-" << pHead->data.session[0].hour << " ";
		wcout << pHead->data.session[1].dayOfWeek << "-" << pHead->data.session[1].hour << " ";
		wcout << endl;
		pHead = pHead->pNext;
	}

	_SText();
}

void displayCourseConsoleInSem(_course* pHead, Date start, Date end) {
	_LText();

	while (pHead != nullptr && pHead->pNext != nullptr) {
		if (pHead->data.startRegis != start) {
			pHead = pHead->pNext; 
			continue;
		}
		wcout << pHead->data.courseId << " ";
		wcout << pHead->data.courseName << " ";
		wcout << pHead->data.teacherName << " ";
		wcout << pHead->data.credit << " ";
		wcout << pHead->data.maxStu << " ";
		wcout << pHead->data.session[0].dayOfWeek << "-" << pHead->data.session[0].hour << " ";
		wcout << pHead->data.session[1].dayOfWeek << "-" << pHead->data.session[1].hour << " ";
		wcout << endl;

		pHead = pHead->pNext;
	}

	_SText();
}

void displayIndividualCourseConsole(course pHead) {
	_LText();

	wcout << pHead.courseId << " ";
	wcout << pHead.courseName << " ";
	wcout << pHead.teacherName << " ";
	wcout << pHead.credit << " ";
	wcout << pHead.maxStu << " ";
	wcout << pHead.session[0].dayOfWeek << "-" << pHead.session[0].hour;
	wcout << " ";
	wcout << pHead.session[1].dayOfWeek << "-" << pHead.session[1].hour;
	wcout << endl;

	_SText();

	cout << endl;
}

void displayStudentAttendIndividualCourse(_studentRegis* pHead) {
	cout << "Student's ID list: " << endl;
	while (pHead != nullptr && pHead->pNext != nullptr) {
		cout << pHead->data << endl;
		pHead = pHead->pNext;
	}
}

_course* findCourse(unsigned long long ID, _course* pHead) {
	while (pHead != nullptr && pHead->pNext != nullptr) {
		if (pHead->data.courseId == ID) return pHead;
		pHead = pHead->pNext;
	}
	return nullptr;
}

_course* findCourseInSem(unsigned long long ID, _course* pHead, Date start, Date end) {
	while (pHead != nullptr && pHead->pNext != nullptr) {
		if (pHead->data.courseId == ID && start == pHead->data.startRegis) return pHead;
		pHead = pHead->pNext;
	}
	return nullptr;
}

void createCourseFromKeyboardInSem(Date start, Date end) {
	_course* pHead = nullptr;

	_mkdir("Data");
	_mkdir("Data\\Course");

	inputFromKeyboardCourseInSem(pHead, start, end);

	addCourseFile(folderDir + folderCourseDir + courseListDir, pHead);

	writeAllIndividualCourseFile(pHead);

	deleteListCourse(pHead);
}

void createCourseFromFileInSem(Date start, Date end) {
	_course* pHead = nullptr;

	_mkdir("Data");
	_mkdir("Data\\Course");

	string path;

	cout << "Input the name of the file contain course's info: ";
	cin >> path;
	path += csvFormat;

	readForInputCourseFileInSem(path, pHead, start, end);

	addCourseFile(folderDir + folderCourseDir + courseListDir, pHead);

	writeAllIndividualCourseFile(pHead);

	deleteListCourse(pHead);
}

void editCourseInSem(Date start, Date end) {
	_course* pHead = nullptr, * pEdit = nullptr;

	readCourseFile(folderDir + folderCourseDir + courseListDir, pHead);
	readAllIndividualCourseFile(folderDir + folderCourseDir, pHead);

	cout << "Course's information list: " << endl;
	displayCourseConsoleInSem(pHead, start, end); 

	unsigned long long tempID;
	cout << "Enter the ID of the course you want to edit: ";
	cin >> tempID;

	pEdit = findCourseInSem(tempID, pHead, start, end); 
	if (pEdit == nullptr) {
		cout << "Can't find!\n";
		deleteListCourse(pHead);
		return;
	}
	cout << "Course's information before edit:" << endl;
	displayIndividualCourseConsole(pEdit->data);

	cin.ignore(1000, '\n');

	_LText();

	wcout << "Course's name: ";
	std::getline(wcin, pEdit->data.courseName, L'\n');
	wcout << "Teacher's name: ";
	std::getline(wcin, pEdit->data.teacherName, L'\n');

	_SText();

	cout << "Number of credits: ";
	cin >> pEdit->data.credit;
	cout << "Course's max student: ";
	cin >> pEdit->data.maxStu;

	for (int i = 0; i < 2; i++) {
		cout << "Day of week " << i + 1 << " of the course will performed (MON / TUE / WED / THU / FRI / SAT): ";
		wcin >> pEdit->data.session[i].dayOfWeek;
		pEdit->data.session[i].dayOfWeek[3] = '\0';
		cout << "The session " << i + 1 << " of the course will performed (S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30)): ";
		wcin >> pEdit->data.session[i].hour;
		pEdit->data.session[i].hour[2] = '\0';
	}

	cout << "Course's information after edit:" << endl;
	displayIndividualCourseConsole(pEdit->data);

	cout << "All course's information:" << endl;
	displayCourseConsoleInSem(pHead, start, end);

	writeCourseFile(folderDir + folderCourseDir + courseListDir, pHead);

	writeAllIndividualCourseFile(pHead);

	deleteListCourse(pHead);
}

void removeCourseInSem(Date start, Date end) {
	_course* pHead = nullptr, * pRemove;

	readCourseFile(folderDir + folderCourseDir + courseListDir, pHead);
	readAllIndividualCourseFile(folderDir + folderCourseDir, pHead);

	cout << "Course's information list: " << endl;
	displayCourseConsoleInSem(pHead, start, end);

	unsigned long long tempID;
	cout << "Enter the ID of the course you want to remove: ";
	cin >> tempID;
	pRemove = findCourseInSem(tempID, pHead, start, end);
	if (pRemove == nullptr) {
		cout << "Can't find!\n";
		deleteListCourse(pHead);
		return;
	}

	writeCourseFileWithout1Course(folderDir + folderCourseDir + courseListDir, pHead, tempID);
	string path;
	path = folderDir + folderCourseDir + to_string(tempID) + csvFormat;
	remove(path.c_str());

	deleteListCourse(pHead);
}

//chua chia ham
void viewAttendStudentInSem(Date start, Date end) {
	_course* pHeadCourse = nullptr;

	readCourseFile(folderDir + folderCourseDir + courseListDir, pHeadCourse);
	readAllIndividualCourseFile(folderDir + folderCourseDir, pHeadCourse);

	_account* pHeadAccount = nullptr;
	readAccount(folderDir + passStudentDir, pHeadAccount); //list of ID and class name of every student

	cout << "Course's information list: " << endl;
	displayCourseConsoleInSem(pHeadCourse, start, end); 

	unsigned long long tempID;
	_student* pHeadStu = nullptr, * pCreateStu = nullptr, * pDisplayStu = nullptr;
	_studentRegis* pCurStu;
	_account* pCurAccount;
	_course* pDisplay;
	int temp = 1;

	wifstream fileIn;
	string path;
	wstring tempRead;
	wchar_t a = ',';

	while (temp != 0) {
		cout << "Enter the ID of the course you want to view student list: ";
		cin >> tempID;
		
		pDisplay = findCourseInSem(tempID, pHeadCourse, start, end); //have list of attend student's ID 
		if (pDisplay == nullptr) {
			cout << "Can't find!\n";
			continue;
		}
		pCurStu = pDisplay->data.studentID;
		pCurAccount = pHeadAccount;
		while (pCurStu != nullptr && pCurStu->pNext != nullptr) {
			while (pCurAccount != nullptr && pCurAccount->pNext != nullptr) {
				if (pCurStu->data == pCurAccount->data.Student_ID) {
					path = folderDir + folderClassDir + pCurAccount->data.className + "\\" + to_string(pCurAccount->data.Student_ID) + csvFormat;
					fileIn.open(path, ios_base::in);
					fileIn.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

					if (pHeadStu == nullptr) {
						pHeadStu = new _student;
						pCreateStu = pHeadStu;
					}
					else {
						pCreateStu->pNext = new _student;
						pCreateStu = pCreateStu->pNext;
					}
					getline(fileIn, tempRead, a);
					pCreateStu->data.Student_ID = wstringToLong(tempRead);
					getline(fileIn, pCreateStu->data.FirstName, a);
					getline(fileIn, pCreateStu->data.LastName, a);
					getline(fileIn, pCreateStu->data.Gender, a);
					getline(fileIn, tempRead, a);
					pCreateStu->data.Date_Of_Birth = wstringToDate(tempRead);
					fileIn >> pCreateStu->data.Social_ID;

					fileIn.close();
					pCreateStu->pNext = nullptr;
				}
				pCurAccount = pCurAccount->pNext;
			}
			pCurStu = pCurStu->pNext;
			pCurAccount = pHeadAccount;
		}
		cout << "List of student attend: \n";
		pDisplayStu = pHeadStu;
		_LText();
		while (pDisplayStu != nullptr) {
			wcout << pDisplayStu->data.Student_ID << " " << pDisplayStu->data.FirstName << " " << pDisplayStu->data.LastName << " " << pDisplayStu->data.Gender << " ";
			wcout << pDisplayStu->data.Date_Of_Birth.day << wchar_t(47) << pDisplayStu->data.Date_Of_Birth.month << wchar_t(47) << pDisplayStu->data.Date_Of_Birth.year << " ";
			wcout << pDisplayStu->data.Social_ID << endl;
			pDisplayStu = pDisplayStu->pNext;
		}
		_SText();
		deleteListStudent(pHeadStu);
		pHeadStu = nullptr;
		cout << "Enter 0 to escape: ";
		cin >> temp;
	}

	deleteListCourse(pHeadCourse);
	deleteListAccount(pHeadAccount);
}

//chua chia ham
void writeAttendStudentInSem(Date start, Date end) {
	_course* pHeadCourse = nullptr;

	readCourseFile(folderDir + folderCourseDir + courseListDir, pHeadCourse);
	readAllIndividualCourseFile(folderDir + folderCourseDir, pHeadCourse);

	_account* pHeadAccount = nullptr;
	readAccount(folderDir + passStudentDir, pHeadAccount); //list of ID and class name of every student

	cout << "Course's information list: " << endl;
	displayCourseConsoleInSem(pHeadCourse, start, end); 

	unsigned long long tempID;
	_student* pHeadStu = nullptr, * pCreateStu = nullptr, * pDisplayStu = nullptr;
	_studentRegis* pCurStu;
	_account* pCurAccount;
	_course* pDisplay;
	int temp = 1;

	wifstream fileIn;
	wofstream fileOut;
	string path;
	wstring tempRead;
	wchar_t a = ',';

	while (temp != 0) {
		cout << "Enter the ID of the course you want to view student list: ";
		cin >> tempID;
		
		pDisplay = findCourseInSem(tempID, pHeadCourse, start, end); //have list of attend student's ID 
		if (pDisplay == nullptr) continue;
		pCurStu = pDisplay->data.studentID;
		pCurAccount = pHeadAccount;
		while (pCurStu != nullptr && pCurStu->pNext != nullptr) {
			while (pCurAccount != nullptr && pCurAccount->pNext != nullptr) {
				if (pCurStu->data == pCurAccount->data.Student_ID) {
					//open doc file blum bla
					path = folderDir + folderClassDir + pCurAccount->data.className + "\\" + to_string(pCurAccount->data.Student_ID) + csvFormat;
					fileIn.open(path, ios_base::in);
					fileIn.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

					if (pHeadStu == nullptr) {
						pHeadStu = new _student;
						pCreateStu = pHeadStu;
					}
					else {
						pCreateStu->pNext = new _student;
						pCreateStu = pCreateStu->pNext;
					}
					getline(fileIn, tempRead, a);
					pCreateStu->data.Student_ID = wstringToLong(tempRead);
					getline(fileIn, pCreateStu->data.FirstName, a);
					getline(fileIn, pCreateStu->data.LastName, a);
					getline(fileIn, pCreateStu->data.Gender, a);
					getline(fileIn, tempRead, a);
					pCreateStu->data.Date_Of_Birth = wstringToDate(tempRead);
					fileIn >> pCreateStu->data.Social_ID;

					fileIn.close();
					pCreateStu->pNext = nullptr;
				}
				pCurAccount = pCurAccount->pNext;
			}
			//cout << "\n\t1" << pCurStu->data;
			pCurStu = pCurStu->pNext;
			pCurAccount = pHeadAccount;
		}
		cout << "Name of file you want to export: ";
		cin >> path;

		fileOut.open(path, ios_base::out);
		fileOut.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

		pDisplayStu = pHeadStu;
		_LText();
		while (pDisplayStu != nullptr) {
			fileOut << pDisplayStu->data.Student_ID << "," << pDisplayStu->data.FirstName << "," << pDisplayStu->data.LastName << "," << pDisplayStu->data.Gender << ",";
			fileOut << pDisplayStu->data.Date_Of_Birth.day << wchar_t(47) << pDisplayStu->data.Date_Of_Birth.month << wchar_t(47) << pDisplayStu->data.Date_Of_Birth.year << ",";
			fileOut << pDisplayStu->data.Social_ID << endl;
			pDisplayStu = pDisplayStu->pNext;
		}
		_SText();

		fileOut.close();
		deleteListStudent(pHeadStu);
		pHeadStu = nullptr;
		cout << "Enter 0 to escape: ";
		cin >> temp;
	}

	deleteListCourse(pHeadCourse);
	deleteListAccount(pHeadAccount);
}


//----------------------------------------------------------

//coi nhu user input du cot diem cua toan bo sv
void readScoreboard(string path, _course*& course) {
	//delete student regis cu
	deleteListStudentAttend(course->data.studentID);
	course->data.studentID = nullptr;
	//load
	wifstream fileIn;
	fileIn.open(path, ios_base::in);
	fileIn.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	if (fileIn.fail())
	{
		cout << "File is not existed " << endl;
		return;
	}

	_studentRegis* pCur = nullptr;
	wchar_t a = ',', b = '\n';
	while (fileIn) {
		if (course->data.studentID == nullptr) {
			course->data.studentID = new _studentRegis;
			pCur = course->data.studentID;
		}
		else {
			pCur->pNext = new _studentRegis;
			pCur = pCur->pNext;
		}
		fileIn >> pCur->no >> a;
		fileIn >> pCur->data >> a;
		getline(fileIn, pCur->name, a);
		fileIn >> pCur->total >> a;
		fileIn >> pCur->final >> a;
		fileIn >> pCur->mid >> a;
		fileIn >> pCur->other >> a;
		fileIn >> pCur->gpa;
		pCur->pNext = nullptr;
	}

	fileIn.close();
	
}

void displayScoreboardConsole(_course* course) {
	//loop
	_studentRegis* pCur = course->data.studentID;
	_LText();
	while (pCur != nullptr && pCur->pNext != nullptr) {
		wcout << pCur->data << " ";
		wcout << pCur->name << " ";
		wcout << pCur->total << " ";
		wcout << pCur->final << " ";
		wcout << pCur->mid << " ";
		wcout << pCur->other << " ";
		wcout << pCur->gpa << endl;
		pCur = pCur->pNext;
	}
	_SText();
}

void writeScoreboardAllIndividualStu(_course* course) {
	_studentRegis* pCurStu = course->data.studentID;

	_account* pHeadAccount = nullptr;
	readAccount(folderDir + passStudentDir, pHeadAccount); //list of ID and class name of every student
	_account* pCurAccount;

	wifstream fileIn;
	wofstream fileOut;
	string path;
	//bien dung de giu tam thong tin cua student
	student temp;
	_score* pCurScore = nullptr;

	while (pCurStu != nullptr && pCurStu->pNext != nullptr) {
		//tim file cua pCur->data 
		pCurAccount = pHeadAccount;
		while (pCurStu != nullptr && pCurStu->pNext != nullptr) {
			while (pCurAccount != nullptr && pCurAccount->pNext != nullptr) {
				if (pCurStu->data == pCurAccount->data.Student_ID) {
					//co ID, co class cua sv
					path = folderDir + folderClassDir + pCurAccount->data.className + "\\" + to_string(pCurAccount->data.Student_ID) + csvFormat;
					//mo file cua sinh vien do
					fileIn.open(path, ios_base::in);
					fileIn.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
					//load toan bo info cua sinh vien do
					temp = findInfoStudent(pCurAccount->data.Student_ID, pCurAccount->data.className);
					//tim cot diem cua mon can chinh
					pCurScore = temp.score;
					while (pCurScore != nullptr && pCurScore->pNext != nullptr) {
						if (pCurScore->data.course_ID == course->data.courseId) {
							//edit
							pCurScore->data.total = pCurStu->total;
							pCurScore->data.final = pCurStu->final;
							pCurScore->data.mid = pCurStu->mid;
							pCurScore->data.other = pCurStu->other;
							pCurScore->data.gpa = pCurStu->gpa;
						}
						pCurScore = pCurScore->pNext;
					}
					//rewrite
					createStudentFile(temp, pCurAccount->data.className);
					//delete
					deleteListScore(temp);
				}
				pCurAccount = pCurAccount->pNext;
			}

			pCurStu = pCurStu->pNext;
			pCurAccount = pHeadAccount;
		}
	}
	deleteListAccount(pHeadAccount);
}

void inputScoreboardInSem(Date start, Date end) {
	//read course list
	_course* pHead = nullptr, * pEdit;
	string path;

	readCourseFile(folderDir + folderCourseDir + courseListDir, pHead);
	readAllIndividualCourseFile(folderDir + folderCourseDir, pHead);

	//display list of courses
	cout << "Course's information list: " << endl;
	
	displayCourseConsoleInSem(pHead, start, end);

	//choose course
	unsigned long long tempID;
	cout << "Enter the ID of the course you want to import scoreboard: ";
	cin >> tempID;
	//find course
	pEdit = findCourseInSem(tempID, pHead, start, end);
	if (pEdit == nullptr) {
		cout << "Can't find!\n";
		deleteListCourse(pHead);
		return;
	}
	//input file name
	cout << "Enter the name of file you want to import: ";
	cin >> path;
	//read
	readScoreboard(path, pEdit);

	//rewrite
	path = folderDir + folderCourseDir + to_string(pEdit->data.courseId) + csvFormat;
	writeIndividualCourseFile(path, pEdit->data);
	writeScoreboardAllIndividualStu(pEdit);

	//delete
	deleteListCourse(pHead);
}

void viewScoreboardCourseInSem(Date start, Date end) {
	//read course list
	_course* pHead = nullptr;
	string FolderPath = "Data\\Course\\", coursePath = "Course.csv", fileFormat = ".csv", path;

	readCourseFile(folderDir + folderCourseDir + courseListDir, pHead);
	readAllIndividualCourseFile(folderDir + folderCourseDir, pHead);

	_account* pHeadAccount = nullptr;
	readAccount(folderDir + passStudentDir, pHeadAccount); //list of ID and class name of every student

	//display list of courses
	cout << "Course's information list: " << endl;
	displayCourseConsoleInSem(pHead, start, end);

	//choose course
	unsigned long long tempID;
	_studentRegis* pCurStu;
	_account* pCurAccount;
	_course* pDisplay;
	int temp = 1;

	wifstream fileIn;
	wstring firstName, lastName, fullName, stringTemp;
	wstring tempRead;
	wchar_t a = ',';

	while (temp != 0) {
		cout << "Enter the ID of the course you want to view scoreboard: ";
		cin >> tempID;
		pDisplay = findCourseInSem(tempID, pHead, start, end); //have list of attend student's ID
		if (pDisplay == nullptr) {
			cout << "Can't find\n";
			continue;
		}
		pCurStu = pDisplay->data.studentID;
		pCurAccount = pHeadAccount;
		while (pCurStu != nullptr && pCurStu->pNext != nullptr) {
			while (pCurAccount != nullptr && pCurAccount->pNext != nullptr) {
				if (pCurStu->data == pCurAccount->data.Student_ID) {
					path = folderDir + folderClassDir + pCurAccount->data.className + "\\" + to_string(pCurAccount->data.Student_ID) + csvFormat;
					fileIn.open(path, ios_base::in);
					fileIn.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

					getline(fileIn, stringTemp, a);
					getline(fileIn, firstName, a);
					getline(fileIn, lastName, a);
					fullName = firstName + L" " + lastName;
					pCurStu->name = fullName;

					fileIn.close();

				}
				pCurAccount = pCurAccount->pNext;
			}

			pCurStu = pCurStu->pNext;
			pCurAccount = pHeadAccount;
		}

		cout << "Scoreboard: \n";
		displayScoreboardConsole(pDisplay);

		cout << "Enter 0 to escape: ";
		cin >> temp;
	}
	deleteListCourse(pHead);
	deleteListAccount(pHeadAccount);
}

void viewScoreboardClassInSem(Date start, Date end) {
	//load class and full course
	string path;

	_Class* pHeadClass = nullptr;
	path = folderDir + folderClassDir + classListDir;
	readClassName(path, pHeadClass);

	_course* pHeadCourse = nullptr, * pCurCourse = nullptr;
	path = folderDir + folderCourseDir + courseListDir;
	readCourseFile(path, pHeadCourse);

	_score* pCurScore = nullptr;

	//choose class
	string chooseClass;
	displayClassName(pHeadClass);
	cout << "Enter class name you want to view scoreboard: ";
	cin >> chooseClass;

	//create a linked list contain stu info in that class
	_student* pHeadStu = nullptr, * pCurStu = nullptr;
	readStuInClass(folderDir + folderClassDir + chooseClass + csvFormat, pHeadStu);

	//run over again and load individual course of that stu
	wifstream fileIn;
	wstring tempCourseID;
	wchar_t a = ',';
	pCurStu = pHeadStu;

	int dem = 0;
	//while loop and then read using findInfoStudent(ID, chooseClass)
	while (pCurStu != nullptr && pCurStu->pNext != nullptr) {
		fileIn.open(folderDir + folderClassDir + chooseClass + "\\" + to_string(pCurStu->data.Student_ID) + csvFormat);
		if (fileIn.fail()) {
			pCurStu = pCurStu->pNext;
			continue;
		}
		dem++;

		fileIn.ignore(1000, '\n');
		while (fileIn) {
			if (pCurStu->data.score == nullptr) {
				pCurStu->data.score = new _score;
				pCurScore = pCurStu->data.score;
			}
			else {
				pCurScore->pNext = new _score;
				pCurScore = pCurScore->pNext;
			}
			getline(fileIn, tempCourseID, a);
			pCurScore->data.course_ID = wstringToLong(tempCourseID);
			fileIn >> pCurScore->data.total >> a;
			fileIn >> pCurScore->data.final >> a;
			fileIn >> pCurScore->data.mid >> a;
			fileIn >> pCurScore->data.other >> a;
			fileIn >> pCurScore->data.gpa;

			pCurScore->pNext = nullptr;
		}
		pCurStu = pCurStu->pNext;
		fileIn.close();
	}
	//got the data we need

	cout << dem;
	system("CLS");
	resizeConsole(1200, 600);
	//while for loop student
	pCurStu = pHeadStu;
	while (pCurStu != nullptr && pCurStu->pNext != nullptr) {
		//gotoXY
		//cout No and name
		GotoXY(0, pCurStu->data.No);
		cout << pCurStu->data.No;
		GotoXY(5, pCurStu->data.No);
		_LText();
		wcout << pCurStu->data.FirstName << " " << pCurStu->data.LastName;
		_SText();
		//while for loop all course
		pCurCourse = pHeadCourse;
		int i = 20;
		double overallGPA = 0;
		int count = 0;
		while (pCurCourse != nullptr && pCurCourse->pNext != nullptr) {
			if (pCurCourse->data.startRegis != start) {
				pCurCourse = pCurCourse->pNext;
				continue;
			}
			//while for loop course that student attends
			i += 12;
			GotoXY(i + 5, 0);
			cout << pCurCourse->data.courseId;
			pCurScore = pCurStu->data.score;
			while (pCurScore != nullptr && pCurScore->pNext != nullptr) {
				//if have that course -> cout score, if not -> cout << X	
				if (pCurCourse->data.courseId == pCurScore->data.course_ID) {
					//gotoXY
					//cout score
					GotoXY(i, pCurStu->data.No);
					cout << fixed << setprecision(2) << pCurScore->data.final;
					GotoXY(i + 6, pCurStu->data.No);
					cout << fixed << setprecision(2) << pCurScore->data.gpa;
					count++;
					overallGPA += pCurScore->data.gpa;
					break;
				}
				pCurScore = pCurScore->pNext;
			}
			if (pCurScore == nullptr || pCurScore->pNext == nullptr) {
				//gotoXY
				//cout X
				GotoXY(i, pCurStu->data.No);
				cout << "  X  ";
				GotoXY(i + 6, pCurStu->data.No);
				cout << "  X  ";
			}
			pCurCourse = pCurCourse->pNext;
		}
		GotoXY(i + 12, 0);
		cout << "Total";
		GotoXY(i + 12, pCurStu->data.No);
		if (count != 0) cout << fixed << setprecision(2) << overallGPA / count;
		if (count == 0) cout << "  X  ";
		pCurStu = pCurStu->pNext;
	}
	//a lot of delete
	deleteListCourse(pHeadCourse);
	deleteListClass(pHeadClass);
}

void editScoreFromCourseInSem(Date start, Date end) {
	//read course list
	_course* pHead = nullptr;
	string path;

	readCourseFile(folderDir + folderCourseDir + courseListDir, pHead);
	readAllIndividualCourseFile(folderDir + folderCourseDir, pHead);

	_account* pHeadAccount = nullptr;
	readAccount(folderDir + passStudentDir, pHeadAccount); //list of ID and class name of every student

	//display list of courses
	cout << "Course's information list: " << endl;
	displayCourseConsoleInSem(pHead, start, end);

	//choose course
	unsigned long long tempID, tempStuID;
	_account* pCurAccount;
	_studentRegis* pCurStu;
	_score* pCurScore;
	_course* pEdit;
	student stu;
	double total, final, mid, other, gpa;

	wifstream fileIn;

	cout << "Enter the ID of the course you want to edit scoreboard: ";
	cin >> tempID;
	
	pEdit = findCourseInSem(tempID, pHead, start, end); //have list of attend student's ID 
	cout << "Enter the ID of the student you want to edit: ";
	cin >> tempStuID;

	//edit file sinh vien
	pCurAccount = pHeadAccount;
	while (pCurAccount != nullptr && pCurAccount->pNext != nullptr) {
		if (tempStuID == pCurAccount->data.Student_ID) {
			//load thong tin sinh vien
			stu = findInfoStudent(pCurAccount->data.Student_ID, pCurAccount->data.className);

			pCurScore = stu.score;
			while (pCurScore != nullptr && pCurScore->pNext != nullptr) {

				//edit
				if (tempID == pCurScore->data.course_ID) {
					cout << "Old score: ";
					cout << "Total: " << pCurScore->data.total << " Final: " << pCurScore->data.final << " Mid: " << pCurScore->data.mid << " Other: " << pCurScore->data.other << " GPA: " << pCurScore->data.gpa << endl;
					cout << "New score: ";
					cin >> total >> final >> mid >> other >> gpa;
					pCurScore->data.total = total;
					pCurScore->data.final = final;
					pCurScore->data.mid = mid;
					pCurScore->data.other = other;
					pCurScore->data.gpa = gpa;
					//rewrite student file
					createStudentFile(stu, pCurAccount->data.className);
					break;
				}
				pCurScore = pCurScore->pNext;
			}
			break;
		}
		pCurAccount = pCurAccount->pNext;
	}

	//edit file course
	pCurStu = pEdit->data.studentID;
	while (pCurStu != nullptr && pCurStu->pNext != nullptr) {
		if (tempStuID == pCurStu->data) {
			pCurStu->total = total;
			pCurStu->final = final;
			pCurStu->mid = mid;
			pCurStu->other = other;
			pCurStu->gpa = gpa;
			//rewrite course file
			path = folderDir + folderCourseDir + to_string(pEdit->data.courseId) + csvFormat;
			writeIndividualCourseFile(path, pEdit->data);
			break;
		}
		pCurStu = pCurStu->pNext;
	}

	deleteListCourse(pHead);
	deleteListAccount(pHeadAccount);
}

void menuManageStudent() {

	int temp = 1;
	while (temp != '0') {
		system("CLS");
		cout << "1. Input class\n2. View class\n0. Escape\n\n";
		temp = _getch();
		switch (temp) {
		case '1':
			inputClass();
			break;
		case '2':
			displayClassAndStudent();
			break;
		default:
			break;
		}
		cout << "\n";
		system("PAUSE");
	}
}

void menuManageCourse() {
	Date start, end;
	create_chooseSem(start, end);

	int temp = 1;
	while (temp != '0') {
		system("CLS");
		cout << "1. Input course\n2. View course\n3. Edit course\n4. Remove course\n5. Export course\n0. Escape\n\n";
		temp = _getch();
		switch (temp) {
		case '1':
		{
			//choose method
			int tempSub;
			cout << "1. Input from keyboard\n2. Input from file\n0. Escape\n\n";
			tempSub = _getch();
			switch (tempSub) {
			case '1':
				createCourseFromKeyboardInSem(start, end);
				break;
			case '2':
				createCourseFromFileInSem(start, end);
				break;
			default:
				break;
			}
		}
		break;
		case '2': {
			_course* pHead = nullptr;
			readCourseFile(folderDir + folderCourseDir + courseListDir, pHead);
			cout << "Course's information list: " << endl;
			displayCourseConsoleInSem(pHead, start, end);
			break;
		}
		case '3':
			editCourseInSem(start, end);
			break;
		case '4':
			removeCourseInSem(start, end);
			break;
		case '5':
			writeAttendStudentInSem(start, end);
			break;
		default:
			break;
		}
		cout << "\n";
		system("PAUSE");
	}
}

void menuManageScore() {
	Date start, end;
	create_chooseSem(start, end);

	int temp = 1;
	while (temp != '0') {
		system("CLS");
		cout << "1. Input score\n2. View score\n3. Edit score\n0. Escape\n\n";
		temp = _getch();
		switch (temp) {
		case '1':
			inputScoreboardInSem(start, end);
			break;
		case '2': {
			//choose method
			int tempSub;
			cout << "1. View course scoreboard\n2. View class score\n0. Escape\n\n";
			tempSub = _getch();
			switch (tempSub) {
			case '1':
				viewScoreboardCourseInSem(start, end);
				break;
			case '2':
				viewScoreboardClassInSem(start, end);
				break;
			default:
				break;
			}
			break; 
		}
		case '3':
			editScoreFromCourseInSem(start, end);
			break;
		default:
			break;
		}
		cout << "\n";
		system("PAUSE");
	}
}

void menuStaff() {
	int temp = 1;
	while (temp != '0') {
		system("CLS");
		cout << "1. Manage student\n2. Manage course\n3. Manage score\n0. Escape\n\n";
		temp = _getch();
		switch (temp) {
		case '1':
			menuManageStudent();
			break;
		case '2':
			menuManageCourse();
			break;
		case '3':
			menuManageScore();
			break;
		default:
			break;
		}
	}
}
