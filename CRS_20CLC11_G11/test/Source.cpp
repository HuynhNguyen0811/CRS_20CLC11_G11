#include "Header.h"

unsigned long long takeTime();

void GotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int compareDate(Date x, Date y) {
	if (x.Year < y.Year || x.Month < y.Month || x.Day < y.Day) return 1; //dayx  < dayy
	else if (x.Year == y.Year && x.Month == y.Month && x.Day == y.Day) return 0; //dayx = dayy
	else return -1; //dayx > dayy
}

int isLeapYear(int year) {
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
		return 29;
	}
	else {
		return 28;
	}
}

unsigned long long calculateDate(Date x) {
	unsigned long long seconds = 0;
	int tempMonth = isLeapYear(x.Year);
	switch (x.Month) {
	case 1: seconds = (unsigned long long) x.Day; break;
	case 2: seconds = (unsigned long long) 31 + x.Day; break;
	case 3: seconds = (unsigned long long) tempMonth + 31 + x.Day; break;
	case 4: seconds = (unsigned long long) 31 + tempMonth + 31 + x.Day; break;
	case 5: seconds = (unsigned long long) 30 + 31 + tempMonth + 31 + x.Day; break;
	case 6: seconds = (unsigned long long) 31 + 30 + 31 + tempMonth + 31 + x.Day; break;
	case 7: seconds = (unsigned long long) 30 + 31 + 30 + 31 + tempMonth + 31 + x.Day; break;
	case 8: seconds = (unsigned long long) 31 + 30 + 31 + 30 + 31 + tempMonth + 31 + x.Day; break;
	case 9: seconds = (unsigned long long) 31 + 31 + 30 + 31 + 30 + 31 + tempMonth + 31 + x.Day; break;
	case 10: seconds = (unsigned long long) 30 + 31 + 31 + 30 + 31 + 30 + 31 + tempMonth + 31 + x.Day; break;
	case 11: seconds = (unsigned long long) 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31 + tempMonth + 31 + x.Day; break;
	case 12: seconds = (unsigned long long) 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31 + tempMonth + 31 + x.Day; break;
	}
	seconds += (unsigned long long) ((unsigned long long) x.Year - 2000) * 365;
	int temp = x.Year;
	while (temp > 2000) {
		if (isLeapYear(temp) == 29) seconds++;
		temp -= 1;
	}
	return seconds * 86400;
}

//ofstream& operator<<(ofstream& f, Date date) {
//	f << date.Day << char(47) << date.Month << char(47) << date.Year;
//}

void menuStudent(unsigned long long& ID, string className);
void menuStaff();
int stringToInt(string str);
unsigned long long stringToLong(string str);
Date stringToDate(string str);
bool checkLogin(string path, unsigned long long ID, string password, string& className);
void findAndPrintStudent(unsigned long long ID, string className);
void infoStudent(WStudent stu);

