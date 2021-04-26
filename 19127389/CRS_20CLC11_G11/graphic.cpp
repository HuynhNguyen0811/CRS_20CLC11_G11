#include "commonFunc.h"
#include "graphic.h"

void drawChoosingOutlineStu(int x, int y) {
	textColor(3);
	GotoXY(x, y);
	for (int i = 0; i < 20; i++) {
		cout << char(205);
	}
	GotoXY(x, 5 + y);
	for (int i = 0; i < 20; i++) {
		cout << char(205);
	}
	for (int i = 0; i < 5; i++) {
		GotoXY(x, y + i);
		cout << char(186);
	}
	for (int i = 0; i < 5; i++) {
		GotoXY(20 + x, y + i);
		cout << char(186);
	}
	GotoXY(x, y);	cout << char(201);
	GotoXY(x, 5 + y);	cout << char(200);
	GotoXY(20 + x, y);	cout << char(187);
	GotoXY(20 + x, 5 + y);	cout << char(188);
	textColor(15);
}
void drawOutlineStu(int x, int y) {
	GotoXY(x, y);
	for (int i = 0; i < 20; i++) {
		cout << char(196);
	}
	GotoXY(x, 5 + y);
	for (int i = 0; i < 20; i++) {
		cout << char(196);
	}
	for (int i = 0; i < 5; i++) {
		GotoXY(x, y + i);
		cout << char(179);
	}
	for (int i = 0; i < 5; i++) {
		GotoXY(20 + x, y + i);
		cout << char(179);
	}
	GotoXY(x, y);	cout << char(218);
	GotoXY(x, 5 + y);	cout << char(192);
	GotoXY(20 + x, y);	cout << char(191);
	GotoXY(20 + x, 5 + y);	cout << char(217);
}
void drawChoosingOutlineStaff(int x, int y) {
	textColor(3);
	GotoXY(25 + x, y);
	for (int i = 0; i < 20; i++) {
		cout << char(205);
	}
	GotoXY(25 + x, 5 + y);
	for (int i = 0; i < 20; i++) {
		cout << char(205);
	}
	for (int i = 0; i < 5; i++) {
		GotoXY(25 + x, y + i);
		cout << char(186);
	}
	for (int i = 0; i < 5; i++) {
		GotoXY(45 + x, y + i);
		cout << char(186);
	}
	GotoXY(25 + x, y);	cout << char(201);
	GotoXY(25 + x, 5 + y);	cout << char(200);
	GotoXY(45 + x, y);	cout << char(187);
	GotoXY(45 + x, 5 + y);	cout << char(188);
	textColor(15);
}
void drawOutlineStaff(int x, int y) {
	GotoXY(25 + x, y);
	for (int i = 0; i < 20; i++) {
		cout << char(196);
	}
	GotoXY(25 + x, 5 + y);
	for (int i = 0; i < 20; i++) {
		cout << char(196);
	}
	for (int i = 0; i < 5; i++) {
		GotoXY(25 + x, y + i);
		cout << char(179);
	}
	for (int i = 0; i < 5; i++) {
		GotoXY(45 + x, y + i);
		cout << char(179);
	}
	GotoXY(25 + x, y);	cout << char(218);
	GotoXY(25 + x, 5 + y);	cout << char(192);
	GotoXY(45 + x, y);	cout << char(191);
	GotoXY(45 + x, 5 + y);	cout << char(217);
}
void writeMenuLogin(int x, int y) {
	GotoXY(6 + x, 2 + y); cout << "Login as";
	GotoXY(31 + x, 2 + y); cout << "Login as";
	GotoXY(7 + x, 3 + y); cout << "Student";
	GotoXY(33 + x, 3 + y); cout << "Staff";
}

