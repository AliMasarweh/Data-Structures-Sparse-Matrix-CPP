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
class Matrix: public MatrixInterface<T, Matrix<T> >
{
public:

    Matrix(size_t rows, size_t columns);
    Matrix(const Matrix& toCopy);
    Matrix& operator=(const Matrix& toCopy);
    virtual ~Matrix();

    virtual T itemAt(size_t row, size_t col);
    virtual void SetItemAt(size_t row, size_t col, T value);

    virtual MatrixInterface<T, Matrix<T> > &operator+=(const T &val);
    virtual MatrixInterface<T, Matrix<T> > &operator*=(const T &val);
    virtual MatrixInterface<T, Matrix<T> > &operator+=(const MatrixInterface<T, Matrix<T> > &val);
    virtual MatrixInterface<T, Matrix<T> > &operator*=(const MatrixInterface<T, Matrix<T> > &val);
    virtual T &operator[](const Point &point);

protected:
    virtual Matrix<T> add(const T &val) const;
    virtual Matrix<T> add(const MatrixInterface<T, Matrix<T> > &mat) const;
    virtual Matrix<T> mul(const T &val) const;
    virtual Matrix<T> mul(const MatrixInterface<T, Matrix<T> > &mat) const;
    virtual MatrixInterface<T, Matrix<T> > &Transpose() const;
    virtual std::string representMat() const;
    virtual bool equals(const MatrixInterface<T, Matrix<T> > &mat) const;

private:
    size_t m_rows;
    size_t m_columns;
    T* m_mat;
};


template<typename T>
Matrix<T>::Matrix(size_t rows, size_t columns) {

}

template<typename T>
Matrix<T>::Matrix(const Matrix &toCopy) {

}

template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix &toCopy) {
    return <#initializer#>;
}

template<typename T>
Matrix<T>::~Matrix() {

}

template<typename T>
T Matrix<T>::itemAt(size_t row, size_t col) {
    return NULL;
}

template<typename T>
void Matrix<T>::SetItemAt(size_t row, size_t col, T value) {

}

template<typename T>
MatrixInterface<T, Matrix<T> > &Matrix<T>::operator+=(const T &val) {
    return <#initializer#>;
}

template<typename T>
MatrixInterface<T, Matrix<T> > &Matrix<T>::operator*=(const T &val) {
    return <#initializer#>;
}

template<typename T>
MatrixInterface<T, Matrix<T> > &Matrix<T>::operator+=(const MatrixInterface<T, Matrix<T> > &val) {
    return <#initializer#>;
}

template<typename T>
MatrixInterface<T, Matrix<T> > &Matrix<T>::operator*=(const MatrixInterface<T, Matrix<T> > &val) {
    return <#initializer#>;
}

template<typename T>
T &Matrix<T>::operator[](const Point &point) {
    return <#initializer#>;
}

template<typename T>
Matrix<T> Matrix<T>::add(const T &val) const {
    return Matrix<T>();
}

template<typename T>
Matrix<T> Matrix<T>::add(const MatrixInterface<T, Matrix<T> > &mat) const {
    return Matrix<T>();
}

template<typename T>
Matrix<T> Matrix<T>::mul(const T &val) const {
    return Matrix<T>();
}

template<typename T>
Matrix<T> Matrix<T>::mul(const MatrixInterface<T, Matrix<T> > &mat) const {
    return Matrix<T>();
}

template<typename T>
MatrixInterface<T, Matrix<T> > &Matrix<T>::Transpose() const {
    return <#initializer#>;
}

template<typename T>
std::string Matrix<T>::representMat() const {
    return NULL;
}

template<typename T>
bool Matrix<T>::equals(const MatrixInterface<T, Matrix<T> > &mat) const {
    return false;
}

#endif //SPARSEMATRIX_MATRIX_H
