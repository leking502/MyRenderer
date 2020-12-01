#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "model.h"

Model::Model(const char* filename) : verts_(), faces_()
{
    std::ifstream in;
    in.open(filename, std::ifstream::in);
    if (in.fail()) return;
    std::string line;
    while (!in.eof())
    {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v "))
        {
            iss >> trash;
            Vector3f v;
            for (int i = 0; i < 3; i++) iss >> v[i];
            verts_.push_back(v);
        }
        else if (!line.compare(0, 3, "vt "))
        {
            iss >> trash>>trash;
            Vector3f v;
            for (int i = 0; i < 2; i++) iss >> v[i];
            texVerts_.push_back(v);
        }
        else if (!line.compare(0, 2, "f "))
        {
            std::vector<int> f;
            std::vector<int> t;
            int itrash, idx,itex;
            iss >> trash;
            while (iss >> idx >> trash >> itex >> trash >> itrash)
            {
                idx--;
                itex--;// in wavefront obj all indices start at 1, not zero
                f.push_back(idx);
                t.push_back(itex);
            }
            texture_.push_back(t);
            faces_.push_back(f);
        }
    }
    std::cerr << "# v# " << verts_.size() << " f# " << faces_.size() << "vt#"<<texture_.size()<<std::endl;
}

Model::~Model()
{
}

int Model::nverts()
{
    return (int)verts_.size();
}

int Model::nfaces()
{
    return (int)faces_.size();
}

std::vector<int> Model::face(int idx)
{
    return faces_[idx];
}
std::vector<int> Model::texture(int idx)
{
    return texture_[idx];
}

Vector3f Model::vert(int i)
{
    return verts_[i];
}
Vector3f Model::texVert(int i)
{
    return texVerts_[i];
}