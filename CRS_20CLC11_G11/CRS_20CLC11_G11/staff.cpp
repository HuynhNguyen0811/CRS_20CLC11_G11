#include "staff.h"
#include "commonFunc.h"

void deleteListClass(_Class*& pHead) {
	_Class* pTmp = pHead;
	while (pHead != nullptr) {
		pHead = pHead->pNext;
		delete pTmp;
		pTmp = pHead;
	}
}

void deleteListCourse(_course*& pHead) {
	_course* pTmp = pHead;
	while (pHead != nullptr) {
		for (int i = 0; i < 2; i++) {
			delete[] pHead->data.session[i].dayOfWeek;
			delete[] pHead->data.session[i].hour;
		}

		delete[] pHead->data.session;
		pHead = pHead->pNext;
		delete pTmp;
		pTmp = pHead;
	}
}

void deleteListStudentAttend(_studentRegis* pHead) {
	_studentRegis* pTmp = pHead;
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
		cout << "Please enter file name that contains class name: ";
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

			newPath = folderName + pathSub + pHeadClass->data.name + fileFormat;
			writeFileStudent(newPath, pHeadClass->data.student);

			deleteListStudent(pHeadClass->data.student);
			pHeadClass = pHeadClass->pNext;
		}
		deleteListClass(pHeadClass);
		menuStaff();
		break;
	default:
		//menuStaff();
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

void inputFromKeyboardCourse(_course*& pHead) {
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
			pCur->data.session[i].dayOfWeek = new wchar_t[3 + 1];
			pCur->data.session[i].hour = new wchar_t[2 + 1];
		}

		for (int i = 0; i < 2; i++) {
			cout << "Day of week " << i + 1 << " of the course will performed (MON / TUE / WED / THU / FRI / SAT): ";
			wcin >> pCur->data.session[i].dayOfWeek;
			pCur->data.session[i].dayOfWeek[3] = '\0';
			cout << "The session " << i + 1 << " of the course will performed (S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30)): ";
			wcin >> pCur->data.session[i].hour;
			pCur->data.session[i].hour[2] = '\0';
		}
		//string temp;
		//cout << "Start registration date: "; cin >> temp; pCur->data.startRegis = stringToDate(temp);
		//cout << "End registration date: "; cin >> temp; pCur->data.endRegis = stringToDate(temp);
		
		pCur->pNext = nullptr;

		cout << "Enter 0 to stop: ";
		cin >> temp;
	}

	pCur->pNext = new _course;
	pCur = pCur->pNext;
	pCur->data.session = new session[2];
	for (int i = 0; i < 2; i++) {
		pCur->data.session[i].dayOfWeek = new wchar_t[3 + 1];
		pCur->data.session[i].hour = new wchar_t[2 + 1];
	}
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
		for (int i = 0; i < 2; i++) {
			pCur->data.session[i].dayOfWeek = new wchar_t[3 + 1];
			pCur->data.session[i].hour = new wchar_t[2 + 1];
		}

		for (int i = 0; i < 2; i++) {
			getline(fileIn, temp, a);
			wstringToWchar(pCur->data.session[i].dayOfWeek, temp);
			getline(fileIn, temp, a);
			wstringToWchar(pCur->data.session[i].hour, temp);
			pCur->data.session[i].dayOfWeek[3] = '\0';
			pCur->data.session[i].hour[2] = '\0';
		}

		getline(fileIn, temp, a);
		pCur->data.startRegis = wstringToDate(temp);
		getline(fileIn, temp, b);
		pCur->data.endRegis = wstringToDate(temp);

		pCur->pNext = nullptr;
	}
	fileIn.close();
}

void readAllIndividualCourseFile(string path, _course* pHead) {
	while (pHead != nullptr && pHead->pNext != nullptr) {
		readIndividualCourseFile(path + to_string(pHead->data.courseId) + ".csv", pHead);
		pHead = pHead->pNext;
	}
}

void readIndividualCourseFile(string path, _course* pHead) { //to read id student that regis
	wifstream fileIn;
	fileIn.open(path, ios_base::in);
	fileIn.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	wstring temp;
	_studentRegis* pCur = nullptr;
	while (fileIn) {
		if (pHead->data.studentID == nullptr) {
			pHead->data.studentID = new _studentRegis;
			pCur = pHead->data.studentID;
		}
		else {
			pCur->pNext = new _studentRegis;
			pCur = pCur->pNext;
		}
		fileIn.ignore(1000, '\n');
		getline(fileIn, temp, L',');
		pCur->data = wstringToLong(temp);
		pCur->pNext = nullptr;
	}
	
	fileIn.close();
}

void writeCourseFile(string path, _course* pHead) {
	if (pHead == nullptr) return;
	wofstream fileOut;
	fileOut.open(path, ios_base::out);
	fileOut.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	
	while (pHead->pNext != nullptr) {
		fileOut << pHead->data.courseId << "," << pHead->data.courseName << "," << pHead->data.teacherName << "," << pHead->data.credit << "," << pHead->data.maxStu << ",";
		fileOut << pHead->data.session[0].dayOfWeek << "," << pHead->data.session[0].hour << ",";
		fileOut	 << pHead->data.session[1].dayOfWeek << "," << pHead->data.session[1].hour << ",";
		fileOut << pHead->data.startRegis.day << L"/" << pHead->data.startRegis.month << L"/" << pHead->data.startRegis.year << ",";
		fileOut << pHead->data.endRegis.day << L"/" << pHead->data.endRegis.month << L"/" << pHead->data.endRegis.year << endl;
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
		fileOut << pCur->data << endl;
		pCur = pCur->pNext;
	}

	fileOut.close();
}

