/// <summary>
/// Лабораторна робота №7, завдання 2, варіант 4. Виконати елементарні
/// перетворення матриці, які користувач вибирає в меню.
/// </summary>
/// <remarks>
/// Ім'я файлу: task2.cpp
/// Автор: Чумак Кирил, гр. ІПЗ-11(3)
/// Номер версії модуля: version 1
/// </remarks>

#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
using namespace std;

// Константи
const int MIN_SIZE = 2;     // найменша кількість рядків і стовпців
const int MAX_SIZE = 10;    // найбільша кількість рядків і стовпців
const int MAX_LIMIT = 1000; // найбільший модуль меж діапазону

// Глобальні змінні
float matrix[MAX_SIZE][MAX_SIZE] = {{0}}; // матриця
int rowCount = 0;                         // кількість рядків
int columnCount = 0;                      // кількість стовпців
int firstIndex = 0;  // номер першого рядка чи стовпця, від 1
int secondIndex = 0; // номер другого рядка чи стовпця, від 1
float constant = 0;  // ненульове число для множення
int outputMode = 0;  // 1 - лише кінцева матриця, 2 - після кожного кроку
int choice = 0;      // вибраний пункт меню

/// <summary>
/// Виводить назву роботи й автора
/// </summary>
void printTitle()
{
    cout << "Lab work 7. Task 2. Variant 4." << endl;
    cout << "Author: Kyryl Chumak, group IPZ-11(3)" << endl << endl;

    cout << "Elementary transformations of a matrix:" << endl;
    cout << "- swap two rows or two columns;" << endl;
    cout << "- multiply a row or a column by a non-zero constant;" << endl;
    cout << "- add to a row or a column another one multiplied" << endl;
    cout << "  by a non-zero constant." << endl;
    cout << "The matrix is entered from the keyboard or generated in a" << endl;
    cout << "given range." << endl << endl;
}

/// <summary>
/// Вводить ціле число із заданих меж. Поки введено не число або число поза
/// межами, введення повторюється
/// </summary>
/// <param name="minValue">нижня межа</param>
/// <param name="maxValue">верхня межа</param>
/// <returns>введене число</returns>
int inputNumber(int minValue, int maxValue)
{
    int number = 0; // введене число

    cin >> number;
    while (cin.fail() || number < minValue || number > maxValue)
    {
        cin.clear();            // скинути помилку введення
        cin.ignore(1000, '\n'); // і пропустити неправильний рядок
        cout << "Error! Enter a number from " << minValue << " to " << maxValue
             << ": ";
        cin >> number;
    }

    return number;
}

/// <summary>
/// Вводить константу для множення. Поки введено не число або нуль, введення
/// повторюється
/// </summary>
void inputConstant()
{
    cout << "Enter a non-zero constant: ";
    cin >> constant;
    while (cin.fail() || constant == 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Error! Enter a non-zero constant: ";
        cin >> constant;
    }
}

/// <summary>
/// Вводить два різні номери рядків або стовпців
/// </summary>
/// <param name="maxIndex">найбільший номер</param>
void inputTwoIndexes(int maxIndex)
{
    cout << "Enter the first index (from 1 to " << maxIndex << "): ";
    firstIndex = inputNumber(1, maxIndex);
    cout << "Enter the second index (from 1 to " << maxIndex << "): ";
    secondIndex = inputNumber(1, maxIndex);

    while (secondIndex == firstIndex)
    {
        cout << "Error! The second index must differ from the first: ";
        secondIndex = inputNumber(1, maxIndex);
    }
}

/// <summary>
/// Вводить елементи матриці з клавіатури
/// </summary>
void inputMatrix()
{
    int i = 0; // номер рядка
    int j = 0; // номер стовпця

    for (i = 0; i < rowCount; i++)
    {
        cout << "Enter row " << i + 1 << " (" << columnCount << " numbers): ";
        for (j = 0; j < columnCount; j++)
        {
            cin >> matrix[i][j];
            while (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Error! Enter a number: ";
                cin >> matrix[i][j];
            }
        }
    }
}

/// <summary>
/// Вводить діапазон і заповнює матрицю псевдовипадковими цілими числами з нього
/// </summary>
void generateMatrix()
{
    int lowerLimit = 0; // нижня межа діапазону
    int upperLimit = 0; // верхня межа діапазону
    int i = 0;          // номер рядка
    int j = 0;          // номер стовпця

    cout << "Enter the lower limit (from " << -MAX_LIMIT << " to " << MAX_LIMIT
         << "): ";
    lowerLimit = inputNumber(-MAX_LIMIT, MAX_LIMIT);
    cout << "Enter the upper limit (from " << lowerLimit << " to " << MAX_LIMIT
         << "): ";
    upperLimit = inputNumber(lowerLimit, MAX_LIMIT);

    for (i = 0; i < rowCount; i++)
    {
        for (j = 0; j < columnCount; j++)
        {
            matrix[i][j] = rand() % (upperLimit - lowerLimit + 1) + lowerLimit;
        }
    }
}

/// <summary>
/// Виводить матрицю рядками і стовпцями
/// </summary>
void printMatrix()
{
    int i = 0; // номер рядка
    int j = 0; // номер стовпця

    cout << fixed << setprecision(2);
    for (i = 0; i < rowCount; i++)
    {
        for (j = 0; j < columnCount; j++)
        {
            cout << setw(10) << matrix[i][j];
        }
        cout << endl;
    }
}

