#include <vector>
#include <cmath>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"
using namespace std;

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const int width = 800;
const int height = 800;

void DrawLine(int x0, int x1, int y0, int y1, TGAImage& image, TGAColor color);
int main(int argc, char** argv) {
	TGAImage image(1000, 1000, TGAImage::RGB);
	Model* model = new Model("obj/african_head.obj");
	for (int i = 0; i < model->nfaces(); i++)
	{
		std::vector<int> face = model->face(i);
		for (int j = 0; j < 3; j++)
		{
			Vector3f v0 = model->vert(face[j]);
			Vector3f v1 = model->vert(face[(j + 1) % 3]);
			int x0 = (v0.x + 1.) * width / 2.;
			int y0 = (v0.y + 1.) * height / 2.;
			int x1 = (v1.x + 1.) * width / 2.;
			int y1 = (v1.y + 1.) * height / 2.;
			DrawLine(x0, y0, x1, y1, image, white);
		}
	}
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
	int dx = x1 - x0;
	int dy = abs(y1 - y0);
	int error = 0;
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
		error += dy;
		if (error * 2  > dx * 3)
		{
			y += (y0 < y1) ? 1 : -1;
			error -= dx;
		}
	}
}
void DrawTriangle(Vector2i* vertex, TGAImage& image, TGAColor color)
{
	
}