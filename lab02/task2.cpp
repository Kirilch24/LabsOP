/// <summary>
/// Лабораторна робота №2, завдання 2, варіант 8. Визначити кількість різних і
/// кількість однакових чисел серед трьох введених.
/// </summary>
/// <remarks>
/// Ім'я файлу: task2.cpp
/// Автор: Чумак Кирил, гр. ІПЗ-11(3)
/// Номер версії модуля: version 1
/// </remarks>

#include <iostream>
using namespace std;

// Глобальні змінні
float a = 0;            // перше число
float b = 0;            // друге число
float c = 0;            // третє число
int differentCount = 0; // кількість різних чисел
int equalCount = 0;     // кількість однакових чисел

/// <summary>
/// Вводить три числа, порівнює їх і виводить обидві кількості
/// </summary>
/// <returns>0</returns>
/// <summary>
/// Головна функція програми
/// </summary>
/// <returns>0 після завершення роботи</returns>
int main()
{
    cout << "Lab work 2. Task 2. Variant 8." << endl;
    cout << "Author: Kyryl Chumak, group IPZ-11(3)" << endl << endl;

    cout << "Enter three real numbers. Find how many different numbers" << endl;
    cout << "there are among them and how many equal ones." << endl << endl;

    cout << "Enter three real numbers: ";
    cin >> a >> b >> c;
    while (cin.fail())
    {
        cin.clear();            // скинути помилку введення
        cin.ignore(1000, '\n'); // і пропустити неправильний рядок
        cout << "Error! Enter three real numbers: ";
        cin >> a >> b >> c;
    }

    if (a == b && b == c)
    {
        differentCount = 1;
        equalCount = 3;
    }
    else if (a == b || a == c || b == c)
    {
        differentCount = 2;
        equalCount = 2;
    }
    else
    {
        differentCount = 3;
        equalCount = 0;
    }

    cout << "Different numbers: " << differentCount << endl;
    cout << "Equal numbers: " << equalCount << endl;
    return 0;
}
