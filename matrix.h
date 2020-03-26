//
// Created by ali-masa on 3/26/20.
//

#ifndef SPARSEMATRIX_MATRIX_H
#define SPARSEMATRIX_MATRIX_H

#include <cstddef>
#include "point.h"

template<typename T, typename U>
class Matrix
{
    template<typename V, typename K>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<V, K>& mat);

    template<typename V, typename K>
    friend bool operator==(const Matrix<T, U>& mat1, const Matrix<V, K>& mat2);

    template<typename V, typename K>
    friend U operator+(const Matrix<T, U>& mat1, const Matrix<V, K>& mat2);

    template<typename V, typename K>
    friend U operator*(const Matrix<T, U>& mat1, const Matrix<V, K>& mat2);

    template<typename V, typename K>
    friend U operator+(const Matrix<T, U>& mat, const V& val);

    template<typename V, typename K>
    friend U operator*(const Matrix<T, U>& mat, const V& val);

public:
    virtual T itemAt(size_t row, size_t col) = 0;
    virtual void SetItemAt(size_t row, size_t col, T value) = 0;

    virtual Matrix<T, U>& operator+=(const T& val) = 0;
    virtual Matrix<T, U>& operator*=(const T& val) = 0;

    virtual Matrix<T, U>& operator+=(const Matrix<T, U>& val) = 0;
    virtual Matrix<T, U>& operator*=(const Matrix<T, U>& val) = 0;

    virtual T& operator[](const Point&) = 0;

protected:
    virtual U add(const T& val) const = 0;
    virtual U add(const Matrix<T, U>& mat) const = 0;
    virtual U mul(const T& val) const = 0;
    virtual U mul(const Matrix<T, U>& mat) const = 0;
    virtual Matrix<T, U>& Transpose() const = 0;
    virtual std::string representMat() const = 0;
    virtual bool equals(const Matrix<T, U>& mat) const = 0;
};

template<typename V, typename K>
K operator*(const Matrix<V, K>& mat, const V & val)
{
    return mat.mul(val);
}

template<typename V, typename K>
K operator+(const Matrix<V, K>& mat, const V & val)
{
    return mat.add(val);
}

template<typename V, typename K>
K operator*(const Matrix<V, K>& mat1, const Matrix<V, K>& mat2)
{
    return mat1.mul(mat2);
}

template<typename V, typename K>
K operator+(const Matrix<V, K>& mat1, const Matrix<V, K>& mat2)
{
    return mat1.add(mat2);
}

template<typename V, typename K>
bool operator==(const Matrix<V, K>& mat1, const Matrix<V, K>& mat2)
{
    return mat1.equals(mat2);
}

template<typename V, typename K>
std::ostream &operator<<(std::ostream &os, const Matrix<V, K>& mat)
{
    os << mat.representMat();
    return os;
}

#endif //SPARSEMATRIX_MATRIX_H
