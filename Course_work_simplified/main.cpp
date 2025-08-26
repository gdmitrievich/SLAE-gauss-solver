#include <Windows.h>

#include <cstdlib>
#include <iostream>
#include <locale>

using namespace std; // Подключение пространства имен std для доступа к объектам
// ввода/вывода.

/// <summary>
/// Устанавливает кол-во рядов и столбцов исходной матрицы.
/// </summary>
void initRowsCols();

/// <summary>
/// Выделяет память для матрицы размерностью rows × cols.
/// </summary>
/// <param name="mtrx">Матрица, для которой необходимо выделить память. Передается по ссылке для инициализации указателя, передаваемого данной функции</param>
/// <param name="rows">Кол-во рядов для выделения</param>
/// <param name="cols">Кол-во столбцов для выделения</param>
void allocateMtrxMemory(double**& mtrx, int rows, int cols);

/// <summary>
/// Освобождает память, выделенную под матрицы.
/// </summary>
/// <param name="mtrx">Матрица, память которой необходимо освободить.</param>
/// <param name="rows">Кол-во рядов в mtrx</param>
void freeMtrxMemory(double**& mtrx, int rows);

/// <summary>
/// Округляет входящее число с плавающей точкой по правилам
/// математики до n-го количества знаков после запятой. Округляет до целого, если передается только один аргумент.
/// </summary>
/// <param name="v">Значение, которое необходимо округлить</param>
/// <param name="p">Кол-во знаков после запятой - определяет точность округления</param>
/// <returns>Возвращает округленное число</returns>
double round(double v, int p = 0);

/// <summary>
/// Проверяет, содержится ли в массиве arr размера size число value. 
/// </summary>
/// <param name="arr">Массив, в котором выполняется поиск. Спецификатор const указывает на то, что данный массив не будет меняться в теле функции.</param>
/// <param name="size">Размер массива arr</param>
/// <param name="value">Значение, которое проверятся на наличие в arr</param>
/// <returns></returns>
bool contains(const int* arr, int size, int value);

/// <summary>
/// Инициализирует СЛАУ значениями, введенными пользователем.
/// </summary>
/// Параметры являются ссылочными типами, т.к. должны изменяться входные аргументы, а не копии указателей.
/// <param name="initMtrx">Исходная матрица, которая должна быть проинициализирована</param>
/// <param name="freeTermsMtrx">Матрица свободных членов, которая должна быть проинициализирована</param>
void initSole(double**& initMtrx, double**& freeTermsMtrx);

/// <summary>
/// Выводит на консоль введенную СЛАУ. 
/// </summary>
/// <param name="initMtrx">Исходная матрица, которая должна быть выведена</param>
/// <param name="freeTermsMtrx">Матрица свободных членов, которая должна быть выведена</param>
void printSole(double** initMtrx, double** freeTermsMtrx);

/// <summary>
/// Выполняет вычисление СЛАУ методом Гаусса. Если система не имеет решения, выполняется экстренное завершение программы.
/// </summary>
/// <param name="initMtrx">Исходная матрица, которая используется для вычисления</param>
/// <param name="freeTermsMtrx">Матрица свободных членов, которая используется для вычисления. Передается по ссылке для изменения указателя передаваемого аргумента</param>
/// <param name="solutionColumnMtrx">Матрица, которая в случае успешного приведения к ступенчатому виду будет содержать решение данной системы. Передается по ссылке для изменения указателя передаваемого аргумента</param>
/// <param name="freeUnknownsCols">Массив, хранящий индексы столбцов со свободными членами. Передается по ссылке для изменения указателя передаваемого аргумента</param>
/// <param name="rank"></param>
void gauss(double** initMtrx, double**& freeTermsMtrx,
    double**& solutionColumnMtrx, int*& freeUnknownsCols, int& rank);

