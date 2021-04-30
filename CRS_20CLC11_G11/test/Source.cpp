#include <iostream>
#include <fstream>
#include<locale.h>
#include<codecvt>
#include<string>
#include <fcntl.h>  
#include <io.h>
#include <Windows.h>

struct Date
{
	int day, month, year;
};

struct Score
{
	std::string courseCode;
	float mid = 0;
	float final = 0;
	float gpa = 0;
	Score* next = nullptr, * prev = nullptr;
};

struct Student
{
	std::wstring Num;
	std::wstring ID;
	std::wstring Lastname;
	std::wstring Firstname;
	std::wstring Gender;
	Date Birthday;
	std::wstring SocialID;
	std::wstring password;
	int no_of_course;
	Score* score = nullptr;
	Student* next = nullptr, * prev = nullptr;
};
struct Courses
{
	std::wstring teacher;
	Date startDate, endDate;
	char*** Session = nullptr;
	std::wstring courseName;
	std::string courseCode;
	int MaxStudent;
	int credit;
	Student* Stu = nullptr;
	Courses* next = nullptr, * prev = nullptr;
};

Date Birthday(std::wstring k)
{
	Date d{ 0,0,0 };
	int i = 0;
	for (i = 0; i < k.length() && k[i] != 47; i++)
	{
		d.day = d.day * 10 + k[i] - '0';
	}
	i++;
	for (i; i < k.length() && k[i] != 47; i++)
	{
		d.month = d.month * 10 + k[i] - '0';
	}
	i++;
	for (i; i < k.length() && k[i] != 47; i++)
	{
		d.year = d.year * 10 + k[i] - '0';
	}
	return d;
}

void GotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

wchar_t* StringtoLongChar(std::string k)
{
	int temp = k.length();
	wchar_t* p = new wchar_t[temp + 1];
	for (int i = 0; i < temp; i++)
	{
		p[i] = k[i];
	}
	p[temp] = '\0';
	return p;
}


std::string WstringToString(std::wstring source) {
	std::string temp;
	temp.resize(source.size());
	for (int i = 0; i < source.length(); i++) {
		temp[i] = source[i];
	}
	return temp;
}

std::wstring StringToWString(std::string source) {
	std::wstring temp;
	temp.resize(source.size());
	for (int i = 0; i < source.length(); i++) {
		temp[i] = source[i];
	}
	return temp;
}


void Vietlanguage()
{
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);
}

void ASCIIlanguage()
{
	_setmode(_fileno(stdin), _O_TEXT);
	_setmode(_fileno(stdout), _O_TEXT);
}

int WStringtoNum(std::wstring k)
{
	int sum = 0;
	for (int i = 0; i < k.length(); i++)
	{
		sum = sum * 10 + (k[i] - '0');
	}
	return sum;
}

int StringtoNum(std::string k)
{
	int sum = 0;
	for (int i = 0; i < k.length(); i++)
	{
		sum = sum * 10 + (k[i] - '0');
	}
	return sum;
}

Courses* InputCoursesCSV(Courses*& pHead, std::string k)
{
	Courses* pCur = pHead;
	std::wfstream CoursesCSV(k, std::wfstream::in);
	CoursesCSV.imbue(std::locale(CoursesCSV.getloc(), new std::codecvt_utf8<wchar_t>));
	if (CoursesCSV.fail())
	{
		std::cout << "File is not existed";
		return nullptr;
	}
	CoursesCSV.seekg(0, std::ios_base::end); //kiem thang ky tu cuoi cung cua file csv, vi no du 1 hang trong nen dich sang trai 1 buoc cho no dung ke thang SI cuoi cung
	int end = CoursesCSV.tellg();
	CoursesCSV.seekg(0, std::ios_base::beg);
	CoursesCSV.ignore(1i64, wchar_t(0xfeff)); //bo qua thang ky tu dau tien do dinh dang BOM UTF8
	std::wstring x;
	while (CoursesCSV.tellg() != end)//no se dung lai vi vi tri no be hon thang ke ben thang ky tu cuoi cung
	{
		if (pHead == nullptr)
		{
			pHead = new Courses;
			pCur = pHead;
		}
		else
		{
			pCur->next = new Courses;
			pCur->next->prev = pCur;
			pCur = pCur->next;
		}
		getline(CoursesCSV, x, L',');
		pCur->courseCode = WstringToString(x);
		getline(CoursesCSV, pCur->courseName, L',');
		getline(CoursesCSV, pCur->teacher, L',');
		getline(CoursesCSV, x, L',');
		pCur->MaxStudent = WStringtoNum(x);
		getline(CoursesCSV, x, L',');
		pCur->credit = WStringtoNum(x);
		getline(CoursesCSV, x, L',');
		pCur->startDate = Birthday(x);
		getline(CoursesCSV, x, L',');
		pCur->endDate = Birthday(x);
		pCur->Session = new char** [2];
		for (int i = 0; i < 2; i++)
		{
			pCur->Session[i] = new char* [2];
			pCur->Session[i][0] = new char[3];
			pCur->Session[i][0][2] = '\0';
			pCur->Session[i][1] = new char[4];
			pCur->Session[i][1][3] = '\0';
			getline(CoursesCSV, x, L',');
			WstringToString(x).copy(pCur->Session[i][1], 3, 0);
			if (i == 0) getline(CoursesCSV, x, L',');
			else getline(CoursesCSV, x);
			WstringToString(x).copy(pCur->Session[i][0], 2, 0);
		}
	}
	return pCur;
}


