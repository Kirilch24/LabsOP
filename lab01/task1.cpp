/// <summary>
/// Лабораторна робота №1, завдання 1, варіант 28. Обчислити значення
/// арифметичного виразу за числами, введеними з клавіатури.
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
float a = 0;           // число A
float b = 0;           // число B
float c = 0;           // кут C у радіанах
float difference = 0;  // значення виразу A - 4B
float numerator = 0;   // чисельник
float denominator = 0; // знаменник
float x = 0;           // значення виразу X

/// <summary>
/// Вводить числа, обчислює вираз і виводить результат
/// </summary>
/// <returns>0</returns>
/// <summary>
/// Головна функція програми
/// </summary>
/// <returns>0 після завершення роботи</returns>
int main()
{
    cout << "Lab work 1. Task 1. Variant 28." << endl;
    cout << "Author: Kyryl Chumak, group IPZ-11(3)" << endl << endl;

    cout << "Calculate the value of the expression for A, B, C entered" << endl;
    cout << "from the keyboard:" << endl;
    cout << "X = (A - 4B)^2 / (1 + (1 + sin C)(1 + cos C))" << endl;
    cout << "Angle C is in radians." << endl << endl;

    cout << "Enter A, B, C: ";
    cin >> a >> b >> c;
    while (cin.fail())
    {
        cin.clear();            // скинути помилку введення
        cin.ignore(1000, '\n'); // і пропустити неправильний рядок
        cout << "Error! Enter three numbers A, B, C: ";
        cin >> a >> b >> c;
    }

    difference = a - 4 * b;
    numerator = difference * difference;
    denominator = 1 + (1 + sin(c)) * (1 + cos(c));
    x = numerator / denominator;

    cout << "Numerator = " << numerator << endl;
    cout << "Denominator = " << denominator << endl;
    cout << "X = " << x << endl;
    return 0;
}
