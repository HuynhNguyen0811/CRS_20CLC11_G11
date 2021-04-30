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

void deleteTimeTable(student& stu) {
	for (int i = 0; i < 4; i++) {
		delete[] stu.timeTable[i];
	}
	delete[] stu.timeTable;
}

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

int countEnrolledCourse(student stu) {
	int result = 0;
	_score* pCur = stu.score;
	while (pCur != nullptr && pCur->pNext != nullptr) {
		result++;
		pCur = pCur->pNext;
	}
	return result;
}

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

void createStudentFileWithout1Course(student stu, string className, unsigned long long course_ID) {

	string folderName = "Data\\Classes\\", fileFormat = ".csv";
	char* path = new char[(folderName + className).size() + 1];
	stringToChar(path, folderName + className);
	_mkdir(path);
	wofstream fileOut;
	fileOut.open(folderName + className + "\\" + to_string(stu.Student_ID) + fileFormat, ios_base::out);
	fileOut.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	fileOut << stu.Student_ID << L"," << stu.FirstName << L"," << stu.LastName << L"," << stu.Gender << L"," << stu.Date_Of_Birth.day << wchar_t(47) << stu.Date_Of_Birth.month << wchar_t(47) << stu.Date_Of_Birth.year << L"," << stu.Social_ID << endl;

	while (stu.score != nullptr && stu.score->pNext != nullptr) {
		if (course_ID != stu.score->data.course_ID) {
			fileOut << stu.score->data.course_ID << "," << stu.score->data.total << "," << stu.score->data.final << "," << stu.score->data.mid << "," << stu.score->data.other << "," << stu.score->data.gpa;
			fileOut << endl;
		}
		stu.score = stu.score->pNext;
	}

	fileOut.close();
}

bool checkEnrollCourse(unsigned long long tempID, _course* pHeadCourse, student stu) {
	while (pHeadCourse != nullptr) {
		if (pHeadCourse->data.courseId == tempID) return checkConflictCourse(stu, pHeadCourse->data);
		pHeadCourse = pHeadCourse->pNext;
	}
	return 0;
}

bool checkConflictCourse(student stu, course course) {
	int x, y;
	for (int i = 0; i < 2; i++) {
		if (course.session[i].dayOfWeek == L"MON") x = 0;
		else if (course.session[i].dayOfWeek == L"TUE") x = 1;
		else if (course.session[i].dayOfWeek == L"WED") x = 2;
		else if (course.session[i].dayOfWeek == L"THU") x = 3;
		else if (course.session[i].dayOfWeek == L"FRI") x = 4;
		else if (course.session[i].dayOfWeek == L"SAT") x = 5;
		else x = 6;
		if (course.session[i].hour == L"S1") y = 0;
		else if (course.session[i].hour == L"S2") y = 1;
		else if (course.session[i].hour == L"S3") y = 2;
		else if (course.session[i].hour == L"S4") y = 3;
		else y = 0;
		if(stu.timeTable[y][x] == 1) return 0;
	}
	return 1;
}

void createTimetable(student& stu, _course* pHeadCourse) {
	stu.timeTable = new int* [4];
	for (int i = 0; i < 4; i++) stu.timeTable[i] = new int[7];

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 7; j++) {
			stu.timeTable[i][j] = 0;
		}
	}

	_score* pCur = stu.score;
	int x, y;
	_course* pCurCourse = pHeadCourse;
	while (pCur != nullptr) {
		while (pCurCourse != nullptr) {
			if (pCur->data.course_ID == pCurCourse->data.courseId) {
				for (int i = 0; i < 2; i++) {
					if (pCurCourse->data.session[i].dayOfWeek == L"MON") x = 0;
					else if (pCurCourse->data.session[i].dayOfWeek == L"TUE") x = 1;
					else if (pCurCourse->data.session[i].dayOfWeek == L"WED") x = 2;
					else if (pCurCourse->data.session[i].dayOfWeek == L"THU") x = 3;
					else if (pCurCourse->data.session[i].dayOfWeek == L"FRI") x = 4;
					else if (pCurCourse->data.session[i].dayOfWeek == L"SAT") x = 5;
					else x = 6;
					if (pCurCourse->data.session[i].hour == L"S1") y = 0;
					else if (pCurCourse->data.session[i].hour == L"S2") y = 1;
					else if (pCurCourse->data.session[i].hour == L"S3") y = 2;
					else if (pCurCourse->data.session[i].hour == L"S4") y = 3;
					else y = 0;
					stu.timeTable[y][x]++;
				}
			}
			pCurCourse = pCurCourse->pNext;
		}
		pCurCourse = pHeadCourse;
		pCur = pCur->pNext;
	}
}