void PrintToChoose(Courses* pHead)
{
	int y = 0;
	Courses* pCur = pHead;
	Vietlanguage();
	std::wcout << pCur->courseName;
	std::wcout << " - " << pCur->teacher;
	ASCIIlanguage();
	std::cout << " - " << pCur->credit;
	std::cout << " - " << pCur->courseCode;
	std::cout << " - " << pCur->Session[0][0] << pCur->Session[0][1] << pCur->Session[1][0] << pCur->Session[1][1];
	std::cout << " - " << pCur->startDate.day << " " << pCur->startDate.month << " " << pCur->startDate.year;
	std::cout << " - " << pCur->endDate.day << " " << pCur->endDate.month << " " << pCur->endDate.year;

}


bool CheckDup2(Courses** check, Courses* source, int n) {
	if (n == 0) return true;
	for (int i = 0; i < n; i++) {
		if (check[i] == source)return false;
	}
	return true;
}

bool CheckSession(Courses** check, Courses* source, int n)
{
	if (n == 0) return true;
	for (int i = 0; i < n; i++) {
		if (
			(strcmp(check[i]->Session[0][0], source->Session[0][0]) == 0 && strcmp(check[i]->Session[0][1], source->Session[0][1]) == 0) ||
			(strcmp(check[i]->Session[0][0], source->Session[1][0]) == 0 && strcmp(check[i]->Session[0][1], source->Session[1][1]) == 0) ||
			(strcmp(check[i]->Session[1][0], source->Session[0][0]) == 0 && strcmp(check[i]->Session[1][1], source->Session[0][1]) == 0) ||
			(strcmp(check[i]->Session[1][0], source->Session[1][0]) == 0 && strcmp(check[i]->Session[1][1], source->Session[1][1]) == 0) // may be :)))
			)return false;
	}
	return true;
}

int StudentLimit(std::string k)
{
	std::wfstream CourseStudentList(k, std::ios_base::in);
	int line;
	std::wstring lines;

	for (line = 0; getline(CourseStudentList, lines); line++);
	return line;
}

void SuccessAttend(Courses* a[5], int t)
{
	int y = 20;
	for (int i = 0; i < 5; i++)
	{
		GotoXY(0, y);
		std::cout << "                                         ";
		y++;
	}
	y = 20;
	for (int i = 0; i < t; i++)
	{
		GotoXY(0, y);
		std::cout << a[i]->courseCode << "Accepted";
		y++;
	}
}

void DeallocateCourses(Courses*& pHead)
{
	Courses* pCur = pHead;
	while (pHead != nullptr)
	{
		pHead = pHead->next;
		delete pCur;
		pCur = pHead;
	}
}

void DeleteInList(std::string k, std::wstring a)
{
	std::wfstream CourseStudentList(k + ".txt", std::ios_base::in);
	Student* pHead = nullptr;
	Student* pCur = pHead;
	CourseStudentList.seekg(-2, std::ios_base::end);
	int end = CourseStudentList.tellg();
	CourseStudentList.seekg(0, std::ios_base::beg);
	while (CourseStudentList.tellg() != end)
	{
		if (pHead == nullptr)
		{
			pHead = new Student;
			pCur = pHead;
		}
		else
		{
			pCur->next = new Student;
			pCur->next->prev = pCur;
			pCur = pCur->next;
		}
		getline(CourseStudentList, pCur->ID);
	}
	CourseStudentList.close();
	pCur = pHead;

	while (pCur != nullptr && pCur->next->ID.compare(a) != 0)
	{
		pCur = pCur->next;
	}
	Student* pTemp = nullptr;
	if (pCur->next != nullptr)
	{
		pTemp = pCur->next;
		pCur->next->next->prev = pCur;
		pCur->next = pCur->next->next;
		delete pTemp;
	}

	while (pHead != nullptr)
	{
		pCur = pHead;
		pHead = pHead->next;
		delete pCur;
	}
}