/// <summary>
/// Выполняет элементарные преобразования над матрицами initMtrx, freeTermsMtrx для приведения системы к ступенчатому виду.
/// </summary>
/// <param name="initMtrx">Исходная матрица, которая приводится к ступенчатому виду</param>
/// <param name="freeTermsMtrx">Матрица со свободными членами, которая приводится к ступенчатому виду</param>
/// <param name="rank">Ранг исходной матрицы, определяющися после приведения матриц</param>
/// <returns>Возвращает true в случае успешного приведения к ступенчатому виду, иначе false</returns>
bool forwardMove(double**& initMtrx, double**& freeTermsMtrx, int& rank);

/// <summary>
/// Выполняет поиск ненулевого элемента в initMtrx в столбце col, начиная со строки row, и возвращает индекс найденной строки.
/// </summary>
/// <param name="row">Строка, с которой начинается поиск</param>
/// <param name="col">Столбец, с которого начинается поиск</param>
/// <param name="initMtrx">Матрица, в которой выполняется поиск</param>
/// <returns>В случае нахождения возвращает данный индекс строки, иначе -1</returns>
int findIdxOfNonZeroRowElement(int row, int col, double** initMtrx);

/// <summary>
/// Выполняет базовое преобразование над строкой. 
/// </summary>
/// <param name="row">Строка, которую необходимо преобразовать</param>
/// <param name="mainRow">Строка, содержащая элемент главной диагонали, относительно которого выполняется преобразование строки row</param>
/// <param name="col">Столбец, с которого начинается преобразование строки row</param>
/// <param name="initMtrx">Исходная матрица, в которой выполняется преобразование строки</param>
/// <param name="freeTermsMtrx">Матрица со свободными членами, в которой выполняется преобразование строки</param>
void transformRow(int row, int mainRow, int col, double**& initMtrx,
    double**& freeTermsMtrx);

/// <summary>
/// Проверяет, содержит ли текущая строка исходной матрицы только нулевые элементы.
/// </summary>
/// <param name="row">Строка для проверки</param>
/// <param name="col">Столбец, с которого начинается проверка</param>
/// <param name="initMtrx">Исходная матрица, в которой выполняется проверка</param>
/// <returns>Возвращает true, если строка row содержит только нули, иначе false</returns>
bool isOnlyZeroesOnInitMtrxRow(int row, int col, double** initMtrx);

/// <summary>
/// Меняет местами строки row1, row2, почленно переставляя между собой элементы из одной строки в другую.
/// </summary>
/// <param name="row1">Первая строка для обмена</param>
/// <param name="row2">Вторая строка для обмена</param>
/// <param name="mtrx">Матрица, в которой необходимо выполнить операцию</param>
/// <param name="cols">Кол-во столбцов в mtrx для обхода по всем элементам ряда</param>
void swapMtrxRows(int row1, int row2, double**& mtrx, int cols);

/// <summary>
/// Выполняет операции по обратному ход для нахождения матрицы столбца неизвестных: solutionColumnMtrx.
/// </summary>
/// <param name="solutionColumnMtrx">Матрица решения, которая будет содержать решение системы после выполнения тела функции. Передается по ссылке для изменения указателя передаваемого аргумента</param>
/// <param name="initMtrx">Исходная матрица, приведенная к ступенчатому виду, необходимая для нахождения solutionColumnMtrx</param>
/// <param name="freeTermsMtrx">Матрица со свободными членами, приведенная к ступенчатому виду, необходимая для нахождения solutionColumnMtrx</param>
/// <param name="freeUnknownsCols">Массив индексов столбцов со свободными неизвестными в initMtrx, который инициализируется внутри функции, на что указывает ссылочный параметр</param>
/// <param name="rank"></param>
void reverseMove(double**& solutionColumnMtrx, double** initMtrx,
    double** freeTermsMtrx, int*& freeUnknownsCols, int rank);

/// <summary>
/// Устанавливает столбцы со свободными и базисными неизвестными: basisUnknownsCols, freeUnknownsCols.
/// </summary>
/// <param name="basisUnknownsCols">Массив индексов столбцов с базисными неизвестными в initMtrx, которые будут установлены в ходе выполения</param>
/// <param name="freeUnknownsCols">Массив индексов столбцов со свободными неизвестными в initMtrx, которые будут установлены в ходе выполения</param>
/// <param name="initMtrx"></param>
void setBasisAndFreeIndexes(int*& basisUnknownsCols, int*& freeUnknownsCols,
    double** initMtrx);

