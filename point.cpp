//
// Created by ali-masa on 3/26/20.
//

#include "point.h"

Point::Point(size_t x, size_t y): m_x(x), m_y(y) {}

size_t Point::getX() const
{
    return m_x;
}

size_t Point::getY() const
{
    return m_y;
}

void Point::setX(size_t mX)
{
    m_x = mX;
}

void Point::setY(size_t mY)
{
    m_y = mY;
}
