#include "model.h"
#include <iostream>
#include <sstream>

Model::Model(const std::string filename)
{
    std::ifstream in;
    in.open(filename, std::ifstream::in);
    if (in.fail())
        return;
    std::string line;
    while (!in.eof())
    {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v "))
        {
            iss >> trash;
            vec3 v;
            for (int i = 0; i < 3; i++)
                iss >> v[i];
            verts.push_back(v);
        }
        else if (!line.compare(0, 3, "vn "))
        {
            iss >> trash >> trash;
            vec3 n;
            for (int i = 0; i < 3; i++)
                iss >> n[i];
            norms.push_back(n.normalized());
        }
        else if (!line.compare(0, 3, "vt "))
        {
            iss >> trash >> trash;
            vec2 uv;
            for (int i = 0; i < 2; i++)
                iss >> uv[i];
            tex_coord.push_back({uv.x, 1 - uv.y});
        }
        else if (!line.compare(0, 2, "f "))
        {
            int f, t, n;
            iss >> trash;
            int cnt = 0;
            while (iss >> f >> trash >> t >> trash >> n)
            {
                facet_vrt.push_back(--f);
                facet_tex.push_back(--t);
                facet_nrm.push_back(--n);
                cnt++;
            }
            if (3 != cnt)
            {
                std::cerr << "Error: the obj file is supposed to be triangulated" << std::endl;
                return;
            }
        }
    }
    std::cerr << "# v# " << nverts() << " f# " << nfaces() << " vt# " << tex_coord.size() << " vn# " << norms.size() << std::endl;
}

int Model::nverts() const
{
    return verts.size();
}

int Model::nfaces() const
{
    return facet_vrt.size() / 3; // Assuming triangles
}

vec3 Model::vert(int i) const
{
    return verts[i];
}

vec3 Model::vert(int iface, int nthvert) const
{
    return verts[facet_vrt[iface * 3 + nthvert]];
}

vec3 Model::norm(int iface, int nthvert) const
{
    return norms[facet_nrm[iface * 3 + nthvert]];
}

vec2 Model::tex(int iface, int nthvert) const
{
    return tex_coord[facet_tex[iface * 3 + nthvert]];
}

std::vector<int> Model::face(int iface) const
{
    std::vector<int> face;
    for (int i = 0; i < 3; i++)
    {
        face.push_back(facet_vrt[iface * 3 + i]);
    }
    return face;
}