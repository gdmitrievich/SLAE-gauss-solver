#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <locale>

#include "fraction.h"
#include "matrix.h"

using namespace std; // ����������� ������������ ���� std ��� ������� � ��������
                     // �����/������.

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
    setlocale(LC_ALL, "ru"); // ����������� ������� ����������� ��� ������
                             // ������������� �������� � �������.

    int m; // ���-�� ���������.
    int n; // ���-�� �����������.
    std::cout << "������� ���-�� ��������� �������: ";
    std::cin >> m;
    std::cout << "������� ���-�� ����������� �������: ";
    std::cin >> n;


    if (n <= 0 || m <= 0) {
        std::cout << "������� �������� �� ������ ���� ������ ��� ����� ����!"
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
        std::cout << "������ ������� �����������!" << std::endl;
        return 0;
    }

    Matrix<Fraction> solutionColumnMtrx;
    reverseMove(solutionColumnMtrx, initMtrx, freeTermsMtrx, freeUnknownsCols,
                rank);

    cout << "������� �������: " << endl;
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
    cout << "�������� ������� �������� �������������� ���������: " << endl;
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

    // � ������, ����� m > n, ������������� �������, ����� ������� � ������
    // ��������� ���������������� ������, ���� �������� ������� �����
    // �����������.
    int nNotBasisRows = rows - rank;
    int nNotZeroesRows = rows;

    // i < rank, �.�. � ��� ��� ��-���, ����������� ���� ���������� ��-��
    // ������� ���������.
    for (std::size_t i = 1, colIndent; i < rank; ++i) {
        // �������� �� ���� i-�� + colIndent ������ ������� � ���� ���������
        // �������.
        colIndent = 0;

        std::size_t indent;
        while (i + colIndent <= cols && initMtrx(i, i + colIndent) == 0) {
            indent =
                findIndentToNonZeroRowElement(i, rows, colIndent, initMtrx);
            if (indent == 0) {
                ++colIndent;
            } else {
                // ������ ������� ��� � ������� ��������� ��� �������� row, ��
                // ���
                // � ��������� ��������� ��������� ��� �������� row + rowIndent
                // ��� � �������� �������, ��� � � ������� ��������� ������.
                swapMtrxRows(i, i + indent, initMtrx);
                swapMtrxRows(i, i + indent, freeTermsMtrx);
                break;
            }
        }

        // ���� ������� ������� �� ������, ������ ���������� ������
        // ���������������.
        if (i + colIndent > cols)
            return false;

        int n =
            nNotZeroesRows; // ��������� ����� �������� ��� ��-�� ����, �������
                            // �� ���� �������� � ���������� �������.
        for (std::size_t j = i + 1; j <= n; ++j) {
            transformRow(j, i, cols, colIndent, initMtrx, freeTermsMtrx);

            bool isOnlyZeroes =
                isOnlyZeroesOnInitMtrxRow(j, i, cols, colIndent, initMtrx);

            // ���� ��� ��-�� ���� ����� ����, � ������� �
            // ��������� ������� ��� ���� �������� ���� ���, �� �������
            // �����������.
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
    // rowIndent - ���������� �������� �� �������������� �������
    // �������� �������� ������������ ����� �������.
    std::size_t rowIndent = 1;
    // �������� �� row-��� �������, ������� � row + rowIndent ��-�� �������,
    // � ���� ��������� �������.
    while (row + rowIndent <= rows &&
           initMtrx(row + rowIndent, row + colIndent) == 0) {
        ++rowIndent;
    }

    // ���� � ������ ������� ��� ��������� ���������, ��������� �
    // ����������.
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
    // ������� �� ������� ��������, ������������ ��� ������� ����������, ��
    // �������, ������� �� ������� ���������.
    Fraction div =
        initMtrx(row, col + colIndent) / initMtrx(col, col + colIndent);

    // �������� �� ���� ��������� ������ ������� � ��������������� ��.
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

    // ��������� ������ ��-�� ������� ����� �����, ������� ����� ��������� ��
    // ������� �������� �����������.
    std::size_t* basisUnknownsCols = new std::size_t[rank] {};
    // ����������� �� ������� �� ���������� ������������.

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
    // �������� �� ���� �������� �������.
    for (std::size_t i = 1, rowIndent; i <= cols; ++i) {
        // �������� �� ��-��� ������� rowIndent + 2 (+ 2, �.�. ��-� 1-�� �����
        // ������� �� ����� ���� � ������ � ������ ���������� � 1), ���� ��
        // ���������, �������� �� ���� ������� �������� ��� ���.
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
                // ��������� ��������� ����� � ������ ����� (� ������� �������),
                // ����� ����.
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

        // ���� ������ �������� ��������� ����������� �������� ������ ��������
        // ���� i, ������ ��� ��������� �����������.
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
    // ����������, ����� ��� ��������� ����� ��������� �������� ������ 1.
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

    cout << "� ���������� ����������� ��������� ������ � ������ ��������� ���� "
            "���������� ��������� ���������: "
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