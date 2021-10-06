/**
 * @file   Brush.cpp
 *
 * Implementation of a brush that smudges the image on the canvas as the mouse is dragged.
 *
 * You should fill this file in for the Brush assignment.
 */
#include <iostream>
#include "SmudgeBrush.h"
#include "Canvas2D.h"


SmudgeBrush::SmudgeBrush(RGBA color, int radius) :
    QuadraticBrush(color, radius)
{
    // @TODO: [BRUSH] Initialize any memory you are going to use here. Hint - you are going to
    //       need to store temporary image data in memory. Remember to use automatically managed memory!
    makePaintBuffer();
    makeMask();
}


SmudgeBrush::~SmudgeBrush()
{
    std::cout << "SmudgeBrush DESTRUCTOR" << std::endl;
    // @TODO: [BRUSH] Be sure not to leak memory!  If you're using automatic memory management everywhere,
    //       this will be empty.
}

void SmudgeBrush::brushUp(int x, int y, Canvas2D* canvas) {
}


//! create a mask with a distribution of your choice (probably want to use quadratic for best results)
void SmudgeBrush::makeMask() {
    // @TODO: [BRUSH] Set up the mask for your brush here. For this brush you will probably want
    //        to use a quadratic distribution for the best results. Linear or Gaussian would
    //        work too, however. Feel free to paste your code from the Linear or Quadratic brushes
    //        or modify the class inheritance to be able to take advantage of one of those class's
    //        existing implementations. The choice is yours!
    //
    QuadraticBrush::makeMask();
}

// Initialize paint buffer to default RGBA values (0, 0, 0, 255)
void SmudgeBrush::makePaintBuffer() {
    // Reserve equivalent area to a mask
    int length = (2 * m_radius + 1) * (2 * m_radius + 1);
    m_paintBuffer.reserve(length);
    for (int i = 0; i < length; i++) {
        m_paintBuffer.push_back(RGBA());
    }
}

void SmudgeBrush::brushDown(int x, int y, Canvas2D *canvas) {
    pickUpPaint(x, y, canvas);
}

//! Picks up paint from the canvas before drawing begins.
void SmudgeBrush::pickUpPaint(int x, int y, Canvas2D* canvas) {
    int width = canvas->width();
    int height = canvas->height();

    int rowStart = y - m_radius;
    int rowEnd = y + m_radius + 1;
    int colStart = x - m_radius;
    int colEnd = x + m_radius + 1;
    int maskSideLength = 2 * m_radius + 1;

    RGBA *pix = canvas->data();
    int rowCounter;
    int colCounter;
    for (rowCounter = rowStart; rowCounter < rowEnd; rowCounter++) {
        for (colCounter = colStart; colCounter < colEnd; colCounter++) {
            int maskRow = rowCounter - rowStart;
            int maskCol = colCounter - colStart;
            int maskIndex = maskRow * maskSideLength + maskCol;
            // Treat off-canvas pixels as black
            if (rowCounter < 0 || rowCounter >= height ||
                    colCounter < 0 || colCounter >= width) {
                m_paintBuffer[maskIndex] = RGBA();
            } else {
                int canvasIndex = rowCounter * width + colCounter;
                RGBA canvasColor = pix[canvasIndex];
                m_paintBuffer[maskIndex] = canvasColor;
            }
        }
    }
}

void SmudgeBrush::brushDragged(int mouseX, int mouseY, Canvas2D* canvas) {
    // @TODO: [BRUSH] Here, you'll need to paste down the paint you picked up in
    //        the previous method. Be sure to take the mask into account! You can
    //        ignore the alpha parameter, but you can also use it (smartly) if you
    //        would like to.

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
            int canvasIndex = rowCounter * canvas->width() + colCounter;
            int maskIndex = maskRow * maskSideLength + maskCol;
            RGBA canvasColor = pix[canvasIndex];
            RGBA copiedColor = m_paintBuffer[maskIndex];
            float maskValue = m_mask[maskIndex];
            pix[canvasIndex] = smudgeColor(canvasColor, copiedColor, maskValue);
        }
    }
    canvas->update();


    // now pick up paint again...
    pickUpPaint(mouseX, mouseY, canvas);

}


RGBA SmudgeBrush::smudgeColor(RGBA canvasColor, RGBA copiedColor, float maskValue) {
    // We don't consider alpha when smudging, so we set it to 1
    int newRed = mixRGBChannel(copiedColor.r / 255.0f, canvasColor.r / 255.0f, maskValue, 1);
    int newGreen = mixRGBChannel(copiedColor.g / 255.0f, canvasColor.g / 255.0f, maskValue, 1);
    int newBlue = mixRGBChannel(copiedColor.b / 255.0f, canvasColor.b / 255.0f, maskValue, 1);
    return RGBA(newRed, newGreen, newBlue, 255);
}


