#include "student.h"
#include "staff.h"
#include "commonFunc.h"

//void menuStudent(unsigned long long& ID, string className) {
//	system("CLS");
//	int flag = -1;
//	while (flag != 0) {
//		cout << "\n1.Check your profile\n2.Manage course\n3.Change password\n4.Log out\n0.Escape";
//		cin >> flag;
//		switch (flag) {
//		case 1:
//			findAndPrintStudent(ID, className);
//			break;
//		case 2:
//			break;
//		case 3:
//			changePassword(ID, className);
//			break;
//		case 4:
//			ID = NULL;
//			login(ID, className);
//			break;
//		default:
//			break;
//		}
//	}
//}

void login(unsigned long long& ID, string& className) {
	system("CLS");
	int flag, out;
	string password = "";
	bool check = 0;
	string path;
	string folderName = "Data\\";
	string pathSub = "Classes\\", fileFormat = ".csv";

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
			path = folderName + "passStudent" + fileFormat;
			check = checkLogin(path, ID, password, className);
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
			path = folderName + "passStudent" + fileFormat;
			check = checkLogin(path, ID, password, className);
		}
		system("CLS");
		menuStaff();
		break;
	default:
		break;
	}
}

void findAndPrintStudent(unsigned long long ID, string className) {
	wifstream fileIn;
	string folderName = "Data\\Classes\\";
	string fileFormat = ".csv";
	string path = folderName + className + fileFormat;
	fileIn.open(path, ios_base::in);
	fileIn.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	student stu;
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
			printInfoStudent(stu);
			break;
		}
		else {
			getline(fileIn, temp, b);
		}
	}
	fileIn.close();
}

void printInfoStudent(student stu) {
	_LText();

	//wcout << "Number in class: " << stu.No << endl;
	wcout << "ID: " << stu.Student_ID << endl;
	wcout << "First Name: " << stu.FirstName << endl;
	wcout << "Last name: " << stu.LastName << endl;
	wcout << "Sex: " << stu.Gender << endl;
	wcout << "Date of birth: " << stu.Date_Of_Birth.day << "/" << stu.Date_Of_Birth.month << "/" << stu.Date_Of_Birth.year << endl;
	wcout << "Social ID: " << stu.Social_ID << endl;

	_SText();
}

void printScoreboard(student stu) {
	while (stu.score != nullptr && stu.score->pNext != nullptr) {
		cout << stu.score->data.course_ID << " ";
		cout << stu.score->data.total << " ";
		cout << stu.score->data.final << " ";
		cout << stu.score->data.mid << " ";
		cout << stu.score->data.other << " ";
		cout << stu.score->data.gpa << endl;
		stu.score = stu.score->pNext;
	}
}

bool checkLogin(string path, unsigned long long ID, string password, string& className) {
	ifstream fileIn;
	fileIn.open(path, ios_base::in); 

	string temp, tempPassword, tempClassName, checkPassword = "";
	unsigned long long tempID = NULL, checkID = NULL;
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
	fileOut.open(path, ios_base::app);
	fileOut << ID << "," << newPassword << "," << className << endl;
	fileOut.close();
}

void changePassword(unsigned long long ID, string className) {
	string newPassword;
	cout << "New password: ";
	cin >> newPassword;
	editFilePassword("Data\\Classes\\passStudent.csv", ID, className, newPassword);
	cout << "Change successfully\n";
	system("PAUSE");
	return;
}

//code lai tu dau
//file sinh vien, info dong dau, nhung dong ke tiep thi moi dong 1 khoa cung voi diem cua khoa do, chua co thi mac dinh la 0

//note: build lai struct score		 DONE



