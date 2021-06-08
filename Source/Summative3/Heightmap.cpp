#include "Heightmap.h"


using namespace std;

const int BYTES_PER_PIXEL = 3; /// red, green, & blue
const int FILE_HEADER_SIZE = 14;
const int INFO_HEADER_SIZE = 40;

Heightmap::Heightmap(int x, int z)
{
	ofstream fout("output.bmp", ios::binary);

	fout.write((char*)&bmpHeader, 14);
	fout.write((char*)&bmpInfoHeader, 40);

	// writing pixel data
	size_t numberOfPixels = bmpInfoHeader.width * bmpInfoHeader.height;
	for (int i = 0; i < numberOfPixels; i++) {
		fout.write((char*)&pixel, 3);
	}
	fout.close();
}

Heightmap::~Heightmap()
{
}

float Heightmap::Random(int x, int y)
{
	int n = x + y * 57;
	n = (n << 13) ^ n;
	int t = (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff;
	return 1.0 - double(t) * 0.931322574615478515625e-9;
}

float Heightmap::Smooth(int x, int y)
{
	float corners;
	float sides;
	float centre;

	corners = (Random(x - 1, y - 1) + Random(x + 1, y - 1) + Random(x - 1, y + 1)) / 16;
	sides = (Random(x - 1, y) + Random(x + 1, y) + Random(x, y - 1) + Random(x, y + 1)) / 8;
	centre = Random(x, y) / 4;

	return corners + sides + centre;
}

float Heightmap::Linear_Interpolation(float a, float b, float x)
{
	return a * (1 - x) + b * x;
}

float Heightmap::Cosine_Interpolation(float a, float b, float x)
{
	float ft = x * 3.1415927;
	float f = (1 - cos(ft)) * 0.5;

	return a * (1 - f) + b * f;
}

float Heightmap::Cubic_Interpolation(float v0, float v1, float v2, float v3, float x)
{
	float P = (v3 - v2) - (v0 - v1);
	float Q = (v0 - v1) - P;
	float R = v2 - v0;
	float S = v1;

	return (P * pow(x, 3.0)) + (Q * pow(x, 2.0)) + (R * x) + S;
}

float Heightmap::Noise(float x, float y)
{
	float fractional_X = x - int(x);
	float fractional_Y = y - int(y);

	//Smooths
	float v1 = Smooth(int(x), int(y));
	float v2 = Smooth(int(x) + 1, int(y));
	float v3 = Smooth(int(x), int(y) + 1);
	float v4 = Smooth(int(x) + 1, int(y) + 1);

	//Interpolates
	float i1 = Linear_Interpolation(v1, v2, fractional_X);
	float i2 = Linear_Interpolation(v3, v4, fractional_X);

	float final = Linear_Interpolation(i1, i2, fractional_Y);

	return final;
}

float Heightmap::totalNoisePerPoint(int x, int y)
{
	int octaves = 8;
	float zoom = 20.0f;
	float persistance = 0.5f;
	float total = 0.0f;

	for (int i = 0; i < octaves; i++)
	{
		float frequency = pow(2, i) / zoom;
		float amplitude = pow(persistance, i);

		total += Noise(x * frequency, y * frequency) * amplitude;
	}

	return total;
}

void Heightmap::SaveToBitmap()
{
	
}