/// <summary>
/// Инициализирует solutionColumnMtrx значениями на основе переданных матриц: initMtrx, freeTermsMtrx; и индексов столбцов freeUnknownsCols.
/// </summary>
/// <param name="solutionColumnMtrx">Инициализирует матрицу решения путем переноса свободных неизвестных из initMtrx в данную матрицу с отрицательными знаком, а также дополнительными столбцом из freeTermsMtrx. Передается по ссылке для присвоения данному указателю адреса проинициализированной памяти</param>
/// <param name="initMtrx">Исходная матрица, приведенная к ступенчатому виду, которая используется для нахождения solutionColumnMtrx</param>
/// <param name="freeTermsMtrx">Матрица со свободными членами, приведенная к ступенчатому виду, которая используется для нахождения solutionColumnMtrx</param>
/// <param name="resultCols">Кол-во столбцов в solutionColumnMtrx</param>
/// <param name="rank">Ранг initMtrx</param>
/// <param name="freeUnknownsCols">Массив индексов столбцов со свободными неизвестными, необходимый для инициализации solutionColumnMtrx</param>
void initSolutionColumnMtrx(double**& solutionColumnMtrx, double** initMtrx,
    double** freeTermsMtrx, int resultCols, int rank,
    const int* freeUnknownsCols);

/// <summary>
/// Вычисляет неизвестные в матрице решения solutionColumnMtrx на основе переданной матрицы initMtrx и индексов столбцов с базисными неизвестными - basisUnknownsCols.
/// </summary>
/// <param name="solutionColumnMtrx">Матрица решения, которая вычисляется в ходе выполнения тела данной функции путем простых математический операций</param>
/// <param name="initMtrx">Исходная матрица, приведенная к ступенчатому виду, которая используется для нахождения solutionColumnMtrx</param>
/// <param name="basisUnknownsCols">Массив индексов столбцов с базисными неизвестными в initMtrx, которые используются для вычисления solutionColumnMtrx</param>
/// <param name="rank">Ранг initMtrx</param>
/// <param name="resultCols">Кол-во столбцов в solutionColumnMtrx</param>
void evaluateSolutionColumnMtrx(double**& solutionColumnMtrx, double** initMtrx,
    const int* basisUnknownsCols, int rank,
    int resultCols);

/// <summary>
/// Выводит пользователю значения неизвестных в виде линейной комбинации базисных и свободных неизвестных.
/// </summary>
/// <param name="solutionColumnMtrx">Матрица решения, элементы которой будут выведены на экран</param>
/// <param name="freeUnknownsCols">Массив индексов столбцов со свободными неизвестными, необходимый для корректного порядка вывода solutionColumnMtrx</param>
/// <param name="rank">Ранг исходной матрицы, необходимый для вычисления кол-ва столбцов со свободными неизвестными</param>
void printSolutionColumnMtrx(double** solutionColumnMtrx,
    const int* freeUnknownsCols, int rank);

/// <summary>
/// Проверяет полученное решение путем подстановки найденных неизвестных в первое уравнение системы. 
/// </summary>
/// <param name="initMtrx">Исходная матрица, необходимая для получения коэффициентов перед неизвестными в первом уравнеии системы</param>
/// <param name="solutionColumnMtrx">Матрица решения</param>
/// <param name="freeTermsMtrx">Матрица со свободными членами, в которой необходим элемент из первой строки</param>
/// <param name="freeUnknownsCols">Массив индексов столбцов со свободными неизвестными, необходимый для корректного отображения элементов из solutionColumnMtrx</param>
/// <param name="rank"></param>
void checkSolution(double** initMtrx, double** solutionColumnMtrx,
    double** freeTermsMtrx, const int* freeUnknownsCols,
    int rank);

int m; // Кол-во уравнений.
int n; // Кол-во неизвестных.
const int COMPUTATIONAL_PRECISION = 6; // Вычислительная точность, используемая при округлении чисел во время выполнения базовых операций.
int outputPrecision; // Точность, устанавливающая кол-во знаков после запятой при выводе десятичных чисел на консоль.