bool CheckInList(std::string k, std::wstring a)
{
	std::wfstream CourseStudentList(k + ".txt", std::ios_base::in);
	Student* pHead = nullptr;
	Student* pCur = pHead;
	CourseStudentList.seekg(-2, std::ios_base::end);
	int end = CourseStudentList.tellg();
	CourseStudentList.seekg(0, std::ios_base::beg);
	while (CourseStudentList.tellg() != end)
	{
		if (pHead == nullptr)
		{
			pHead = new Student;
			pCur = pHead;
		}
		else
		{
			pCur->next = new Student;
			pCur->next->prev = pCur;
			pCur = pCur->next;
		}
		getline(CourseStudentList, pCur->ID);
	}
	CourseStudentList.close();
	pCur = pHead;

	while (pCur->next->ID.compare(a) != 0)
	{
		pCur = pCur->next;
	}
	if (pCur->next != nullptr)
	{
		return true;
	}
	else return false;
}

Student* TakeList(std::wstring a, Student*& Temp)
{
	std::fstream AllStudentList("All.txt", std::ios_base::in);
	Student* pHead = nullptr;
	Student* pCur = pHead;
	Score* pTemp = nullptr;
	std::string x;
	AllStudentList.seekg(-2, std::ios_base::end);
	int end = AllStudentList.tellg();
	AllStudentList.seekg(0, std::ios_base::beg);
	while (AllStudentList.tellg() < end)
	{
		if (pHead == nullptr)
		{
			pHead = new Student;
			pCur = pHead;
		}
		else
		{
			pCur->next = new Student;
			pCur->next->prev = pCur;
			pCur = pCur->next;
		}
		AllStudentList >> x;
		pCur->ID = StringToWString(x);
		AllStudentList >> x;
		pCur->no_of_course = StringtoNum(x);
		std::cout << pCur->no_of_course << " ";
		//std::cout << x << " ";
		for (int i = 0; i < pCur->no_of_course; i++)
		{
			if (pCur->score == nullptr)
			{
				pCur->score = new Score;
				pTemp = pCur->score;
			}
			else
			{
				pTemp->next = new Score;
				pTemp->next->prev = pTemp;
				pTemp = pTemp->next;
			}
			AllStudentList >> pTemp->courseCode;
		}
		AllStudentList.ignore(10000, '\n');
	}

	AllStudentList.close();


	pCur = pHead;
	while (pCur != nullptr && pCur->ID.compare(a) != 0)
	{
		pCur = pCur->next;
	}
	if (pCur != nullptr)
	{
		Temp = pCur;
		if (pCur->next != nullptr)
			pCur->next->prev = pCur->prev;
		if (pCur->prev != nullptr)
			pCur->prev->next = pCur->next;
		if (Temp == pHead) { pHead = pHead->next; pCur = pHead; }
		else pCur = pHead;
		AllStudentList.open("All.txt", std::ios_base::out);
		while (pCur != nullptr)
		{
			//std::cout << 3;
			AllStudentList << WstringToString(pCur->ID) << ' ';
			AllStudentList << pCur->no_of_course << ' ';
			pTemp = pCur->score;
			for (int i = 0; i < pCur->no_of_course; i++)
			{
				if (i == pCur->no_of_course - 1)
				{
					AllStudentList << pTemp->courseCode << '\n';
				}
				else
				{
					AllStudentList << pTemp->courseCode << ' ';
					pTemp = pTemp->next;
				}
			}
			pCur = pCur->next;
		}
	}
	while (pHead != nullptr)
	{
		//std::cout << 4;
		pCur = pHead;
		pHead = pHead->next;
		delete pCur;
	}
	return Temp;
}


