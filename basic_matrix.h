//
// Created by ali-masa on 3/27/20.
//

#ifndef SPARSEMATRIX_BASIC_MATRIX_H
#define SPARSEMATRIX_BASIC_MATRIX_H

#include <ostream>
#include "point.h"

template <typename T>
class BasicMatrix
{
    template<typename V>
    friend std::ostream& operator<<(std::ostream& os, const BasicMatrix<V>& mat);
    template<typename V>
    friend bool operator==(const BasicMatrix<V>& mat1, const BasicMatrix<V>& mat2);
    template<typename V>
    friend BasicMatrix<V> operator+(const BasicMatrix<V>& mat1, const BasicMatrix<V>& mat2);
    template<typename V>
    friend BasicMatrix<V> operator*(const BasicMatrix<V>& mat1, const BasicMatrix<V>& mat2);
    template<typename V>
    friend BasicMatrix<V> operator+(const BasicMatrix<V>& mat, V val);
    template<typename V>
    friend BasicMatrix<V> operator*(const BasicMatrix<V>& mat, V val);

public:
    BasicMatrix(size_t rows, size_t columns);
    virtual ~BasicMatrix<T>() {}

    T itemAt(size_t row, size_t col);
    void SetItemAt(size_t row, size_t col, T value);

    BasicMatrix<T>& operator+=(T val);
    BasicMatrix<T>& operator*=(T val);

    BasicMatrix<T>& operator+=(const BasicMatrix<T>& val);
    BasicMatrix<T>& operator*=(const BasicMatrix<T>& val);

    const T& operator[](const Point&) const;
    T& at(const Point&);
    BasicMatrix<T>& Transpose();

    size_t getRowsNumber() const;
    size_t getColumnsNumber() const;

private:
    std::ostream & streamRow(std::ostream &os, size_t row);
    T multiplyRowByColumn(size_t row, BasicMatrix<T>& matrix, size_t column);

    size_t m_rows;
    size_t m_columns;
    T* m_mat;
};

class MatrixException: public std::exception
{
public:
    MatrixException(std::string message): m_message(message) {}
    const char *what() const throw() { return m_message.c_str(); }
    ~MatrixException() throw() {}

private:
    std::string m_message;
};

class IncompatibleShapeMatrixException: public MatrixException
{
public:
    IncompatibleShapeMatrixException(): MatrixException("Incompatible shapes!") {}
};

class ShapeMatrixException: public MatrixException
{
public:
    ShapeMatrixException(): MatrixException("Minimal shape must be (1, 1)!") {}
};

class MatrixIndexingException: public MatrixException
{
public:
    MatrixIndexingException(): MatrixException("Out of bounds point!") {}
};


template<typename T>
std::ostream &BasicMatrix<T>::streamRow(std::ostream &os, size_t row)
{
    os << "[" << this->m_mat[0];
    for (int i = 1; i < this->m_columns; ++i)
    {
        os << ", " << this->m_mat[i];
    }
    os << "]";

    return os;
}

template<typename V>
std::ostream &operator<<(std::ostream &os, const BasicMatrix<V> &mat)
{
    os << "[" << mat.streamRow(0);

    for (int i = 1; i < mat.m_rows; ++i)
    {
        os << mat.streamRow(i);
    }

    os << "]";

    return os;
}

template<typename V>
bool operator==(const BasicMatrix<V> &mat1, const BasicMatrix<V> &mat2)
{
    if(mat1.m_columns != mat2.m_columns || mat1.m_rows != mat2.m_rows)
        return false;

    for (int i = 0; i < mat1.m_rows; ++i)
    {
        for (int j = 0; j < mat1.m_columns; ++j)
        {
            if(mat1[Point(i, j)] != mat2[Point(i, j)])
                return false;
        }
    }

    return true;
}

template<typename V>
BasicMatrix<V> operator+(const BasicMatrix<V> &mat1, const BasicMatrix<V> &mat2)
{
    if(mat1.m_columns != mat2.m_columns || mat1.m_rows != mat2.m_rows)
        throw IncompatibleShapeMatrixException();

    BasicMatrix<V> ans(mat1.m_rows, mat2.m_columns);

    for (int i = 0; i < mat1.m_rows; ++i)
    {
        for (int j = 0; j < mat1.m_columns; ++j)
        {
            ans[Point(i, j)] = mat1[Point(i, j)] + mat2[Point(i, j)];
        }
    }

    return ans;
}

