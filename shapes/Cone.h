#ifndef CONE_H
#define CONE_H

#define PI 3.14159265f

#include "Tessellator.h"
#include "TriMesh.h"
#include "Shape.h"
#include "CircleBase.h"

/** Cone bounded by a 1x1x1 cube centered at the origin */
class Cone : public Shape
{
public:
    Cone(int param1, int param2);
    ~Cone();

private:
    std::unique_ptr<Tessellator> m_tessellator;
    std::unique_ptr<CircleBase> m_bottom;
    void initializeVertexData();
    std::vector<glm::vec3> makeSideGrid();
    void setSideNormals(std::vector<Triangle> &faces);
};


#endif // CONE_H
