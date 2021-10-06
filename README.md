# Tessellation

**Note: most of the relevant code lives in the `shapes` directory**

For this project, I implemented parametric tessellators for a cube, cylinder, cone, and sphere.

## Data Structures

To store triangle meshes, I created the `Triangle` and `TriMesh` data structures in `TriMesh.h`.

```
struct Triangle {
    std::vector<int> vertexIndices;
    std::vector<glm::vec3> vertexNormals;
};

struct TriMesh {
    std::vector<glm::vec3> &vertices;
    std::vector<Triangle> &faces;
};
```

Storing vertex indices instead of the vertices themselves helps maintain consistency and reduce 
the size of the mesh.

## Composition and Inheritance

For the most part, I favored composition over inheritance for this project. I factored out the circular base of the 
`Cone` and `Cylinder` into a `CircleBase m_circleBase` member variable, and added `Tessellator m_tessellator` 
to each shape as well.

I did use inheritance, however, by having the `Cube`, `Cylinder`, `Cone`, and `Sphere` all
extend a new base class `Shape`. `Shape` is a thin wrapper around `OpenGLShape` which allows setting 
tessellation parameters (param1 and param2) and has a pure virtual method `initializeVertexData`.
Every class derived from `Shape` must implement the`initializeVertexData` method in order to be rendered by OpenGL.

## The Tessellator Utility Class

The class `Tessellator` implements functionality common to all or many shapes. It has the following methods:

```
std::vector<Triangle> tessellate(int gridWidth, int gridHeight);
std::vector<float> processTriMesh(TriMesh triMesh);
void setUncurvedMeshNormals(TriMesh triMesh);
```

The `tessellate` function will traverse a vertex grid and construct counter-clockwise ordered triangle faces.
The `processTriMesh` function converts a completed triangle mesh into the vector of floats representing vertices and normals
that OpenGL requires.
And `setUncurvedMeshNormals` simplifies the process of setting normals for any uncurved surface, like the side of a cube
or the base of a cylinder. It uses crossproducts to compute one normal for each face directly from the vertex positions. 
For curved surfaces, like a sphere or the side of a cyliner/cone, the 3 vertices of a face will have different normals,
so we instead use parametric calculations to compute the normals separately.