student findInfoStudent(unsigned long long ID, string className) {
	string folderName = "Data\\Classes\\", fileFormat = ".csv";
	wifstream fileIn;
	
	fileIn.open(folderName + className + "\\" + to_string(ID) + fileFormat, ios_base::in);
	fileIn.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	fileIn.ignore(1000, wchar_t(0xfeff));

	fileIn.seekg(0, ios_base::end);
	int end = fileIn.tellg();
	fileIn.seekg(0, ios_base::beg);

	student stu;

	if (fileIn.fail()) { //lan dau dang nhap, chua co san file rieng
		stu = findStudent(ID, className);
		return stu;
	} 

	//co san file rieng

	wchar_t a = ',', b = '\n';
	wstring temp;
	getline(fileIn, temp, a);
	stu.Student_ID = wstringToLong(temp);
	getline(fileIn, stu.FirstName, a);
	getline(fileIn, stu.LastName, a);
	getline(fileIn, stu.Gender, a);
	getline(fileIn, temp, a);
	stu.Date_Of_Birth = wstringToDate(temp);
	fileIn >> stu.Social_ID;

	_score* pCurScore = nullptr;
	while (fileIn) {
		if (stu.score == nullptr) {
			stu.score = new _score;
			pCurScore = stu.score;
		} else {
			pCurScore->pNext = new _score;
			pCurScore = pCurScore->pNext;
		}

		getline(fileIn, temp, a);
		pCurScore->data.course_ID = wstringToLong(temp);
		fileIn >> pCurScore->data.total >> a;
		fileIn >> pCurScore->data.final >> a;
		fileIn >> pCurScore->data.mid >> a;
		fileIn >> pCurScore->data.other >> a;
		fileIn >> pCurScore->data.gpa;

		pCurScore->pNext = nullptr;
	}

	printScoreboard(stu);

	fileIn.close();
	return stu;
}

student findStudent(unsigned long long ID, string className) {
	wifstream fileIn;
	string folderName = "Data\\Classes\\";
	string fileFormat = ".csv";

	string path = folderName + className + fileFormat;
	fileIn.open(path, ios_base::in);
	fileIn.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	student stu;
	wstring temp, tempID, tempDate;
	wchar_t a = ',', b = '\n';
	while (fileIn) {
		getline(fileIn, temp, a);
		getline(fileIn, tempID, a);
		stu.No = wstringToInt(temp);
		stu.Student_ID = wstringToLong(tempID);
		getline(fileIn, stu.FirstName, a);
		getline(fileIn, stu.LastName, a);
		getline(fileIn, stu.Gender, a);
		getline(fileIn, tempDate, a);
		stu.Date_Of_Birth = wstringToDate(tempDate);
		fileIn >> stu.Social_ID;

		if (stu.Student_ID == ID) break;
	}
	fileIn.close();
	return stu; 
}

void createStudentFile(student stu, string className) {
	
	string folderName = "Data\\Classes\\", fileFormat = ".csv";
	char* path = new char[(folderName + className).size() + 1];
	stringToChar(path, folderName + className);
	_mkdir(path);
	wofstream fileOut;
	fileOut.open(folderName + className + "\\" + to_string(stu.Student_ID) + fileFormat, ios_base::out);
	fileOut.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	fileOut << stu.Student_ID << L"," << stu.FirstName << L"," << stu.LastName << L"," << stu.Gender << L"," << stu.Date_Of_Birth.day << wchar_t(47) << stu.Date_Of_Birth.month << wchar_t(47) << stu.Date_Of_Birth.year << L"," << stu.Social_ID << endl;

	while (stu.score != nullptr && stu.score->pNext != nullptr) {
		fileOut << stu.score->data.course_ID << "," << stu.score->data.total << "," << stu.score->data.final << "," << stu.score->data.mid << "," << stu.score->data.other << "," << stu.score->data.gpa;
		fileOut << endl;
		stu.score = stu.score->pNext;
	}

	fileOut.close();
}

bool checkEnrollCourse(unsigned long long tempID, _course* pHeadCourse) {
	while (pHeadCourse != nullptr) {
		if (pHeadCourse->data.courseId == tempID) return 1;
		pHeadCourse = pHeadCourse->pNext;
	}
	return 0;
}

