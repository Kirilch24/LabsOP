/// <summary>
/// Лабораторна робота №5, завдання 1, варіант 8. Обчислити добуток двох чисел
/// за рекурентним співвідношенням рекурсією і циклом, знайти глибину рекурсії і
/// кількість ітерацій.
/// </summary>
/// <remarks>
/// Ім'я файлу: task1.cpp
/// Автор: Чумак Кирил, гр. ІПЗ-11(3)
/// Номер версії модуля: version 1
/// </remarks>

#include <iostream>
using namespace std;

// Константи
const int MIN_NUMBER = 0;     // найменше допустиме число
const int MAX_NUMBER = 10000; // найбільше число, добуток вміщається в int

// Глобальні змінні
int firstNumber = 0;      // перший множник a
int secondNumber = 0;     // другий множник b
int recursiveProduct = 0; // добуток, знайдений рекурсією
int iterativeProduct = 0; // добуток, знайдений циклом
int currentDepth = 0;     // кількість незавершених викликів зараз
int maxDepth = 0;         // глибина рекурсії
int iterationCount = 0;   // кількість ітерацій циклу

/// <summary>
/// Виводить назву роботи, автора і рекурентне співвідношення
/// </summary>
void printTitle()
{
    cout << "Lab work 5. Task 1. Variant 8." << endl;
    cout << "Author: Kyryl Chumak, group IPZ-11(3)" << endl << endl;

    cout << "Enter two integers a, b and calculate their product by" << endl;
    cout << "the recurrence relation, with recursion and with a loop." << endl;
    cout << "Compare the recursion depth and the number of iterations." << endl
         << endl;
    cout << "           a,                if b = 1" << endl;
    cout << "p(a, b) =  b,                if a = 1" << endl;
    cout << "           0,                if a = 0 or b = 0" << endl;
    cout << "           a + p(a, b - 1),  otherwise" << endl << endl;
}

/// <summary>
/// Вводить ціле число. Поки введено не число або число поза межами, введення
/// повторюється
/// </summary>
/// <param name="minValue">найменше значення</param>
/// <param name="maxValue">найбільше</param>
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
/// Вводить два множники
/// </summary>
void inputNumbers()
{
    cout << "Enter a (from 0 to 10000): ";
    firstNumber = inputNumber(MIN_NUMBER, MAX_NUMBER);

    cout << "Enter b (from 0 to 10000): ";
    secondNumber = inputNumber(MIN_NUMBER, MAX_NUMBER);
}

/// <summary>
/// Обчислює добуток за рекурентним співвідношенням і запам'ятовує найбільшу
/// кількість незавершених викликів
/// </summary>
/// <param name="first">множник a</param>
/// <param name="second">множник b</param>
/// <returns>добуток a і b</returns>
int multiplyRecursive(int first, int second)
{
    int result = 0; // значення p(a, b)

    currentDepth++;
    if (currentDepth > maxDepth)
    {
        maxDepth = currentDepth;
    }

    if (second == 1)
    {
        result = first;
    }
    else if (first == 1)
    {
        result = second;
    }
    else if (first == 0 || second == 0)
    {
        result = 0;
    }
    else
    {
        result = first + multiplyRecursive(first, second - 1);
    }

    currentDepth--;
    return result;
}

/// <summary>
/// Обчислює добуток циклом. Умови ті самі, що в рекурентному співвідношенні, а
/// додавання виконуються в циклі
/// </summary>
void multiplyIterative()
{
    int i = 0; // лічильник додавань

    if (secondNumber == 1)
    {
        iterativeProduct = firstNumber;
    }
    else if (firstNumber == 1)
    {
        iterativeProduct = secondNumber;
    }
    else if (firstNumber == 0 || secondNumber == 0)
    {
        iterativeProduct = 0;
    }
    else
    {
        iterativeProduct = firstNumber;
        for (i = 2; i <= secondNumber; i++)
        {
            iterativeProduct = iterativeProduct + firstNumber;
            iterationCount++;
        }
    }
}

/// <summary>
/// Виводить результати обох способів
/// </summary>
void printResults()
{
    cout << endl << "Recursion:" << endl;
    cout << "p(" << firstNumber << ", " << secondNumber
         << ") = " << recursiveProduct << endl;
    cout << "recursion depth: " << maxDepth << endl;

    cout << endl << "Loop:" << endl;
    cout << "p(" << firstNumber << ", " << secondNumber
         << ") = " << iterativeProduct << endl;
    cout << "number of iterations: " << iterationCount << endl;
}

/// <summary>
/// Головна функція програми
/// </summary>
/// <returns>0 після завершення роботи</returns>
int main()
{
    printTitle();
    inputNumbers();
    recursiveProduct = multiplyRecursive(firstNumber, secondNumber);
    multiplyIterative();
    printResults();
    return 0;
}
