/**
 * @file Canvas2D.cpp
 *
 * CS123 2-dimensional canvas. Contains support code necessary for Brush, Filter, Intersect, and
 * Ray.
 *
 * YOU WILL NEED TO FILL THIS IN!
 *
 */

// For your convenience, a few headers are included for you.
#include <assert.h>
#include <iostream>
#include <math.h>
#include <memory>
#include <unistd.h>
#include "Canvas2D.h"
#include "Settings.h"
#include "RayScene.h"

#include <QCoreApplication>
#include <QPainter>
#include "brush/Brush.h"
#include "brush/ConstantBrush.h"
#include "brush/LinearBrush.h"
#include "brush/QuadraticBrush.h"
#include "brush/SmudgeBrush.h"

Canvas2D::Canvas2D() :
    // @TODO: Initialize any pointers in this class here.
    m_rayScene(nullptr),
    m_brush(nullptr),
    m_brushType(settings.brushType),
    m_brushRadius(settings.brushRadius),
    m_brushColor(settings.brushColor)
{
    makeBrushFromSettings();
}

Canvas2D::~Canvas2D()
{
}

// This is called when the canvas size is changed. You can change the canvas size by calling
// resize(...). You probably won't need to fill this in, but you can if you want to.
void Canvas2D::notifySizeChanged(int w, int h) {
}

void Canvas2D::paintEvent(QPaintEvent *e) {
    // You probably won't need to fill this in, but you can if you want to override any painting
    // events for the 2D canvas. For now, we simply call the superclass.
    SupportCanvas2D::paintEvent(e);

}

void Canvas2D::makeBrushFromSettings() {
    int brushType = settings.brushType;
    int brushRadius = settings.brushRadius;
    RGBA brushColor = settings.brushColor;
    if (brushType == BRUSH_CONSTANT) {
       m_brush = std::make_unique<ConstantBrush>(brushColor, brushRadius);
    } else if (brushType == BRUSH_LINEAR) {
       m_brush = std::make_unique<LinearBrush>(brushColor, brushRadius);
    } else if (brushType == BRUSH_QUADRATIC) {
       m_brush = std::make_unique<QuadraticBrush>(brushColor, brushRadius);
    } else if (brushType == BRUSH_SMUDGE) {
       m_brush = std::make_unique<SmudgeBrush>(brushColor, brushRadius);
    }
    m_brushType = brushType;
}

void Canvas2D::settingsChanged() {
    int brushType = settings.brushType;
    int brushRadius = settings.brushRadius;
    RGBA brushColor = settings.brushColor;
    if (brushType != m_brushType) {
        std::cout << "BRUSH TYPE CHANGED\n";
        makeBrushFromSettings();
    } else {
        if (brushRadius != m_brushRadius) {
            std::cout << "BRUSH RADIUS CHANGED\n";
            m_brush->setRadius(brushRadius);
            m_brushRadius = brushRadius;
        }
        if (brushColor != m_brushColor) {
            std::cout << "BRUSH COLOR CHANGED\n";
            m_brush->setRGBA(brushColor);
            m_brushColor = brushColor;
        }
    }

    std::cout << "Canvas2d::settingsChanged() called. Settings have changed" << std::endl;
}

// ********************************************************************************************
// ** BRUSH
// ********************************************************************************************
void Canvas2D::setBrush(Brush *brush) {
    m_brush.reset(brush);
}

void Canvas2D::mouseDown(int x, int y) {
    // @TODO: [BRUSH] Mouse interaction for brush. You will probably want to create a separate
    //        class for each of your brushes. Remember that you can use the static Settings
    //        object to get the currently selected brush and its parameters.

    // You're going to need to leave the alpha value on the canvas itself at 255, but you will
    // need to use the actual alpha value to compute the new color of the pixel

    //  bool fixAlphaBlending = settings.fixAlphaBlending; // for extra/half credit

    std::cout << "Canvas2d::mouseDown() called" << std::endl;

    m_brush->brushDown(x, y, this);
}

void Canvas2D::mouseDragged(int x, int y) {
    // TODO: [BRUSH] Mouse interaction for Brush.
     m_brush->brushDragged(x, y, this);
    std::cout << "Canvas2d::mouseDragged() called" << std::endl;

}

void Canvas2D::mouseUp(int x, int y) {
    // TODO: [BRUSH] Mouse interaction for Brush.
    std::cout << "Canvas2d::mouseUp() called" << std::endl;
}



// ********************************************************************************************
// ** FILTER
// ********************************************************************************************

void Canvas2D::filterImage() {
    // TODO: [FILTER] Filter the image. Some example code to get the filter type is provided below.

    switch(settings.filterType) {
        case FILTER_BLUR:
            // ...
            break;
            // fill in the rest
    }

    // Leave this code here! This code ensures that the Canvas2D will be completely wiped before
    // drawing the new image.
    repaint(rect());
    QCoreApplication::processEvents();
}

// ********************************************************************************************
// ** RAY
// ********************************************************************************************

void Canvas2D::setScene(RayScene *scene) {
    m_rayScene.reset(scene);
}

void Canvas2D::renderImage(Camera *camera, int width, int height) {
    if (m_rayScene) {
        // @TODO: raytrace the scene based on settings
        //        YOU MUST FILL THIS IN FOR INTERSECT/RAY

        // If you want the interface to stay responsive, make sure to call
        // QCoreApplication::processEvents() periodically during the rendering.

    }
}

void Canvas2D::cancelRender() {
    // TODO: cancel the raytracer (optional)
}




