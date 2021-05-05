#include "struct.h"
#include "bigData.h"
#include "staff.h"
#include "student.h"
#include "commonFunc.h"

int main() {
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
	//cout << countLine("Course.csv");

	//createCourse();

	//AtTheBeginningOfSchoolYear();

	//displayClassAndStudent();

	//viewAttendStudent();
	//writeAttendStudent();

	viewScoreboardClass();

	/*viewScoreboardCourse();
	editScoreFromCourse();
	viewScoreboardCourse();*/
	
	//inputScoreboard();

	/*unsigned long long ID = NULL;
	string className = "";
	login(ID, className);*/

	if (_CrtDumpMemoryLeaks())
	{
		std::cout << "Leak";
	}
	else std::cout << "No";
	return 0;
}