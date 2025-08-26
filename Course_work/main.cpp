#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <locale>

#include "fraction.h"
#include "matrix.h"

using namespace std; // Подключение пространства имен std для доступа к объектам
                     // ввода/вывода.

template <typename T>
void initSole(Matrix<T>& initMtrx, Matrix<T>& freeTermsMtrx);
template <typename T>
void printSole(const Matrix<T>& initMtrx, const Matrix<T>& freeTermsMtrx);

template <typename T>
bool forwardMove(Matrix<T>& initMtrx, Matrix<T>& freeTermsMtrx,
                 std::size_t& rank);
template <typename T>
std::size_t findIndentToNonZeroRowElement(std::size_t row, std::size_t rows,
                                          std::size_t colIndent,
                                          Matrix<T>& initMtrx);
template <typename T>
void transformRow(std::size_t row, std::size_t col, std::size_t cols,
                  std::size_t colIndent, Matrix<T>& initMtrx,
                  Matrix<T>& freeTermsMtrx);
template <typename T>
bool isOnlyZeroesOnInitMtrxRow(std::size_t row, std::size_t col,
                               std::size_t cols, std::size_t colIndent,
                               const Matrix<T>& initMtrx);
template <typename T>
void swapMtrxRows(std::size_t row1, std::size_t row2, Matrix<T>& mtrx);

template <typename T>
void reverseMove(Matrix<T>& solutionColumnMtrx, Matrix<T>& initMtrx,
                 Matrix<T>& freeTermsMtrx, std::size_t*& freeUnknownsCols,
                 std::size_t rank);
template <typename T>
void setBasisAndFreeIndexes(std::size_t*& basisUnknownsCols,
                            std::size_t*& freeUnknownsCols,
                            const Matrix<T>& initMtrx);
template <typename T>
void initSolutionColumnMtrx(Matrix<T>& solutionColumnMtrx,
                            const Matrix<T>& initMtrx,
                            const Matrix<T>& freeTermsMtrx,
                            std::size_t resultCols, std::size_t rank,
                            const std::size_t* freeUnknownsCols);
template <typename T>
void evaluateSolutionColumnMtrx(Matrix<T>& solutionColumnMtrx,
                                const Matrix<T>& initMtrx,
                                const std::size_t* basisUnknownsCols,
                                std::size_t rank, std::size_t resultCols);

template <typename T>
void printSolutionColumnMtrx(const Matrix<T>& solutionColumnMtrx,
                             const std::size_t* freeUnknownsCols,
                             std::size_t rank, std::size_t initMtrxCols);

template <typename T>
bool contains(const T* arr, std::size_t size, T value);

template <typename T>
void checkSolution(const Matrix<T>& initMtrx,
                   const Matrix<T>& solutionColumnMtrx,
                   const Matrix<T>& freeTermsMtrx,
                   const std::size_t* freeUnknownsCols, std::size_t rank,
                   std::size_t initMtrxCols);

int main() {
    setlocale(LC_ALL, "ru"); // Подключение русской локализации для вывода
                             // кириллических символов в консоли.

    int m; // Кол-во уравнений.
    int n; // Кол-во неизвестных.
    std::cout << "Введите кол-во уравнений системы: ";
    std::cin >> m;
    std::cout << "Введите кол-во неизвестных системы: ";
    std::cin >> n;


    if (n <= 0 || m <= 0) {
        std::cout << "Входные значения не должны быть меньше или равны нулю!"
                  << std::endl;

        return 0;
    }

    Matrix<Fraction> initMtrx(m, n);
    Matrix<Fraction> freeTermsMtrx(m);

    initSole(initMtrx, freeTermsMtrx);
    printSole(initMtrx, freeTermsMtrx);

    std::size_t* freeUnknownsCols = nullptr;
    std::size_t rank = n < m ? n : m;

    if (!forwardMove(initMtrx, freeTermsMtrx, rank)) {
        std::cout << "Данная система несовместна!" << std::endl;
        return 0;
    }

    Matrix<Fraction> solutionColumnMtrx;
    reverseMove(solutionColumnMtrx, initMtrx, freeTermsMtrx, freeUnknownsCols,
                rank);

    cout << "Столбец решения: " << endl;
    printSolutionColumnMtrx(solutionColumnMtrx, freeUnknownsCols, rank,
                            initMtrx.getCols());

    checkSolution(initMtrx, solutionColumnMtrx, freeTermsMtrx, freeUnknownsCols,
                  rank, initMtrx.getCols());
    delete[] freeUnknownsCols;
    return 0;
}

