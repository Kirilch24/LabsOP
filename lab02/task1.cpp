/// <summary>
/// Лабораторна робота №2, завдання 1, варіант 4. Обчислити значення кусково
/// заданої функції для аргументу, введеного з клавіатури.
/// </summary>
/// <remarks>
/// Ім'я файлу: task1.cpp
/// Автор: Чумак Кирил, гр. ІПЗ-11(3)
/// Номер версії модуля: version 1
/// </remarks>

#include <cmath>
#include <iostream>
using namespace std;

// Глобальні змінні
float x = 0;           // аргумент функції
float y = 0;           // значення функції
bool isDefined = true; // ознака того, що функція визначена в точці x

/// <summary>
/// Вводить аргумент, вибирає гілку функції і виводить результат
/// </summary>
/// <returns>0</returns>
/// <summary>
/// Головна функція програми
/// </summary>
/// <returns>0 після завершення роботи</returns>
int main()
{
    cout << "Lab work 2. Task 1. Variant 4." << endl;
    cout << "Author: Kyryl Chumak, group IPZ-11(3)" << endl << endl;

    cout << "Calculate the function f(x) for x entered from the" << endl;
    cout << "keyboard:" << endl;
    cout << "f(x) = 5 * sqrt(x),  x > 5" << endl;
    cout << "f(x) = 1 / x,        1 < x < 5" << endl;
    cout << "f(x) = x^2,          -5 <= x <= 1" << endl;
    cout << "f(x) = 10 * x,       x < -5" << endl << endl;

    cout << "Enter x: ";
    cin >> x;
    while (cin.fail())
    {
        cin.clear();            // скинути помилку введення
        cin.ignore(1000, '\n'); // і пропустити неправильний рядок
        cout << "Error! Enter x as a number: ";
        cin >> x;
    }

    if (x > 5)
    {
        y = 5 * sqrt(x);
    }
    else if (x > 1 && x < 5)
    {
        y = 1 / x;
    }
    else if (x >= -5 && x <= 1)
    {
        y = x * x;
    }
    else if (x < -5)
    {
        y = 10 * x;
    }
    else
    {
        isDefined = false;
    }

    if (isDefined)
    {
        cout << "f(x) = " << y << endl;
    }
    else
    {
        cout << "The function is not defined for x = " << x << endl;
    }

    return 0;
}