void AttendCoursesMenu(Courses* pHead, Student* stu)
{
	Courses* pCur = pHead;
	int y = 0;
	while (pCur != nullptr)
	{
		GotoXY(0, y);
		PrintToChoose(pCur);
		pCur = pCur->next;
		y = y + 1;
	}

	GotoXY(10, y + 2);
	std::cout << "Instruction";
	GotoXY(10, y + 3);
	std::cout << "W move up";
	GotoXY(10, y + 4);
	std::cout << "S move down";
	GotoXY(10, y + 5);
	std::cout << "Enter to choose";
	GotoXY(10, y + 6);
	std::cout << "Backspace to unchoose";
	GotoXY(10, y + 7);
	std::cout << "E to exit and save" << std::endl;

	y = 0;
	pCur = pHead;
	GotoXY(0, y);
	std::cout << "->";
	char a;

	int t = 0;
	Courses** add = new Courses * [5];

	Student* Temp = nullptr;
	TakeList(stu->ID, Temp);
	std::wcout << Temp->ID;
	a = _getwch();
	if (Temp != nullptr)
	{
		Score* pAdd = Temp->score;
		while (pAdd != nullptr)
		{
			while (pCur->courseCode.compare(pAdd->courseCode) != 0)
			{
				pCur = pCur->next;
			}
			add[t] = pCur;
			t++;
			pCur = pHead;
			pAdd = pAdd->next;
		}
	}
	SuccessAttend(add, t);
	if (Temp != nullptr) delete Temp;

	while (a != 'e')
	{
		while (a != 13 && a != 8)
		{
			if (tolower(a) == 'w' && pCur->prev != nullptr)
			{
				GotoXY(0, y);
				PrintToChoose(pCur); std::cout << "  ";
				pCur = pCur->prev;
				y -= 1;
				GotoXY(0, y);
				std::cout << "->";
				PrintToChoose(pCur);
			}
			if (tolower(a) == 's' && pCur->next != nullptr)
			{
				GotoXY(0, y);
				PrintToChoose(pCur); std::cout << "  ";
				pCur = pCur->next;
				y += 1;
				GotoXY(0, y);
				std::cout << "->";
				PrintToChoose(pCur);
			}
			a = _getwch();
		}
		if (a == 8 && pCur != nullptr && CheckDup2(add, pCur, t) != 1)
		{
			//do trong mang xem thang muon xoa o dau
			for (int i = 0; i < t; i++)
			{
				if (add[i]->courseCode.compare(pCur->courseCode) == 0)
				{
					DeleteInList(add[i]->courseCode, stu->ID);
					add[i] = add[t - 1];
					t -= 1;
					SuccessAttend(add, t);
					break;
				}
			}
		}
		if (a == 13 && CheckDup2(add, pCur, t) && CheckSession(add, pCur, t) && StudentLimit(pCur->courseCode + ".csv") < pCur->MaxStudent && t < 5)
		{
			if (add == nullptr)
			{
				add[t] = pCur;
				t++;
				SuccessAttend(add, t);
			}
			else
			{
				add[t] = pCur;
				t++;
				SuccessAttend(add, t);
			}
		}
		a = _getwch();
	}

	for (int i = 0; i < t; i++)
	{
		if (stu->score == nullptr)
		{
			stu->score = new Score;
			stu->score->courseCode = add[i]->courseCode;
		}
		else
		{
			stu->score->next = new Score;
			stu->score->next->prev = stu->score;
			stu->score = stu->score->next;
			stu->score->courseCode = add[i]->courseCode;
		}
	}

	//pCur = pHead;
	for (int i = 0; i < t; i++)
	{
		if (CheckInList(add[i]->courseCode, stu->ID) == 0)
		{
			std::wfstream CourseStudentList(add[i]->courseCode + ".txt", std::ios_base::app);
			CourseStudentList << stu->ID << L'\n';
			CourseStudentList.close();
		}
	}

	std::wfstream AllStudentCourse("All.txt", std::ios_base::app);
	AllStudentCourse.imbue(std::locale(AllStudentCourse.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
	AllStudentCourse << stu->ID << L' ';
	AllStudentCourse << t << L' ';
	for (int i = 0; i < t; i++)
	{
		if (i == t - 1)
		{
			wchar_t* temp = StringtoLongChar(add[i]->courseCode);
			AllStudentCourse << temp << L'\n';
			delete[]temp;
		}
		else
		{
			wchar_t* temp = StringtoLongChar(add[i]->courseCode);
			AllStudentCourse << temp << L' ';
			delete[]temp;
		}
	}
	AllStudentCourse.close();
}

void main()
{
	Courses* pHead = nullptr;
	Student* stu = new Student;
	stu->ID = L"20127101";
	InputCoursesCSV(pHead, "testfinal.csv");
	AttendCoursesMenu(pHead, stu);
	//InputCousesCSV(pHead, k);
	//AttendCoursesMenu(pHead,stu);
}