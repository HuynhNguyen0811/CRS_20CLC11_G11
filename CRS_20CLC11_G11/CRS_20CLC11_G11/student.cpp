#include "student.h"
#include "staff.h"

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
			findInfoStudent(stu);
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

void findInfoStudent(student stu) {
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