int main() {
    setlocale(LC_ALL, "ru"); // Подключение русской локализации для вывода
    // кириллических символов в консоли.
    initRowsCols(); // Инициализация входных значений.
    // Объявление указателей на исходную матрицу и матрицу свободных членов.
    double** initMtrx = nullptr;
    double** freeTermsMtrx = nullptr;
    // Выделение памяти для вышеуказанных матриц, в зависимости от введенных
    // значений пользователем (m, n).
    allocateMtrxMemory(initMtrx, m, n);
    allocateMtrxMemory(freeTermsMtrx, m, 1); // Данная матрица свободных членов всегда содержит только один столбец.

    initSole(initMtrx, freeTermsMtrx); // Инициализация пользователем СЛАУ.
    printSole(initMtrx, freeTermsMtrx); // Выводит введенную СЛАУ.

    int rank = n < m ? n : m; // Ранг исходной матрицы, равный наименьшему значению: n или m.

    int* freeUnknownsCols = nullptr; // Объявление указателя на массив столбцов со свободными членами.
    double** solutionColumnMtrx = nullptr; // Объявление указателя на матрицу решения.
    gauss(initMtrx, freeTermsMtrx, solutionColumnMtrx, freeUnknownsCols, rank); // Вычисление СЛАУ методом Гаусса.

    // Выводит полученную матрицу столбца решения - solutionColumnMtrx.
    printSolutionColumnMtrx(solutionColumnMtrx, freeUnknownsCols, rank);

    // Проверяет корректность решения системы.
    checkSolution(initMtrx, solutionColumnMtrx, freeTermsMtrx, freeUnknownsCols,
        rank);

    // Освобождение выделенной памяти.
    delete[] freeUnknownsCols;
    freeMtrxMemory(initMtrx, m);
    freeMtrxMemory(freeTermsMtrx, m);
    freeMtrxMemory(solutionColumnMtrx, rank);

    // Приостановка выполнения программы перед ее завершением.
    std::cin.get();
    std::cin.get();
    return 0;
}

void initRowsCols() {
    std::cout << "Введите кол-во уравнений системы: ";
    std::cin >> m;
    std::cout << "Введите кол-во неизвестных системы: ";
    std::cin >> n;
    std::cout << "Введите кол-во знаков после запятой для вывода десятичных чисел: ";
    std::cin >> outputPrecision;

    if (n <= 0 || m <= 0) {
        std::cout << "Входные значения не должны быть меньше или равны нулю!"
            << std::endl;

        exit(0); // Завершает программу.
    }
}

void allocateMtrxMemory(double**& mtrx, int rows, int cols) {
    mtrx = new double* [rows] { // Выделяет память для массива указателей на double размера rows.
        };
    // Проходит по каждому указателю из mtrx.
    for (int i = 0; i < rows; ++i)
        mtrx[i] = new double[cols]; // И для каждого из них выделяет массив чисел типа double размера cols.
}

void freeMtrxMemory(double**& mtrx, int rows) {
    for (int i = 0; i < rows; ++i) // Освобождает память, на которую указывают указатели.
        delete[] mtrx[i];
    delete[] mtrx; // Освобождает память, выделенную для массива указателей.
}

double round(double v, int p) {
    double k = std::pow(10, p); // p = 2
    return int(v * k + (v > 0 ? 0.5 : -0.5)) / k;
}

bool contains(const int* arr, int size, int value) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == value)
            return true;
    }

    return false;
}

void initSole(double**& initMtrx, double**& freeTermsMtrx) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << "mtrx[" << i + 1 << ", " << j + 1 << "] = ";
            cin >> initMtrx[i][j];
        }
        cout << "freeTermsMtrx[" << i + 1 << "] = ";
        cin >> freeTermsMtrx[i][0];
    }
}