/// <summary>
/// Вводить розміри, виводить меню способу створення матриці, виконує вибраний
/// пункт і виводить вхідну матрицю
/// </summary>
void createMatrix()
{
    srand(time(NULL));

    cout << "Enter the number of rows (from " << MIN_SIZE << " to " << MAX_SIZE
         << "): ";
    rowCount = inputNumber(MIN_SIZE, MAX_SIZE);
    cout << "Enter the number of columns (from " << MIN_SIZE << " to "
         << MAX_SIZE << "): ";
    columnCount = inputNumber(MIN_SIZE, MAX_SIZE);

    cout << "1 - enter the matrix from the keyboard" << endl;
    cout << "2 - fill the matrix with pseudorandom numbers" << endl;
    cout << "Your choice: ";
    choice = inputNumber(1, 2);

    switch (choice)
    {
        case 1 : inputMatrix(); break;
        default : generateMatrix(); break; // пункт 2
    }

    cout << endl << "Input matrix:" << endl;
    printMatrix();
}

/// <summary>
/// Міняє місцями два рядки
/// </summary>
void swapRows()
{
    float temporary = 0; // значення для обміну
    int j = 0;           // номер стовпця

    inputTwoIndexes(rowCount);
    for (j = 0; j < columnCount; j++)
    {
        temporary = matrix[firstIndex - 1][j];
        matrix[firstIndex - 1][j] = matrix[secondIndex - 1][j];
        matrix[secondIndex - 1][j] = temporary;
    }

    cout << "Rows " << firstIndex << " and " << secondIndex << " are swapped."
         << endl;
}

/// <summary>
/// Міняє місцями два стовпці
/// </summary>
void swapColumns()
{
    float temporary = 0; // значення для обміну
    int i = 0;           // номер рядка

    inputTwoIndexes(columnCount);
    for (i = 0; i < rowCount; i++)
    {
        temporary = matrix[i][firstIndex - 1];
        matrix[i][firstIndex - 1] = matrix[i][secondIndex - 1];
        matrix[i][secondIndex - 1] = temporary;
    }

    cout << "Columns " << firstIndex << " and " << secondIndex
         << " are swapped." << endl;
}

/// <summary>
/// Множить рядок на ненульову константу
/// </summary>
void multiplyRow()
{
    int j = 0; // номер стовпця

    cout << "Enter the row index (from 1 to " << rowCount << "): ";
    firstIndex = inputNumber(1, rowCount);
    inputConstant();
    for (j = 0; j < columnCount; j++)
    {
        matrix[firstIndex - 1][j] = matrix[firstIndex - 1][j] * constant;
    }

    cout << "Row " << firstIndex << " is multiplied by " << constant << "."
         << endl;
}

/// <summary>
/// Множить стовпець на ненульову константу
/// </summary>
void multiplyColumn()
{
    int i = 0; // номер рядка

    cout << "Enter the column index (from 1 to " << columnCount << "): ";
    firstIndex = inputNumber(1, columnCount);
    inputConstant();
    for (i = 0; i < rowCount; i++)
    {
        matrix[i][firstIndex - 1] = matrix[i][firstIndex - 1] * constant;
    }

    cout << "Column " << firstIndex << " is multiplied by " << constant << "."
         << endl;
}

/// <summary>
/// Додає до першого рядка другий, помножений на константу
/// </summary>
void addRow()
{
    int j = 0; // номер стовпця

    inputTwoIndexes(rowCount);
    inputConstant();
    for (j = 0; j < columnCount; j++)
    {
        matrix[firstIndex - 1][j] =
            matrix[firstIndex - 1][j] + matrix[secondIndex - 1][j] * constant;
    }

    cout << "Row " << secondIndex << " multiplied by " << constant
         << " is added to row " << firstIndex << "." << endl;
}

/// <summary>
/// Додає до першого стовпця другий, помножений на константу
/// </summary>
void addColumn()
{
    int i = 0; // номер рядка

    inputTwoIndexes(columnCount);
    inputConstant();
    for (i = 0; i < rowCount; i++)
    {
        matrix[i][firstIndex - 1] =
            matrix[i][firstIndex - 1] + matrix[i][secondIndex - 1] * constant;
    }

    cout << "Column " << secondIndex << " multiplied by " << constant
         << " is added to column " << firstIndex << "." << endl;
}

/// <summary>
/// Вводить режим виведення, виводить меню перетворень і виконує вибрані пункти,
/// поки користувач не вибере завершення. Після цього виводить кінцеву матрицю
/// </summary>
void runMenu()
{
    cout << endl << "1 - show only the final matrix" << endl;
    cout << "2 - show the matrix after each transformation" << endl;
    cout << "Your choice: ";
    outputMode = inputNumber(1, 2);

    do
    {
        cout << endl << "1 - swap two rows" << endl;
        cout << "2 - swap two columns" << endl;
        cout << "3 - multiply a row by a constant" << endl;
        cout << "4 - multiply a column by a constant" << endl;
        cout << "5 - add another row multiplied by a constant to a row" << endl;
        cout << "6 - add another column multiplied by a constant to a column"
             << endl;
        cout << "0 - finish" << endl;
        cout << "Your choice: ";
        choice = inputNumber(0, 6);

        switch (choice)
        {
            case 1 : swapRows(); break;
            case 2 : swapColumns(); break;
            case 3 : multiplyRow(); break;
            case 4 : multiplyColumn(); break;
            case 5 : addRow(); break;
            case 6 : addColumn(); break;
            default : break; // пункт 0
        }

        if (outputMode == 2 && choice != 0)
        {
            printMatrix();
        }
    } while (choice != 0);

    cout << endl << "Final matrix:" << endl;
    printMatrix();
}

/// <summary>
/// Головна функція програми
/// </summary>
/// <returns>0 після завершення роботи</returns>
int main()
{
    printTitle();
    createMatrix();
    runMenu();
    return 0;
}
