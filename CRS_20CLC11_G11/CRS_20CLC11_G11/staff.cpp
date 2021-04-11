#include "struct.h"
#include "bigData.h"

void deleteListClass(_Class*& pHead) {
	_Class* pTmp = pHead;
	while (pHead != nullptr) {
		pHead = pHead->pNext;
		delete pTmp;
		pTmp = pHead;
	}
}

void loadClassName(string className, _Class*& pHeadClass) {
	ifstream fileIn;
	fileIn.open(className, ios_base::in);
	_Class* pCurClass = nullptr;
	while (fileIn) {
		if (pHeadClass == nullptr) {
			pHeadClass = new _Class;
			pCurClass = pHeadClass;
		}
		else {
			pCurClass->pNext = new _Class;
			pCurClass = pCurClass->pNext;
		}
		getline(fileIn, pCurClass->data.name, '\n');
		pCurClass->pNext = nullptr;
	}

	fileIn.close();
}