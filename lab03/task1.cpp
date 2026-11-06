/// <summary>
/// Лабораторна робота №3, варіант 6. Обчислити подвійну суму із заданою
/// точністю і подати обчислення таблицею.
/// </summary>
/// <remarks>
/// Ім'я файлу: task1.cpp
/// Автор: Чумак Кирил, гр. ІПЗ-11(3)
/// Номер версії модуля: version 1
/// </remarks>

#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

// Константи
const float MIN_ACCURACY = 0.000001f; // нижня межа точності
const float MAX_ACCURACY = 1;         // верхня межа точності
const float SMALL_LIMIT = 1e-38f;     // межі модуля доданка з умови
const float BIG_LIMIT = 1e38f;

// Глобальні змінні
float accuracy = 0; // задана точність
float term = 0;     // поточний доданок
float total = 0;    // накопичена сума
int x = 0;          // параметр зовнішньої суми
int k = 0;          // параметр внутрішньої суми
int termCount = 0;  // кількість доданків при поточному x

/// <summary>
/// Виводить назву роботи, автора і формулу суми
/// </summary>
void printTitle()
{
    cout << "Lab work 3. Variant 6." << endl;
    cout << "Author: Kyryl Chumak, group IPZ-11(3)" << endl << endl;

    cout << "Calculate the double sum with the accuracy entered from" << endl;
    cout << "the keyboard. Print a table: x, k, the term and the" << endl;
    cout << "accumulated sum." << endl << endl;
    cout << "      5    inf       (-1)^k * x^(2k)" << endl;
    cout << "S =  sum   sum   ------------------------" << endl;
    cout << "     x=1   k=1   k^x * (k + 1) * (k + 2)" << endl << endl;
}

/// <summary>
/// Вводить точність. Поки введено не число або число поза межами, введення
/// повторюється
/// </summary>
void inputAccuracy()
{
    cout << "Enter accuracy (from 0.000001 to 1): ";
    cin >> accuracy;
    while (cin.fail() || accuracy < MIN_ACCURACY || accuracy > MAX_ACCURACY)
    {
        cin.clear();            // скинути помилку введення
        cin.ignore(1000, '\n'); // і пропустити неправильний рядок
        cout << "Error! Enter accuracy from 0.000001 to 1: ";
        cin >> accuracy;
    }
}

/// <summary>
/// Отримує наступний доданок із поточного: множить його на -x^2 * (k + 1) / (k
/// + 3) і x разів на k / (k + 1)
/// </summary>
void calculateNextTerm()
{
    int i = 0; // лічильник множень

    for (i = 1; i <= x; i++)
    {
        term = term * k / (k + 1);
    }
    term = -term * (k + 1) / (k + 3) * x * x;
    k++;
}

/// <summary>
/// Рахує суму і виводить таблицю. Внутрішній цикл працює, поки модуль доданка
/// не менший за точність і лежить між межами умови
/// </summary>
void calculateSum()
{
    cout << endl << scientific << setprecision(6);
    cout << setw(3) << "x" << setw(5) << "k" << setw(16) << "term" << setw(16)
         << "sum" << endl;

    for (x = 1; x <= 5; x++)
    {
        k = 1;
        termCount = 0;
        term = -(float)(x * x) / 6; // перший доданок, коли k = 1

        while (fabs(term) >= accuracy && fabs(term) > SMALL_LIMIT
               && fabs(term) < BIG_LIMIT)
        {
            total = total + term;
            termCount++;
            cout << setw(3) << x << setw(5) << k << setw(16) << term << setw(16)
                 << total << endl;
            calculateNextTerm();
        }

        cout << "number of terms for x = " << x << ": " << termCount << endl;
    }
}

/// <summary>
/// Виводить підсумок
/// </summary>
void printResult()
{
    cout << endl << "S = " << total << endl;
    cout << "For x >= 2 the terms grow, so S is only a partial sum." << endl;
}

/// <summary>
/// Головна функція програми
/// </summary>
/// <returns>0 після завершення роботи</returns>
int main()
{
    printTitle();
    inputAccuracy();
    calculateSum();
    printResult();
    return 0;
}
