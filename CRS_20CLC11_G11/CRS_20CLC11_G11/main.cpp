#include "struct.h"
#include "bigData.h"
#include "staff.h"
#include "student.h"
#include "commonFunc.h"

int main() {
	_course* pHead = nullptr, * pEdit;
	string FolderPath = "Data\\Course\\", coursePath = "Course.csv", fileFormat = ".csv";

	readCourseFile(FolderPath + coursePath, pHead);
	readAllIndividualCourseFile(FolderPath, pHead);

	cout << "Course's information list: " << endl;
	displayCourseConsole(pHead);

	unsigned long long tempID;
	cout << "Enter the ID of the course you want to remove: ";
	cin >> tempID;

	writeCourseFileWithout1Course(FolderPath + coursePath, pHead, tempID);
	string path;
	path = FolderPath + to_string(tempID) + fileFormat;
	remove(path.c_str());

	deleteListCourse(pHead);
	//createCourse();

	//AtTheBeginningOfSchoolYear();

	/*student stu;
	enrollCourse(stu);*/

	/*unsigned long long ID = 20127575;
	string className = "20CLC11";
	menuStudent(ID, className);*/
	
	/*unsigned long long ID = NULL;
	string className = "";
	login(ID, className);*/

	return 0;
}