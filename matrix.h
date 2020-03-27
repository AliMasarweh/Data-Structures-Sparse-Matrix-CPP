//
// Created by ali-masa on 3/26/20.
//

#ifndef SPARSEMATRIX_MATRIX_H
#define SPARSEMATRIX_MATRIX_H

#include <cstddef>
#include <string>
#include <sstream>
#include "matrix_interface.h"

template <typename T>
class Matrix;

template <typename T>
class IMatrix
{
public:
    typedef MatrixInterface<T, Matrix<T> > type;
};

template <typename T>
class Array;

template <typename T>
class Matrix: public MatrixInterface<T, Matrix<T> >
{
public:

    Matrix(size_t rows, size_t columns);
    Matrix(const Matrix& toCopy);
    Matrix& operator=(const Matrix& toCopy);
    virtual ~Matrix();

    virtual T itemAt(size_t row, size_t col);
    virtual void SetItemAt(size_t row, size_t col, T value);

    virtual MatrixInterface<T, Matrix<T> > &operator+=(T val);
    virtual MatrixInterface<T, Matrix<T> > &operator*=(T val);
    virtual MatrixInterface<T, Matrix<T> > &operator+=(const MatrixInterface<T, Matrix<T> > &val);
    virtual MatrixInterface<T, Matrix<T> > &operator*=(const MatrixInterface<T, Matrix<T> > &val);
    virtual T &operator[](const Point &point);

protected:
    virtual Matrix<T> add(T val) const;
    virtual Matrix<T> add(const MatrixInterface<T, Matrix<T> > &mat) const;
    virtual Matrix<T> mul(T val) const;
    virtual Matrix<T> mul(const MatrixInterface<T, Matrix<T> > &mat) const;
    virtual MatrixInterface<T, Matrix<T> > &Transpose() const;
    virtual std::string representMat() const;
    virtual bool equals(const MatrixInterface<T, Matrix<T> > &mat) const;

private:
    T* m_mat;
};

template <typename T>
class PointerArray
{
    friend class Matrix<T>;
    template <typename U>
    friend U operator*(const PointerArray<U>& array1, const PointerArray<U>& array2);

public:
    PointerArray(MatrixInterface<T, Matrix<T> >& matRef, size_t row, size_t column);

private:
    MatrixInterface<T, Matrix<T> >* m_matRef;
    size_t m_row;
    size_t m_column;
    size_t m_size;
    size_t* m_incrementer;
};


template<typename T>
PointerArray<T>::PointerArray(MatrixInterface<T, Matrix<T>> &matRef, size_t row, size_t column):m_matRef(&matRef)
    ,m_row(row), m_column(column)
{
    if(m_row != -1 && m_column != -1)
        std::cout << "Warning: one argument should be -1 when constructing PointerArray,"
                     " assumption now on columns" << std::endl;
    if(m_row == -1)
    {
        m_incrementer = &m_row;
        m_size = matRef.m_rows;
    }
    else
    {
        m_incrementer = &m_column;
        m_size = matRef.m_columns;
    }

    *m_incrementer = 0;
}

template<typename U>
U operator*(const PointerArray<U> &array1, const PointerArray<U> &array2)
{
    if(array1.m_size != array2.m_size)
        throw -1; // shape error
    U ans = 0;
    for (int i = 0; i < array1.m_size; ++i)
    {
        ans += array1.m_matRef[Point(array1.m_row, array1.m_column)] *
                array2.m_matRef[Point(array2.m_row, array2.m_column)];
        *(array1.m_incrementer) += 1;
        *(array2.m_incrementer) += 1;
    }

    return ans;
}


template<typename T>
Matrix<T>::Matrix(size_t rows, size_t columns): MatrixInterface<T, Matrix<T> >(rows, columns)
        , m_mat(new T[rows*columns])
{
    size_t cap = this->m_rows * this->m_columns;

    for (int i = 0; i < cap; ++i)
    {
        this->m_mat[i] = 0;
    }
}

template<typename T>
Matrix<T>::Matrix(const Matrix &toCopy): MatrixInterface<T, Matrix<T> >(toCopy.m_rows, toCopy.m_columns)
        , m_mat(new T[this->m_rows*this->m_columns])
{

    delete[] this->m_mat;
    size_t cap = this->m_rows * this->m_columns;
    this->m_mat = new T[cap];

    for (int i = 0; i < cap; ++i)
    {
        this->m_mat[i] = toCopy.m_mat[i];
    }
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix &toCopy)
{
    if(this != &toCopy)
    {
        this->m_rows = toCopy.m_rows;
        this->m_columns = toCopy.m_columns;

        delete[] this->m_mat;
        size_t cap = this->m_rows * this->m_columns;
        this->m_mat = new T[cap];

        for (int i = 0; i < cap; ++i)
        {
            this->m_mat[i] = toCopy.m_mat[i];
        }
    }

    return *this;
}

