#include <stdexcept>

#include "matrix.h"

template <typename T>
Matrix<T>::Matrix() : data_(), rows_(), cols_() {} // Конструктор по умолчанию.

template <typename T>
Matrix<T>::Matrix(std::size_t rows) :
    rows_(rows),
    cols_(1) { // Конструктор создающий матрицу размерностью rows x 1.
    data_ = new T* [rows_] {
    };
    for (std::size_t i = 0; i < rows_; ++i)
        data_[i] = new T[cols_] {};
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& m) :
    rows_(m.rows_),
    cols_(m.cols_) { // Конструктор копирования.
    data_ = new T* [rows_] {
    };
    for (std::size_t i = 0; i < rows_; ++i)
        data_[i] = new T[cols_] {};

    for (std::size_t i = 0, j; i < rows_; ++i)
        for (j = 0; j < cols_; ++j)
            data_[i][j] = m.data_[i][j];
}

template <typename T>
Matrix<T>::Matrix(std::size_t rows, std::size_t cols) :
    rows_(rows),
    cols_(cols) { // Конструктор создающий матрицу размерностью rows x cols.
    data_ = new T* [rows_] {
    };
    for (std::size_t i = 0; i < rows_; ++i)
        data_[i] = new T[cols_] {};
}

template <typename T>
Matrix<T>::~Matrix() { // Деструктор, освобождающий выделенную память под эл-ты
                       // матрицы.
    for (std::size_t i = 0; i < rows_; ++i)
        delete[] data_[i];
    delete[] data_;
}

template <typename T>
T& Matrix<T>::operator()(std::size_t row,
                         std::size_t col) { // Возвращает ссылку на элемент
                                            // матрицы под индексом row, col.
    if (row <= 0 || row > rows_ || col <= 0 || col > cols_) {
        throw std::invalid_argument("Index was out of range");
    }

    return data_[row - 1][col - 1];
}

template <typename T>
T Matrix<T>::operator()(std::size_t row, std::size_t col)
    const { // Возвращает копию элемента матрицы под индексом row, col.
    if (row <= 0 || row > rows_ || col <= 0 || col > cols_) {
        throw std::invalid_argument("Index was out of range");
    }

    return data_[row - 1][col - 1];
}

template <typename T>
inline std::size_t Matrix<T>::getRows()
    const { // Возвращает кол-во рядов матрицы.
    return rows_;
}

template <typename T>
inline std::size_t Matrix<T>::getCols()
    const { // Возвращает кол-во столбцов матрицы.
    return cols_;
}

template <typename T>
void Matrix<T>::resize(std::size_t rows,
                       std::size_t cols) { // Изменяет размерность матрицы.
    // Инициализация нового массива размерности rows x cols.
    T** newData = new T* [rows] {
    };
    for (std::size_t i = 0; i < rows; ++i)
        newData[i] = new T[cols] {};

    // Копия элементов из старой матрицы (data_) в новую (newData), которые
    // одновременно существуют как в старой, так и в новой матрицах.
    std::size_t minRows = rows_ < rows ? rows_ : rows;
    std::size_t minCols = cols_ < cols ? cols_ : cols;
    for (std::size_t i = 0, j; i < minRows; ++i)
        for (j = 0; j < minCols; ++j)
            newData[i][j] = data_[i][j];

    // Освобождение старых данных.
    for (std::size_t i = 0; i < rows_; ++i)
        delete[] data_[i];
    delete[] data_;
    data_ = newData; // Присваивание новых данных текущему объекту.

    rows_ = rows;
    cols_ = cols;
}

template <typename T>
std::ostream& operator<<(
    std::ostream& os,
    const Matrix<T>& m) { // Выводит матрицу на консоль в матричном виде.
    std::size_t rows = m.getRows();
    std::size_t cols = m.getCols();
    for (std::size_t i = 1; i <= rows; i++) {
        os << "(";
        for (std::size_t j = 1; j <= cols; j++) {
            if (j != cols)
                os << m(i, j) << '\t';
            else
                os << m(i, j);
        }
        os << ")" << std::endl;
    }

    return os;
}