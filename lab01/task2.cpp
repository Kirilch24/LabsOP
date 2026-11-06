/// <summary>
/// Лабораторна робота №1, завдання 2, варіант 3. Знайти довжини медіан і
/// бісектрис трикутника за його сторонами.
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

// Глобальні змінні
float a = 0;         // сторона a
float b = 0;         // сторона b
float c = 0;         // сторона c
float perimeter = 0; // периметр трикутника
float medianA = 0;   // медіана до сторони a
float medianB = 0;   // медіана до сторони b
float medianC = 0;   // медіана до сторони c
float bisectorA = 0; // бісектриса до сторони a
float bisectorB = 0; // бісектриса до сторони b
float bisectorC = 0; // бісектриса до сторони c

/// <summary>
/// Вводить сторони, перевіряє, чи існує трикутник, і виводить довжини медіан і
/// бісектрис
/// </summary>
/// <returns>0</returns>
/// <summary>
/// Головна функція програми
/// </summary>
/// <returns>0 після завершення роботи</returns>
int main()
{
    cout << "Lab work 1. Task 2. Variant 3." << endl;
    cout << "Author: Kyryl Chumak, group IPZ-11(3)" << endl << endl;

    cout << "Find the lengths of all medians and bisectors of a" << endl;
    cout << "triangle with the sides a, b, c entered from the" << endl;
    cout << "keyboard." << endl << endl;

    cout << "Enter sides a, b, c: ";
    cin >> a >> b >> c;
    while (cin.fail() || a <= 0 || b <= 0 || c <= 0)
    {
        cin.clear();            // скинути помилку введення
        cin.ignore(1000, '\n'); // і пропустити неправильний рядок
        cout << "Error! Enter three positive numbers a, b, c: ";
        cin >> a >> b >> c;
    }

    if (a + b > c && a + c > b && b + c > a)
    {
        perimeter = a + b + c;

        medianA = sqrt(2 * b * b + 2 * c * c - a * a) / 2;
        medianB = sqrt(2 * a * a + 2 * c * c - b * b) / 2;
        medianC = sqrt(2 * a * a + 2 * b * b - c * c) / 2;

        bisectorA = sqrt(b * c * perimeter * (b + c - a)) / (b + c);
        bisectorB = sqrt(a * c * perimeter * (a + c - b)) / (a + c);
        bisectorC = sqrt(a * b * perimeter * (a + b - c)) / (a + b);

        cout << fixed << setprecision(4);
        cout << "Medians:   " << setw(10) << medianA << setw(10) << medianB
             << setw(10) << medianC << endl;
        cout << "Bisectors: " << setw(10) << bisectorA << setw(10) << bisectorB
             << setw(10) << bisectorC << endl;
    }
    else
    {
        cout << "A triangle with these sides does not exist." << endl;
    }

    return 0;
}
