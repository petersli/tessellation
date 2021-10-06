#include "ExampleShape.h"

ExampleShape::ExampleShape()
{
}

ExampleShape::ExampleShape(int param1, int param2) :
    m_param1(param1),
    m_param2(param2)
{
    m_vertexData = CUBE_DATA_POSITIONS;
    /**
     * Initialize the OpenGLShapeProperties so that the shape is ready to be drawn.
     * Note that this does not actually draw the shape, that happens in ShapesScene.cpp
     */
    initializeOpenGLShapeProperties();
}

ExampleShape::~ExampleShape()
{
}