void displayTimetable(student stu) {
	cout << "MON TUE WED THU FRI SAT\n";
	for (int i = 0; i < 4; i++) {
		cout << " ";
		for (int j = 0; j < 6; j++) {
			cout << stu.timeTable[i][j] << "   ";
		}
		cout << endl;
	}
}

void addEnrolledCourse(student stu, string className, unsigned long long course_ID) {
	string folderName = "Data\\Classes\\", fileFormat = ".csv";
	wofstream fileOut;
	fileOut.open(folderName + className + "\\" + to_string(stu.Student_ID) + fileFormat, ios_base::app);
	fileOut.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	fileOut << course_ID << "," << 0 << "," << 0 << "," << 0 << "," << 0 << "," << 0 << endl;

	fileOut.close();
}

void addStudentToCourse(unsigned long long student_ID, unsigned long long course_ID) {
	string FolderPath = "Data\\Course\\", fileFormat = ".csv";
	wofstream fileOut;
	fileOut.open(FolderPath + to_string(course_ID) + fileFormat, ios_base::app);
	fileOut.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));

	fileOut << student_ID << "," << 0 << "," << 0 << "," << 0 << "," << 0 << "," << 0 << ",,,,," << endl;

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

	//
	if (countEnrolledCourse(stu) == 5) {
		cout << "Full slot of enrolled course.\n";
		return;
	}

	int temp = -1;
	unsigned long long tempID;
	string FolderPath = "Data\\Course\\", coursePath = "Course.csv", fileFormat = ".csv";
	while (temp != 0) {
		cout << "Input the course's ID you want to enroll: ";
		cin >> tempID;
		if (checkEnrollCourse(tempID, pHeadCourse, stu)) {
			addEnrolledCourse(stu, className, tempID);
			addStudentToCourse(stu.Student_ID, tempID);
			deleteTimeTable(stu);
			
			readAllIndividualCourseFile(FolderPath, pHeadCourse);
			stu = findInfoStudent(stu.Student_ID, className);
			createTimetable(stu, pHeadCourse);
		}
		else cout << "Invalid choice\n";
		cout << "Enter '0' to escape: ";
		cin >> temp;
	}
}

void viewEnrollCourse(student stu, _course* pHeadCourse) {
	cout << "Total course: " << countEnrolledCourse(stu) << endl;
	cout << "Enrolled course: " << endl;

	//_course* pDisplay = nullptr;
	_score* pCur = stu.score;

	while (pHeadCourse != nullptr && pHeadCourse->pNext != nullptr) {
		while (pCur != nullptr) {
			if (pCur->data.course_ID == pHeadCourse->data.courseId) displayIndividualCourseConsole(pHeadCourse->data);
			pCur = pCur->pNext;
		}
		pCur = stu.score;
		pHeadCourse = pHeadCourse->pNext;
	}

}

void removeEnrollCourse(student& stu, string className, _course* pHeadCourse) {
	viewEnrollCourse(stu, pHeadCourse);
	int temp, tempID;
	_course* pCur = nullptr;
	cout << "Enter 0 to skip remove course section: ";
	cin >> temp;
	while (temp != 0) {
		cout << "Enter course's ID you want to remove: ";
		cin >> tempID;
		pCur = pHeadCourse;
		while (pCur != nullptr && pCur->data.courseId != tempID) { pCur = pCur->pNext; }
		if (pCur != nullptr) {
			writeIndividualCourseFileWithout1Student("Data\\Course\\" + to_string(pCur->data.courseId) + ".csv", pCur->data, stu.Student_ID);
			createStudentFileWithout1Course(stu, className, tempID);
			deleteTimeTable(stu);

			readAllIndividualCourseFile("Data\\Course\\", pHeadCourse);
			stu = findInfoStudent(stu.Student_ID, className);
			createTimetable(stu, pHeadCourse);
		}

		cout << "Enter 0 to escape: ";
		cin >> temp;
	}
}

void menuManageCourseStudent(student stu, string className) {
	int flag = -1;
	//load toan bo course hien co
	_course* pHeadCourse = nullptr;
	string FolderPath = "Data\\Course\\", coursePath = "Course.csv", fileFormat = ".csv";
	readCourseFile(FolderPath + coursePath, pHeadCourse);
	readAllIndividualCourseFile(FolderPath, pHeadCourse);

	//create time table -> chuyen sang phan enroll va remove course
	createTimetable(stu, pHeadCourse);

	while (flag != 0) {
		system("CLS");
		cout << "1. Enroll course\n2. View enrolled course\n3. Remove enrolled course\n4. View scoreboard\n0. Back to main menu\n";
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
			removeEnrollCourse(stu, className, pHeadCourse);
			system("PAUSE");
			break;
		case 4:
			printScoreboard(stu);
			system("PAUSE");
			break;
		case 0:
			// thieu delete
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

	//menu
	while (flag != 0) {
		system("CLS");
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