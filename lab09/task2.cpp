/// <summary>
/// Лабораторна робота №9, завдання 2, варіант 4. Стиснути текст за шифром так,
/// щоб довжина стиснутого тексту була найменшою.
/// </summary>
/// <remarks>
/// Ім'я файлу: task2.cpp
/// Автор: Чумак Кирил, гр. ІПЗ-11(3)
/// Номер версії модуля: version 1
/// </remarks>

#include <cctype>
#include <cstring>
#include <iostream>
using namespace std;

// Константи
const int MAX_LINES = 10;   // найбільша кількість рядків тексту
const int MAX_CIPHERS = 10; // найбільша кількість рядків шифру
const int MAX_LENGTH = 81;  // розмір рядка разом із символом кінця

// Глобальні змінні
char text[MAX_LINES][MAX_LENGTH] = {""};       // текст малими літерами
char cipher[MAX_CIPHERS][MAX_LENGTH] = {""};   // рядки шифру
char compressed[MAX_LINES][MAX_LENGTH] = {""}; // стиснутий текст
int best[MAX_LENGTH] = {0};       // найменша довжина перших i символів
int usedCipher[MAX_LENGTH] = {0}; // номер шифру в позиції i або -1
int lineCount = 0;                // кількість рядків тексту
int cipherCount = 0;              // кількість рядків шифру

/// <summary>
/// Виводить назву роботи й автора
/// </summary>
void printTitle()
{
    cout << "Lab work 9. Task 2. Variant 4." << endl;
    cout << "Author: Kyryl Chumak, group IPZ-11(3)" << endl << endl;

    cout << "Enter a text of n lines and a cipher: lines like Aab," << endl;
    cout << "where a capital letter stands for a sequence of small" << endl;
    cout << "letters. Replace the sequences with the capital letters" << endl;
    cout << "so that the text is as short as possible." << endl << endl;
}

/// <summary>
/// Вводить ціле число в заданих межах і пропускає кінець рядка. Підказку
/// виводить той, хто її викликає
/// </summary>
/// <param name="minValue">нижня межа</param>
/// <param name="maxValue">верхня межа</param>
/// <returns>введене число</returns>
int inputNumber(int minValue, int maxValue)
{
    int number = 0;

    cin >> number;
    while (cin.fail() || number < minValue || number > maxValue)
    {
        cin.clear();            // скинути помилку введення
        cin.ignore(1000, '\n'); // і пропустити неправильний рядок
        cout << "Error! Enter number from " << minValue << " to " << maxValue
             << ": ";
        cin >> number;
    }
    cin.ignore(1000, '\n'); // кінець рядка не потрапить у cin.getline

    return number;
}

/// <summary>
/// Вводить один рядок. Якщо він задовгий, введення повторюється
/// </summary>
/// <param name="line">рядок, у який записується введення</param>
void inputLine(char line[])
{
    cin.getline(line, MAX_LENGTH);
    while (cin.fail())
    {
        cin.clear();            // скинути помилку введення
        cin.ignore(1000, '\n'); // і пропустити залишок рядка
        cout << "Error! Enter up to 80 characters: ";
        cin.getline(line, MAX_LENGTH);
    }
}

/// <summary>
/// Перевіряє, що рядок не порожній і містить лише латинські літери
/// </summary>
/// <param name="line">рядок, який перевіряється</param>
/// <returns>true, якщо рядок правильний</returns>
bool isLatinLine(char line[])
{
    bool isCorrect = true;
    int length = strlen(line);
    int i = 0;

    if (length == 0)
    {
        isCorrect = false;
    }

    for (i = 0; i < length; i++)
    {
        if (!isalpha((unsigned char)line[i]))
        {
            isCorrect = false;
        }
    }
    return isCorrect;
}

/// <summary>
/// Перевіряє рядок шифру: велика літера, а за нею хоча б одна мала
/// </summary>
/// <param name="line">рядок, який перевіряється</param>
/// <returns>true, якщо рядок правильний</returns>
bool isCipherCorrect(char line[])
{
    bool isCorrect = true;
    int length = strlen(line);
    int i = 0;

    if (length < 2 || !isupper((unsigned char)line[0]))
    {
        isCorrect = false;
    }

    for (i = 1; i < length; i++)
    {
        if (!islower((unsigned char)line[i]))
        {
            isCorrect = false;
        }
    }
    return isCorrect;
}