void printSole(double** initMtrx, double** freeTermsMtrx) {
    double v; // Хранит округленное значение матрицы.
    system("cls"); // Очищает консоль перед выводом системы.
    cout << "Исходная система линейных алгебраических уравнений: " << endl;
    bool isFirstNonZeroElem; // Проверяет, является ли текущий элемент матрицы первым ненулевым элементом.
    for (int i = 0, j; i < m; ++i) {
        isFirstNonZeroElem = true;

        for (j = 0; j < n; ++j) {
            v = round(initMtrx[i][j], outputPrecision);
            if (v == 0)
                continue;

            if (isFirstNonZeroElem) { // Если это первый ненулевой элемент в строке, выводим его без изменений.
                cout << v;
            }
            else { // Иначе добавляем знак перед числом и выводим его абсолютную величину.
                cout << (v > 0 ? " + " : " - ") << (v > 0 ? v : -v);
            }

            cout << 'x' << j + 1;
            isFirstNonZeroElem = false;
        }

        v = round(freeTermsMtrx[i][0], outputPrecision);
        if (isFirstNonZeroElem)
            cout << "0 = " << v << endl;
        else
            cout << " = " << v << endl;
    }
    cout << endl;
}

void gauss(double** initMtrx, double**& freeTermsMtrx, double**& solutionColumnMtrx, int*& freeUnknownsCols, int& rank) {
    // Прямой ход СЛАУ. Если forwardMove возвращает true, значит система совместна, в противном случае программа выведет пользователю сообщение о несовместимости системы и завершит выполнение.
    if (!forwardMove(initMtrx, freeTermsMtrx, rank)) {
        std::cout << "Данная система несовместна!" << std::endl;
        // Освобождение выделенной памяти.
        freeMtrxMemory(initMtrx, m);
        freeMtrxMemory(freeTermsMtrx, m);

        exit(0); // Завершает программу.
    }

    // Обратный ход СЛАУ.
    reverseMove(solutionColumnMtrx, initMtrx, freeTermsMtrx, freeUnknownsCols,
        rank);
}

bool forwardMove(double**& initMtrx, double**& freeTermsMtrx, int& rank) {
    int nNonZeroRows = m; // Хранит количество ненулевых строк initMtrx.

    int curCol; // Хранит индекс текущего столбца initMtrx.
    // Проходит по всем строкам матрицы, которые образуют ранг матрицы, кроме последней.
    for (int i = 0; i < rank - 1; ++i) {
        curCol = i;

        int idx; // Индекс ненулевого элемента текущего ряда, находящегося в столбце curCol.
        while (curCol < n && initMtrx[i][curCol] == 0) { // Проходит по всем столбцам initMtrx до тех пор, пока не найдет ненулевой элемент.
            idx = findIdxOfNonZeroRowElement(i + 1, curCol, initMtrx); // Возвращает индекс ряда искомого элемента при его находке, иначе -1.
            if (idx == -1) { // Если элемент не найден, переходим к следующему столбцу.
                ++curCol;
            }
            else { // Иначе меняем местами ряд с нулевым элементом (row) и ряд с найденным ненулевым элементом под инедксом idx в initMtrx и freeTermsMtrx.
                swapMtrxRows(i, idx, initMtrx, n);
                swapMtrxRows(i, idx, freeTermsMtrx, 1);
                break; // Выходим из цикла while, т.к. элемент найден.
            }
        }

        // Позволяет циклу обнулить все эл-ты ряда, которые
        // не были обнулены в предыдущем столбце.
        int k = nNonZeroRows; // 
        // Проходит по строкам матрицы, начиная со строки, расположенной ниже текущего элемента главной диагонали, и заканчивая на ненулевых строках.
        for (int j = i + 1; j < k; ++j) {
            transformRow(j, i, curCol, initMtrx, freeTermsMtrx); // Преобразовывает строку под индексом j.

            bool isOnlyZeroes = isOnlyZeroesOnInitMtrxRow(j, curCol, initMtrx); // Проверяет, является ли преобразованная строка в initMtrx нулевой.

            if (isOnlyZeroes && freeTermsMtrx[j][0] != 0) // Если все эл-ты ряда равны нулю, а элемент в свободной матрице под этим индексом ряда нет, то система несовместна.
                return false;
            else if (isOnlyZeroes) { // Если и ряд, и элемент в свободной матрице под этим рядом равны нулю.
                --nNonZeroRows;
                if (nNonZeroRows < rank) // Если кол-во ненулевых строк меньше ранга матрицы, меняем ранг матрицы.
                    rank = nNonZeroRows;
            }
        }
    }

    return true;
}

