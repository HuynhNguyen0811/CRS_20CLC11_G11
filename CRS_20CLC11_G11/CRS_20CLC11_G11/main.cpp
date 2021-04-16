#include "struct.h"
#include "bigData.h"
#include "staff.h"
#include "student.h"
#include "commonFunc.h"
#include <direct.h>

int main()
{
	//createCourse();

	//AtTheBeginningOfSchoolYear();

	string FolderName = "Data\\Classes\\", fileFormat = ".csv", className = "20CLC11";
	char* path = new char[(FolderName + className).size() + 1];
	stringToChar(path, FolderName + className);
	_mkdir(path);

	//unsigned long long ID = NULL;
	//string className = "";
	//login(ID, className);

	return 0;
}