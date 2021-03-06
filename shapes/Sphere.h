#ifndef SPHERE_H
#define SPHERE_H

#define PI 3.14159265f

#include "Tessellator.h"
#include "TriMesh.h"
#include "Shape.h"

/** A sphere with radius of 0.5, centered at the origin */
class Sphere : public Shape
{
public:
    Sphere(int param1, int param2);
    ~Sphere();
    std::vector<float> getVertexData();

private:
    std::unique_ptr<Tessellator> m_tessellator;
    void initializeVertexData();
    std::vector<glm::vec3> makeVertexGrid();
    void setSphereNormals(TriMesh triMesh);
};


#endif // SPHERE_H
