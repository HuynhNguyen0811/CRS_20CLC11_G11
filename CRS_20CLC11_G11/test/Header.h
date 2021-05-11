#include <iostream>
#include <fstream>
#include <Windows.h>

struct BmpSignature {
	unsigned char data[2];
};
#pragma pack(1)
struct BmpHeader {
	BmpSignature signature;//
	uint32_t fileSize;//
	uint16_t reserved1;//
	uint16_t reserved2;//
	uint32_t dataOffset;//
};

struct BmpDib {
	uint32_t dibSize;//
	int32_t imageWidth;//
	int32_t imageHeight;//
	uint16_t colorPlaneCount;//
	uint16_t pixelSize;//
	uint32_t compressMethod;//
	uint32_t bitMapByteCount;
	int32_t horizontalResolution;//
	int32_t verticalHorizontal;//
	uint32_t colorCount;//
	uint32_t importantColorCount;//
};

struct Color {
	unsigned char blue;
	unsigned char green;
	unsigned char red;
};

struct ColorTable {
	Color* colors;
	uint32_t length;
};

struct PixelArray {
	Color** pixels;
	uint32_t rowCount;
	uint32_t columnCount;
};

bool isBmpFile(std::ifstream& fileIn);
void readBmpHeader(std::ifstream& fileIn, BmpHeader& header);
void writeBmpHeader(std::ofstream& fileOut, BmpHeader& header);

void readBmpDib(std::ifstream& fileIn, BmpDib& dib);
void writeBmpDib(std::ofstream& fileOut, BmpDib& dib);

void readBmpPixelArray(std::ifstream& f, BmpHeader header, BmpDib dib, PixelArray& data);
void writeBmpPixelArray(std::ofstream& fileOut, BmpHeader header, BmpDib dib, PixelArray& data);

void scanBmpPixelLine(std::ifstream& f, Color*& line, uint32_t length);
void skipBmpPadding(std::ifstream& f, char count);
void scanWriteBmpPixelVerticalLine(std::ofstream& fileOut, Color*& line, uint32_t length);
void scanWriteBmpPixelHorizontalLine(std::ofstream& fileOut, Color*& line, uint32_t length);
void skipWriteBmpPadding(std::ofstream& fileOut, char count);

void drawBmp(BmpDib dib, PixelArray data);
void releaseBmpPixelArray(PixelArray data);