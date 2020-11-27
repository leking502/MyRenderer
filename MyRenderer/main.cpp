#include "tgaimage.h"
using namespace std;

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

void DrawLine(int x0, int x1, int y0, int y1, TGAImage& image, TGAColor color);
int main(int argc, char** argv) {
	TGAImage image(1000, 1000, TGAImage::RGB);
	DrawLine(200, 800, 300, 400, image, white);
	DrawLine(300, 400, 700, 500, image, white);
	DrawLine(700, 500, 200, 800, image, white);
	image.flipVertically(); // i want to have the origin at the left bottom corner of the image
	image.writeTgaFile("output.tga");
	return 0;
}
void DrawLine(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color)
{
	bool steep = false;
	if (abs(x0 - x1) < abs(y0 - y1))
	{
		swap(x0, y0);
		swap(x1, y1);
		steep = true;
	}
	if (x0 > x1)
	{
		swap(x0, x1);
		swap(y0, y1);
	}
	float error = 0;
	float derror = abs((y1 - y0) / float(x1 - x0));
	int y = y0;
	for (int x = x0; x < x1; x++)
	{		
		if (!steep)
		{
			image.set(x,y,color);
		}
		else
		{
			image.set(y, x, color);
		}
		error += derror;
		if (error > 0.75f)
		{
			y += (y0 < y1) ? 1 : -1;
			error -= 1;
		}
	}
}