int findIdxOfNonZeroRowElement(int row, int col, double** initMtrx) {
    int curRow = row; // Текущий ряд матрицы.
    while (curRow < m && initMtrx[curRow][col] == 0)
        ++curRow;

    // Если в данном столбце нет ненулевых элементов, переходим к следующему.
    if (curRow >= m) { // Если элемент не был найден, возвращает -1.
        return -1;
    }
    else { // В противном случае возвращает индекс найденного ряда.
        return curRow;
    }
}

void transformRow(int row, int mainRow, int col, double**& initMtrx,
    double**& freeTermsMtrx) {
    // Частное от деления элемента, находящегося под главной диагональю в строке row столбца col, на элемент, стоящий на главной диагонали в этом же столбце.
    double div = initMtrx[row][col] / initMtrx[mainRow][col];

    // Вычитает из строки row, строку mainRow, умноженную на найденное частное div, округляя полученные значения.
    for (int i = col; i < n; ++i)
        initMtrx[row][i] = round(initMtrx[row][i] - div * initMtrx[mainRow][i],
            COMPUTATIONAL_PRECISION);
    // Все то же самое, что и выше.
    freeTermsMtrx[row][0] =
        round(freeTermsMtrx[row][0] - div * freeTermsMtrx[mainRow][0],
            COMPUTATIONAL_PRECISION);
}

bool isOnlyZeroesOnInitMtrxRow(int row, int col, double** initMtrx) {
    for (int i = col; i < n; ++i)
        if (initMtrx[row][i] != 0)
            return false;

    return true;
}

void swapMtrxRows(int row1, int row2, double**& mtrx, int cols) {
    double tmp; // Сохраняет временное значение элемента, находящегося на пересечении строки row1 и столбца i.
    for (int i = 0; i < cols; ++i) {
        tmp = mtrx[row1][i];
        mtrx[row1][i] = mtrx[row2][i];
        mtrx[row2][i] = tmp;
    }
}

void reverseMove(double**& solutionColumnMtrx, double** initMtrx,
    double** freeTermsMtrx, int*& freeUnknownsCols, int rank) {
    int* basisUnknownsCols = new int[rank]; // Указатель на массив индексов столбцов с базисными неизвестными.
    // Инициализация данного массива значениями по умолчанию.
    for (int i = 0; i < rank; ++i)
        basisUnknownsCols[i] = -1;

    int nFreeUnknowns = n - rank; // Количество свободных неизвестных.
    if (nFreeUnknowns != 0) {
        freeUnknownsCols = new int[nFreeUnknowns] {};
    }

    setBasisAndFreeIndexes(basisUnknownsCols, freeUnknownsCols, initMtrx); // Устанавливает столбцы базисных и свободных неизвестных.

    int resultCols = nFreeUnknowns + 1; // Количество столбцов в матрице решения.
    initSolutionColumnMtrx(solutionColumnMtrx, initMtrx, freeTermsMtrx, rank,
        resultCols, freeUnknownsCols); // Инициализирует матрицу решения путем перенесения свободных неизвестных в данную матрицу с противоположным знаком, а также копирования элементов из матрицы свободных членов.

    evaluateSolutionColumnMtrx(solutionColumnMtrx, initMtrx, basisUnknownsCols,
        rank, resultCols); // Вычисляет матрицу решения.

    delete[] basisUnknownsCols; // Освобождает массив со столбцами базисных неизвестных.
}