template <typename T>
void initSole(Matrix<T>& initMtrx, Matrix<T>& freeTermsMtrx) {
    std::size_t rows = initMtrx.getRows();
    std::size_t cols = initMtrx.getCols();
    for (std::size_t i = 1; i <= rows; ++i) {
        for (std::size_t j = 1; j <= cols; ++j) {
            cout << "mtrx[" << i << ", " << j << "] = ";
            cin >> initMtrx(i, j);
        }
        cout << "freeTermsMtrx[" << i << "] = ";
        cin >> freeTermsMtrx(i, 1);
    }
}

template <typename T>
void printSole(const Matrix<T>& initMtrx, const Matrix<T>& freeTermsMtrx) {
    cout << "Исходная система линейных алгебраических уравнений: " << endl;
    std::size_t rows = initMtrx.getRows();
    std::size_t cols = initMtrx.getCols();
    for (std::size_t i = 1, j; i <= rows; ++i) {
        bool isFirstNonZeroElem = true;
        for (j = 1; j <= cols; ++j) {
            if (initMtrx(i, j) == 0)
                continue;

            if (isFirstNonZeroElem) {
                cout << initMtrx(i, j);
            } else {
                cout << (initMtrx(i, j) > 0 ? " + " : " - ")
                     << (initMtrx(i, j) > 0 ? initMtrx(i, j) : -initMtrx(i, j));
            }

            cout << 'x' << j;
            isFirstNonZeroElem = false;
        }

        if (isFirstNonZeroElem)
            cout << "0 = " << freeTermsMtrx(i, 1) << endl;
        else
            cout << " = " << freeTermsMtrx(i, 1) << endl;
    }
}

template <typename T>
bool forwardMove(Matrix<T>& initMtrx, Matrix<T>& freeTermsMtrx,
                 std::size_t& rank) {
    std::size_t rows = initMtrx.getRows();
    std::size_t cols = initMtrx.getCols();

    // В случае, когда m > n, устанавливает границу, после которой в случае
    // обнуления пропорциональной строки, ранг исходной матрицы будет
    // уменьшаться.
    int nNotBasisRows = rows - rank;
    int nNotZeroesRows = rows;

    // i < rank, Т.к. у нас нет эл-тов, находящихся ниже последнего эл-та
    // главной диагонали.
    for (std::size_t i = 1, colIndent; i < rank; ++i) {
        // Проходит по всей i-ой + colIndent строке матрицы и ищет ненулевой
        // элемент.
        colIndent = 0;

        std::size_t indent;
        while (i + colIndent <= cols && initMtrx(i, i + colIndent) == 0) {
            indent =
                findIndentToNonZeroRowElement(i, rows, colIndent, initMtrx);
            if (indent == 0) {
                ++colIndent;
            } else {
                // Меняем местами ряд с нулевым элементом под индексом row, на
                // ряд
                // с найденным ненулевым элементом под инедксом row + rowIndent
                // как в исходной матрице, так и в матрице свободных членов.
                swapMtrxRows(i, i + indent, initMtrx);
                swapMtrxRows(i, i + indent, freeTermsMtrx);
                break;
            }
        }

        // Если нулевой элемент не найден, значит оставшиеся строки
        // пропорциональны.
        if (i + colIndent > cols)
            return false;

        int n =
            nNotZeroesRows; // позволяет циклу обнулить все эл-ты ряда, которые
                            // не были обнулены в предыдущем столбце.
        for (std::size_t j = i + 1; j <= n; ++j) {
            transformRow(j, i, cols, colIndent, initMtrx, freeTermsMtrx);

            bool isOnlyZeroes =
                isOnlyZeroesOnInitMtrxRow(j, i, cols, colIndent, initMtrx);

            // Если все эл-ты ряда равны нулю, а элемент в
            // свободной матрице под этим индексом ряда нет, то система
            // несовместна.
            if (isOnlyZeroes && freeTermsMtrx(j, 1) != 0)
                return false;
            else if (isOnlyZeroes) {
                if (nNotZeroesRows == rank)
                    --rank;
                --nNotZeroesRows;
            }
        }
    }

    return true;
}

template <typename T>
std::size_t findIndentToNonZeroRowElement(std::size_t row, std::size_t rows,
                                          std::size_t colIndent,
                                          Matrix<T>& initMtrx) {
    // rowIndent - определяет смещение от первоначальной позиции
    // текущего элемента относительно строк матрицы.
    std::size_t rowIndent = 1;
    // Проходит по row-ому столбцу, начиная с row + rowIndent эл-та матрицы,
    // и ищет ненулевой элемент.
    while (row + rowIndent <= rows &&
           initMtrx(row + rowIndent, row + colIndent) == 0) {
        ++rowIndent;
    }

    // Если в данном столбце нет ненулевых элементов, переходим к
    // следующему.
    if (row + rowIndent > rows) {
        return 0;
    } else {
        return rowIndent;
    }
}

