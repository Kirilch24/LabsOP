/// <summary>
/// Лабораторна робота №6, завдання 3, варіант 4. Знайти суму, різницю і добуток
/// двох многочленів і вивести їх у вигляді виразів.
/// </summary>
/// <remarks>
/// Ім'я файлу: task3.cpp
/// Автор: Чумак Кирил, гр. ІПЗ-11(3)
/// Номер версії модуля: version 1
/// </remarks>

#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

// Константи
const int MIN_DEGREE = 3;         // найменший степінь за умовою
const int MAX_DEGREE = 10;        // найбільший степінь многочлена
const int MAX_COEFFICIENT = 1000; // найбільший модуль коефіцієнта
const int TERMS = MAX_DEGREE + 1; // найбільша кількість коефіцієнтів
const int PRODUCT_TERMS = 2 * MAX_DEGREE + 1; // коефіцієнтів у добутку

// Глобальні змінні
int firstPolynomial[TERMS] = {0};  // коефіцієнти a[i] при x^(n - i)
int secondPolynomial[TERMS] = {0}; // коефіцієнти b[i] при x^(m - i)
int sum[TERMS] = {0};              // коефіцієнти суми
int difference[TERMS] = {0};       // коефіцієнти різниці
int product[PRODUCT_TERMS] = {0};  // коефіцієнти добутку
int firstDegree = 0;               // степінь n
int secondDegree = 0;              // степінь m
int largerDegree = 0;              // більший зі степенів n і m
int lowerBound = 0;                // нижня межа випадкових коефіцієнтів
int upperBound = 0;                // верхня межа випадкових коефіцієнтів