template<typename T>
Matrix<T>::~Matrix()
{
    delete[] this->m_mat;
}

template<typename T>
T Matrix<T>::itemAt(size_t row, size_t col)
{
    if(row >= this->m_rows || col > this->m_columns)
    {
        // throw OutOfBounds
    }

    return this->m_mat[row*this->m_columns + col];
}

template<typename T>
void Matrix<T>::SetItemAt(size_t row, size_t col, T value)
{
    if(row >= this->m_rows || col > this->m_columns)
    {
        // throw OutOfBounds
    }

    this->m_mat[row*this->m_columns + col] = value;
}

template<typename T>
MatrixInterface<T, Matrix<T> > &Matrix<T>::operator+=(T val)
{
    Matrix<T> tmp = *this + val;
    *this = tmp;
    return *this;
}

template<typename T>
MatrixInterface<T, Matrix<T> > &Matrix<T>::operator*=(T val)
{
    Matrix<T> tmp = *this * val;
    *this = tmp;
    return *this;
}

template<typename T>
MatrixInterface<T, Matrix<T> > &Matrix<T>::operator+=(const MatrixInterface<T, Matrix<T> > & mat)
{
    Matrix<T> tmp = *this + mat;
    *this = tmp;
    return *this;
}

template<typename T>
MatrixInterface<T, Matrix<T> > &Matrix<T>::operator*=(const MatrixInterface<T, Matrix<T> > & mat)
{
    Matrix<T> tmp = *this * mat;
    *this = tmp;
    return *this;
}

template<typename T>
T &Matrix<T>::operator[](const Point &point)
{
    size_t row = point.getX(), col = point.getY();
    if(row >= this->m_rows || col > this->m_columns)
    {
        // throw OutOfBounds
    }
    return this->m_mat(row*this->m_columns + col);
}

template<typename T>
Matrix<T> Matrix<T>::add(T val) const
{
    Matrix<T> tmp(*this);
    for (int i = 0; i < this->m_rows; ++i)
    {
        for (int j = 0; j < this->m_columns; ++j)
        {
            tmp[Point(i, j)] += val;
        }
    }

    return tmp;
}

template<typename T>
Matrix<T> Matrix<T>::add(const MatrixInterface<T, Matrix<T> > &mat) const
{
    Matrix<T> tmp(*this);
    for (int i = 0; i < this->m_rows; ++i)
    {
        for (int j = 0; j < this->m_columns; ++j)
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
    for (int i = 0; i < this->m_rows; ++i)
    {
        for (int j = 0; j < this->m_columns; ++j)
        {
            tmp[Point(i, j)] *= val;
        }
    }

    return tmp;
}

template<typename T>
Matrix<T> Matrix<T>::mul(const MatrixInterface<T, Matrix<T> > &mat) const
{
    if(this->m_columns != mat.m_rows)
    {
        // Shape error
    }

    Matrix<T> ans(this->m_rows, mat.m_columns);

    for (int i = 0; i < this->m_rows; ++i)
    {
        for (int j = 0; j < mat.m_columns; ++j)
        {
            ans[Point(i,j)] =
                    ArrayPointer<T>(*this, i, -1) *
                    ArrayPointer<T>(mat, -1, j);
        }
    }

    return ans;
}

template<typename T>
MatrixInterface<T, Matrix<T> > &Matrix<T>::Transpose() const
{
    size_t tmp = this->m_rows;
    this->m_rows = this->m_columns;
    this->m_columns = tmp;

    return *this;
}

template<typename T>
std::string Matrix<T>::representMat() const
{
    std::stringstream ss;
    ss << "[" << this->row(0);
    for (int i = 1; i < this->m_rows; ++i)
    {
        ss << ", " << this->row(i);
    }
    ss << "]";

    return ss.str();
}

template<typename T>
bool Matrix<T>::equals(const MatrixInterface<T, Matrix<T> > &mat) const
{
    Matrix<T>& tmpRef = *this;
    for (int i = 0; i < this->m_rows; ++i)
    {
        for (int j = 0; j < this->m_columns; ++j)
        {
            if(tmpRef[Point(i, j)] != mat[Point(i, j)])
                return false;
        }
    }

    return true;
}

#endif //SPARSEMATRIX_MATRIX_H
