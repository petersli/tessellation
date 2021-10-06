/**
 * @file   ConstantBrush.cpp
 *
 * Implementation of a brush with a constant mask distribution.
 *
 * You should fill this file in while completing the Brush assignment.
 */

#include "ConstantBrush.h"

ConstantBrush::ConstantBrush(RGBA color, int radius)
    : Brush(color, radius)
{
    // @TODO: [BRUSH] You'll probably want to set up the mask right away.
    makeMask();
}


ConstantBrush::~ConstantBrush()
{
}

void ConstantBrush::makeMask() {
    // @TODO: [BRUSH] Set up the mask for your Constant brush here...

    // Mask always has odd side length
    int sideLength = 2 * m_radius + 1;
    int squareRadius = m_radius * m_radius;

    m_mask.reserve(sideLength * sideLength);
    for (int row = 0; row < sideLength; row++) {
        for (int col = 0; col < sideLength; col++) {
            int squareDistanceFromCenter = Brush::squareMagnitude(col - m_radius, row - m_radius);
            int index = row * sideLength + col;
            if (squareDistanceFromCenter < squareRadius) {
                m_mask[index] = 1;
            } else {
                m_mask[index] = 0;
            }
        }
    }
}