template <typename T>
void transformRow(std::size_t row, std::size_t col, std::size_t cols,
                  std::size_t colIndent, Matrix<T>& initMtrx,
                  Matrix<T>& freeTermsMtrx) {
    // Частное от деления элемента, находящегося под главной диагональю, на
    // элемент, стоящий на главной диагонали.
    Fraction div =
        initMtrx(row, col + colIndent) / initMtrx(col, col + colIndent);

    // Проходит по всем элементам строки матрицы и преобразовывает ее.
    for (std::size_t i = col + colIndent; i <= cols; ++i)
        initMtrx(row, i) = initMtrx(row, i) - div * initMtrx(col, i);

    freeTermsMtrx(row, 1) = freeTermsMtrx(row, 1) - div * freeTermsMtrx(col, 1);
}

template <typename T>
bool isOnlyZeroesOnInitMtrxRow(std::size_t row, std::size_t col,
                               std::size_t cols, std::size_t colIndent,
                               const Matrix<T>& initMtrx) {
    bool isOnlyZeroes = true;
    for (std::size_t i = col + colIndent; i <= cols; ++i) {
        if (initMtrx(row, i) != 0)
            isOnlyZeroes = false;
    }

    return isOnlyZeroes;
}

template <typename T>
void swapMtrxRows(std::size_t row1, std::size_t row2, Matrix<T>& mtrx) {
    Fraction tmp;
    std::size_t cols = mtrx.getCols();
    for (std::size_t i = 1; i <= cols; ++i) {
        tmp = mtrx(row1, i);
        mtrx(row1, i) = mtrx(row2, i);
        mtrx(row2, i) = tmp;
    }
}

template <typename T>
void reverseMove(Matrix<T>& solutionColumnMtrx, Matrix<T>& initMtrx,
                 Matrix<T>& freeTermsMtrx, std::size_t*& freeUnknownsCols,
                 std::size_t rank) {
    std::size_t rows = initMtrx.getRows();
    std::size_t cols = initMtrx.getCols();

    // Заполняем нулями эл-ты массива целых чисел, которые будут указывать на
    // столбцы базисных неизвестных.
    std::size_t* basisUnknownsCols = new std::size_t[rank] {};
    // Указательна на столбцы со свободными неизвестными.

    if (cols - rank != 0) {
        freeUnknownsCols = new std::size_t[cols - rank];
    }

    setBasisAndFreeIndexes(basisUnknownsCols, freeUnknownsCols, initMtrx);

    std::size_t resultCols = cols - rank + 1;
    initSolutionColumnMtrx(solutionColumnMtrx, initMtrx, freeTermsMtrx, rank,
                           resultCols, freeUnknownsCols);

    evaluateSolutionColumnMtrx(solutionColumnMtrx, initMtrx, basisUnknownsCols,
                               rank, resultCols);

    delete[] basisUnknownsCols;
}

template <typename T>
void setBasisAndFreeIndexes(std::size_t*& basisUnknownsCols,
                            std::size_t*& freeUnknownsCols,
                            const Matrix<T>& initMtrx) {
    std::size_t rows = initMtrx.getRows();
    std::size_t cols = initMtrx.getCols();
    std::size_t position = 0;
    // Проходит по всем столбцам матрицы.
    for (std::size_t i = 1, rowIndent; i <= cols; ++i) {
        // Проходит по эл-там столбца rowIndent + 2 (+ 2, т.к. эл-т 1-ой строк
        // матрицы не равен нулю и отсчет у матриц начинается с 1), пока не
        // установит, является ли этот столбец базисным или нет.
        rowIndent = 0;
        while (rowIndent + 2 <= rows && initMtrx(rowIndent + 2, i) != 0) {
            ++rowIndent;
        }

        if (basisUnknownsCols[rowIndent] == 0)
            basisUnknownsCols[rowIndent] = i;
        else
            freeUnknownsCols[position++] = i;
    }
}

template <typename T>
void initSolutionColumnMtrx(Matrix<T>& solutionColumnMtrx,
                            const Matrix<T>& initMtrx,
                            const Matrix<T>& freeTermsMtrx, std::size_t rank,
                            std::size_t resultCols,
                            const std::size_t* freeUnknownsCols) {
    solutionColumnMtrx.resize(rank, resultCols);
    for (std::size_t i = 1; i <= rank; ++i) {
        for (std::size_t j = 1; j <= resultCols; ++j) {
            if (j != resultCols)
                // Переносим свободные члены в правую часть (в матрицу решения),
                // меняя знак.
                solutionColumnMtrx(i, j) =
                    -initMtrx(i, freeUnknownsCols[j - 1]);
            else
                solutionColumnMtrx(i, j) = freeTermsMtrx(i, 1);
        }
    }
}

