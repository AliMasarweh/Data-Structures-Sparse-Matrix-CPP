//
// Created by ali-masa on 3/26/20.
//

#ifndef SPARSEMATRIX_MATRIX_INTERFACE_H
#define SPARSEMATRIX_MATRIX_INTERFACE_H

#include <cstddef>
#include "point.h"

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

    virtual T& operator[](const Point&) = 0;
    virtual MatrixInterface<T, U>& Transpose() const = 0;

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

class MatrixException: public std::exception
{
public:
    MatrixException(std::string message);
    const char *what() const throw();
    ~MatrixException() throw() {}

private:
    std::string m_message;
};

class ShapeMatrixException: public MatrixException
{
public:
    ShapeMatrixException(): MatrixException("Incompatible shapes!") {}
};

class IndexingMatrixException: public MatrixException
{
public:
    IndexingMatrixException(): MatrixException("Out of bounds point!") {}
};

// MatrixInterface Definitions
template<typename V, typename K>
MatrixInterface<V, K>::MatrixInterface(size_t rows, size_t columns)
: m_rows(rows), m_columns(columns){}

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

// MatrixException Definitions
MatrixException::MatrixException(std::string message): m_message(message){}

const char * MatrixException::what() const throw()
{
    return m_message.c_str();
}

#endif //SPARSEMATRIX_MATRIX_INTERFACE_H
