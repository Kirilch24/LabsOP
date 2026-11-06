/// <summary>
/// Лабораторна робота №4, завдання 2, варіант 4. Обчислити нескінченний
/// ланцюговий дріб для числа pi із заданою точністю.
/// </summary>
/// <remarks>
/// Ім'я файлу: task2.cpp
/// Автор: Чумак Кирил, гр. ІПЗ-11(3)
/// Номер версії модуля: version 1
/// </remarks>

#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

// Константи
const float MIN_ACCURACY = 0.000001f; // нижня межа точності
const float MAX_ACCURACY = 0.01f;     // верхня межа точності
const float PI = 3.1415927f;          // стандартне значення pi

// Глобальні змінні
float accuracy = 0;      // задана точність
float currentValue = 0;  // значення дробу при поточній глибині
float previousValue = 0; // значення дробу при попередній глибині
float difference = 0;    // різниця двох сусідніх значень
int depth = 0;           // поточна глибина дробу

/// <summary>
/// Виводить назву роботи, автора і ланцюговий дріб
/// </summary>
void printTitle()
{
    cout << "Lab work 4. Task 2. Variant 4." << endl;
    cout << "Author: Kyryl Chumak, group IPZ-11(3)" << endl << endl;

    cout << "Calculate the infinite continued fraction for pi with the" << endl;
    cout << "accuracy entered from the keyboard." << endl << endl;
    cout << "pi = 4 / (1 + 1^2 / (3 + 2^2 / (5 + 3^2 / (7 + 4^2 / (9 + ...)))))"
         << endl
         << endl;
}

/// <summary>
/// Вводить точність. Поки введено не число або число поза межами, введення
/// повторюється
/// </summary>
void inputAccuracy()
{
    cout << "Enter accuracy (from 0.000001 to 0.01): ";
    cin >> accuracy;
    while (cin.fail() || accuracy < MIN_ACCURACY || accuracy > MAX_ACCURACY)
    {
        cin.clear();            // скинути помилку введення
        cin.ignore(1000, '\n'); // і пропустити неправильний рядок
        cout << "Error! Enter accuracy from 0.000001 to 0.01: ";
        cin >> accuracy;
    }
}

/// <summary>
/// Рахує дріб заданої глибини знизу вгору, від останнього знаменника до першого
/// </summary>
/// <param name="fractionDepth">кількість вкладених дробів</param>
/// <returns>наближене значення pi</returns>
float calculateFraction(int fractionDepth)
{
    float denominator = 2 * fractionDepth + 1; // поточний знаменник
    int i = 0;                                 // номер рівня дробу

    for (i = fractionDepth; i >= 1; i--)
    {
        denominator = (2 * i - 1) + i * i / denominator;
    }

    return 4 / denominator;
}

/// <summary>
/// Збільшує глибину дробу, поки два сусідні значення не відрізнятимуться менше
/// ніж на точність, і виводить таблицю
/// </summary>
void calculatePi()
{
    currentValue = calculateFraction(depth);

    cout << endl << fixed << setprecision(7);
    cout << setw(6) << "depth" << setw(14) << "value" << setw(14)
         << "difference" << endl;

    do
    {
        previousValue = currentValue;
        depth++;
        currentValue = calculateFraction(depth);
        difference = fabs(currentValue - previousValue);
        cout << setw(6) << depth << setw(14) << currentValue << setw(14)
             << difference << endl;
    } while (difference >= accuracy);
}

/// <summary>
/// Виводить підсумок і порівнює його зі стандартним pi
/// </summary>
void printResult()
{
    cout << endl << "Fraction depth = " << depth << endl;
    cout << "pi from the fraction = " << currentValue << endl;
    cout << "standard pi = " << PI << endl;
    cout << "error = " << fabs(currentValue - PI) << endl;
}

/// <summary>
/// Головна функція програми
/// </summary>
/// <returns>0 після завершення роботи</returns>
int main()
{
    printTitle();
    inputAccuracy();
    calculatePi();
    printResult();
    return 0;
}
