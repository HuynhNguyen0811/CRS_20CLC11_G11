#include <iostream>
#include <fstream>

using namespace std;

struct coord {
	int x;
	int y;
};

int main() {
	int a = 765, length = 5, d = 500;
	double b = 5.5;
	int* c = new int[5]{ 1,0,1,0,0 };
	int r, lengthr;
	double s;
	int* t;
	coord coord = { 5, 10 };

	fstream fileOut;
	fileOut.open("test.bin", ios_base::out | ios_base::binary);

	fileOut.write((char*)&a, sizeof(int));
	//fileOut.write((char*)&coord, sizeof(coord));
	fileOut.write((char*)&b, sizeof(double));
	fileOut.write((char*)&length, sizeof(int));
	fileOut.write((char*)&*c, sizeof(int) * length);
	/*for (int i = 0; i < length; i++) {
		fileOut.write((char*)&c[i], sizeof(int));
	}*/
	long pos = fileOut.tellp();
	fileOut.seekp(pos - sizeof(int) * length - sizeof(int) - sizeof(double) - sizeof(int));
	fileOut.write((char*)&d, sizeof(int));

	fileOut.close();

	fstream fileIn;
	fileIn.open("test.bin", ios_base::in | ios_base::binary);

	fileIn.read((char*)&r, sizeof(int));
	fileIn.read((char*)&s, sizeof(double));
	fileIn.read((char*)&lengthr, sizeof(int));
	t = new int[lengthr];
	fileIn.read((char*)&*t, sizeof(int) * lengthr);

	fileIn.close();

	cout << r << " " << s;
	for (int i = 0; i < lengthr; i++) {
		cout << " " << t[i];
	}
	delete[] c;
	delete[] t;

	return 0;
}