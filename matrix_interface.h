//
// Created by ali-masa on 3/26/20.
//

#ifndef SPARSEMATRIX_MATRIX_INTERFACE_H
#define SPARSEMATRIX_MATRIX_INTERFACE_H

#include <cstddef>
#include "point.h"
#include "basic_matrix.h"

template<typename T, typename U>
class MatrixInterface
{
    template<typename V, typename K>
    friend std::ostream& operator<<(std::ostream& os, const MatrixInterface<V, K>& mat);
    template<typename V, typename K>
    friend bool operator==(const MatrixInterface<V, K>& mat1, const MatrixInterface<V, K>& mat2);
    template<typename V, typename K>
    friend K operator+(const MatrixInterface<V, K>& mat1, const MatrixInterface<V, K>& mat2);
    template<typename V, typename K>
    friend K operator*(const MatrixInterface<V, K>& mat1, const MatrixInterface<V, K>& mat2);
    template<typename V, typename K>
    friend K operator+(const MatrixInterface<V, K>& mat, V val);
    template<typename V, typename K>
    friend K operator*(const MatrixInterface<V, K>& mat, V val);

public:
    MatrixInterface(size_t rows, size_t columns);
    virtual ~MatrixInterface<T, U>() {}

    virtual T itemAt(size_t row, size_t col) = 0;
    virtual void SetItemAt(size_t row, size_t col, T value) = 0;

    virtual MatrixInterface<T, U>& operator+=(T val) = 0;
    virtual MatrixInterface<T, U>& operator*=(T val) = 0;

    virtual MatrixInterface<T, U>& operator+=(const MatrixInterface<T, U>& val) = 0;
    virtual MatrixInterface<T, U>& operator*=(const MatrixInterface<T, U>& val) = 0;

    virtual const T& operator[](const Point&) const = 0;
    virtual T& at(const Point&) = 0;
    virtual MatrixInterface<T, U>& Transpose() = 0;

    virtual operator BasicMatrix<T>() const = 0;

    size_t getRowsNumber() const;
    size_t getColumnsNumber() const;

protected:
    virtual U add(T val) const = 0;
    virtual U add(const MatrixInterface<T, U>& mat) const = 0;
    virtual U mul(T val) const = 0;
    virtual U mul(const MatrixInterface<T, U>& mat) const = 0;
    virtual std::string representMat() const = 0;
    virtual bool equals(const MatrixInterface<T, U>& mat) const = 0;

    size_t m_rows;
    size_t m_columns;
};

// MatrixInterface Definitions
template<typename V, typename K>
MatrixInterface<V, K>::MatrixInterface(size_t rows, size_t columns)
: m_rows(rows), m_columns(columns)
{
    if(m_rows == 0 || m_columns == 0)
        throw ShapeMatrixException();
}

template<typename V, typename K>
K operator*(const MatrixInterface<V, K>& mat, V val)
{
    return mat.mul(val);
}

template<typename V, typename K>
K operator+(const MatrixInterface<V, K>& mat, V val)
{
    return mat.add(val);
}

template<typename V, typename K>
K operator*(const MatrixInterface<V, K>& mat1, const MatrixInterface<V, K>& mat2)
{
    return mat1.mul(mat2);
}

template<typename V, typename K>
K operator+(const MatrixInterface<V, K>& mat1, const MatrixInterface<V, K>& mat2)
{
    return mat1.add(mat2);
}

template<typename V, typename K>
bool operator==(const MatrixInterface<V, K>& mat1, const MatrixInterface<V, K>& mat2)
{
    return mat1.equals(mat2);
}

template<typename V, typename K>
std::ostream &operator<<(std::ostream &os, const MatrixInterface<V, K>& mat)
{
    os << mat.representMat();
    return os;
}

template<typename T, typename U>
size_t MatrixInterface<T, U>::getRowsNumber() const 
{
    return m_rows;
}

template<typename T, typename U>
size_t MatrixInterface<T, U>::getColumnsNumber() const 
{
    return m_columns;
}

#endif //SPARSEMATRIX_MATRIX_INTERFACE_H
