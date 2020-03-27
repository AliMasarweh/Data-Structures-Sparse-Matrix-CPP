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
    virtual const T &operator[](const Point &point) const;
    virtual T &at(const Point &point);

protected:
    virtual Matrix<T> add(T val) const;
    virtual Matrix<T> add(const MatrixInterface<T, Matrix<T> > &mat) const;
    virtual Matrix<T> mul(T val) const;
    virtual Matrix<T> mul(const MatrixInterface<T, Matrix<T> > &mat) const;
    virtual MatrixInterface<T, Matrix<T> > &Transpose();
    virtual std::string representMat() const;
    virtual bool equals(const MatrixInterface<T, Matrix<T> > &mat) const;

private:
    T* m_mat;
};

template <typename T>
class ArrayPointer
{
    friend class Matrix<T>;
    template <typename U>
    friend U operator*(const ArrayPointer<U>& array1, const ArrayPointer<U>& array2);
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, ArrayPointer& arrayPointer);

public:
    ArrayPointer(const MatrixInterface<T, Matrix<T> >& matRef, size_t row, size_t column);
    const T& operator[](const Point &point) const;
    void incrementPointer(size_t size = 1) { (*m_incrementer) += 1; }
    void decrementPointer(size_t size = 1) { *(m_incrementer) -= 1; }

    size_t getRow() const { return m_row; }
    size_t getColumn() const { return m_column; }
    size_t getSize() const { return m_size; }

private:
    const MatrixInterface<T, Matrix<T> >* m_matRef;
    size_t m_row;
    size_t m_column;
    size_t m_size;
    size_t* m_incrementer;
};

// Matrix Definitions

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
        throw IndexingMatrixException();
    }

    return this->m_mat[row*this->m_columns + col];
}

template<typename T>
void Matrix<T>::SetItemAt(size_t row, size_t col, T value)
{
    if(row >= this->m_rows || col > this->m_columns)
    {
        throw IndexingMatrixException();
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
const T &Matrix<T>::operator[](const Point &point) const
{
    size_t row = point.getX(), col = point.getY();
    if(row >= this->m_rows || col > this->m_columns)
    {
        throw IndexingMatrixException();
    }
    return this->m_mat[row*this->m_columns + col];
}


template<typename T>
T &Matrix<T>::at(const Point &point)
{
    size_t row = point.getX(), col = point.getY();
    if(row >= this->m_rows || col > this->m_columns)
    {
        throw IndexingMatrixException();
    }
    return this->m_mat[row*this->m_columns + col];
}

template<typename T>
Matrix<T> Matrix<T>::add(T val) const
{
    Matrix<T> tmp(*this);
    for (int i = 0; i < this->m_rows; ++i)
    {
        for (int j = 0; j < this->m_columns; ++j)
        {
            tmp.at(Point(i, j)) += val;
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
            tmp.at(Point(i, j)) += mat[Point(i, j)];
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
            tmp.at(Point(i, j)) *= val;
        }
    }

    return tmp;
}

template<typename T>
Matrix<T> Matrix<T>::mul(const MatrixInterface<T, Matrix<T> > &mat) const
{
    if(this->m_columns != mat.getRowsNumber())
    {
        throw ShapeMatrixException();
    }

    Matrix<T> ans(this->m_rows, mat.getColumnsNumber());

    for (int i = 0; i < this->m_rows; ++i)
    {
        for (int j = 0; j < mat.getColumnsNumber(); ++j)
        {
            ans.at(Point(i,j)) =
                    ArrayPointer<T>(*this, i, -1) *
                    ArrayPointer<T>(mat, -1, j);
        }
    }

    return ans;
}

template<typename T>
MatrixInterface<T, Matrix<T> > &Matrix<T>::Transpose()
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
    ArrayPointer<T> arrayPointer(*this, 0, -1);
    ss << "[" << arrayPointer;
    for (int i = 1; i < this->m_rows; ++i)
    {
        ArrayPointer<T> arrayPointer(*this, i, -1);
        ss << ", " << arrayPointer;
    }
    ss << "]";

    return ss.str();
}

template<typename T>
bool Matrix<T>::equals(const MatrixInterface<T, Matrix<T> > &mat) const
{
    const Matrix<T>& tmpRef = *this;
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


// ArrayPointer definitions
template<typename T>
ArrayPointer<T>::ArrayPointer(const MatrixInterface<T, Matrix<T> > &matRef, size_t row, size_t column):m_matRef(&matRef)
        ,m_row(row), m_column(column)
{
    if(m_row != -1 && m_column != -1)
        std::cout << "Warning: one argument should be -1 when constructing ArrayPointer,"
                     " assumption now on columns" << std::endl;
    if(m_row == -1)
    {
        m_incrementer = &m_row;
        m_size = matRef.getRowsNumber();
    }
    else
    {
        m_incrementer = &m_column;
        m_size = matRef.getColumnsNumber();
    }

    *m_incrementer = 0;
}

template<typename T>
const T& ArrayPointer<T>::operator[](const Point &point) const
{
    return (*m_matRef)[point];
}

template<typename U>
U operator*(const ArrayPointer<U> &array1, const ArrayPointer<U> &array2)
{
    if(array1.m_size != array2.m_size)
        throw ShapeMatrixException();
    U ans = 0;
    for (int i = 0; i < array1.m_size; ++i)
    {
        ans += array1[Point(array1.m_row, array1.m_column)] *
               array2[Point(array2.m_row, array2.m_column)];
        *(array1.m_incrementer) += 1;
        *(array2.m_incrementer) += 1;
    }

    return ans;
}

template<typename U>
std::ostream& operator<<(std::ostream& os, ArrayPointer<U> &arrayPointer)
{
    os << "[" << arrayPointer[Point(arrayPointer.getRow(), arrayPointer.getColumn())];
    arrayPointer.incrementPointer();

    for (int i = 1; i < arrayPointer.getSize(); ++i)
    {
        os << ", " << arrayPointer[Point(arrayPointer.getRow(), arrayPointer.getColumn())];
        arrayPointer.incrementPointer();
    }
    os << "]";

    return os;
}

#endif //SPARSEMATRIX_MATRIX_H
