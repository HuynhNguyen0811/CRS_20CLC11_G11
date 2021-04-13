#include "staff.h"

void deleteListClass(_Class*& pHead) {
	_Class* pTmp = pHead;
	while (pHead != nullptr) {
		pHead = pHead->pNext;
		delete pTmp;
		pTmp = pHead;
	}
}

void loadClassName(string className, _Class*& pHeadClass) {
	ifstream fileIn;
	fileIn.open(className, ios_base::in);
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

void createClassListFile(string path, string className) {
	ofstream fileOut;
	fileOut.open(path, ios_base::app);

	fileOut << className << endl;

	fileOut.close();
}
void AtTheBeginningOfSchoolYear() {
	system("CLS");
	//SchoolYear sy;
	_student* pHead = nullptr;
	string className;
	_Class* pHeadClass = nullptr;

	_mkdir("Data");
	_mkdir("Data\\Classes");

	string path; //duong dan cua file test case input class
	string folderName = "Data\\", newPath, fileFormat = ".csv", pathSub = "Classes\\";
	int flag;
	cout << "Choose method to input class name\n1.From keyboard\n2.From a file\n0.Escape";
	cin >> flag;
	switch (flag) {
	case 1:
		while (true) {
			cout << "Creating a class:\nPlease enter class name: ";
			cin >> className;

			newPath = folderName + pathSub + "Class_Name" + fileFormat;
			createClassListFile(newPath, className);

			readFileStudent(path, pHead);

			newPath = folderName + "passStudent";
			createLogInStudent(newPath, pHead, className);

			newPath = folderName + pathSub + className + fileFormat;
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
		menuStaff();
		break;
	case 2:
		cout << "Please enter file that contain class name: ";
		cin >> className;
		loadClassName(className, pHeadClass);
		if (pHeadClass == nullptr) menuStaff();
		while (pHeadClass->pNext != nullptr) {

			newPath = folderName + pathSub + "Class_Name" + fileFormat;
			createClassListFile(newPath, pHeadClass->data.name);

			pHeadClass->data.student = nullptr;
			readFileStudent(path, pHeadClass->data.student);

			newPath = folderName + "passStudent";
			createLogInStudent(newPath, pHeadClass->data.student, pHeadClass->data.name);

			newPath = folderName + pHeadClass->data.name + fileFormat;
			writeFileStudent(newPath, pHeadClass->data.student);

			deleteListStudent(pHeadClass->data.student);
			pHeadClass = pHeadClass->pNext;
		}
		deleteListClass(pHeadClass);
		menuStaff();
		break;
	default:
		menuStaff();
		break;
	}
}


void menuStaff() {
	system("CLS");
	cout << "Log in as staff successfull";
	int flag;
	cin >> flag;
	switch (flag) {
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	}
}

/*void AtTheBeginningOfSchoolYear() {
	system("CLS");
	//SchoolYear sy;
	_student* pHead = nullptr;
	string className;
	_Class* pHeadClass = nullptr;
	//createSchoolYear(sy);
	//cout << "Creating a school year (" << sy.x << "-" << sy.y << ")" << endl;
	int flag;
	cout << "Choose method to input class name\n1.From keyboard\n2.From a file\n0.Escape";
	cin >> flag;
	switch (flag) {
	case 1:
		while (true) {
			cout << "Creating a class:\nPlease enter class name: ";
			cin >> className;
			//createClassList(to_string(sy.x) + to_string(sy.y) + "year1" + className, sy);
			string path, newPath;
			readFileStudent(path, pHead);
			createLogInStudent("passStudent", pHead, className);
			writeFileStudent(className, pHead);
			deleteListStudent(pHead);
			int temp;
			cout << "Input '0' if you want to escape: ";
			cin >> temp;
			if (temp == 0) {
				system("CLS");
				break;
			}
		}
		menuStaff();
		break;
	case 2:
		cout << "Please enter file that contain class name: ";
		cin >> className;
		loadClassName(className, pHeadClass);
		if (pHeadClass == nullptr) menuStaff();
		while (pHeadClass->pNext != nullptr) {
			//createClassList(to_string(sy.x) + to_string(sy.y) + "year1" + pHeadClass->data.name, sy);
			string path, newPath;
			pHeadClass->data.student = nullptr;
			readFileStudent(path, pHeadClass->data.student);
			createLogInStudent("passStudent", pHeadClass->data.student, pHeadClass->data.name);
			//newPath = to_string(sem.x) + "-" + to_string(sem.y) + className;
			//rename(path + ".csv", newPath + ".csv");
			writeFileStudent(pHeadClass->data.name, pHeadClass->data.student);
			deleteListStudent(pHeadClass->data.student);
			pHeadClass = pHeadClass->pNext;
		}
		deleteListClass(pHeadClass);
		menuStaff();
		break;
	default:
		menuStaff();
		break;
	}
}*/

void AtTheBeginningOfSemester() {
	int* flag = new int;
	cout << "Choose:\n1. Create semester\n2. Create a course registration\n3. Add a course\n4. View list of courses\n5. Update course infomation\n6. Delete course";
	cin >> *flag;
	switch (*flag) {
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	default:
		break;
	}
	delete flag;
}

void readCourseFile(_course*& pHead) {
	string path;
	cout << "Input the name of the file contain sourse's info: ";
	cin >> path;
	wifstream fileIn;
	fileIn.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	fileIn.open(path + ".csv", ios_base::in);
	if (fileIn.fail())
	{
		cout << "File is not existed " << endl;
		createCourse();
	}
	_course* pCur = nullptr;
	wstring temp;
	wchar_t a = ',';
	while (fileIn) {
		if (pHead == nullptr) {
			pHead = new _course;
			pCur = pHead;
			pHead->pPrevious = nullptr;
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
		pCur->pNext = nullptr;
	}
	fileIn.close();
}

void writeCourseFile(_course* pHead) {
	wofstream fileOut;
	fileOut.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	while (pHead->pNext != nullptr) {
		fileOut << pHead->data.courseId << "," << pHead->data.courseName << "," << pHead->data.credit << "," << pHead->data.maxStu << endl;
		pHead = pHead->pNext;
	}
	fileOut.close();
}

void createCourse() {
	int flag = -1;
	while (flag != 0) {
		cout << "1. Input course from keyboard\n2. Input course from file .csv\n0. Escape\n";
		cin >> flag;
		switch (flag) {
		case 1:

			break;
		case 2:

			break;
		default:
			break;
		}
	}
}