void designMenuLogin(int x, int y) {
	system("cls");
	ShowCur(0);
	writeMenuLogin(x, y);
	int pointer = 0, temp;
	while (true) {
		for (int i = 0; i < 2; ++i)
		{
			if (i == pointer)
			{
				drawChoosingOutlineStaff(x, y);
				drawOutlineStu(x, y);
			}
			else
			{
				drawChoosingOutlineStu(x, y);
				drawOutlineStaff(x, y);
			}
		}
		while (true) {
			temp = _getch();
			if (temp == 75 || temp == 'a' || temp == 'A') {
				pointer--;
				if (pointer == -1) pointer = 1;
				break;
			}
			else if (temp == 77 || temp == 'd' || temp == 'D') {
				pointer++;
				if (pointer == 2) pointer = 0;
				break;
			}
			else if (temp == 13 || temp == 32) {
				switch (pointer) {
					ShowCur(1);
				case 0:
					designMenuStudent(0, 0);
					break;
				case 1:
					designMenuStaff(0, 0);
					break;
				}
				break;
			}
		}
		if (temp == 13 || temp == 32) {
			break;
		}
	}
}

void designMenuManageCourseStaff(int x, int y) {
	system("cls");
	ShowCur(0);
	int pointer = 0, temp;
	GotoXY(x, y); cout << "Staff manage course menu";
	string menu[6] = { "Create new course", "Delete course", "Change information course", "View course list", "Input scoreboard" , "Back to main menu" };
	while (true) {
		for (int i = 0; i < 6; ++i)
		{
			if (i == pointer)
			{
				GotoXY(x, 1 + y + i);
				textColor(3);
				cout << ">> " << menu[i] << " <<";
				textColor(15);
			}
			else
			{
				GotoXY(x, 1 + y + i);
				cout << "   " << menu[i] << "              ";
			}
		}
		while (true) {
			temp = _getch();
			if (temp == 72 || temp == 'w' || temp == 'W')
			{
				pointer--;
				if (pointer == -1)
				{
					pointer = 5;
				}
				break;
			}
			else if (temp == 80 || temp == 's' || temp == 'S')
			{
				pointer++;
				if (pointer == 6)
				{
					pointer = 0;
				}
				break;
			}

			else if (temp == 13 || temp == 32)
			{
				ShowCur(1);
				switch (pointer)
				{
				case 0:
				{

				} break;

				case 1:
				{

				} break;
				case 2:
				{

				} break;
				case 3: {

				} break;
				case 4: {

				} break;
				case 5: {
					designMenuStaff(x, y);
				} break;
				}
				break;
			}
		}
		if (temp == 13 || temp == 32) {
			break;
		}
	}
}

void designMenuManageStudentStaff(int x, int y) {
	system("cls");
	ShowCur(0);
	int pointer = 0, temp;
	GotoXY(2 + x, y); cout << "Staff mangage student menu";
	string menu[3] = { "Input new class", "View class list", "Back to main menu" };
	while (true) {
		for (int i = 0; i < 3; ++i)
		{
			if (i == pointer)
			{
				GotoXY(x, 1 + y + i);
				textColor(3);
				cout << ">> " << menu[i] << " <<";
				textColor(15);
			}
			else
			{
				GotoXY(x, 1 + y + i);
				cout << "   " << menu[i] << "               ";
			}
		}
		while (true) {
			temp = _getch();
			if (temp == 72 || temp == 'w' || temp == 'W')
			{
				pointer--;
				if (pointer == -1)
				{
					pointer = 2;
				}
				break;
			}
			else if (temp == 80 || temp == 's' || temp == 'S')
			{
				pointer++;
				if (pointer == 3)
				{
					pointer = 0;
				}
				break;
			}

			else if (temp == 13 || temp == 32)
			{
				ShowCur(1);
				switch (pointer)
				{
				case 0:
				{

				} break;

				case 1:
				{

				} break;
				case 2:
				{
					designMenuStaff(x, y);
				} break;
				}
				break;
			}
		}
		if (temp == 13 || temp == 32) {
			break;
		}
	}
}

void designMenuManageSystemStaff(int x, int y) {

}