/// <summary>
/// Виводить назву роботи, автора і вигляд многочленів
/// </summary>
void printTitle()
{
    cout << "Lab work 6. Task 3. Variant 4." << endl;
    cout << "Author: Kyryl Chumak, group IPZ-11(3)" << endl << endl;

    cout << "Enter the degrees n, m of polynomials Pn(x) and Pm(x)," << endl;
    cout << "both greater than 2. Enter the coefficients or generate" << endl;
    cout << "them in a given range. Print the sum, the difference and" << endl;
    cout << "the product." << endl << endl;
    cout << "Pn(x) = a0 * x^n + a1 * x^(n-1) + ... + an" << endl;
    cout << "Pm(x) = b0 * x^m + b1 * x^(m-1) + ... + bm" << endl << endl;
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
/// Вводить степені двох многочленів
/// </summary>
void inputDegrees()
{
    cout << "Enter degree n of the first polynomial (from 3 to 10): ";
    firstDegree = inputNumber(MIN_DEGREE, MAX_DEGREE);

    cout << "Enter degree m of the second polynomial (from 3 to 10): ";
    secondDegree = inputNumber(MIN_DEGREE, MAX_DEGREE);
}

/// <summary>
/// Вводить коефіцієнти многочлена з клавіатури
/// </summary>
/// <param name="polynomial">коефіцієнти</param>
/// <param name="degree">степінь</param>
void enterPolynomial(int polynomial[], int degree)
{
    int i = 0; // індекс коефіцієнта

    for (i = 0; i <= degree; i++)
    {
        cout << "Coefficient at x^" << degree - i << " (from -1000 to 1000): ";
        polynomial[i] = inputNumber(-MAX_COEFFICIENT, MAX_COEFFICIENT);
    }
}

/// <summary>
/// Вводить межі діапазону випадкових коефіцієнтів
/// </summary>
void inputRange()
{
    cout << "Enter lower bound (from -1000 to 1000): ";
    lowerBound = inputNumber(-MAX_COEFFICIENT, MAX_COEFFICIENT);

    cout << "Enter upper bound (from " << lowerBound << " to 1000): ";
    upperBound = inputNumber(lowerBound, MAX_COEFFICIENT);
}

/// <summary>
/// Заповнює многочлен випадковими коефіцієнтами з діапазону
/// </summary>
/// <param name="polynomial">коефіцієнти</param>
/// <param name="degree">степінь</param>
void generatePolynomial(int polynomial[], int degree)
{
    int i = 0; // індекс коефіцієнта

    for (i = 0; i <= degree; i++)
    {
        polynomial[i] = lowerBound + rand() % (upperBound - lowerBound + 1);
    }
}

/// <summary>
/// Виводить меню і створює многочлени вибраним способом
/// </summary>
void createPolynomials()
{
    int choice = 0; // вибраний пункт меню

    cout << endl << "How to create the coefficients:" << endl;
    cout << "1 - enter from the keyboard" << endl;
    cout << "2 - generate random numbers" << endl;
    cout << "Your choice: ";
    choice = inputNumber(1, 2);

    switch (choice)
    {
        case 1 :
            cout << "First polynomial:" << endl;
            enterPolynomial(firstPolynomial, firstDegree);
            cout << "Second polynomial:" << endl;
            enterPolynomial(secondPolynomial, secondDegree);
            break;
        case 2 :
            inputRange();
            srand(time(NULL));
            generatePolynomial(firstPolynomial, firstDegree);
            generatePolynomial(secondPolynomial, secondDegree);
            break;
        default : cout << "There is no such menu item." << endl; break;
    }
}

/// <summary>
/// Обчислює суму і різницю. Менший многочлен зсувається вправо, щоб коефіцієнти
/// при однакових степенях стояли під одним індексом
/// </summary>
void calculateSumAndDifference()
{
    int i = 0;     // індекс коефіцієнта
    int shift = 0; // зсув індексів

    largerDegree = firstDegree;
    if (secondDegree > largerDegree)
    {
        largerDegree = secondDegree;
    }

    shift = largerDegree - firstDegree;
    for (i = 0; i <= firstDegree; i++)
    {
        sum[i + shift] = firstPolynomial[i];
        difference[i + shift] = firstPolynomial[i];
    }

    shift = largerDegree - secondDegree;
    for (i = 0; i <= secondDegree; i++)
    {
        sum[i + shift] = sum[i + shift] + secondPolynomial[i];
        difference[i + shift] = difference[i + shift] - secondPolynomial[i];
    }
}

/// <summary>
/// Обчислює добуток: кожен коефіцієнт першого многочлена множиться на кожен
/// коефіцієнт другого
/// </summary>
void calculateProduct()
{
    int i = 0; // індекс коефіцієнта першого многочлена
    int j = 0; // індекс коефіцієнта другого многочлена

    for (i = 0; i <= firstDegree; i++)
    {
        for (j = 0; j <= secondDegree; j++)
        {
            product[i + j] =
                product[i + j] + firstPolynomial[i] * secondPolynomial[j];
        }
    }
}

/// <summary>
/// Виводить один доданок: знак, модуль коефіцієнта і степінь x. Коефіцієнт 1
/// перед x не пишеться
/// </summary>
/// <param name="coefficient">коефіцієнт</param>
/// <param name="power">степінь x</param>
/// <param name="isFirst">чи це перший доданок виразу</param>
void printTerm(int coefficient, int power, bool isFirst)
{
    if (coefficient < 0)
    {
        if (isFirst)
        {
            cout << "-";
        }
        else
        {
            cout << " - ";
        }
    }
    else if (!isFirst)
    {
        cout << " + ";
    }

    if (abs(coefficient) != 1 || power == 0)
    {
        cout << abs(coefficient);
    }

    if (power == 1)
    {
        cout << "x";
    }
    else if (power > 1)
    {
        cout << "x^" << power;
    }
}

/// <summary>
/// Виводить многочлен без нульових доданків. Якщо всі коефіцієнти нульові,
/// виводить 0
/// </summary>
/// <param name="polynomial">коефіцієнти</param>
/// <param name="degree">степінь</param>
void printPolynomial(int polynomial[], int degree)
{
    int i = 0;           // індекс коефіцієнта
    bool isFirst = true; // чи ще не було доданків

    for (i = 0; i <= degree; i++)
    {
        if (polynomial[i] != 0)
        {
            printTerm(polynomial[i], degree - i, isFirst);
            isFirst = false;
        }
    }

    if (isFirst)
    {
        cout << "0";
    }
    cout << endl;
}

/// <summary>
/// Виводить обидва многочлени, суму, різницю і добуток
/// </summary>
void printResults()
{
    cout << endl << "Pn(x) = ";
    printPolynomial(firstPolynomial, firstDegree);
    cout << "Pm(x) = ";
    printPolynomial(secondPolynomial, secondDegree);

    cout << endl << "Sum: ";
    printPolynomial(sum, largerDegree);
    cout << "Difference: ";
    printPolynomial(difference, largerDegree);
    cout << "Product: ";
    printPolynomial(product, firstDegree + secondDegree);
}

/// <summary>
/// Головна функція програми
/// </summary>
/// <returns>0 після завершення роботи</returns>
int main()
{
    printTitle();
    inputDegrees();
    createPolynomials();
    calculateSumAndDifference();
    calculateProduct();
    printResults();
    return 0;
}
