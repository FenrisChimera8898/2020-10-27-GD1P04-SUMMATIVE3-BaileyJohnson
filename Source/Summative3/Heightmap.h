#pragma once
#include <vector>
#include <fstream>

class Heightmap
{
public:
	Heightmap(int x, int z);
	~Heightmap();

	float Random(int x, int y);
	float Smooth(int x, int y);
	float Linear_Interpolation(float a, float b, float x);
	float Cosine_Interpolation(float a, float b, float x);
	float Cubic_Interpolation(float v0, float v1, float v2, float v3, float x);
	float Noise(float x, float y);

	float totalNoisePerPoint(int x, int y);

	void SaveToBitmap();

private:
	struct BmpHeader {
		char bitmapSignatureBytes[2] = { 'B', 'M' };
		uint32_t sizeOfBitmapFile = 54 + 786432;
		uint32_t reservedBytes = 0;
		uint32_t pixelDataOffset = 54;
	} bmpHeader;

	struct BmpInfoHeader {
		uint32_t sizeOfThisHeader = 40;
		int32_t width = 512; // in pixels
		int32_t height = 512; // in pixels
		uint16_t numberOfColorPlanes = 1; // must be 1
		uint16_t colorDepth = 24;
		uint32_t compressionMethod = 0;
		uint32_t rawBitmapDataSize = 0; // generally ignored
		int32_t horizontalResolution = 3780; // in pixel per meter
		int32_t verticalResolution = 3780; // in pixel per meter
		uint32_t colorTableEntries = 0;
		uint32_t importantColors = 0;
	} bmpInfoHeader;
	
	struct Pixel {
		uint8_t blue = 255;
		uint8_t green = 255;
		uint8_t red = 0;
	} pixel;
};

