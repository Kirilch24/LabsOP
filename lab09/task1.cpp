/// <summary>
/// Лабораторна робота №9, завдання 1, варіант 4. Видалити з рядка літери,
/// перетворити цифри в числа і виконати арифметичні дії в порядку знаків.
/// </summary>
/// <remarks>
/// Ім'я файлу: task1.cpp
/// Автор: Чумак Кирил, гр. ІПЗ-11(3)
/// Номер версії модуля: version 1
/// </remarks>

#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

// Константи
const int MAX_LENGTH = 81; // розмір рядка разом із символом кінця

// Глобальні змінні
char text[MAX_LENGTH] = "";      // введений рядок
char cleanText[MAX_LENGTH] = ""; // рядок лише з цифр і знаків дій
int position = 0;                // поточна позиція в cleanText
double total = 0;                // результат; double, бо у float 7 цифр
bool isDivisionByZero = false;   // чи було ділення на нуль

/// <summary>
/// Виводить назву роботи й автора
/// </summary>
void printTitle()
{
    cout << "Lab work 9. Task 1. Variant 4." << endl;
    cout << "Author: Kyryl Chumak, group IPZ-11(3)" << endl << endl;

    cout << "Enter a string of letters, digits and signs + - * /." << endl;
    cout << "Remove the letters, convert the digits to numbers and" << endl;
    cout << "perform the operations from left to right. If a number is" << endl;
    cout << "missing, use 0 for + and -, and 1 for * and /." << endl << endl;
}

/// <summary>
/// Вводить рядок. Якщо рядок задовгий, введення повторюється
/// </summary>
void inputText()
{
    cout << "Enter string (up to 80 characters): ";
    cin.getline(text, MAX_LENGTH);
    while (cin.fail())
    {
        cin.clear();            // скинути помилку введення
        cin.ignore(1000, '\n'); // і пропустити залишок рядка
        cout << "Error! Enter string of up to 80 characters: ";
        cin.getline(text, MAX_LENGTH);
    }
}

/// <summary>
/// Копіює в cleanText лише цифри й знаки дій, а потім виводить обидва рядки
/// </summary>
void removeLetters()
{
    int length = strlen(text);
    int cleanLength = 0;
    int i = 0;
    char symbol = ' ';

    for (i = 0; i < length; i++)
    {
        symbol = text[i];
        if (isdigit((unsigned char)symbol) || symbol == '+' || symbol == '-'
            || symbol == '*' || symbol == '/')
        {
            cleanText[cleanLength] = symbol;
            cleanLength++;
        }
    }
    cleanText[cleanLength] = '\0';

    cout << "Source string: " << text << endl;
    cout << "Without letters: " << cleanText << endl;
}

/// <summary>
/// Перетворює цифри з поточної позиції на число і переходить на перший символ
/// після них
/// </summary>
/// <returns>прочитане число</returns>
double readNumber()
{
    double number = atof(&cleanText[position]);

    while (isdigit(cleanText[position]))
    {
        position++;
    }
    return number;
}

/// <summary>
/// Чистить рядок, виділяє з нього всі числа й виводить їх
/// </summary>
void printNumbers()
{
    int numberCount = 0;

    removeLetters();
    position = 0;

    cout << "Numbers:";
    while (cleanText[position] != '\0')
    {
        if (isdigit(cleanText[position]))
        {
            cout << " " << readNumber();
            numberCount++;
        }
        else
        {
            position++;
        }
    }
    cout << endl << "Count of numbers: " << numberCount << endl;
}

/// <summary>
/// Читає операнд. Якщо в поточній позиції немає числа, операнд дорівнює 0 для +
/// і - та 1 для * і /
/// </summary>
/// <param name="sign">знак дії, для якої потрібен операнд</param>
/// <returns>операнд</returns>
double readOperand(char sign)
{
    double operand = 0;

    if (isdigit(cleanText[position]))
    {
        operand = readNumber();
    }
    else if (sign == '*' || sign == '/')
    {
        operand = 1;
    }
    return operand;
}

/// <summary>
/// Виконує одну дію над результатом. Ділення на нуль не виконується, а лише
/// запам'ятовується
/// </summary>
/// <param name="sign">знак дії</param>
/// <param name="operand">другий операнд дії</param>
void applySign(char sign, double operand)
{
    if (sign == '+')
    {
        total = total + operand;
    }
    else if (sign == '-')
    {
        total = total - operand;
    }
    else if (sign == '*')
    {
        total = total * operand;
    }
    else if (operand == 0)
    {
        isDivisionByZero = true;
    }
    else
    {
        total = total / operand;
    }
}

/// <summary>
/// Чистить рядок, виконує дії зліва направо і виводить вираз разом із
/// результатом
/// </summary>
void calculateExpression()
{
    double operand = 0;
    char sign = ' ';

    removeLetters();
    position = 0;
    isDivisionByZero = false;

    if (cleanText[0] == '\0')
    {
        cout << "Nothing to calculate: no digits or signs." << endl;
    }
    else
    {
        total = readOperand(cleanText[0]);
        cout << "Expression: " << total;

        while (cleanText[position] != '\0')
        {
            sign = cleanText[position];
            position++;
            operand = readOperand(sign);
            cout << sign << operand;
            applySign(sign, operand);
        }

        if (total == 0)
        {
            total = 0; // прибрати знак мінус у нуля, щоб не вивести -0
        }

        if (isDivisionByZero)
        {
            cout << endl << "Error! Division by zero." << endl;
        }
        else
        {
            cout << "=" << total << endl;
        }
    }
}

/// <summary>
/// Виводить меню і виконує вибрані пункти до вибору виходу
/// </summary>
void runMenu()
{
    int choice = 0;

    cout << setprecision(15); // щоб довгі числа виводились усіма цифрами

    do
    {
        cout << endl << "Menu:" << endl;
        cout << "1 - remove letters" << endl;
        cout << "2 - convert digits to numbers" << endl;
        cout << "3 - calculate expression" << endl;
        cout << "0 - exit" << endl;

        cout << "Enter your choice (from 0 to 3): ";
        cin >> choice;
        while (cin.fail() || choice < 0 || choice > 3)
        {
            cin.clear();            // скинути помилку введення
            cin.ignore(1000, '\n'); // і пропустити неправильний рядок
            cout << "Error! Enter choice from 0 to 3: ";
            cin >> choice;
        }

        switch (choice)
        {
            case 1 : removeLetters(); break;
            case 2 : printNumbers(); break;
            case 3 : calculateExpression(); break;
            default : cout << "End of work." << endl; break;
        }
    } while (choice != 0);
}

/// <summary>
/// Головна функція програми
/// </summary>
/// <returns>0 після завершення роботи</returns>
int main()
{
    printTitle();
    inputText();
    runMenu();
    return 0;
}