void addCourseListFile(string path, course pHead) { //khong dung
	wofstream fileOut;
	fileOut.open(path, ios_base::app);
	fileOut.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	fileOut << pHead.courseId << endl;

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

void writeAllIndividualCourseFile(string path, _course* pHead) {
	string FolderPath = "Data\\Course\\", fileFormat = ".csv";

	while (pHead->pNext != nullptr) {
		writeIndividualCourseFile(FolderPath + to_string(pHead->data.courseId) + fileFormat, pHead->data);
		pHead = pHead->pNext;
	}

}

void displayCourseConsole(_course* pHead) {
	_LText();

	while (pHead->pNext != nullptr) {
		wcout << pHead->data.courseId << " ";
		wcout << pHead->data.courseName << " ";
		wcout << pHead->data.teacherName << " ";
		wcout << pHead->data.credit << " ";
		wcout << pHead->data.maxStu << " ";
		wcout << pHead->data.session[0].dayOfWeek << "-" << pHead->data.session[0].hour << " ";
		wcout << pHead->data.session[1].dayOfWeek << "-" << pHead->data.session[1].hour << " ";
		wcout << pHead->data.startRegis.day << L"/" << pHead->data.startRegis.month << L"/" << pHead->data.startRegis.year << " ";
		wcout << pHead->data.endRegis.day << L"/" << pHead->data.endRegis.month << L"/" << pHead->data.endRegis.year << endl;
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
	wcout << " ";
	wcout << pHead.startRegis.day << L"/" << pHead.startRegis.month << L"/" << pHead.startRegis.year << " ";
	wcout << pHead.endRegis.day << L"/" << pHead.endRegis.month << L"/" << pHead.endRegis.year << endl;

	_SText();

	cout << endl;
}

void displayStudentAttendIndividualCourse(_studentRegis* pHead) {
	cout << "Student's ID list: " << endl;
	while (pHead->pNext != nullptr) {
		cout << pHead->data << endl;
		pHead = pHead->pNext;
	}
}

_course* findCourse(unsigned long long ID, _course* pHead) {
	while (pHead != nullptr) {
		if (pHead->data.courseId == ID) return pHead;
		pHead = pHead->pNext;
	}
}

void createCourseFromKeyboard() {
	_course* pHead = nullptr;
	string FolderPath = "Data\\Course\\", coursePath = "Course.csv", fileFormat = ".csv";

	_mkdir("Data");
	_mkdir("Data\\Course");

	inputFromKeyboardCourse(pHead);

	//displayCourseConsole(pHead);

	writeCourseFile(FolderPath + coursePath, pHead);

	writeAllIndividualCourseFile("", pHead);

	deleteListCourse(pHead);
}

void createCourseFromFile() {
	_course* pHead = nullptr;
	string FolderPath = "Data\\Course\\", coursePath = "Course.csv", fileFormat = ".csv";

	_mkdir("Data");
	_mkdir("Data\\Course");

	string path;

	cout << "Input the name of the file contain course's info: ";
	cin >> path;
	path += fileFormat;

	ifstream fileIn; 
	fileIn.open(path, ios_base::in);
	if (fileIn.fail())
	{
		cout << "File is not existed " << endl;
		fileIn.close();
		return;
	}

	readCourseFile(path, pHead);

	//displayCourseConsole(pHead);

	writeCourseFile(FolderPath + coursePath, pHead);

	writeAllIndividualCourseFile("", pHead);

	deleteListCourse(pHead);
}

void editCourse() {
	_course* pHead = nullptr, *pEdit;
	string FolderPath = "Data\\Course\\", coursePath = "Course.csv", fileFormat = ".csv";

	readCourseFile(FolderPath + coursePath, pHead);
	readAllIndividualCourseFile(FolderPath, pHead);

	cout << "Course's information list: " << endl;
	displayCourseConsole(pHead);

	unsigned long long tempID;
	cout << "Enter the ID of the course you want to edit: ";
	cin >> tempID;

	pEdit = findCourse(tempID, pHead);

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
	displayCourseConsole(pHead);

	writeCourseFile(FolderPath + coursePath, pHead);

	writeAllIndividualCourseFile("", pHead);

	deleteListCourse(pHead);
}

void createCourse() {
	int flag = -1;
	while (flag != 0) {
		cout << "1. Input course from keyboard\n2. Input course from file .csv\n3. Edit course's information\n0. Escape\n";
		cin >> flag;
		switch (flag) {
		case 1:
			createCourseFromKeyboard();
			break;
		case 2:
			createCourseFromFile();
			break;
		case 3:
			editCourse();
			break;
		default:
			break;
		}
	}
}