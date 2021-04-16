#include "student.h"
#include "staff.h"
#include "commonFunc.h"

void menuStudent(unsigned long long& ID, string className) {
	system("CLS");
	int flag = -1;
	while (flag != 0) {
		cout << "\n1.Check your profile\n2.Manage course\n3.Change password\n4.Log out\n0.Escape";
		cin >> flag;
		switch (flag) {
		case 1:
			findAndPrintStudent(ID, className);
			break;
		case 2:
			break;
		case 3:
			changePassword(ID, className);
			break;
		case 4:
			ID = NULL;
			login(ID, className);
			break;
		default:
			break;
		}
	}
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
	wcout << "Number in class: " << stu.No << endl;
	wcout << "ID: " << stu.Student_ID << endl;
	wcout << "First Name: " << stu.FirstName << endl;
	wcout << "Last name: " << stu.LastName << endl;
	wcout << "Sex: " << stu.Gender << endl;
	wcout << "Date of birth: " << stu.Date_Of_Birth.day << "/" << stu.Date_Of_Birth.month << "/" << stu.Date_Of_Birth.year << endl;
	wcout << "Social ID: " << stu.Social_ID << endl;
	_SText();
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
	menuStudent(ID, className);
}







//code lai tu dau
//file sinh vien, info dong dau, nhung dong ke tiep thi moi dong 1 khoa cung voi diem cua khoa do, chua co thi mac dinh la 0

//note: build lai struct score

//student findInfoStudent(unsigned long long ID, string className) {
//	
//}
//
//student findStudent(unsigned long long ID, string className) {
//	wifstream fileIn;
//	string folderName = "Data\\Classes\\";
//	string fileFormat = ".csv";
//
//	string path = folderName + className + fileFormat;
//	fileIn.open(path, ios_base::in);
//	fileIn.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
//
//	student stu;
//	wstring temp, tempID, tempDate;
//	wchar_t a = ',', b = '\n';
//	while (fileIn) {
//		getline(fileIn, temp, a);
//		getline(fileIn, tempID, a);
//		stu.No = wstringToInt(temp);
//		stu.Student_ID = wstringToLong(tempID);
//		getline(fileIn, stu.FirstName, a);
//		getline(fileIn, stu.LastName, a);
//		getline(fileIn, stu.Gender, a);
//		getline(fileIn, tempDate, a);
//		stu.Date_Of_Birth = wstringToDate(tempDate);
//		fileIn >> stu.Social_ID;
//
//		if (stu.Student_ID == ID) break;
//	}
//	fileIn.close();
//	return stu; 
//}
//
//void createStudentFile(student stu, string className) {
//	
//	string folderName = "Data\\Classes\\", fileFormat = ".csv";
//	char* path = new char[(folderName + className).size() + 1];
//	stringToChar(path, folderName + className);
//	_mkdir(path);
//	wofstream fileOut;
//	fileOut.open(folderName + className + "\\" + to_string(stu.Student_ID) + fileFormat, ios_base::in);
//	fileOut.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
//
//	fileOut << stu.No << L"," << stu.Student_ID << L"," << stu.FirstName << L"," << stu.LastName << L"," << stu.Gender << L"," << stu.Date_Of_Birth.day << wchar_t(47) << stu.Date_Of_Birth.month << wchar_t(47) << stu.Date_Of_Birth.year << L"," << stu.Social_ID << endl;
//
//	fileOut.close();
//}
//
//void menuStudent(unsigned long long ID, string className) {
//	int flag = -1;
//	// find student & return student
//	
//	// create separate file for that specific student
//
//	//create time table
//
//	//menu
//	while (flag != 0) {
//		cout << "1. View info\n2. Manage course\n3. Change password\n4. Log out\n";
//		cin >> flag;
//
//	}
//
//	//option 1: view info
//
//	//option 2: manage course
//	//view enroll course
//	//regis course
//	//delete course
//
//	//option 3: change pass
//
//	//option 4: logout (just break)
//
//}