/// <summary>
/// Вводить текст, переводить його в нижній регістр і виводить
/// </summary>
void inputText()
{
    int i = 0;
    int j = 0;

    cout << "Enter number of lines (from 1 to 10): ";
    lineCount = inputNumber(1, MAX_LINES);

    for (i = 0; i < lineCount; i++)
    {
        cout << "Enter line " << i + 1 << ": ";
        inputLine(text[i]);
        while (!isLatinLine(text[i]))
        {
            cout << "Error! Use only Latin letters: ";
            inputLine(text[i]);
        }

        for (j = 0; text[i][j] != '\0'; j++)
        {
            text[i][j] = tolower(text[i][j]);
        }
    }

    cout << endl << "Text in lower case:" << endl;
    for (i = 0; i < lineCount; i++)
    {
        cout << text[i] << endl;
    }
}

/// <summary>
/// Вводить рядки шифру виду Aab
/// </summary>
void inputCipher()
{
    int i = 0;

    cout << endl << "Enter number of cipher lines (from 1 to 10): ";
    cipherCount = inputNumber(1, MAX_CIPHERS);

    for (i = 0; i < cipherCount; i++)
    {
        cout << "Enter cipher " << i + 1 << ": ";
        inputLine(cipher[i]);
        while (!isCipherCorrect(cipher[i]))
        {
            cout << "Error! Use a capital letter and small letters: ";
            inputLine(cipher[i]);
        }
    }
}

/// <summary>
/// Заповнює масив best для одного рядка і запам'ятовує в usedCipher, який шифр
/// дав найменшу довжину
/// </summary>
/// <param name="row">номер рядка тексту</param>
void findBestLengths(int row)
{
    int length = strlen(text[row]);
    int size = 0;  // довжина послідовності шифру
    int start = 0; // початок цієї послідовності в тексті
    int i = 0;
    int j = 0;

    best[0] = 0;
    for (i = 1; i <= length; i++)
    {
        best[i] = best[i - 1] + 1; // символ лишається без заміни
        usedCipher[i] = -1;

        for (j = 0; j < cipherCount; j++)
        {
            size = strlen(cipher[j]) - 1;
            start = i - size;

            if (start >= 0 && best[start] + 1 < best[i])
            {
                if (strncmp(&text[row][start], &cipher[j][1], size) == 0)
                {
                    best[i] = best[start] + 1;
                    usedCipher[i] = j;
                }
            }
        }
    }
}

/// <summary>
/// Відновлює стиснутий рядок за масивом usedCipher, проходячи текст від кінця
/// до початку
/// </summary>
/// <param name="row">номер рядка тексту</param>
void restoreLine(int row)
{
    int i = strlen(text[row]); // позиція в тексті
    int place = best[i];       // позиція в стиснутому рядку
    int cipherIndex = 0;

    compressed[row][place] = '\0';
    while (i > 0)
    {
        place--;
        cipherIndex = usedCipher[i];

        if (cipherIndex == -1)
        {
            compressed[row][place] = text[row][i - 1];
            i--;
        }
        else
        {
            compressed[row][place] = cipher[cipherIndex][0];
            i = i - (strlen(cipher[cipherIndex]) - 1);
        }
    }
}

/// <summary>
/// Стискає кожен рядок окремо, виводить стиснутий текст і довжини тексту до
/// стиснення та після нього
/// </summary>
void compressText()
{
    int lengthBefore = 0;
    int lengthAfter = 0;
    int i = 0;

    cout << endl << "Compressed text:" << endl;
    for (i = 0; i < lineCount; i++)
    {
        findBestLengths(i);
        restoreLine(i);
        cout << compressed[i] << endl;

        lengthBefore = lengthBefore + strlen(text[i]);
        lengthAfter = lengthAfter + strlen(compressed[i]);
    }

    cout << endl << "Length before compression: " << lengthBefore << endl;
    cout << "Length after compression: " << lengthAfter << endl;
}

/// <summary>
/// Головна функція програми
/// </summary>
/// <returns>0 після завершення роботи</returns>
int main()
{
    printTitle();
    inputText();
    inputCipher();
    compressText();
    return 0;
}
