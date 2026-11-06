/// <summary>
/// Лабораторна робота №7, завдання 1, варіант 4. Порахувати маршрути шахового
/// короля на дошці n * m і вивести матрицю найкоротшого маршруту.
/// </summary>
/// <remarks>
/// Ім'я файлу: task1.cpp
/// Автор: Чумак Кирил, гр. ІПЗ-11(3)
/// Номер версії модуля: version 1
/// </remarks>

#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
using namespace std;

// Константи
const int MAX_SIZE = 10; // найбільший розмір дошки

// Глобальні змінні
int routeCounts[MAX_SIZE][MAX_SIZE] = {{0}}; // кількість маршрутів до клітинки
int routeCells[MAX_SIZE][MAX_SIZE] = {{0}};  // 1 - клітинка маршруту, 0 - інша
int rowCount = 0;                            // кількість рядків n
int columnCount = 0;                         // кількість стовпців m
int choice = 0;                              // вибраний пункт меню

/// <summary>
/// Виводить назву роботи, автора і короткий зміст задачі
/// </summary>
void printTitle()
{
    cout << "Lab work 7. Task 1. Variant 4." << endl;
    cout << "Author: Kyryl Chumak, group IPZ-11(3)" << endl << endl;

    cout << "A chess king starts in the top left corner of an n x m" << endl;
    cout << "board. It moves right, down or right-down along the" << endl;
    cout << "diagonal. Count its routes to the bottom right corner." << endl;
    cout << "Print the number of routes and a matrix where route cells" << endl;
    cout << "are 1 and the others are 0." << endl << endl;
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
/// Вводить розміри дошки з клавіатури
/// </summary>
void inputBoardSize()
{
    cout << "Enter n (from 1 to " << MAX_SIZE << "): ";
    rowCount = inputNumber(1, MAX_SIZE);
    cout << "Enter m (from 1 to " << MAX_SIZE << "): ";
    columnCount = inputNumber(1, MAX_SIZE);
}

/// <summary>
/// Дає розмірам дошки псевдовипадкові значення від 1 до 10
/// </summary>
void generateBoardSize()
{
    rowCount = rand() % MAX_SIZE + 1;
    columnCount = rand() % MAX_SIZE + 1;
}

/// <summary>
/// Виводить меню способу створення дошки і виконує вибраний пункт
/// </summary>
void chooseBoardSize()
{
    srand(time(NULL));

    cout << "1 - enter the board size" << endl;
    cout << "2 - generate the board size at random" << endl;
    cout << "Your choice: ";
    choice = inputNumber(1, 2);

    switch (choice)
    {
        case 1 : inputBoardSize(); break;
        default : generateBoardSize(); break; // пункт 2
    }
}

/// <summary>
/// Рахує кількість маршрутів до кожної клітинки. До клітинки першого рядка чи
/// стовпця веде один маршрут, а до решти стільки, скільки сумарно до лівої,
/// верхньої і лівої верхньої сусідніх
/// </summary>
void calculateRoutes()
{
    int i = 0; // номер рядка
    int j = 0; // номер стовпця

    for (i = 0; i < rowCount; i++)
    {
        for (j = 0; j < columnCount; j++)
        {
            if (i == 0 || j == 0)
            {
                routeCounts[i][j] = 1;
            }
            else
            {
                routeCounts[i][j] = routeCounts[i - 1][j]
                                    + routeCounts[i][j - 1]
                                    + routeCounts[i - 1][j - 1];
            }
        }
    }
}

/// <summary>
/// Позначає клітинки найкоротшого маршруту: король іде діагоналлю, поки можна,
/// а потім прямо
/// </summary>
void markShortestRoute()
{
    int i = 0; // поточний рядок короля
    int j = 0; // поточний стовпець короля

    routeCells[0][0] = 1;
    while (i < rowCount - 1 || j < columnCount - 1)
    {
        if (i < rowCount - 1)
        {
            i++;
        }
        if (j < columnCount - 1)
        {
            j++;
        }
        routeCells[i][j] = 1;
    }
}

/// <summary>
/// Виводить матрицю рядками і стовпцями
/// </summary>
/// <param name="matrix">матриця</param>
/// <param name="width">ширина стовпця</param>
void printMatrix(int matrix[MAX_SIZE][MAX_SIZE], int width)
{
    int i = 0; // номер рядка
    int j = 0; // номер стовпця

    for (i = 0; i < rowCount; i++)
    {
        for (j = 0; j < columnCount; j++)
        {
            cout << setw(width) << matrix[i][j];
        }
        cout << endl;
    }
}

/// <summary>
/// Виводить розміри дошки, кількість маршрутів і дві матриці
/// </summary>
void printResult()
{
    cout << endl << "Board size: " << rowCount << " x " << columnCount << endl;
    cout << "Number of routes: " << routeCounts[rowCount - 1][columnCount - 1]
         << endl;

    cout << endl << "Number of routes to each cell:" << endl;
    printMatrix(routeCounts, 8);

    cout << endl << "One shortest route (1 - on the route, 0 - not):" << endl;
    printMatrix(routeCells, 3);
}

/// <summary>
/// Головна функція програми
/// </summary>
/// <returns>0 після завершення роботи</returns>
int main()
{
    printTitle();
    chooseBoardSize();
    calculateRoutes();
    markShortestRoute();
    printResult();
    return 0;
}