template <typename T>
void evaluateSolutionColumnMtrx(Matrix<T>& solutionColumnMtrx,
                                const Matrix<T>& initMtrx,
                                const std::size_t* basisUnknownsCols,
                                std::size_t rank, std::size_t resultCols) {
    for (std::size_t i = rank; i >= 1; --i) {
        for (std::size_t j = 1; j <= rank - i + 1; ++j) {
            for (std::size_t k = 1; k <= resultCols; ++k) {
                if (rank - j + 1 != i) {
                    solutionColumnMtrx(i, k) =
                        solutionColumnMtrx(i, k) -
                        initMtrx(i, basisUnknownsCols[rank - j]) *
                            solutionColumnMtrx(rank - j + 1, k);
                } else {
                    solutionColumnMtrx(i, k) =
                        solutionColumnMtrx(i, k) /
                        initMtrx(i, basisUnknownsCols[rank - j]);
                }
            }
        }
    }
}

template <typename T>
void printSolutionColumnMtrx(const Matrix<T>& solutionColumnMtrx,
                             const std::size_t* freeUnknownsCols,
                             std::size_t rank, std::size_t initMtrxCols) {
    std::size_t rows = solutionColumnMtrx.getRows();
    std::size_t cols = solutionColumnMtrx.getCols();
    std::size_t basisUnknownIdx = 1;
    std::size_t freeUnknownIdx = 0;

    for (std::size_t i = 1, j; i <= initMtrxCols; ++i) {
        cout << '(' << 'x' << i << ')';
        if (i !=
            (initMtrxCols % 2 == 0 ? initMtrxCols / 2 : initMtrxCols / 2 + 1))
            cout << "   (";
        else
            cout << " = (";

        // Если массив индексов свободных неизвестных содержит индекс текущего
        // ряда i, значит это свободная неизвестная.
        if (contains(freeUnknownsCols, initMtrxCols - rank, i)) {
            cout << 'z' << freeUnknownsCols[freeUnknownIdx++] << ')' << endl;
            continue;
        }

        bool isFirstNonZeroElem = true;
        for (j = 1; j <= cols; ++j) {
            if (solutionColumnMtrx(basisUnknownIdx, j) == 0)
                continue;

            if (isFirstNonZeroElem) {
                cout << solutionColumnMtrx(basisUnknownIdx, j);
            } else {
                cout << (solutionColumnMtrx(basisUnknownIdx, j) > 0 ? " + " :
                                                                      " - ")
                     << (solutionColumnMtrx(basisUnknownIdx, j) > 0 ?
                             solutionColumnMtrx(basisUnknownIdx, j) :
                             -solutionColumnMtrx(basisUnknownIdx, j));
            }

            if (j != cols)
                cout << 'z' << freeUnknownsCols[j - 1];
            isFirstNonZeroElem = false;
        }

        basisUnknownIdx++;
        cout << ')' << endl;
    }
}

template <typename T>
void checkSolution(const Matrix<T>& initMtrx,
                   const Matrix<T>& solutionColumnMtrx,
                   const Matrix<T>& freeTermsMtrx,
                   const std::size_t* freeUnknownsCols, std::size_t rank,
                   std::size_t initMtrxCols) {
    std::size_t initCols = initMtrx.getCols();
    std::size_t resultCols = solutionColumnMtrx.getCols();

    std::size_t basisUnknownIdx = 1;
    Fraction sum = 0;
    // Представим, будто все свободные члены принимают значение равное 1.
    for (std::size_t i = 1; i <= initCols; ++i) {
        if (contains(freeUnknownsCols, initMtrxCols - rank, i)) {
            sum = sum + initMtrx(1, i);
            continue;
        }

        for (std::size_t j = 1; j <= resultCols; ++j) {
            sum = sum + initMtrx(1, i) * solutionColumnMtrx(basisUnknownIdx, j);
        }
        basisUnknownIdx++;
    }

    cout << "В результате подстановки свободных членов в первое уравнение СЛАУ "
            "получилось следующее тождество: "
         << sum << " = " << freeTermsMtrx(1, 1) << endl;
}

template <typename T>
bool contains(const T* arr, std::size_t size, T value) {
    for (std::size_t i = 0; i < size; ++i) {
        if (arr[i] == value)
            return true;
    }

    return false;
}