void designMenuStaff(int x, int y) {
	system("cls");
	ShowCur(0);
	int pointer = 0, temp;
	GotoXY(2 + x, y); cout << "Staff main menu";
	string menu[4] = { "Manage course", "Manage student", "Manage system", "Back to login menu" };
	while (true) {
		for (int i = 0; i < 4; ++i)
		{
			if (i == pointer)
			{
				GotoXY(x, 1 + y + i);
				textColor(3);
				cout << ">> " << menu[i] << " <<";
				textColor(15);
			}
			else
			{
				GotoXY(x, 1 + y + i);
				cout << "   " << menu[i] << "                 ";
			}
		}
		while (true) {
			temp = _getch();
			if (temp == 72 || temp == 'w' || temp == 'W')
			{
				pointer--;
				if (pointer == -1)
				{
					pointer = 3;
				}
				break;
			}
			else if (temp == 80 || temp == 's' || temp == 'S')
			{
				pointer++;
				if (pointer == 4)
				{
					pointer = 0;
				}
				break;
			}

			else if (temp == 13 || temp == 32)
			{
				ShowCur(1);
				switch (pointer)
				{
				case 0:
				{
					designMenuManageCourseStaff(x, y);
				} break;

				case 1:
				{
					designMenuManageStudentStaff(x, y);
				} break;
				case 2:
				{

				} break;
				case 3: {
					designMenuLogin(0, 0);
				} break;
				}
				break;
			}
		}
		if (temp == 13 || temp == 32) {
			break;
		}
	}
}

void designMenuManageCourseStudent(int x, int y) {
	system("cls");
	ShowCur(0);
	int pointer = 0, temp;
	GotoXY(2 + x, y); cout << "Student manage course menu";
	string menu[4] = { "Enroll course", "View enrolled course", "View scoreboard", "Back to main menu" };
	while (true) {
		for (int i = 0; i < 4; ++i)
		{
			if (i == pointer)
			{
				GotoXY(x, 1 + y + i);
				textColor(3);
				cout << ">> " << menu[i] << " <<";
				textColor(15);
			}
			else
			{
				GotoXY(x, 1 + y + i);
				cout << "   " << menu[i] << "                 ";
			}
		}
		while (true) {
			temp = _getch();
			if (temp == 72 || temp == 'w' || temp == 'W')
			{
				pointer--;
				if (pointer == -1)
				{
					pointer = 3;
				}
				break;
			}
			else if (temp == 80 || temp == 's' || temp == 'S')
			{
				pointer++;
				if (pointer == 4)
				{
					pointer = 0;
				}
				break;
			}

			else if (temp == 13 || temp == 32)
			{
				ShowCur(1);
				switch (pointer)
				{
				case 0:
				{

				} break;

				case 1:
				{

				} break;
				case 2:
				{

				} break;
				case 3: {
					designMenuStudent(0, 0);
				} break;
				}
				break;
			}
		}
		if (temp == 13 || temp == 32) {
			break;
		}
	}
}

void designMenuStudent(int x, int y) {
	system("cls");
	ShowCur(0);
	int pointer = 0, temp;
	GotoXY(2 + x, y); cout << "Student main menu";
	string menu[4] = { "View profile", "Manage course", "Change password", "Back to login menu" };
	while (true) {
		for (int i = 0; i < 4; ++i)
		{
			if (i == pointer)
			{
				GotoXY(x, 1 + y + i);
				textColor(3);
				cout << ">> " << menu[i] << " <<";
				textColor(15);
			}
			else
			{
				GotoXY(x, 1 + y + i);
				cout << "   " << menu[i] << "                 ";
			}
		}
		while (true) {
			temp = _getch();
			if (temp == 72 || temp == 'w' || temp == 'W')
			{
				pointer--;
				if (pointer == -1)
				{
					pointer = 3;
				}
				break;
			}
			else if (temp == 80 || temp == 's' || temp == 'S')
			{
				pointer++;
				if (pointer == 4)
				{
					pointer = 0;
				}
				break;
			}

			else if (temp == 13 || temp == 32)
			{
				ShowCur(1);
				switch (pointer)
				{
				case 0:
				{

				} break;

				case 1:
				{
					designMenuManageCourseStudent(x, y);
				} break;
				case 2:
				{

				} break;
				case 3: {
					designMenuLogin(0, 0);
				} break;
				}
				break;
			}
		}
		if (temp == 13 || temp == 32) {
			break;
		}
	}
}