void _LText() //chuyen sang tieng viet
{
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);
}
void _SText() { // tat tieng viet
	_setmode(_fileno(stdin), _O_TEXT);
	_setmode(_fileno(stdout), _O_TEXT);
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

void login(unsigned long long& ID, string& className) {
	system("CLS");
	int flag, out;
	//unsigned long long ID = NULL;
	string password = "";
	bool check = 0;
	cout << "Login as student or staff: \n1.Student\n2.Staff\nEnter any others value to escape\n";
	cin >> flag;
	switch (flag) {
	case 1:
		while (check == 0) {
			if (ID != NULL && password != "") {
				cout << "Please enter again\n";
				cout << "Enter 0 if you want to come back to main menu: ";
				cin >> out;
				if (out == 0) login(ID, className);
			}
			cout << "ID: ";
			cin >> ID;
			cout << "Password: ";
			cin >> password;
			check = checkLogin("passStudent", ID, password, className);
		}
		system("CLS");
		menuStudent(ID, className);
		break;
	case 2:
		while (check == 0) {
			if (ID != NULL && password != "") {
				cout << "Please enter again\n";
				cout << "Enter 0 if you want to come back to main menu: ";
				cin >> out;
				if (out == 0) login(ID, className);
			}
			cout << "ID: ";
			cin >> ID;
			cout << "Password: ";
			cin >> password;
			check = checkLogin("passStaff", ID, password, className);
		}
		system("CLS");
		menuStaff();
		break;
	default:
		break;
	}
}
void changePassword(unsigned long long ID, string className);

void menuStudent(unsigned long long& ID, string className) {
	system("CLS");
	int flag;
	cout << "\n1.Check your profile\n2.Sign course\n3.View enrolled courses\n4.View students in course\n5.Change password\n6.Log out\n0.Escape";
	cin >> flag;
	switch (flag) {
	case 1:
		findAndPrintStudent(ID, className);
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		changePassword(ID, className);
		break;
	case 6:
		ID = NULL;
		login(ID, className);
		break;
	default:
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

void findAndPrintStudent(unsigned long long ID, string className) {
	wifstream fileIn;
	fileIn.open(className + ".csv", ios_base::in);
	fileIn.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	WStudent stu;
	wstring temp, tempID, tempDate;
	wchar_t a = ',', b = '\n';
	while (fileIn) {
		getline(fileIn, temp, a);
		getline(fileIn, tempID, a);
		if (wstringToLong(tempID) == ID) {
			stu.No = wstringToInt(temp);
			stu.Student_ID = wstringToLong(tempID);
			getline(fileIn, stu.FirstName, a);
			getline(fileIn, stu.LastName, a);
			getline(fileIn, stu.Gender, a);
			getline(fileIn, tempDate, a);
			stu.Date_Of_Birth = wstringToDate(tempDate);
			fileIn >> stu.Social_ID;
			fileIn.close();
			infoStudent(stu);
			system("PAUSE");
			menuStudent(ID, className);
		}
		else {
			getline(fileIn, temp, b);
		}
	}
	fileIn.close();
	cout << "Can't find information\n";
	system("PAUSE");
	menuStudent(ID, className);
}

void infoStudent(WStudent stu) {
	_LText();
	wcout << "Number in class: " << stu.No << endl;
	wcout << "ID: " << stu.Student_ID << endl;
	wcout << "First Name: " << stu.FirstName << endl;
	wcout << "Last name: " << stu.LastName << endl;
	wcout << "Sex: " << stu.Gender << endl;
	wcout << "Date of birth: " << stu.Date_Of_Birth.Day << "/" << stu.Date_Of_Birth.Month << "/" << stu.Date_Of_Birth.Year << endl;
	wcout << "Social ID: " << stu.Social_ID << endl;
	_SText();
}

bool checkLogin(string path, unsigned long long ID, string password, string& className) {
	ifstream fileIn;
	fileIn.open(path + ".csv", ios_base::in);
	string temp, tempPassword, tempClassName, checkPassword = "";
	unsigned long long tempID, checkID = NULL;
	while (fileIn) {
		getline(fileIn, temp, ',');
		tempID = stringToLong(temp);
		getline(fileIn, tempPassword, ',');
		fileIn >> tempClassName;
		if (tempID == ID) {
			className = tempClassName;
			checkID = tempID;
			checkPassword = tempPassword;
		}
	}
	if (checkID == ID && checkPassword == password) {
		className = tempClassName;
		fileIn.close();
		return 1;
	}
	else {
		fileIn.close();
		return 0;
	}
}

void editFilePassword(string path, unsigned long long ID, string className, string newPassword) {
	ofstream fileOut;
	fileOut.open(path + ".csv", ios_base::app);
	fileOut << ID << "," << newPassword << "," << className << endl;
	fileOut.close();
}

void changePassword(unsigned long long ID, string className) {
	string newPassword;
	cout << "New password: ";
	cin >> newPassword;
	editFilePassword("passStudent", ID, className, newPassword);
	cout << "Change successfully\n";
	system("PAUSE");
	menuStudent(ID, className);
}

void createSchoolYear(SchoolYear& sy) {
	sy.x = sy.y = 0;
	int i = 2000;
	unsigned long long current = takeTime();
	while (sy.x == 0) {
		Date date{ 1, 9, i };
		if (calculateDate(date) > current) {
			sy.x = i;
			sy.y = i + 1;
		}
		i++;
	}
}
void deleteList(NodeStudent*& pHead) {
	NodeStudent* pTmp = pHead;
	while (pHead != nullptr) {
		pHead = pHead->pNext;
		delete pTmp;
		pTmp = pHead;
	}
}

void deleteLastMember(NodeStudent*& pHead) {
	if (pHead == nullptr) return;
	if (pHead->pNext == nullptr) {
		delete pHead;
		pHead = nullptr;
	}
	NodeStudent* pCur = pHead;
	while (pCur->pNext->pNext != nullptr) pCur = pCur->pNext;
	NodeStudent* temp = pCur->pNext;
	pCur->pNext = pCur->pNext->pNext;
	delete temp;
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

void readFileStudent(string& path, NodeStudent*& pHead) {
	cout << "Please enter the name of the file you want to input: ";
	cin >> path;
	ifstream fileIn;
	fileIn.open(path + ".csv", ios_base::in);

	if (fileIn.fail())
	{
		cout << "File is not existed " << endl;
		readFileStudent(path, pHead);
	}

	NodeStudent* pCur = nullptr;
	string temp;
	getline(fileIn, temp, char(191));
	while (fileIn) {
		if (pHead == nullptr) {
			pHead = new NodeStudent;
			pCur = pHead;
		}
		else {
			pCur->pNext = new NodeStudent;
			pCur = pCur->pNext;
		}
		getline(fileIn, temp, ',');
		pCur->data.No = stringToInt(temp);
		getline(fileIn, temp, ',');
		pCur->data.Student_ID = stringToLong(temp);

		getline(fileIn, pCur->data.FirstName, ',');
		getline(fileIn, pCur->data.LastName, ',');
		getline(fileIn, pCur->data.Gender, ',');
		getline(fileIn, temp, ',');
		pCur->data.Date_Of_Birth = stringToDate(temp);
		fileIn >> pCur->data.Social_ID;
		pCur->pNext = nullptr;
	}
	fileIn.close();
}

void writeFileStudent(string path, NodeStudent* pHead) {
	ofstream fileOut;
	fileOut.open(path + ".csv", ios_base::out);
	fileOut << char(239) << char(187) << char(191);
	while (pHead->pNext != nullptr) {
		fileOut << pHead->data.No << "," << pHead->data.Student_ID << "," << pHead->data.FirstName << "," << pHead->data.LastName << "," << pHead->data.Gender << "," << pHead->data.Date_Of_Birth.Day << char(47) << pHead->data.Date_Of_Birth.Month << char(47) << pHead->data.Date_Of_Birth.Year << "," << pHead->data.Social_ID << endl;
		pHead = pHead->pNext;
	}
	fileOut.close();
}

void createLogInStudent(string path, NodeStudent* pHead, string classname) {
	ofstream fileOut;
	fileOut.open(path + ".csv", ios_base::app);
	while (pHead->pNext != nullptr) {
		fileOut << pHead->data.Student_ID << "," << 1 << "," << classname << endl;
		pHead = pHead->pNext;
	}
	fileOut.close();
}

void createClassList(string className, SchoolYear sy) {
	ofstream fileOut;
	fileOut.open(to_string(sy.x) + to_string(sy.y) + (string)"year1ClassName" + ".csv", ios_base::app);

	fileOut << className << endl;
	fileOut.close();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void createCourse();

void readCourseFile(_course* &pHead) {
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

void AtTheBeginningOfSchoolYear() {
	system("CLS");
	SchoolYear sy;
	NodeStudent* pHead = nullptr;
	string className;
	_Class* pHeadClass = nullptr;
	createSchoolYear(sy);
	cout << "Creating a school year (" << sy.x << "-" << sy.y << ")" << endl;
	int flag;
	cout << "Choose method to input class name\n1.From keyboard\n2.From a file\n0.Escape";
	cin >> flag;
	switch (flag) {
	case 1:
		while (true) {
			cout << "Creating a class:\nPlease enter class name: ";
			cin >> className;
			createClassList(to_string(sy.x) + to_string(sy.y) + "year1" + className, sy);
			string path, newPath;
			readFileStudent(path, pHead);
			createLogInStudent("passStudent", pHead, className);
			//newPath = to_string(sem.x) + "-" + to_string(sem.y) + className;
			//rename(path + ".csv", newPath + ".csv");
			writeFileStudent(/*to_string(sy.x) + to_string(sy.y) + "year1" + */className, pHead);
			deleteList(pHead);
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
			createClassList(to_string(sy.x) + to_string(sy.y) + "year1" + pHeadClass->data.name, sy);
			string path, newPath;
			pHeadClass->data.student = nullptr;
			readFileStudent(path, pHeadClass->data.student);
			createLogInStudent("passStudent", pHeadClass->data.student, pHeadClass->data.name);
			//newPath = to_string(sem.x) + "-" + to_string(sem.y) + className;
			//rename(path + ".csv", newPath + ".csv");
			writeFileStudent(/*to_string(sy.x) + to_string(sy.y) + "year1" + */pHeadClass->data.name, pHeadClass->data.student);
			deleteList(pHeadClass->data.student);
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

unsigned long long takeTime() {
	time_t timer;
	struct tm y2k = { 0 };
	unsigned long long seconds;

	y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
	y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

	time(&timer);  /* get current time; same as: timer = time(NULL)  */

	seconds = difftime(timer, mktime(&y2k));
	return seconds;
}

#include <direct.h>

int main()
{
	/*string a, b; int c, d;
	Date date{ 26, 3, 2021 };
	NodeStudent* pHead = nullptr;
	SchoolYear sy;
	cout << takeTime() - calculateDate(date) << endl;
	createSchoolYear(sy);
	cout << sy.x << "-" << sy.y << endl;*/

	AtTheBeginningOfSchoolYear();

	unsigned long long ID = NULL;
	string className = "";
	login(ID, className);







	//_mkdir("myfolder");
	//_mkdir("myfolder\\alo");
	//ofstream fileOut;
	//string path;
	//string pathCon1 = "myfolder\\alo\\";
	//string pathCon2 = "okechua";
	//string pathCon3 = ".csv";
	//
	////code ngon
	//path = pathCon1 + pathCon2 + pathCon3;

	//fileOut.open(path, ios_base::out);

	//fileOut << 1 << endl;
	//fileOut.close();
	return 0;
}