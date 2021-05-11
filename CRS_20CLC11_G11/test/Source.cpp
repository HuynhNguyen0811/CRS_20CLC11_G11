#include "Header.h"


bool isBmpFile(std::ifstream& fileIn) {
	if (!fileIn.is_open()) return false;

	BmpSignature signature;
	fileIn.seekg(0, fileIn.beg);
	fileIn.read((char*)&signature, sizeof(BmpSignature));
	std::cout << signature.data[0] << signature.data[1] << std::endl;
	return (signature.data[0] == 'B' && signature.data[1] == 'M');
}

void readBmpHeader(std::ifstream& fileIn, BmpHeader& header) {
	if (!fileIn.is_open()) return;
	fileIn.seekg(0, fileIn.beg);
	fileIn.read((char*)&header, sizeof(BmpHeader));
}
void writeBmpHeader(std::ofstream& fileOut, BmpHeader& header) {
	if (!fileOut.is_open()) return;
	fileOut.seekp(0, std::ios_base::beg);
	fileOut.write((char*)&header, sizeof(BmpHeader));
}

void readBmpDib(std::ifstream& fileIn, BmpDib& dib) {
	if (!fileIn.is_open()) return;

	fileIn.seekg(sizeof(BmpHeader), fileIn.beg);
	fileIn.read((char*)&dib, sizeof(BmpDib));
}
void writeBmpDib(std::ofstream& fileOut, BmpDib& dib) {
	if (!fileOut.is_open()) return;

	fileOut.seekp(sizeof(BmpHeader), std::ios_base::beg);
	fileOut.write((char*)&dib, sizeof(BmpDib));
}

void readBmpPixelArray(std::ifstream& f, BmpHeader header, BmpDib dib, PixelArray& data) {
	if (!f.is_open()) return;

	data.rowCount = dib.imageHeight;
	data.columnCount = dib.imageWidth;
	data.pixels = new Color * [data.rowCount];

	char paddingCount = (4 - (dib.imageWidth * (dib.pixelSize / 8) % 4)) % 4;

	f.seekg(header.dataOffset, f.beg);

	for (int i = 0; i < data.rowCount; i++) {
		scanBmpPixelLine(f, data.pixels[data.rowCount - 1 - i], dib.imageWidth);
		skipBmpPadding(f, paddingCount);
	}
}
void writeBmpPixelArray(std::ofstream& fileOut, BmpHeader header, BmpDib dib, PixelArray& data) {
	if (!fileOut.is_open()) return;

	data.rowCount = dib.imageHeight;
	data.columnCount = dib.imageWidth;
	data.pixels = new Color * [data.rowCount];

	char paddingCount = (4 - (dib.imageWidth * (dib.pixelSize / 8) % 4)) % 4;

	fileOut.seekp(header.dataOffset, std::ios_base::beg);

	for (int i = 0; i < data.rowCount; i++) {
		if (i <= data.rowCount * 3 / 7 || i >= data.rowCount * 4 / 7) {
			scanWriteBmpPixelVerticalLine(fileOut, data.pixels[data.rowCount - 1 - i], dib.imageWidth);
			skipWriteBmpPadding(fileOut, paddingCount);
		}
		else {
			scanWriteBmpPixelHorizontalLine(fileOut, data.pixels[data.rowCount - 1 - i], dib.imageWidth);
			skipWriteBmpPadding(fileOut, paddingCount);
		}

	}
}

void scanBmpPixelLine(std::ifstream& f, Color*& line, uint32_t length) {
	if (!f.is_open()) return;

	line = new Color[length];
	for (int i = 0; i < length; i++) f.read((char*)&line[i], sizeof(Color));

}
void skipBmpPadding(std::ifstream& f, char count) {
	if (!f.is_open() || count == 0) return;

	char padding[3];
	f.read((char*)padding, count);
}
void scanWriteBmpPixelVerticalLine(std::ofstream& fileOut, Color*& line, uint32_t length) {
	if (!fileOut.is_open()) return;

	line = new Color[length];
	for (int i = 0; i < length; i++) {
		if (i <= length * 4 / 9 || i >= length * 5 / 9)
			line[i] = { 255, 255, 255 };
		else
			line[i] = { 0, 0, 255 };
	}
	for (int i = 0; i < length; i++) fileOut.write((char*)&line[i], sizeof(Color));
}
void scanWriteBmpPixelHorizontalLine(std::ofstream& fileOut, Color*& line, uint32_t length) {
	if (!fileOut.is_open()) return;

	line = new Color[length];
	for (int i = 0; i < length; i++) {
		line[i] = { 0, 0, 255 };
	}
	for (int i = 0; i < length; i++) fileOut.write((char*)&line[i], sizeof(Color));
}
void skipWriteBmpPadding(std::ofstream& fileOut, char count) {
	if (!fileOut.is_open() || count == 0) return;

	char padding[3]{ 0, 0, 0 };
	fileOut.write((char*)padding, count);
}

void drawBmp(BmpDib dib, PixelArray data) {
	HWND console = GetConsoleWindow();
	HDC hdc = GetDC(console);

	for (int i = 0; i < dib.imageHeight; i++) {
		for (int j = 0; j < dib.imageWidth; j++) {
			Color pixel = data.pixels[i][j];
			SetPixel(hdc, j, i, RGB(pixel.red, pixel.green, pixel.blue));
		}
	}
	ReleaseDC(console, hdc);
}

void releaseBmpPixelArray(PixelArray data) {
	for (int i = 0; i < data.rowCount; i++) {
		delete[] data.pixels[i];
	}
	delete[] data.pixels;
}

int main() {
	std::ifstream f;
	BmpHeader header;
	BmpDib dib;
	PixelArray data;

	std::ofstream fileOut;

	header.signature.data[0] = 'B';
	header.signature.data[1] = 'M';
	header.dataOffset = 54;

	std::cout << "Width: ";
	std::cin >> dib.imageWidth;
	std::cout << "Height: ";
	std::cin >> dib.imageHeight;
	header.fileSize = dib.imageWidth * dib.imageHeight * 4;

	dib.dibSize = 40;
	dib.pixelSize = 24;
	dib.bitMapByteCount = dib.imageWidth * dib.imageHeight * 4;
	dib.compressMethod = 0;
	dib.horizontalResolution = dib.verticalHorizontal = 2835;
	dib.colorCount = 0;
	dib.importantColorCount = 0;

	fileOut.open("toi.bmp", std::ios_base::app | std::ios_base::binary);

	/*writeBmpHeader(fileOut, header);
	writeBmpDib(fileOut, dib);
	writeBmpPixelArray(fileOut, header, dib, data);*/
	while (true) {
		fileOut.write((char*)&header, sizeof(BmpHeader));
	}
	releaseBmpPixelArray(data);

	fileOut.close();

	
	return 0;
}