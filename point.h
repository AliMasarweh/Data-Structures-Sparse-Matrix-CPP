//
// Created by ali-masa on 3/26/20.
//

#ifndef SPARSEMATRIX_POINT_H
#define SPARSEMATRIX_POINT_H


#include <cstddef>

class Point
{
public:
    Point(size_t x, size_t y);

    size_t getX() const;
    size_t getY() const;
    void setX(size_t mX);
    void setY(size_t mY);

private:
    size_t m_x;
    size_t m_y;
};


#endif //SPARSEMATRIX_POINT_H
