//
// Created by ali-masa on 3/26/20.
//

#ifndef SPARSEMATRIX_MATRIX_H
#define SPARSEMATRIX_MATRIX_H

#include <ostream>

template <class T>
class MatrixRow;

template <class T>
class Matrix
{
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix);
    friend Matrix<T>& operator+(const Matrix<T>& mat1, const T& scalar);
    friend Matrix<T>& operator*(const Matrix<T>& mat1, const T& scalar);

    friend Matrix<T>& operator+(const Matrix<T>& mat1, const Matrix<T>& mat2);
    friend Matrix<T>& operator*(const Matrix<T>& mat1, const Matrix<T>& mat2);

    friend class MatrixRow<T>;

public:
    Matrix(unsigned short rows, unsigned short columns);
    Matrix(const Matrix& toCopy);
    Matrix<T>& operator=(const Matrix<T>& toAssign);
    /* virtual?? */ ~Matrix();

    MatrixRow<T>& operator[](unsigned short row);
    const T& getElementAt(unsigned short row, unsigned short column) const;
    Matrix<T>& transpose();

private:
    struct Shape
    {
        unsigned short m_rows;
        unsigned short m_columns;
    };

    T* m_array;
    Shape m_shape;
};

template <class T>
class MatrixRow
{
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix);

    friend Matrix<T>& operator+(const MatrixRow<T>& mat1, const MatrixRow<T>& mat2);
    friend Matrix<T>& operator*(const MatrixRow<T>& mat1, const MatrixRow<T>& mat2);
public:
    MatrixRow(Matrix<T>& mat, unsigned short row);
    T& operator[](unsigned short column);
    const T& getElementAt(unsigned short column) const;

private:
    Matrix<T>* m_matRef;
    unsigned short row;
};

#endif //SPARSEMATRIX_MATRIX_H