void addEnrolledCourse(student stu, string className, unsigned long long course_ID) {
	string folderName = "Data\\Classes\\", fileFormat = ".csv";
	wofstream fileOut;
	fileOut.open(folderName + className + "\\" + to_string(stu.Student_ID) + fileFormat, ios_base::app);
	fileOut.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	fileOut << course_ID << 0 << "," << 0 << "," << 0 << "," << 0 << "," << 0 << endl;

	fileOut.close();
}

_score* takeTailEnrollCourse(student stu) {
	_score* pCur = stu.score;
	while (pCur != nullptr && pCur->pNext != nullptr) {
		pCur = pCur->pNext;
	}
	return pCur;
}

void enrollCourse(student& stu, string className, _course* pHeadCourse) {
	cout << "Course's information list: " << endl;
	displayCourseConsole(pHeadCourse);

	int temp = -1;
	unsigned long long tempID;
	_score* pCur = takeTailEnrollCourse(stu);
	while (temp != 0) {
		cout << "Input the course's ID you want to enroll: ";
		cin >> tempID;
		if (checkEnrollCourse(tempID, pHeadCourse)) {
			if (stu.score == nullptr) {
				stu.score = new _score;
				pCur = stu.score;
			}
			else {
				pCur->pNext = new _score;
				pCur = pCur->pNext;
			}
			pCur->data.course_ID = tempID;
			pCur->pNext = nullptr;

			addEnrolledCourse(stu, className, tempID);
		}
		else cout << "Invalid choice\n";
		cout << "Enter '0' to escape: ";
		cin >> temp;
	}
}

void viewEnrollCourse(student stu, _course* pHeadCourse) {
	cout << "Enrolled course: " << endl;

	_course* pDisplay = nullptr;
	_score* pCur = stu.score;

	while (pHeadCourse != nullptr) {
		while (pCur != nullptr) {
			if (pCur->data.course_ID == pHeadCourse->data.courseId) displayIndividualCourseConsole(pHeadCourse->data);
			pCur = pCur->pNext;
		}
		pCur = stu.score;
		pHeadCourse = pHeadCourse->pNext;
	}
}

void menuManageCourseStudent(student stu, string className) {
	int flag = -1;
	//load toan bo course hien co
	_course* pHeadCourse = nullptr, * pEdit;
	string FolderPath = "Data\\Course\\", coursePath = "Course.csv", fileFormat = ".csv";

	readCourseFile(FolderPath + coursePath, pHeadCourse);

	while (flag != 0) {
		system("CLS");
		cout << "1. Enroll course\n2. View enrolled course\n3. View scoreboard\n0. Back to main menu\n";
		cin >> flag;

		switch (flag) {
		case 1:
			enrollCourse(stu, className, pHeadCourse);
			system("PAUSE");
			break;
		case 2:
			viewEnrollCourse(stu, pHeadCourse);
			system("PAUSE");
			break;
		case 3:
			printScoreboard(stu);
			system("PAUSE");
			break;
		default:
			break;
		}
	
	}
}

void menuStudent(unsigned long long ID, string className) {
	int flag = -1;

	// find student & return student
	student stu;
	stu = findInfoStudent(ID, className);

	// create separate file for that specific student
	createStudentFile(stu, className);

	//create time table
	//de sau di

	//menu
	while (flag != 0) {
		//system("CLS");
		cout << "1. View info\n2. Manage course\n3. Change password\n0. Log out\n";
		cin >> flag;
		switch (flag) {
		case 1:
			printInfoStudent(stu);
			system("PAUSE");
			break;
		case 2:
			menuManageCourseStudent(stu, className);
			system("PAUSE");
			break;
		case 3: 
			changePassword(ID, className);
			system("PAUSE");
			break;
		default: 
			break;
		}
	}

	//option 1: view info

	//option 2: manage course
	//view enroll course
	//regis course
	//delete course

	//option 3: change pass

	//option 4: logout 
}