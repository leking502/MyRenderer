#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
#include "geometry.h"
#include "tgaimage.h"

class Model
{
private:
	std::vector<Vector3f> verts_;
	std::vector<Vector3f> texVerts_;
	std::vector<std::vector<int> > faces_;
	std::vector<std::vector<int>> texture_;
public:
	Model(const char* filename);
	~Model();
	int nverts();
	int nfaces();
	Vector3f vert(int i);
	Vector3f texVert(int i);
	std::vector<int> face(int idx);
	std::vector<int> texture(int idx);
};

#endif //__MODEL_H__
