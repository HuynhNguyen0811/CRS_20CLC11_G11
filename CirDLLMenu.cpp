#include <iostream>
#include <string>

using namespace std;

struct menu {
	string data;
	menu* pNext, * pPrevious;
};

void addMenu(string source, menu*& pHead);
void displayMenu(menu* pHead);
void deleteMenu(menu*& pHead);

void addMenu(string source, menu*& pHead)
{
	if (pHead->data.length() == 0 )
	{
		pHead->data = source;
		pHead->pNext = pHead;
		pHead->pPrevious = pHead;
		return;
	}
	menu* last = pHead->pPrevious;
	menu* temp = new menu();
	temp->data = source;
	temp->pNext = pHead;
	temp->pPrevious = last;
	last->pNext = temp;
	pHead->pPrevious = temp;
	return;
}

void displayMenu(menu* pHead)
{
	if (pHead == NULL) return;
	menu* pCur = pHead;
	while (pCur->pNext != pHead)
	{
		cout << pCur->data << endl;
		pCur = pCur->pNext;
	}
	cout << pCur->data;
	return;
}

void deleteMenu(menu*& pHead)
{
	if (pHead != NULL)
	{
		menu* temp, * pCur = pHead->pNext;
		while (pCur != pHead)
		{
			temp = pCur;
			pCur = pCur->pNext;
			free(temp);
		}
	}
	//free(pHead)
	pHead->data = "";
	pHead->pNext = pHead;
	pHead->pPrevious = pHead;
	return;
}

int main()
{
	menu* pHead = new menu();
	addMenu("a", pHead);
	addMenu("b", pHead);
	addMenu("c", pHead);
	displayMenu(pHead);
	deleteMenu(pHead);
	cout << endl << endl;
	addMenu("c", pHead);
	addMenu("b", pHead);
	addMenu("a", pHead);
	displayMenu(pHead);
	delete pHead;
}