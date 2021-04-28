#include <iostream>
#include <fstream>
#include<locale.h>
#include<codecvt>
#include<string>
#include <fcntl.h>  
#include <io.h>
#include <Windows.h>
using namespace std;

struct Date {
	int day, month, year;
};

struct Score {
	string courseCode;
	float mid = 0;
	float final = 0;
	float gpa = 0;
	Score* next, * prev;
};

struct Student {
	wstring Num;
	wstring ID;
	wstring Lastname;
	wstring Firstname;
	wstring Gender;
	Date Birthday;
	wstring SocialID;
	wstring password;
	Score* score;
	Student* next, * prev;
};
struct Courses {
	wstring teacher;
	Date startDate, endDate;
	char*** Session;
	wstring courseName;
	string courseCode;
	int credit;
	Student* Stu;
	Courses* next = nullptr, * prev = nullptr;
};

Date Birthday(wstring k)
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


string WstringToString(wstring source) {
	string temp;
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

wchar_t* StringtoLongChar(string k)
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

int WStringtoNum(wstring k)
{
	int sum = 0;
	for (int i = 0; i < k.length(); i++)
	{
		sum = sum * 10 + (k[i] - '0');
	}
	return sum;
}

Courses* InputCoursesCSV(Courses*& pHead, string k)
{
	Courses* pCur = pHead;
	wfstream CoursesCSV(k, wfstream::in);
	CoursesCSV.imbue(std::locale(CoursesCSV.getloc(), new std::codecvt_utf8<wchar_t>));
	if (CoursesCSV.fail())
	{
		cout << "File is not existed";
		return nullptr;
	}
	CoursesCSV.seekg(0, ios_base::end); //kiem thang ky tu cuoi cung cua file csv, vi no du 1 hang trong nen dich sang trai 1 buoc cho no dung ke thang SI cuoi cung
	int end = CoursesCSV.tellg();
	CoursesCSV.seekg(0, ios_base::beg);
	CoursesCSV.ignore(1i64, wchar_t(0xfeff)); //bo qua thang ky tu dau tien do dinh dang BOM UTF8
	wstring x;
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

void ouputAllCourses(Courses*& pHead) {
	Courses* pCur = pHead;
	int count = 0;
	while (pCur) {
		count += 1;
		cout << count << ".)" << endl;
		Vietlanguage();
		wcout << "Course name: " << pCur->courseName << endl;
		wcout << "Teacher name: " << pCur->teacher << endl;
		ASCIIlanguage();
		cout << "Credit: " << pCur->credit << endl;
		cout << "Course ID: " << pCur->courseCode << endl;
		cout << "Session: " << pCur->Session[0][0] << pCur->Session[0][1] << pCur->Session[1][0] << pCur->Session[1][1] << endl;
		cout << "Start Date: " << pCur->startDate.day << " " << pCur->startDate.month << " " << pCur->startDate.year << endl;
		cout << "End Date: " << pCur->endDate.day << " " << pCur->endDate.month << " " << pCur->endDate.year << endl << endl;
		pCur = pCur->next;
	}
}

Courses* ouputCoursesbyID(Courses* pHead, string cID) {
	while (pHead != nullptr)
	{
		if (pHead->courseCode.compare(cID) == 0) {
			Vietlanguage();
			wcout << "Course name: " << pHead->courseName << endl;
			wcout << "Teacher name: " << pHead->teacher << endl;
			ASCIIlanguage();
			cout << "Course ID: " << pHead->courseCode << endl;
			cout << "Session: " << pHead->Session[0][0] << pHead->Session[0][1] << pHead->Session[1][0] << pHead->Session[1][1] << endl;
			cout << "Start Date: " << pHead->startDate.day << " " << pHead->startDate.month << " " << pHead->startDate.year << endl;
			cout << "End Date: " << pHead->endDate.day << " " << pHead->endDate.month << " " << pHead->endDate.year << endl;
			return pHead;
		}
		pHead = pHead->next;
	}
	return nullptr;
}

void PrintToChoose(Courses* pHead)
{
	int y = 0;
	Courses* pCur = pHead;
	Vietlanguage();
	wcout << pCur->courseName;
	wcout << " - " << pCur->teacher;
	ASCIIlanguage();
	cout << " - " << pCur->credit;
	cout << " - " << pCur->courseCode;
	cout << " - " << pCur->Session[0][0] << pCur->Session[0][1] << pCur->Session[1][0] << pCur->Session[1][1];
	cout << " - " << pCur->startDate.day << " " << pCur->startDate.month << " " << pCur->startDate.year;
	cout << " - " << pCur->endDate.day << " " << pCur->endDate.month << " " << pCur->endDate.year;

}

bool CheckDup(string k, Score* HeadAdd)
{
	while (HeadAdd != nullptr)
	{
		if (HeadAdd->courseCode.compare(k) == 0)
		{
			return false;
		}
		else HeadAdd = HeadAdd->next;
	}
	return true;
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

int StudentLimit(wstring k)
{
	wfstream CourseStudentList(k, ios_base::in);
	int line;
	wstring lines;

	for (line = 0; getline(CourseStudentList, lines); line++);
	return line;
}

void SuccessAttend(Courses* a[5], int t)
{
	for (int i = 0; i < 5; i++)
	{
		cout << "                                         ";
		cout << endl;
	}
	for (int i = 0; i < t; i++)
	{
		GotoXY(0, 20);
		cout << a[i]->courseCode << "Accepted";
		cout << endl;
	}
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
	y = 0;
	pCur = pHead;
	GotoXY(0, y);
	cout << "->";
	char a;
	a = _getwch();
	int t = 0;
	Courses** add = new Courses * [5];
	while (a != 'e')//chac la se doi dk o day de tui no con xoa Course xai bien a
	{
		while (a != 13 && a != 8)
		{
			if (tolower(a) == 'w' && pCur->prev != nullptr)
			{
				GotoXY(0, y);
				PrintToChoose(pCur); cout << "  ";
				pCur = pCur->prev;
				y -= 1;
				GotoXY(0, y);
				cout << "->";
				PrintToChoose(pCur);
			}
			if (tolower(a) == 's' && pCur->next != nullptr)
			{
				GotoXY(0, y);
				PrintToChoose(pCur); cout << "  ";
				pCur = pCur->next;
				y += 1;
				GotoXY(0, y);
				cout << "->";
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
					add[i] = add[t - 1];
					t -= 1;
					cout << "delete";
					GotoXY(0, 20);
					SuccessAttend(add, t);
					break;
				}
			}
		}
		if (a == 13 && CheckDup2(add, pCur, t) && CheckSession(add, pCur, t) /*&& StudentLimit(pCur->courseName + L".csv")<50*/)
		{
			cout << "done";
			if (add == nullptr)
			{
				add[t] = pCur;
				t++;
				GotoXY(0, 20);
				SuccessAttend(add, t);
			}
			else
			{
				add[t] = pCur;
				t++;
				GotoXY(0, 20);
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
			stu->score->next = nullptr;
			stu->score->prev = nullptr;
		}
		else
		{
			stu->score->next = new Score;
			stu->score->next->prev = stu->score;
			stu->score = stu->score->next;
			stu->score->courseCode = add[i]->courseCode;
		}
	}

	//luu file
	pCur = pHead;
	while (pCur != nullptr)
	{
		wfstream CourseStudentList(pCur->courseName + L".csv", ios_base::app);
		CourseStudentList << stu->ID;
		CourseStudentList.close();
		pCur = pCur->next;
	}

	pCur = pHead;
	wfstream AllStudentScore;
	AllStudentScore.open("Allstudent.csv");
	Student* pStart = nullptr;
	Student* pRun = pStart;
	AllStudentScore.seekg(0, ios_base::end);
	int end = AllStudentScore.tellg();
	AllStudentScore.seekg(0, ios_base::beg);

	while (AllStudentScore.tellg() != end);
	{
		if (pStart == nullptr)
		{
			pStart = new Student;
			pRun = pStart;
		}
		else
		{
			pRun->next = new Student;
			pRun->next->prev = pRun;
			pRun = pRun->next;
		}
		getline(AllStudentScore, pRun->ID);
	}
	AllStudentScore.close();

	pRun = pStart;
	while (stu->ID.compare(pRun->ID) != 0) pRun = pRun->next;
	//quy dinh stt cua tung mon de luu vao ds All thi them 1 bien thu tu nua dc k cho de luu
}

void main()
{
	Courses* pHead = nullptr;
	Student* stu = nullptr;
	string k;
	cin >> k;
	InputCoursesCSV(pHead, k);
	AttendCoursesMenu(pHead, stu);
}