#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include "geometry.h"
#include <fstream>

class Model
{
private:
    std::vector<vec3> verts;
    std::vector<vec3> norms;
    std::vector<vec2> tex_coord;
    std::vector<int> facet_vrt;
    std::vector<int> facet_nrm;
    std::vector<int> facet_tex;

public:
    Model(const std::string filename);
    int nverts() const;
    int nfaces() const;
    vec3 vert(int i) const;
    vec3 vert(int iface, int nthvert) const;
    vec3 norm(int iface, int nthvert) const;
    vec2 tex(int iface, int nthvert) const;
    std::vector<int> face(int iface) const; // 新增的方法
};

#endif // MODEL_H