void setBasisAndFreeIndexes(int*& basisUnknownsCols, int*& freeUnknownsCols,
    double** initMtrx) {
    int position = 0; // Содержит индекс незанятой ячейки в массиве freeUnknownsCols.
    int nNonZeroItems; // Хранит количество ненулевых строк в текущем столбце, начиная со второй строки.
    for (int i = 0; i < n; ++i) {
        // Проходит по эл-там столбца i, пока не дойдет до нулевого элемента или до крайней нижней строки матрицы.
        nNonZeroItems = 0;
        while (nNonZeroItems + 1 < m && initMtrx[nNonZeroItems + 1][i] != 0)
            ++nNonZeroItems;
        // Первый столбец среди всех столбцов с одинаковым nNonZeroItems является базисным, остальные - свободными. По этой причине basisUnknownsCols заполнен по умолчанию -1, т.к. строки матрицы индексируются с 0 и nNonZeroItems не может содержать значение ниже 0.
        if (basisUnknownsCols[nNonZeroItems] == -1) // Если по индексу nNonZeroItems в массиве basisUnknownsCols находится -1 - столбец i является базисным.
            basisUnknownsCols[nNonZeroItems] = i; // И индекс данного столбца записывается в basisUnknownsCols.
        else
            freeUnknownsCols[position++] = i; // В противном случае - в freeUnknownsCols.
    }
}

void initSolutionColumnMtrx(double**& solutionColumnMtrx, double** initMtrx,
    double** freeTermsMtrx, int rank, int resultCols,
    const int* freeUnknownsCols) {
    allocateMtrxMemory(solutionColumnMtrx, rank, resultCols); // Выделяет память под solutionColumnMtrx размерностью rank x resultCols. 
    for (int i = 0; i < rank; ++i) {
        for (int j = 0; j < resultCols; ++j) {
            // Элементы из интервала [0, resultCols - 1) представляют столбцы со свободными членами, которые необходимо перенести за знак равенства со сменой знака, проинициализировав solutionColumnMtrx.
            if (j != resultCols - 1)
                // Однако вместо переноса выполним копирование элементов из данных столбцов с противоположным знаком.
                solutionColumnMtrx[i][j] = -initMtrx[i][freeUnknownsCols[j]];
            else
                // Если данный столбец равен столбцу со свободным членом, скопируем его значение.
                solutionColumnMtrx[i][j] = freeTermsMtrx[i][0];
        }
    }
}

void evaluateSolutionColumnMtrx(double**& solutionColumnMtrx, double** initMtrx,
    const int* basisUnknownsCols, int rank,
    int resultCols) {
    // Проходит по строкам матрицы, образующих ранг initMtrx, начиная с нижней и заканчивая первой.
    for (int i = rank - 1; i >= 0; --i) {
        // Проходит по строке i, начиная с крайнего правого элемента и заканчивая элементом на главной диагонали включительно.
        for (int j = 0; j < rank - i; ++j) {
            // Проходит по всем столбцам solutionColumnMtrx ряда i, начиная с крайнего левого, заканчивая крайним правым.
            for (int k = 0; k < resultCols; ++k) {
                int basisItemCol = rank - j - 1; // Содержит индекс столбца текущего базисного элемента, на основе которого вычисляются значения в матрице решения.
                // Обновление значения в матрице решения на основе вычитания из этого числа произведения коэффициента перед базисным неизвестным и значения из матрицы решения, находящегося в ряду basisItemCol, пока не пройдет по всем элементам из этого ряда, кроме последнего.
                if (basisItemCol != i) {
                    solutionColumnMtrx[i][k] =
                        round(solutionColumnMtrx[i][k] -
                            initMtrx[i][basisUnknownsCols[basisItemCol]] *
                            solutionColumnMtrx[basisItemCol][k],
                            COMPUTATIONAL_PRECISION);
                }
                else { // Обновление значения в матрице решения путем его делении на коэффициент перед базисным неизвестным.
                    solutionColumnMtrx[i][k] =
                        round(solutionColumnMtrx[i][k] /
                            initMtrx[i][basisUnknownsCols[basisItemCol]],
                            COMPUTATIONAL_PRECISION);
                }
            }
        }
    }
}

