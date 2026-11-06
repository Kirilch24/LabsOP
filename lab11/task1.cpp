/// <summary>
/// Лабораторна робота №11, завдання 1, варіант 4.1. Записати рядки у текстовий
/// файл і дописати в кінець кожного непарного рядка слово з найбільшою
/// кількістю голосних.
/// </summary>
/// <remarks>
/// Ім'я файлу: task1.cpp
/// Автор: Чумак Кирил, гр. ІПЗ-11(3)
/// Номер версії модуля: version 1
/// </remarks>

#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

// Константи
const char FILE_NAME[] = "text.txt";   // текстовий файл
const char TEMP_NAME[] = "text.tmp";   // тимчасовий файл
const char VOWELS[] = "aeiouyAEIOUY";  // голосні літери
const char SEPARATORS[] = " ,.;:!?\t"; // символи між словами
const int MAX_LINES = 20;              // найбільша кількість рядків
const int INPUT_SIZE = 81;             // розмір введеного рядка разом із нулем
const int LINE_SIZE = 256;             // розмір рядка файлу разом із нулем

/// <summary>
/// Виводить назву роботи й автора
/// </summary>
void printTitle()
{
    cout << "Lab work 11. Task 1. Variant 4.1." << endl;
    cout << "Author: Kyryl Chumak, group IPZ-11(3)" << endl << endl;

    cout << "Enter lines from the keyboard and write them to a text" << endl;
    cout << "file. In each odd line find the word with the most vowels" << endl;
    cout << "and append it to the end of that line." << endl;
}

/// <summary>
/// Вводить кількість рядків файлу і забирає кінець рядка, щоб після неї
/// працювало cin.getline
/// </summary>
/// <returns>кількість рядків</returns>
int inputLineCount()
{
    int lineCount = 0; // кількість рядків

    cout << "Enter number of lines (from 1 to " << MAX_LINES << "): ";
    cin >> lineCount;
    while (cin.fail() || lineCount < 1 || lineCount > MAX_LINES)
    {
        cin.clear();            // скинути помилку введення
        cin.ignore(1000, '\n'); // і пропустити неправильний рядок
        cout << "Error! Enter a number from 1 to " << MAX_LINES << ": ";
        cin >> lineCount;
    }
    cin.ignore(1000, '\n');

    return lineCount;
}

/// <summary>
/// Створює текстовий файл із рядків, введених з клавіатури
/// </summary>
void createFile()
{
    char line[INPUT_SIZE] = "";       // введений рядок
    int lineCount = inputLineCount(); // кількість рядків
    int i = 0;                        // номер рядка
    ofstream file(FILE_NAME);         // файл для запису

    if (!file.is_open())
    {
        cout << "Cannot create the file." << endl;
    }
    else
    {
        for (i = 1; i <= lineCount; i++)
        {
            cout << "Line " << i << ": ";
            cin.getline(line, INPUT_SIZE);
            while (cin.fail())
            {
                cin.clear();            // скинути помилку введення
                cin.ignore(1000, '\n'); // і пропустити задовгий рядок
                cout << "Error! Enter at most 80 characters: ";
                cin.getline(line, INPUT_SIZE);
            }
            file << line << endl;
        }
        file.close();
    }
}

/// <summary>
/// Виводить вміст файлу на екран разом із номерами рядків
/// </summary>
void printFile()
{
    char line[LINE_SIZE] = ""; // прочитаний рядок
    int lineNumber = 0;        // номер рядка
    ifstream file(FILE_NAME);  // файл для читання

    if (!file.is_open())
    {
        cout << "File not found. Create it first." << endl;
    }
    else
    {
        while (file.getline(line, LINE_SIZE))
        {
            lineNumber++;
            cout << lineNumber << ": " << line << endl;
        }
        file.close();
    }
}

/// <summary>
/// Рахує голосні літери в слові
/// </summary>
/// <param name="word">слово</param>
/// <returns>кількість голосних</returns>
int countVowels(char word[])
{
    int count = 0;             // кількість голосних
    int length = strlen(word); // довжина слова
    int i = 0;                 // номер літери

    for (i = 0; i < length; i++)
    {
        if (strchr(VOWELS, word[i]) != NULL)
        {
            count++;
        }
    }

    return count;
}

/// <summary>
/// Шукає в рядку слово з найбільшою кількістю голосних. Копія рядка потрібна
/// тому, що strtok псує рядок, який ділить на слова
/// </summary>
/// <param name="line">рядок</param>
/// <param name="bestWord">масив для знайденого слова</param>
void findBestWord(char line[], char bestWord[])
{
    char lineCopy[LINE_SIZE] = ""; // копія рядка
    char* word = NULL;             // поточне слово
    int vowelCount = 0;            // голосні поточного слова
    int maxVowels = -1;            // найбільша кількість голосних

    strcpy(bestWord, "");
    strcpy(lineCopy, line);
    word = strtok(lineCopy, SEPARATORS);

    while (word != NULL)
    {
        vowelCount = countVowels(word);
        if (vowelCount > maxVowels)
        {
            maxVowels = vowelCount;
            strcpy(bestWord, word);
        }
        word = strtok(NULL, SEPARATORS);
    }
}

/// <summary>
/// Дописує до рядка знайдене слово, якщо воно є і вміщається в рядок
/// </summary>
/// <param name="line">рядок</param>
/// <param name="lineNumber">номер рядка для повідомлення</param>
void appendBestWord(char line[], int lineNumber)
{
    char bestWord[LINE_SIZE] = ""; // знайдене слово

    findBestWord(line, bestWord);

    if (strlen(bestWord) > 0 && strlen(line) + strlen(bestWord) + 1 < LINE_SIZE)
    {
        strcat(line, " ");
        strcat(line, bestWord);
        cout << "Line " << lineNumber << ": " << bestWord << endl;
    }
}

/// <summary>
/// Переписує файл у тимчасовий, дописуючи слова до непарних рядків, а потім
/// ставить тимчасовий файл на місце початкового
/// </summary>
void processFile()
{
    char line[LINE_SIZE] = ""; // прочитаний рядок
    int lineNumber = 0;        // номер рядка
    ifstream input(FILE_NAME); // початковий файл
    ofstream output;           // тимчасовий файл

    if (!input.is_open())
    {
        cout << "File not found. Create it first." << endl;
    }
    else
    {
        output.open(TEMP_NAME);
        while (input.getline(line, LINE_SIZE))
        {
            lineNumber++;
            if (lineNumber % 2 == 1)
            {
                appendBestWord(line, lineNumber);
            }
            output << line << endl;
        }
        input.close();
        output.close();

        remove(FILE_NAME);
        rename(TEMP_NAME, FILE_NAME);
    }
}

/// <summary>
/// Показує меню і викликає вибрані дії, поки не вибрано вихід
/// </summary>
void runMenu()
{
    int choice = -1; // вибраний пункт меню

    while (choice != 0)
    {
        cout << endl << "1. Create file from keyboard" << endl;
        cout << "2. Print file" << endl;
        cout << "3. Append found words to odd lines" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose menu item: ";

        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            choice = -1;
        }
        cin.ignore(1000, '\n');

        switch (choice)
        {
            case 1 : createFile(); break;
            case 2 : printFile(); break;
            case 3 : processFile(); break;
            case 0 : break;
            default : cout << "No such menu item." << endl;
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
    runMenu();
    return 0;
}