template<typename T>
T BasicMatrix<T>::multiplyRowByColumn(size_t row, BasicMatrix<T>& matrix, size_t column)
{
    T ans = 0;

    BasicMatrix<T>& thisRef = *this;

    for (int i = 0; i < thisRef.m_columns; ++i)
    {
        ans += thisRef[Point(row, i)] * matrix[Point(i, column)];
    }

    return ans;
}

template<typename V>
BasicMatrix<V> operator*(const BasicMatrix<V> &mat1, const BasicMatrix<V> &mat2)
{
    if(mat1.m_columns != mat2.m_rows)
        throw IncompatibleShapeMatrixException();

    BasicMatrix<V> ans(mat1.m_rows, mat2.m_columns);

    for (int i = 0; i < mat1.m_rows; ++i)
    {
        for (int j = 0; j < mat1.m_columns; ++j)
        {
            ans[Point(i, j)] = mat1.multiplyRowByColumn(i, mat2, j);
        }
    }

    return ans;
}

template<typename V>
BasicMatrix<V> operator+(const BasicMatrix<V> &mat, V val)
{
    BasicMatrix<V> ans(mat.m_rows, mat.m_columns);

    for (int i = 0; i < mat.m_rows; ++i)
    {
        for (int j = 0; j < mat.m_columns; ++j)
        {
            ans[Point(i, j)] = mat[Point(i, j)] + val;
        }
    }

    return ans;
}

template<typename V>
BasicMatrix<V> operator*(const BasicMatrix<V> &mat, V val)
{
    BasicMatrix<V> ans(mat.m_rows, mat.m_columns);

    for (int i = 0; i < mat.m_rows; ++i)
    {
        for (int j = 0; j < mat.m_columns; ++j)
        {
            ans[Point(i, j)] = mat[Point(i, j)] * val;
        }
    }

    return ans;
}

template<typename T>
BasicMatrix<T>::BasicMatrix(size_t rows, size_t columns) :m_rows(rows), m_columns(columns),
    m_mat(new T[rows*columns]){}

template<typename T>
T BasicMatrix<T>::itemAt(size_t row, size_t col)
{
    if(row >= m_rows || col >= m_columns)
        throw MatrixIndexingException();
    return this->m_mat[row*m_columns + col];
}

template<typename T>
void BasicMatrix<T>::SetItemAt(size_t row, size_t col, T value)
{
    if(row >= m_rows || col >= m_columns)
        throw MatrixIndexingException();
    this->m_mat[row*m_columns + col] = value;
}

template<typename T>
BasicMatrix<T> &BasicMatrix<T>::operator+=(T val)
{
    *this = *this + val;
    return *this;
}

template<typename T>
BasicMatrix<T> &BasicMatrix<T>::operator*=(T val)
{
    *this = *this * val;
    return *this;
}

template<typename T>
BasicMatrix<T> &BasicMatrix<T>::operator+=(const BasicMatrix<T> &mat)
{
    *this = *this + mat;
    return *this;
}

template<typename T>
BasicMatrix<T> &BasicMatrix<T>::operator*=(const BasicMatrix<T> &mat)
{
    *this = *this * mat;
    return *this;
}

template<typename T>
const T &BasicMatrix<T>::operator[](const Point & p) const {

    if(p.getX() >= m_rows || p.getY() >= m_columns)
        throw MatrixIndexingException();
    return this->m_mat[m_columns*p.getX() + p.getY()];
}

template<typename T>
T &BasicMatrix<T>::at(const Point & p)
{
    if(p.getX() >= m_rows || p.getY() >= m_columns)
        throw MatrixIndexingException();
    return this->m_mat[m_columns*p.getX() + p.getY()];
}

template<typename T>
BasicMatrix<T> &BasicMatrix<T>::Transpose()
{
    size_t tmp = m_rows;
    m_rows = m_columns;
    m_columns = tmp;

    return *this;
}

template<typename T>
size_t BasicMatrix<T>::getRowsNumber() const
{
    return m_rows;
}

template<typename T>
size_t BasicMatrix<T>::getColumnsNumber() const
{
    return m_columns;
}

#endif //SPARSEMATRIX_BASIC_MATRIX_H