void printSolutionColumnMtrx(double** solutionColumnMtrx,
    const int* freeUnknownsCols, int rank) {
    int basisUnknownIdx = 0; // Хранит индекс текущего базисного неизвестного.
    int freeUnknownIdx = 0; // Хранит индекс текущего свободного неизвестного.
    int nFreeUnknowns = n - rank; // Количество свободных неизвестных.

    double v; // Хранит округленное значение матрицы.
    cout << "Столбец решения: " << endl;

    bool isFirstNonZeroElem; // Проверяет, является ли текущий элемент матрицы первым ненулевым элементом.
    int solutionColumnCols; // Содержит количество столбцов в матрице решения.
    // Проходит по всем рядам solutionColumnMtrx.
    for (int i = 0, j; i < n; ++i) {
        cout << '(' << 'x' << i + 1 << ')';
        if (i + 1 != (n % 2 == 0 ? n / 2 : n / 2 + 1)) // Если цикл доходит до центрального уравнения системы, на экран выводится знак равенства вместо пробела.
            cout << "   (";
        else
            cout << " = (";

        if (contains(freeUnknownsCols, nFreeUnknowns, i)) { // Если массив столбцов со свободными неизвестными содержит индекс текущего ряда i, значит это свободная неизвестная.
            cout << 'z' << freeUnknownsCols[freeUnknownIdx++] + 1 << ')' // Выводим переменную z с номером столбца свободной неизвестной.
                << endl;
            continue; // Переходим к следующей итерации цикла.
        }

        isFirstNonZeroElem = true;
        solutionColumnCols = nFreeUnknowns + 1; // + 1 для столбца со свободными неизвестными.
        for (j = 0; j < solutionColumnCols; ++j) {
            v = round(solutionColumnMtrx[basisUnknownIdx][j], outputPrecision);
            if (v == 0)
                continue;

            if (isFirstNonZeroElem) { // Если это первый ненулевой элемент в строке, выводим его без изменений.
                cout << v;
            }
            else { // Иначе добавляем знак перед числом и выводим его абсолютную величину.
                cout << (v > 0 ? " + " : " - ") << (v > 0 ? v : -v);
            }

            if (j != solutionColumnCols - 1) // Если это не последний элемент в ряду i матрицы решения. 
                cout << 'z' << freeUnknownsCols[j] + 1; // Выводим переменную z с номером столбца свободной неизвестной.
            isFirstNonZeroElem = false;
        }

        basisUnknownIdx++;
        cout << ')' << endl;
    }
    cout << endl;
}

void checkSolution(double** initMtrx, double** solutionColumnMtrx,
    double** freeTermsMtrx, const int* freeUnknownsCols,
    int rank) { // Проверим систему, считая, что все свободные члены принимают значение равное 1.
    int basisUnknownIdx = 0; // Хранит индекс текущего базисного неизвестного.
    int nFreeUnknowns = n - rank; // Количество свободных неизвестных.
    double sum = 0;

    for (int i = 0; i < n; ++i) {
        if (contains(freeUnknownsCols, nFreeUnknowns, i)) { // Если массив столбцов со свободными неизвестными содержит индекс текущего ряда i, значит это свободная неизвестная.
            sum = round(sum + initMtrx[0][i], COMPUTATIONAL_PRECISION); // Поэтому достаточно к сумме прибавить значение элемента из initMtrx, находящегося в столбце с этой неизвестной.
            continue; // Переходим к следующей итерации цикла.
        }

        // Проходит по всем столбцам из матрицы solutionColumnMtrx в ряду i и прибавляет к сумме результат произведения коэффициента перед неизвестной в initMtrx в столбце i на каждый элемент из матрицы решения в данной ряду.
        for (int j = 0; j < nFreeUnknowns + 1; ++j) {
            sum = sum + round(initMtrx[0][i] * solutionColumnMtrx[basisUnknownIdx][j],
                COMPUTATIONAL_PRECISION);
        }
        basisUnknownIdx++;
    }

    cout << "В результате подстановки свободных членов в первое уравнение СЛАУ "
        "получилось следующее тождество: "
        << sum << " = " << freeTermsMtrx[0][0] << endl;
}