/**
 * @file   Brush.cpp
 *
 * Implementation of common functionality of bitmap brushes.
 *
 * You should fill this file in while completing the Brush assignment.
 */

#include "Brush.h"
#include "Canvas2D.h"

static unsigned char lerp(unsigned char a, unsigned char b, float percent) {
    float fa = static_cast<float>(a) / 255.0f;
    float fb = static_cast<float>(b) / 255.0f;
    return static_cast<unsigned char>((fa + (fb - fa) * percent) * 255.0f + 0.5f);
}



Brush::Brush(RGBA color, int radius) :
    // Pro-tip: Initialize all variables in the initialization list
    m_color(color),
    m_radius(radius)
{
    // Pro-tip: By the time you get to the constructor body, all of the
    // member variables have already been initialized.
}


Brush::~Brush()
{
    // Pro-tip: The destructor (here) is where you free all the resources
    // you allocated during the lifetime of the class
    // Pro-tip: If you use std::unique_ptr or std::vector, you probabably
    // won't need to put anything in here.
}

int Brush::getAlpha() const {
    return m_color.a;
}

RGBA Brush::getRGBA() const {
    return m_color;
}

int Brush::getBlue() const {
    return m_color.b;
}

int Brush::getGreen() const {
    return m_color.g;
}

int Brush::getRadius() const {
    return m_radius;
}

int Brush::getRed() const {
    return m_color.r;
}

void Brush::setAlpha(int alpha) {
    m_color.a = alpha;
}

void Brush::setRGBA(const RGBA &rgba) {
    m_color = rgba;
}

void Brush::setBlue(int blue) {
    m_color.b = blue;
}

void Brush::setGreen(int green) {
    m_color.g = green;
}

void Brush::setRed(int red) {
    m_color.r = red;
}

void Brush::setRadius(int radius) {
    m_radius = radius;
    makeMask();
}

int Brush::squareMagnitude(int x, int y) {
    return x * x + y * y;
}

int Brush::mixRGBChannel(float brushIntensity, float canvasIntensity, float maskValue, float alpha) {
    float newIntensity = maskValue * alpha * brushIntensity + (1 - maskValue * alpha) * canvasIntensity;
    return newIntensity * 255;
}

RGBA Brush::mixColor(RGBA canvasColor, float maskValue) {
    float alpha = m_color.a / 255.0f;
    int newRed = mixRGBChannel(m_color.r / 255.0f, canvasColor.r / 255.0f, maskValue, alpha);
    int newGreen = mixRGBChannel(m_color.g / 255.0f, canvasColor.g / 255.0f, maskValue, alpha);
    int newBlue = mixRGBChannel(m_color.b / 255.0f, canvasColor.b / 255.0f, maskValue, alpha);
    return RGBA(newRed, newGreen, newBlue, 255);
}

void Brush::brushDragged(int mouseX, int mouseY, Canvas2D* canvas) {
    // @TODO: [BRUSH] You can do any painting on the canvas here. Or, you can
    //        override this method in a subclass and do the painting there.
    //
    //
    int rowStart = std::max(0, mouseY - m_radius);
    int rowEnd = std::min(canvas->height(), mouseY + m_radius + 1);
    int colStart = std::max(0, mouseX - m_radius);
    int colEnd = std::min(canvas->width(), mouseX + m_radius + 1);
    int maskSideLength = 2 * m_radius + 1;

    RGBA *pix = canvas->data();
    int rowCounter;
    int colCounter;
    for (rowCounter = rowStart; rowCounter < rowEnd; rowCounter++) {
        for (colCounter = colStart; colCounter < colEnd; colCounter++) {
            int maskRow = rowCounter - rowStart;
            int maskCol = colCounter - colStart;
            // If the mask would have gone off the canvas, update our row/col
            // for indexing into the mask appropriately
            if (rowStart == 0) {
                maskRow -= mouseY - m_radius;
            }
            if (colStart == 0) {
                maskCol -= mouseX - m_radius;
            }
            int index = rowCounter * canvas->width() + colCounter;
            RGBA canvasColor = pix[index];
            float maskValue = m_mask[maskRow * maskSideLength + maskCol];
            pix[index] = mixColor(canvasColor, maskValue);
        }
    }
    canvas->update();
}
