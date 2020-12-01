#include <vector>
#include <cmath>
#include <cstdlib>
#include <limits>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"
using namespace std;

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const int width = 800;
const int height =800;

void DrawLine(int x0, int x1, int y0, int y1, TGAImage& image, TGAColor color);
void DrawTriangle(Vector3f* vertex, float* zBuffer,TGAImage& image, TGAColor color);
Vector3f Barycentric(Vector3f* vertex, Vector3f& p);
Vector3f cross(const Vector3f& v0, const Vector3f& v1);
int main(int argc, char** argv) {
	TGAImage image(width, height, TGAImage::RGB);
	Model* model = new Model("obj/african_head.obj");
	float* zBuffer = new float[width * height];
	for (int i = 0; i < model->nfaces(); i++)
	{
		vector<int> face = model->face(i);
		Vector3f vertex[3];
		Vector3f vec3f[3];		

		for (int j = 0; j < 3; j++)
		{
			Vector3f v = model->vert(face[j]);
			vertex[j] = Vector3f(
				int((v.x + 1.0) * width / 2.0 + 0.5), 
				int((v.y + 1.0) * height / 2.0 + 0.5),
				v.z);
			vec3f[j] = v;
		}
		Vector3f vec = cross(vec3f[1] - vec3f[0], vec3f[2] - vec3f[0]);
		vec.normalize();
		float n =  vec * Vector3f(0,0,1);
		if (n > 0)
		{
			DrawTriangle(vertex, zBuffer,image, TGAColor(255 * n, 255 * n, 255 * n, 255 * n));
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
void DrawTriangle(Vector3f* vertex, float* zBuffer,TGAImage& image, TGAColor color)
{
	Vector2i limitBoxMax =  Vector2i(0, 0);
	Vector2i limitBoxMin =  Vector2i(image.getWidth() - 1, image.getHeight() - 1);
	Vector2i clamp =  Vector2i(image.getWidth() - 1, image.getHeight() - 1);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			limitBoxMax[j] = min(clamp[j], max(limitBoxMax[j], int(vertex[i][j])));
			limitBoxMin[j] = max(0, min(limitBoxMin[j], int(vertex[i][j])));
		}
	}
	Vector3f p;
	for (p.x= limitBoxMin.x; p.x < limitBoxMax.x; p.x++)
	{
		for (p.y = limitBoxMin.y; p.y < limitBoxMax.y; p.y++)
		{
			Vector3f v = Barycentric(vertex, p);
			if (v.x < 0 || v.y < 0 || v.z < 0)
				continue;
			p.z = 0;
			for (int i = 0; i < 3; i++)
			{
				p.z += vertex[i].z * v[i];
			}
			if (zBuffer[int(p.x + p.y * width)] < p.z)
			{
				zBuffer[int(p.x + p.y * width)] = p.z;
				image.set(p.x, p.y, color);
			}
		}
	}
}
Vector3f cross(const Vector3f& v0, const Vector3f& v1)
{
	return Vector3f(v0.y * v1.z - v1.y * v0.z, v0.z * v1.x- v0.x * v1.z, v0.x * v1.y - v0.y * v1.x);
}
Vector3f Barycentric(Vector3f* vertex, Vector3f& p)
{
	Vector3f vec = cross(
		Vector3f(vertex[1].x - vertex[0].x, vertex[2].x - vertex[0].x, vertex[0].x - p.x),
		Vector3f(vertex[1].y - vertex[0].y, vertex[2].y - vertex[0].y, vertex[0].y - p.y));
	if (abs(vec.z) < 1)
		return Vector3f(-1,1,1);
	return Vector3f(1.f-(vec.x+vec.y)/vec.z,vec.y/vec.z,vec.x/vec.z);
}
