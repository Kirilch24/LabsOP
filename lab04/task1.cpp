/// <summary>
/// Лабораторна робота №4, завдання 1, варіант 4. Обчислити кусково задану
/// функцію через ряд для arcsin(x) і подати результати таблицею.
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
const float MAX_ACCURACY = 0.01f;     // верхня межа точності
const int MAX_STEPS = 1000;           // найбільша кількість кроків
const float STEP_RESERVE = 0.001f;    // запас на похибку float

// Глобальні змінні
float minX = 0;         // найменше значення аргументу
float maxX = 0;         // найбільше значення аргументу
float step = 0;         // крок зміни аргументу
float accuracy = 0;     // задана точність
float x = 0;            // поточне значення аргументу
float y = 0;            // значення функції через ряд
float standardY = 0;    // значення через бібліотечну функцію
float error = 0;        // похибка
bool isDefined = false; // ознака того, що функція визначена в точці x

/// <summary>
/// Виводить назву роботи, автора, функцію y і ряд для arcsin
/// </summary>
void printTitle()
{
    cout << "Lab work 4. Task 1. Variant 4." << endl;
    cout << "Author: Kyryl Chumak, group IPZ-11(3)" << endl << endl;

    cout << "Calculate y for x from min to max with a given step," << endl;
    cout << "expanding arcsin into a Taylor series with the accuracy" << endl;
    cout << "entered from the keyboard. Print x, y, the standard value" << endl;
    cout << "and the error." << endl << endl;
    cout << "y = arcsin(x / 2) / arcsin(2x),  -2 <= x < 0" << endl;
    cout << "y = arcsin(x + 5) + arcsin(x^2),  0 <= x <= 2" << endl;
    cout << "arcsin(t) = t + t^3 / (2 * 3) + 1 * 3 * t^5 / (2 * 4 * 5) + ..."
         << endl
         << endl;
}

/// <summary>
/// Вводить межі аргументу і крок із перевіркою
/// </summary>
void inputRange()
{
    cout << "Enter minimum x: ";
    cin >> minX;
    while (cin.fail())
    {
        cin.clear();            // скинути помилку введення
        cin.ignore(1000, '\n'); // і пропустити неправильний рядок
        cout << "Error! Enter minimum x as a number: ";
        cin >> minX;
    }

    cout << "Enter maximum x (not less than minimum): ";
    cin >> maxX;
    while (cin.fail() || maxX < minX)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Error! Enter maximum x not less than minimum: ";
        cin >> maxX;
    }

    cout << "Enter step (greater than 0, at most 1000 steps): ";
    cin >> step;
    while (cin.fail() || step <= 0 || (maxX - minX) / step > MAX_STEPS)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Error! Enter step greater than 0, at most 1000 steps: ";
        cin >> step;
    }
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
/// Рахує суму ряду для arcsin. Наступний член ряду отримується з поточного,
/// цикл працює, поки член ряду не менший за точність
/// </summary>
/// <param name="argument">аргумент від -1 до 1</param>
/// <returns>сума ряду</returns>
float calculateArcsin(float argument)
{
    float member = argument; // поточний член ряду
    float sum = argument;    // сума ряду
    int n = 0;               // номер члена ряду

    while (fabs(member) >= accuracy)
    {
        member = member * argument * argument * (2 * n + 1) * (2 * n + 1)
                 / ((2 * n + 2) * (2 * n + 3));
        sum = sum + member;
        n++;
    }

    return sum;
}

/// <summary>
/// Обчислює y і стандартне значення для поточного x. Якщо x поза межами або
/// аргумент arcsin за модулем більший за 1, функція не визначена
/// </summary>
void calculateFunction()
{
    isDefined = false;

    if (x >= -2 && x < 0)
    {
        if (fabs(x / 2) <= 1 && fabs(2 * x) <= 1)
        {
            y = calculateArcsin(x / 2) / calculateArcsin(2 * x);
            standardY = asin(x / 2) / asin(2 * x);
            isDefined = true;
        }
    }
    else if (x >= 0 && x <= 2)
    {
        if (fabs(x + 5) <= 1 && fabs(x * x) <= 1)
        {
            y = calculateArcsin(x + 5) + calculateArcsin(x * x);
            standardY = asin(x + 5) + asin(x * x);
            isDefined = true;
        }
    }
}

/// <summary>
/// Виводить таблицю. Кількість кроків рахується наперед, щоб останнє значення x
/// не втратилось через похибку float
/// </summary>
void printTable()
{
    int stepCount = 0; // кількість кроків
    int i = 0;         // номер кроку

    cout << endl
         << setw(9) << "x" << setw(13) << "y" << setw(13) << "standard"
         << setw(13) << "error" << endl;

    stepCount = (int)((maxX - minX) / step + STEP_RESERVE);
    for (i = 0; i <= stepCount; i++)
    {
        x = minX + i * step;
        calculateFunction();

        cout << fixed << setprecision(4) << setw(9) << x;
        if (isDefined)
        {
            error = fabs(y - standardY);
            cout << setprecision(6) << setw(13) << y << setw(13) << standardY
                 << scientific << setprecision(3) << setw(13) << error << endl;
        }
        else
        {
            cout << "   function is not defined" << endl;
        }
    }
}

/// <summary>
/// Головна функція програми
/// </summary>
/// <returns>0 після завершення роботи</returns>
int main()
{
    printTitle();
    inputRange();
    inputAccuracy();
    printTable();
    return 0;
}
