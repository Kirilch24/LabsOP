/// <summary>
/// Лабораторна робота №6, завдання 2, варіант 4. Відсортувати масив швидким
/// сортуванням, знайти значення рекурсивним бінарним пошуком і порахувати
/// порівняння та обміни.
/// </summary>
/// <remarks>
/// Ім'я файлу: task2.cpp
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
int numbers[MAX_SIZE] = {0}; // масив
int arraySize = 0;           // кількість елементів
int sortCompareCount = 0;    // кількість порівнянь при сортуванні
int swapCount = 0;           // кількість обмінів
int searchCompareCount = 0;  // кількість порівнянь при пошуку
int target = 0;              // значення, яке шукаємо
bool isDetailed = false;     // чи виводити проміжні ітерації

/// <summary>
/// Виводить назву роботи, автора і завдання
/// </summary>
void printTitle()
{
    cout << "Lab work 6. Task 2. Variant 4." << endl;
    cout << "Author: Kyryl Chumak, group IPZ-11(3)" << endl << endl;

    cout << "Create an array from the keyboard or with random numbers." << endl;
    cout << "Sort it by quick sort and find a value by recursive" << endl;
    cout << "binary search. Count the comparisons and the swaps. Print" << endl;
    cout << "only the sorted array or the intermediate iterations too." << endl
         << endl;
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
/// Вводить елементи масиву з клавіатури
/// </summary>
void enterArray()
{
    int i = 0; // індекс елемента

    for (i = 0; i < arraySize; i++)
    {
        cout << "Element " << i << " (from -10000 to 10000): ";
        numbers[i] = inputNumber(-MAX_VALUE, MAX_VALUE);
    }
}

/// <summary>
/// Заповнює масив псевдовипадковими числами
/// </summary>
void generateArray()
{
    int i = 0; // індекс елемента

    srand(time(NULL));
    for (i = 0; i < arraySize; i++)
    {
        numbers[i] = rand() % RANDOM_RANGE;
    }
}

/// <summary>
/// Виводить елементи масиву в один рядок
/// </summary>
void printArray()
{
    int i = 0; // індекс елемента

    for (i = 0; i < arraySize; i++)
    {
        cout << numbers[i] << " ";
    }
    cout << endl;
}

/// <summary>
/// Вводить розмір, виводить меню, створює масив вибраним способом і виводить
/// його
/// </summary>
void createArray()
{
    int choice = 0; // вибраний пункт меню

    cout << "Enter size of the array (from 1 to 100): ";
    arraySize = inputNumber(1, MAX_SIZE);

    cout << endl << "How to create the array:" << endl;
    cout << "1 - enter from the keyboard" << endl;
    cout << "2 - generate random numbers" << endl;
    cout << "Your choice: ";
    choice = inputNumber(1, 2);

    switch (choice)
    {
        case 1 : enterArray(); break;
        case 2 : generateArray(); break;
        default : cout << "There is no such menu item." << endl; break;
    }

    cout << endl << "Array: ";
    printArray();
}

/// <summary>
/// Дає вибрати режим виведення
/// </summary>
void chooseOutputMode()
{
    int choice = 0; // вибраний режим

    cout << endl << "Output mode:" << endl;
    cout << "1 - only the sorted array" << endl;
    cout << "2 - with intermediate iterations" << endl;
    cout << "Your choice: ";
    choice = inputNumber(1, 2);

    if (choice == 2)
    {
        isDetailed = true;
    }
}

/// <summary>
/// Сортує частину масиву за алгоритмом Хоара і рахує порівняння елементів та
/// обміни
/// </summary>
/// <param name="left">індекс початку частини</param>
/// <param name="right">індекс її кінця</param>
void quickSort(int left, int right)
{
    int i = left;                            // індекс, що йде вправо
    int j = right;                           // індекс, що йде вліво
    int pivot = numbers[(left + right) / 2]; // опорний елемент
    int temp = 0;                            // змінна для обміну

    if (isDetailed)
    {
        cout << "left = " << left << ", right = " << right
             << ", pivot = " << pivot << endl;
    }

    do
    {
        sortCompareCount++;
        while (numbers[i] < pivot)
        {
            i++;
            sortCompareCount++;
        }

        sortCompareCount++;
        while (numbers[j] > pivot)
        {
            j--;
            sortCompareCount++;
        }

        if (i < j)
        {
            temp = numbers[i];
            numbers[i] = numbers[j];
            numbers[j] = temp;
            swapCount++;

            if (isDetailed)
            {
                printArray();
            }
        }

        if (i <= j)
        {
            i++;
            j--;
        }
    } while (i <= j);

    if (left < j)
    {
        quickSort(left, j);
    }
    if (i < right)
    {
        quickSort(i, right);
    }
}

/// <summary>
/// Запускає сортування і виводить його результат
/// </summary>
void sortArray()
{
    cout << endl;
    quickSort(0, arraySize - 1);

    cout << "Sorted array: ";
    printArray();
    cout << "Sort comparisons: " << sortCompareCount << endl;
    cout << "Swaps: " << swapCount << endl;
}

/// <summary>
/// Шукає значення target у частині відсортованого масиву: порівнює його із
/// середнім елементом і викликає себе для лівої або правої половини
/// </summary>
/// <param name="left">індекс початку частини</param>
/// <param name="right">індекс її кінця</param>
/// <returns>індекс знайденого елемента, або -1</returns>
int findValue(int left, int right)
{
    int index = -1; // індекс знайденого елемента
    int middle = 0; // індекс середнього елемента

    if (left <= right)
    {
        middle = (left + right) / 2;
        searchCompareCount++;

        if (numbers[middle] == target)
        {
            index = middle;
        }
        else
        {
            searchCompareCount++;

            if (target < numbers[middle])
            {
                index = findValue(left, middle - 1);
            }
            else
            {
                index = findValue(middle + 1, right);
            }
        }
    }

    return index;
}

/// <summary>
/// Вводить значення, шукає його і виводить результат пошуку
/// </summary>
void searchInArray()
{
    int foundIndex = -1; // індекс знайденого елемента

    cout << endl << "Enter value to find (from -10000 to 10000): ";
    target = inputNumber(-MAX_VALUE, MAX_VALUE);
    foundIndex = findValue(0, arraySize - 1);

    if (foundIndex == -1)
    {
        cout << "Value " << target << " is not in the array." << endl;
    }
    else
    {
        cout << "Value " << target << " has index " << foundIndex
             << " in the sorted array." << endl;
    }
    cout << "Search comparisons: " << searchCompareCount << endl;
}

/// <summary>
/// Головна функція програми
/// </summary>
/// <returns>0 після завершення роботи</returns>
int main()
{
    printTitle();
    createArray();
    chooseOutputMode();
    sortArray();
    searchInArray();
    return 0;
}
