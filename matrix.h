//
// Created by ali-masa on 3/26/20.
//

#ifndef SPARSEMATRIX_MATRIX_H
#define SPARSEMATRIX_MATRIX_H

#include <cstddef>
#include <string>
#include "matrix_interface.h"

template <typename T>
class Matrix;

template <typename T>
using IMatrix = MatrixInterface<T, Matrix<T> >;

template <typename T>
class Matrix: public IMatrix<T>
{
public:

    Matrix(size_t rows, size_t columns);
    Matrix(const Matrix& toCopy);
    Matrix& operator=(const Matrix& toCopy);
    virtual ~Matrix();

    virtual T itemAt(size_t row, size_t col);
    virtual void SetItemAt(size_t row, size_t col, T value);

    virtual IMatrix<T> &operator+=(T val);
    virtual IMatrix<T> &operator*=(T val);
    virtual IMatrix<T> &operator+=(const IMatrix<T> &val);
    virtual IMatrix<T> &operator*=(const IMatrix<T> &val);
    virtual T &operator[](const Point &point);

protected:
    virtual Matrix<T> add(T val) const;
    virtual Matrix<T> add(const IMatrix<T> &mat) const;
    virtual Matrix<T> mul(T val) const;
    virtual Matrix<T> mul(const IMatrix<T> &mat) const;
    virtual IMatrix<T> &Transpose() const;
    virtual std::string representMat() const;
    virtual bool equals(const IMatrix<T> &mat) const;

private:
    size_t m_rows;
    size_t m_columns;
    T* m_mat;
};


template<typename T>
Matrix<T>::Matrix(size_t rows, size_t columns): m_rows(rows), m_columns(columns)
, m_mat(new T[rows*columns])
{
    size_t cap = m_rows * m_columns;

    for (int i = 0; i < cap; ++i)
    {
        m_mat[i] = 0;
    }
}

template<typename T>
Matrix<T>::Matrix(const Matrix &toCopy): m_rows(toCopy.m_rows), m_columns(toCopy.m_columns)
{
    if(this != &toCopy)
    {
        delete[] m_mat;
        size_t cap = m_rows * m_columns;
        m_mat = new T[cap];

        for (int i = 0; i < cap; ++i)
        {
            m_mat[i] = toCopy.m_mat[i];
        }
    }
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix &toCopy)
{
    if(this != &toCopy)
    {
        m_rows = toCopy.m_rows;
        m_columns = toCopy.m_columns;

        delete[] m_mat;
        size_t cap = m_rows * m_columns;
        m_mat = new T[cap];

        for (int i = 0; i < cap; ++i)
        {
            m_mat[i] = toCopy.m_mat[i];
        }
    }

    return *this;
}

template<typename T>
Matrix<T>::~Matrix()
{
    delete[] m_mat;
}

template<typename T>
T Matrix<T>::itemAt(size_t row, size_t col)
{
    if(row >= m_rows || col > m_columns)
    {
        // throw OutOfBounds
    }

    return m_mat[row*m_columns + col];
}

template<typename T>
void Matrix<T>::SetItemAt(size_t row, size_t col, T value)
{
    if(row >= m_rows || col > m_columns)
    {
        // throw OutOfBounds
    }

    m_mat[row*m_columns + col] = value;
}

template<typename T>
IMatrix<T> &Matrix<T>::operator+=(T val)
{
    Matrix<T> tmp = *this + val;
    *this = tmp;
    return *this;
}

template<typename T>
IMatrix<T> &Matrix<T>::operator*=(T val)
{
    Matrix<T> tmp = *this * val;
    *this = tmp;
    return *this;
}

template<typename T>
IMatrix<T> &Matrix<T>::operator+=(const IMatrix<T> & mat)
{
    Matrix<T> tmp = *this + mat;
    *this = tmp;
    return *this;
}

template<typename T>
IMatrix<T> &Matrix<T>::operator*=(const IMatrix<T> & mat)
{
    Matrix<T> tmp = *this * mat;
    *this = tmp;
    return *this;
}

template<typename T>
T &Matrix<T>::operator[](const Point &point)
{
    size_t row = point.getX(), col = point.getY();
    if(row >= m_rows || col > m_columns)
    {
        // throw OutOfBounds
    }
    return m_mat(row*m_columns + col);
}

template<typename T>
Matrix<T> Matrix<T>::add(T val) const
{
    Matrix<T> tmp(*this);
    for (int i = 0; i < m_rows; ++i)
    {
        for (int j = 0; j < m_columns; ++j)
        {
            tmp[Point(i, j)] += val;
        }
    }

    return tmp;
}

template<typename T>
Matrix<T> Matrix<T>::add(const IMatrix<T> &mat) const
{
    Matrix<T> tmp(*this);
    for (int i = 0; i < m_rows; ++i)
    {
        for (int j = 0; j < m_columns; ++j)
        {
            tmp[Point(i, j)] += mat[Point(i, j)];
        }
    }

    return tmp;
}

template<typename T>
Matrix<T> Matrix<T>::mul(T val) const
{
    Matrix<T> tmp(*this);
    for (int i = 0; i < m_rows; ++i)
    {
        for (int j = 0; j < m_columns; ++j)
        {
            tmp[Point(i, j)] *= val;
        }
    }

    return tmp;
}

template<typename T>
Matrix<T> Matrix<T>::mul(const IMatrix<T> &mat) const
{
    return Matrix<T>();
}

template<typename T>
IMatrix<T> &Matrix<T>::Transpose() const
{
    size_t tmp = m_rows;
    m_rows = m_columns;
    m_columns = tmp;

    return *this;
}

template<typename T>
std::string Matrix<T>::representMat() const
{
    return NULL;
}

template<typename T>
bool Matrix<T>::equals(const IMatrix<T> &mat) const
{
    Matrix<T>& tmpRef = *this;
    for (int i = 0; i < m_rows; ++i)
    {
        for (int j = 0; j < m_columns; ++j)
        {
            if(tmpRef[Point(i, j)] != mat[Point(i, j)])
                return false;
        }
    }

    return true;
}

#endif //SPARSEMATRIX_MATRIX_H
