//
// Created by ali-masa on 3/26/20.
//

#ifndef SPARSEMATRIX_NIAVE_MATRIX_H
#define SPARSEMATRIX_NIAVE_MATRIX_H

#include <cstddef>
#include <string>
#include <sstream>
#include "matrix_interface.h"
#include "basic_matrix.h"

template <typename T>
class NaiveMatrix;

template <typename T>
class IMatrix
{
public:
    typedef MatrixInterface<T, BasicMatrix<T> > type;
};

template <typename T>
class Array;

template <typename T>
class NaiveMatrix: public MatrixInterface<T, BasicMatrix<T> >
{
public:

    NaiveMatrix(size_t rows, size_t columns);
    NaiveMatrix(const BasicMatrix<T>& basicMatrix);
    NaiveMatrix(const NaiveMatrix& toCopy);
    NaiveMatrix& operator=(const NaiveMatrix& toCopy);
    virtual ~NaiveMatrix();

    virtual T itemAt(size_t row, size_t col);
    virtual void SetItemAt(size_t row, size_t col, T value);

    virtual MatrixInterface<T, BasicMatrix<T> > &operator+=(T val);
    virtual MatrixInterface<T, BasicMatrix<T> > &operator*=(T val);
    virtual MatrixInterface<T, BasicMatrix<T> > &operator+=(const MatrixInterface<T, BasicMatrix<T> > &val);
    virtual MatrixInterface<T, BasicMatrix<T> > &operator*=(const MatrixInterface<T, BasicMatrix<T> > &val);
    virtual const T &operator[](const Point &point) const;
    virtual T &at(const Point &point);

    operator BasicMatrix<T>() const;

protected:
    virtual BasicMatrix<T> add(T val) const;
    virtual BasicMatrix<T> add(const MatrixInterface<T, BasicMatrix<T> > &mat) const;
    virtual BasicMatrix<T> mul(T val) const;
    virtual BasicMatrix<T> mul(const MatrixInterface<T, BasicMatrix<T> > &mat) const;
    virtual MatrixInterface<T, BasicMatrix<T> > &Transpose();
    virtual std::string representMat() const;
    virtual bool equals(const MatrixInterface<T, BasicMatrix<T> > &mat) const;

private:
    T* m_mat;
};

template <typename T>
class ArrayPointer
{
    friend class NaiveMatrix<T>;
    template <typename U>
    friend U operator*(const ArrayPointer<U>& array1, const ArrayPointer<U>& array2);
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, ArrayPointer& arrayPointer);

public:
    ArrayPointer(const MatrixInterface<T, BasicMatrix<T> >& matRef, size_t row, size_t column);
    const T& operator[](const Point &point) const;
    void incrementPointer(size_t size = 1) { (*m_incrementer) += 1; }
    void decrementPointer(size_t size = 1) { *(m_incrementer) -= 1; }

    size_t getRow() const { return m_row; }
    size_t getColumn() const { return m_column; }
    size_t getSize() const { return m_size; }

private:
    const MatrixInterface<T, BasicMatrix<T> >* m_matRef;
    size_t m_row;
    size_t m_column;
    size_t m_size;
    size_t* m_incrementer;
};

// NaiveMatrix Definitions

template<typename T>
NaiveMatrix<T>::NaiveMatrix(size_t rows, size_t columns): MatrixInterface<T, BasicMatrix<T> >(rows, columns)
        , m_mat(new T[rows*columns])
{
    size_t cap = this->m_rows * this->m_columns;

    for (int i = 0; i < cap; ++i)
    {
        this->m_mat[i] = 0;
    }
}

template<typename T>
NaiveMatrix<T>::NaiveMatrix(const BasicMatrix<T>& basicMatrix):
    MatrixInterface<T, BasicMatrix<T> >(basicMatrix.getRowsNumber(), basicMatrix.getColumnsNumber()),
    m_mat(new T[this->m_rows * this->m_columns])
{

}

template<typename T>
NaiveMatrix<T>::NaiveMatrix(const NaiveMatrix &toCopy): MatrixInterface<T, BasicMatrix<T> >(toCopy.m_rows, toCopy.m_columns)
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
NaiveMatrix<T> &NaiveMatrix<T>::operator=(const NaiveMatrix &toCopy)
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
NaiveMatrix<T>::~NaiveMatrix()
{
    delete[] this->m_mat;
}

