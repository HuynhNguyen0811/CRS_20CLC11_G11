#include "struct.h"
#include "bigData.h"
#include "staff.h"
#include "student.h"
#include "commonFunc.h"
#include <direct.h>

int main()
{
	_course* pHead = nullptr;
	string FolderPath = "Data\\Course\\", coursePath = "Course.csv", fileFormat = ".csv";

	_mkdir("Data");
	_mkdir("Data\\Course");

	inputFromKeyboardCourse(pHead);
	
	writeCourseFile(FolderPath + coursePath, pHead);
	
	while (pHead->pNext != nullptr) {
		writeIndividualCourseFile(FolderPath + to_string(pHead->data.courseId) + fileFormat, pHead->data);
		pHead = pHead->pNext;
	}

	displayCourseConsole(pHead);

	deleteListCourse(pHead);

	/*AtTheBeginningOfSchoolYear();

	unsigned long long ID = NULL;
	string className = "";
	login(ID, className);*/

	return 0;
}