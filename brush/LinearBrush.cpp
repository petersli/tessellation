/**
 * @file   LinearBrush.cpp
 *
 * Implementation of a brush with a linear mask distribution.
 *
 * You should fill this file in while completing the Brush assignment.
 */

#include "LinearBrush.h"

#include <math.h>

LinearBrush::LinearBrush(RGBA color, int radius)
    : Brush(color, radius)
{
    // @TODO: [BRUSH] You'll probably want to set up the mask right away.
    makeMask();
}


LinearBrush::~LinearBrush()
{
}

void LinearBrush::makeMask() {
    // @TODO: [BRUSH] Set up the mask for your Linear brush here...

    // Mask always has odd side length
    int sideLength = 2 * m_radius + 1;

    m_mask.reserve(sideLength * sideLength);
    for (int row = 0; row < sideLength; row++) {
        for (int col = 0; col < sideLength; col++) {
            int squareDistanceFromCenter = Brush::squareMagnitude(col - m_radius, row - m_radius);
            int distanceFromCenter = sqrt(squareDistanceFromCenter);
            int index = row * sideLength + col;
            if (distanceFromCenter < m_radius) {
                m_mask[index] = (m_radius - distanceFromCenter) / static_cast<float>(m_radius);
            } else {
                m_mask[index] = 0;
            }
        }
    }
}