template<typename T>
T NaiveMatrix<T>::itemAt(size_t row, size_t col)
{
    if(row >= this->m_rows || col > this->m_columns)
    {
        throw MatrixIndexingException();
    }

    return this->m_mat[row*this->m_columns + col];
}

template<typename T>
void NaiveMatrix<T>::SetItemAt(size_t row, size_t col, T value)
{
    if(row >= this->m_rows || col > this->m_columns)
    {
        throw MatrixIndexingException();
    }

    this->m_mat[row*this->m_columns + col] = value;
}

template<typename T>
MatrixInterface<T, BasicMatrix<T> > &NaiveMatrix<T>::operator+=(T val)
{
    NaiveMatrix<T> tmp = *this + val;
    *this = tmp;
    return *this;
}

template<typename T>
MatrixInterface<T, BasicMatrix<T> > &NaiveMatrix<T>::operator*=(T val)
{
    NaiveMatrix<T> tmp = *this * val;
    *this = tmp;
    return *this;
}

template<typename T>
MatrixInterface<T, BasicMatrix<T> > &NaiveMatrix<T>::operator+=(const MatrixInterface<T, BasicMatrix<T> > & mat)
{
    NaiveMatrix<T> tmp = *this + mat;
    *this = tmp;
    return *this;
}

template<typename T>
MatrixInterface<T, BasicMatrix<T> > &NaiveMatrix<T>::operator*=(const MatrixInterface<T, BasicMatrix<T> > & mat)
{
    NaiveMatrix<T> tmp = *this * mat;
    *this = tmp;
    return *this;
}

template<typename T>
const T &NaiveMatrix<T>::operator[](const Point &point) const
{
    size_t row = point.getX(), col = point.getY();
    if(row >= this->m_rows || col > this->m_columns)
    {
        throw MatrixIndexingException();
    }
    return this->m_mat[row*this->m_columns + col];
}

template<typename T>
T &NaiveMatrix<T>::at(const Point &point)
{
    size_t row = point.getX(), col = point.getY();
    if(row >= this->m_rows || col > this->m_columns)
    {
        throw MatrixIndexingException();
    }
    return this->m_mat[row*this->m_columns + col];
}

template<typename T>
NaiveMatrix<T>::operator BasicMatrix<T>() const
{
    const NaiveMatrix<T>& thisRef = *this;
    BasicMatrix<T> ans(thisRef.m_rows, thisRef.m_columns);

    for (int i = 0; i < thisRef.m_rows; ++i)
    {
        for (int j = 0; j < thisRef.m_columns; ++j)
        {
            Point p(i, j);
            ans.at(p) = thisRef[p];
        }
    }

    return ans;
}

template<typename T>
BasicMatrix<T> NaiveMatrix<T>::add(T val) const
{
    BasicMatrix<T> tmp(BasicMatrix<T>(*this));
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
BasicMatrix<T> NaiveMatrix<T>::add(const MatrixInterface<T, BasicMatrix<T> > &mat) const
{
    BasicMatrix<T> tmp(BasicMatrix<T>(*this));
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
BasicMatrix<T> NaiveMatrix<T>::mul(T val) const
{
    BasicMatrix<T> tmp(BasicMatrix<T>(*this));
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
BasicMatrix<T> NaiveMatrix<T>::mul(const MatrixInterface<T, BasicMatrix<T> > &mat) const
{
    if(this->m_columns != mat.getRowsNumber())
    {
        throw IncompatibleShapeMatrixException();
    }

    BasicMatrix<T> ans(this->m_rows, mat.getColumnsNumber());

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
MatrixInterface<T, BasicMatrix<T> > &NaiveMatrix<T>::Transpose()
{
    size_t tmp = this->m_rows;
    this->m_rows = this->m_columns;
    this->m_columns = tmp;

    return *this;
}

template<typename T>
std::string NaiveMatrix<T>::representMat() const
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
bool NaiveMatrix<T>::equals(const MatrixInterface<T, BasicMatrix<T> > &mat) const
{
    const NaiveMatrix<T>& tmpRef = *this;
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
ArrayPointer<T>::ArrayPointer(const MatrixInterface<T, BasicMatrix<T> > &matRef, size_t row, size_t column):m_matRef(&matRef)
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
        throw IncompatibleShapeMatrixException();
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

#endif //SPARSEMATRIX_NIAVE_MATRIX_H
