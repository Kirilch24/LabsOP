/// <summary>
/// Лабораторна робота №6, завдання 1, варіант 4. Знайти найменший елемент
/// першого масиву серед тих, що збігаються з елементами другого масиву.
/// </summary>
/// <remarks>
/// Ім'я файлу: task1.cpp
/// Автор: Чумак Кирил, гр. ІПЗ-11(3)
/// Номер версії модуля: version 1
/// </remarks>

#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

// Константи
const int MAX_SIZE = 100;    // найбільша кількість елементів масиву
const int MAX_VALUE = 10000; // найбільший модуль елемента з клавіатури
const int RANDOM_RANGE = 30; // випадкові числа від 0 до 29

// Глобальні змінні
int firstArray[MAX_SIZE] = {0};  // перший масив
int secondArray[MAX_SIZE] = {0}; // другий масив
int firstSize = 0;               // кількість елементів першого масиву
int secondSize = 0;              // кількість елементів другого масиву
int smallestIndex = -1;          // індекс знайденого елемента, -1 якщо немає

/// <summary>
/// Виводить назву роботи, автора і завдання
/// </summary>
void printTitle()
{
    cout << "Lab work 6. Task 1. Variant 4." << endl;
    cout << "Author: Kyryl Chumak, group IPZ-11(3)" << endl << endl;

    cout << "Create two arrays, from the keyboard or with random" << endl;
    cout << "numbers. Find the smallest element of the first array" << endl;
    cout << "that is equal to some element of the second array. Print" << endl;
    cout << "the arrays, this element and its index." << endl << endl;
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
/// Вводить кількість елементів обох масивів
/// </summary>
void inputSizes()
{
    cout << "Enter size of the first array (from 1 to 100): ";
    firstSize = inputNumber(1, MAX_SIZE);

    cout << "Enter size of the second array (from 1 to 100): ";
    secondSize = inputNumber(1, MAX_SIZE);
}

/// <summary>
/// Вводить елементи масиву з клавіатури
/// </summary>
/// <param name="array">масив</param>
/// <param name="size">кількість елементів</param>
void enterArray(int array[], int size)
{
    int i = 0; // індекс елемента

    for (i = 0; i < size; i++)
    {
        cout << "Element " << i << " (from -10000 to 10000): ";
        array[i] = inputNumber(-MAX_VALUE, MAX_VALUE);
    }
}

/// <summary>
/// Заповнює масив псевдовипадковими числами
/// </summary>
/// <param name="array">масив</param>
/// <param name="size">кількість елементів</param>
void generateArray(int array[], int size)
{
    int i = 0; // індекс елемента

    for (i = 0; i < size; i++)
    {
        array[i] = rand() % RANDOM_RANGE;
    }
}

/// <summary>
/// Виводить меню і створює масиви вибраним способом
/// </summary>
void createArrays()
{
    int choice = 0; // вибраний пункт меню

    cout << endl << "How to create the arrays:" << endl;
    cout << "1 - enter from the keyboard" << endl;
    cout << "2 - generate random numbers" << endl;
    cout << "Your choice: ";
    choice = inputNumber(1, 2);

    switch (choice)
    {
        case 1 :
            cout << "First array:" << endl;
            enterArray(firstArray, firstSize);
            cout << "Second array:" << endl;
            enterArray(secondArray, secondSize);
            break;
        case 2 :
            srand(time(NULL));
            generateArray(firstArray, firstSize);
            generateArray(secondArray, secondSize);
            break;
        default : cout << "There is no such menu item." << endl; break;
    }
}

/// <summary>
/// Виводить елементи масиву в один рядок
/// </summary>
/// <param name="array">масив</param>
/// <param name="size">кількість елементів</param>
void printArray(int array[], int size)
{
    int i = 0; // індекс елемента

    for (i = 0; i < size; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

/// <summary>
/// Перевіряє, чи є значення в другому масиві
/// </summary>
/// <param name="value">значення, яке шукаємо</param>
/// <returns>true, якщо значення є в другому масиві</returns>
bool isInSecondArray(int value)
{
    bool isFound = false; // чи знайдено значення
    int i = 0;            // індекс елемента

    for (i = 0; i < secondSize; i++)
    {
        if (secondArray[i] == value)
        {
            isFound = true;
        }
    }

    return isFound;
}

/// <summary>
/// Шукає в першому масиві найменший елемент, який є в другому масиві. Менший
/// елемент замінює знайдений, тому серед однакових мінімумів лишається перший
/// </summary>
void findSmallestCommon()
{
    int i = 0; // індекс елемента першого масиву

    for (i = 0; i < firstSize; i++)
    {
        if (isInSecondArray(firstArray[i]))
        {
            if (smallestIndex == -1
                || firstArray[i] < firstArray[smallestIndex])
            {
                smallestIndex = i;
            }
        }
    }
}

/// <summary>
/// Виводить обидва масиви і результат пошуку
/// </summary>
void printResult()
{
    cout << endl << "First array:  ";
    printArray(firstArray, firstSize);
    cout << "Second array: ";
    printArray(secondArray, secondSize);

    if (smallestIndex == -1)
    {
        cout << "The arrays have no equal elements." << endl;
    }
    else
    {
        cout << "Smallest common element: " << firstArray[smallestIndex]
             << endl;
        cout << "Its index in the first array: " << smallestIndex << endl;
    }
}

/// <summary>
/// Головна функція програми
/// </summary>
/// <returns>0 після завершення роботи</returns>
int main()
{
    printTitle();
    inputSizes();
    createArrays();
    findSmallestCommon();
    printResult();
    return 0;
}
