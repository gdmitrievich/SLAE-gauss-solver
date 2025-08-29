#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>
#include <iostream>

template <typename T>
class Matrix;
template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& m);

template <typename T>
class Matrix {
   private:
    T** data_; // Массив элементов матрицы.

    std::size_t rows_; // Кол-во рядов матрицы.
    std::size_t cols_; // Кол-во столбцов матрицы.

   public:
    Matrix();
    explicit Matrix(std::size_t rows);
    Matrix(const Matrix<T>& m);
    Matrix(std::size_t rows, std::size_t cols);
    ~Matrix();

    T& operator=(const Matrix<T>& m) = delete;

    T& operator()(std::size_t row, std::size_t col);
    T operator()(std::size_t row, std::size_t col) const;

    std::size_t getRows() const;
    std::size_t getCols() const;

    void resize(std::size_t rows, std::size_t cols);

    friend std::ostream& operator<< <>(std::ostream& os, const Matrix& m);
};

#include "matrix.ipp"

#endif // !MATRIX_H
