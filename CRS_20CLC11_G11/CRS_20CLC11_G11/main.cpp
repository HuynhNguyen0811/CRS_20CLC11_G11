#include "struct.h"
#include "bigData.h"
#include "staff.h"
#include "student.h"

#include "commonFunc.h"

void drawChoosingOutlineStu() {
	textColor(3);
	GotoXY(20, 5);
	for (int i = 0; i < 20; i++) {
		cout << char(205);
	}
	GotoXY(20, 10);
	for (int i = 0; i < 20; i++) {
		cout << char(205);
	}
	for (int i = 0; i < 5; i++) {
		GotoXY(20, 5 + i);
		cout << char(186);
	}
	for (int i = 0; i < 5; i++) {
		GotoXY(40, 5 + i);
		cout << char(186);
	}
	GotoXY(20, 5);	cout << char(201);
	GotoXY(20, 10);	cout << char(200);
	GotoXY(40, 5);	cout << char(187);
	GotoXY(40, 10);	cout << char(188);
	textColor(15);
}
void drawOutlineStu() {
	GotoXY(20, 5);
	for (int i = 0; i < 20; i++) {
		cout << char(196);
	}
	GotoXY(20, 10);
	for (int i = 0; i < 20; i++) {
		cout << char(196);
	}
	for (int i = 0; i < 5; i++) {
		GotoXY(20, 5 + i);
		cout << char(179);
	}
	for (int i = 0; i < 5; i++) {
		GotoXY(40, 5 + i);
		cout << char(179);
	}
	GotoXY(20, 5);	cout << char(218);
	GotoXY(20, 10);	cout << char(192);
	GotoXY(40, 5);	cout << char(191);
	GotoXY(40, 10);	cout << char(217);
}
void drawChoosingOutlineStaff() {
	textColor(3);
	GotoXY(45, 5);
	for (int i = 0; i < 20; i++) {
		cout << char(205);
	}
	GotoXY(45, 10);
	for (int i = 0; i < 20; i++) {
		cout << char(205);
	}
	for (int i = 0; i < 5; i++) {
		GotoXY(45, 5 + i);
		cout << char(186);
	}
	for (int i = 0; i < 5; i++) {
		GotoXY(65, 5 + i);
		cout << char(186);
	}
	GotoXY(45, 5);	cout << char(201);
	GotoXY(45, 10);	cout << char(200);
	GotoXY(65, 5);	cout << char(187);
	GotoXY(65, 10);	cout << char(188);
	textColor(15);
}
void drawOutlineStaff() {
	GotoXY(45, 5);
	for (int i = 0; i < 20; i++) {
		cout << char(196);
	}
	GotoXY(45, 10);
	for (int i = 0; i < 20; i++) {
		cout << char(196);
	}
	for (int i = 0; i < 5; i++) {
		GotoXY(45, 5 + i);
		cout << char(179);
	}
	for (int i = 0; i < 5; i++) {
		GotoXY(65, 5 + i);
		cout << char(179);
	}
	GotoXY(45, 5);	cout << char(218);
	GotoXY(45, 10);	cout << char(192);
	GotoXY(65, 5);	cout << char(191);
	GotoXY(65, 10);	cout << char(217);
}
void writeMenuLogin() {
	GotoXY(26, 6); cout << "Login as";
	GotoXY(51, 6); cout << "Login as";
}

void designMenuLogin() {
	system("cls");
	ShowCur(0); 
	drawChoosingOutlineStu();
	drawOutlineStaff();
	writeMenuLogin();
	int pointer = 0, temp;
	while (true) {
		temp = _getch();
		if (temp == 75 || temp == 'a' || temp == 'A') {
			drawChoosingOutlineStu();
			drawOutlineStaff();
			pointer--;
			if (pointer == -1) pointer = 1;
		}
		else if (temp == 77 || temp == 'd' || temp == 'D') {
			drawChoosingOutlineStaff();
			drawOutlineStu();
			pointer++;
			if (pointer == 2) pointer = 0;
		}
		else if (temp == 13 || temp == 32) {
			switch (pointer) {
			case 0:
				ShowCur(1);
				
				break;
			case 1:
				ShowCur(1);

				break;
			}
			break;
		}

	}
}

void designMenuStaff() {

}

void designMenuStudent() {

}



int main()
{
	
	designMenuLogin();

	/*AtTheBeginningOfSchoolYear();

	unsigned long long ID = NULL;
	string className = "";
	login(ID, className);*/

	return 0;
}