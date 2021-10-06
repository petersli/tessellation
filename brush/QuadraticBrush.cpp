/**
 * @file   QuadraticBrush.cpp
 *
 * Implementation of a brush with a quadratic mask distribution.
 *
 * You should fill this file in while completing the Brush assignment.
 */

#include "QuadraticBrush.h"

#include <math.h>

QuadraticBrush::QuadraticBrush(RGBA color, int radius)
    : Brush(color, radius)
{
    // @TODO: [BRUSH] You'll probably want to set up the mask right away.
    makeMask();
}

QuadraticBrush::~QuadraticBrush()
{
}

void QuadraticBrush::makeMask() {
    // @TODO: [BRUSH] Set up the mask for your Quadratic brush here...
    int sideLength = 2 * m_radius + 1;

    m_mask.reserve(sideLength * sideLength);
    for (int row = 0; row < sideLength; row++) {
        for (int col = 0; col < sideLength; col++) {
            int squareDistanceFromCenter = Brush::squareMagnitude(col - m_radius, row - m_radius);
            float distance = sqrt(squareDistanceFromCenter);
            int index = row * sideLength + col;
            if (distance < m_radius) {
                m_mask[index] = ((distance * distance) / static_cast<float>(m_radius * m_radius)) - (2.0f / m_radius) * distance + 1;
            } else {
                m_mask[index] = 0;
            }
        }
    }
}


