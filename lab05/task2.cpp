/// <summary>
/// Лабораторна робота №5, завдання 2, варіант 8. Рекурсивно знайти кількість
/// k-значних натуральних чисел із сумою цифр s.
/// </summary>
/// <remarks>
/// Ім'я файлу: task2.cpp
/// Автор: Чумак Кирил, гр. ІПЗ-11(3)
/// Номер версії модуля: version 1
/// </remarks>

#include <iostream>
using namespace std;

// Константи
const int MIN_DIGITS = 1; // найменша кількість цифр
const int MAX_DIGITS = 7; // найбільша кількість цифр
const int MIN_SUM = 1;    // найменша сума цифр
const int MAX_SUM = 63;   // найбільша сума цифр семизначного числа

// Глобальні змінні
int digitCount = 0;  // кількість цифр k
int digitSum = 0;    // сума цифр s
int numberCount = 0; // кількість знайдених чисел

/// <summary>
/// Виводить назву роботи, автора і завдання
/// </summary>
void printTitle()
{
    cout << "Lab work 5. Task 2. Variant 8." << endl;
    cout << "Author: Kyryl Chumak, group IPZ-11(3)" << endl << endl;

    cout << "Enter natural numbers k and s. Count the k-digit natural" << endl;
    cout << "numbers with the sum of digits s. The first digit is not" << endl;
    cout << "0." << endl << endl;
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
/// Вводить кількість цифр k і суму цифр s
/// </summary>
void inputData()
{
    cout << "Enter k (from 1 to 7): ";
    digitCount = inputNumber(MIN_DIGITS, MAX_DIGITS);

    cout << "Enter s (from 1 to 63): ";
    digitSum = inputNumber(MIN_SUM, MAX_SUM);
}

/// <summary>
/// Рахує, скількома способами можна записати задану кількість цифр від 0 до 9
/// із заданою сумою. Для кожної цифри викликає себе для решти позицій
/// </summary>
/// <param name="digitsLeft">кількість вільних позицій</param>
/// <param name="sumLeft">сума, яку ще треба набрати</param>
/// <returns>кількість способів</returns>
int countEndings(int digitsLeft, int sumLeft)
{
    int total = 0; // кількість способів
    int digit = 0; // цифра на поточній позиції

    if (digitsLeft == 0)
    {
        if (sumLeft == 0)
        {
            total = 1;
        }
    }
    else
    {
        for (digit = 0; digit <= 9 && digit <= sumLeft; digit++)
        {
            total = total + countEndings(digitsLeft - 1, sumLeft - digit);
        }
    }

    return total;
}

/// <summary>
/// Перебирає першу цифру числа від 1 до 9 і додає кількість закінчень для
/// кожної з них
/// </summary>
void countNumbers()
{
    int digit = 0; // перша цифра числа

    for (digit = 1; digit <= 9 && digit <= digitSum; digit++)
    {
        numberCount =
            numberCount + countEndings(digitCount - 1, digitSum - digit);
    }
}

/// <summary>
/// Виводить результат
/// </summary>
void printResult()
{
    cout << endl
         << "Numbers with " << digitCount << " digits and digit sum "
         << digitSum << ": " << numberCount << endl;
}

/// <summary>
/// Головна функція програми
/// </summary>
/// <returns>0 після завершення роботи</returns>
int main()
{
    printTitle();
    inputData();
    countNumbers();
    printResult();
    return 0;
}
