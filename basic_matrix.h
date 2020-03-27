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
    friend V operator+(const BasicMatrix<V>& mat1, const BasicMatrix<V>& mat2);
    template<typename V>
    friend V operator*(const BasicMatrix<V>& mat1, const BasicMatrix<V>& mat2);
    template<typename V>
    friend V operator+(const BasicMatrix<V>& mat, V val);
    template<typename V>
    friend V operator*(const BasicMatrix<V>& mat, V val);

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
    size_t m_rows;
    size_t m_columns;
    T* m_mat;
};

template<typename V>
std::ostream &operator<<(std::ostream &os, const BasicMatrix<V> &mat) {
    return os;
}

template<typename V>
bool operator==(const BasicMatrix<V> &mat1, const BasicMatrix<V> &mat2) {
    return 0;
}

template<typename V>
V operator+(const BasicMatrix<V> &mat1, const BasicMatrix<V> &mat2) {
    return NULL;
}

template<typename V>
V operator*(const BasicMatrix<V> &mat1, const BasicMatrix<V> &mat2) {
    return NULL;
}

template<typename V>
V operator+(const BasicMatrix<V> &mat, V val) {
    return NULL;
}

template<typename V>
V operator*(const BasicMatrix<V> &mat, V val) {
    return NULL;
}

template<typename T>
BasicMatrix<T>::BasicMatrix(size_t rows, size_t columns) {

}

template<typename T>
T BasicMatrix<T>::itemAt(size_t row, size_t col) {
    return NULL;
}

template<typename T>
void BasicMatrix<T>::SetItemAt(size_t row, size_t col, T value) {

}

template<typename T>
BasicMatrix<T> &BasicMatrix<T>::operator+=(T val) {
    return *this;
}

template<typename T>
BasicMatrix<T> &BasicMatrix<T>::operator*=(T val) {
    return *this;
}

template<typename T>
BasicMatrix<T> &BasicMatrix<T>::operator+=(const BasicMatrix<T> &val) {
    return *this;
}

template<typename T>
BasicMatrix<T> &BasicMatrix<T>::operator*=(const BasicMatrix<T> &val) {
    return *this;
}

template<typename T>
const T &BasicMatrix<T>::operator[](const Point &) const {
    return T();
}

template<typename T>
T &BasicMatrix<T>::at(const Point &) {
    return T();
}

template<typename T>
BasicMatrix<T> &BasicMatrix<T>::Transpose() {
    return *this;
}

template<typename T>
size_t BasicMatrix<T>::getRowsNumber() const {
    return 0;
}

template<typename T>
size_t BasicMatrix<T>::getColumnsNumber() const {
    return 0;
}

#endif //SPARSEMATRIX_BASIC_MATRIX_H
