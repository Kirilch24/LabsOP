/// <summary>
/// Лабораторна робота №11, завдання 2, варіант 3.2. Програма лабораторної
/// роботи №10, доповнена обробкою бінарних файлів: запис, друк, додавання,
/// заміна, видалення записів і запити з результатами у файлах.
/// </summary>
/// <remarks>
/// Ім'я файлу: task2.cpp
/// Автор: Чумак Кирил, гр. ІПЗ-11(3)
/// Номер версії модуля: version 1
/// </remarks>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
using namespace std;

// Константи
const char JOURNAL_FILE[] = "journal.dat";     // файл із записами
const char BEST_FILE[] = "best.dat";           // результат запиту 1
const char EXCELLENT_FILE[] = "excellent.dat"; // результат запиту 2
const char GROUPS_FILE[] = "groups.dat";       // результат запиту 3
const int MAX_RECORDS = 30;                    // найбільша кількість записів
const int FIELD_SIZE = 16;   // розмір текстового поля разом із нулем
const int EXAM_COUNT = 3;    // кількість іспитів
const int MAX_COURSE = 4;    // найбільший курс
const int FAIL_GRADE = 2;    // двійка
const int TOP_GRADE = 5;     // п'ятірка
const int FACULTY_COUNT = 3; // кількість факультетів для генерації
const int SUFFIX_COUNT = 4;  // кількість закінчень назви групи
const int SURNAME_COUNT = 8; // кількість прізвищ для генерації

// факультети, закінчення назв груп і прізвища для генерації
const char FACULTIES[FACULTY_COUNT][FIELD_SIZE] = {"FIT", "LAW", "ECO"};
const char SUFFIXES[SUFFIX_COUNT][FIELD_SIZE] = {"-11", "-12", "-21", "-22"};
const char SURNAMES[SURNAME_COUNT][FIELD_SIZE] = {
    "Melnyk",  "Bondar",  "Tkachuk", "Savchuk",
    "Rudenko", "Lysenko", "Moroz",   "Klymenko"};

// Структури
struct StudentRecord // запис про одного студента
{
    char faculty[FIELD_SIZE];
    int course;
    char group[FIELD_SIZE];
    char surname[FIELD_SIZE];
    int grades[EXAM_COUNT];
};

// Глобальні змінні
StudentRecord journal[MAX_RECORDS] = {}; // масив записів про студентів
int recordCount = 0;                     // кількість записів у масиві

/// <summary>
/// Виводить назву роботи й автора
/// </summary>
void printTitle()
{
    cout << "Lab work 11. Task 2. Variant 3.2." << endl;
    cout << "Author: Kyryl Chumak, group IPZ-11(3)" << endl << endl;

    cout << "Array of structures: faculty, course, group, surname," << endl;
    cout << "exam grades. It is written to a binary file. Records can" << endl;
    cout << "be added to the file, replaced and deleted. Requests to" << endl;
    cout << "the file: the faculty and course with the most excellent" << endl;
    cout << "students, the list of excellent students, the groups" << endl;
    cout << "without failing students." << endl;
}

/// <summary>
/// Вводить ціле число із заданих меж і забирає кінець рядка, щоб після неї
/// працювало cin.getline
/// </summary>
/// <param name="minValue">нижня межа числа</param>
/// <param name="maxValue">верхня межа числа</param>
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
    cin.ignore(1000, '\n');

    return number;
}

/// <summary>
/// Вводить текстове поле довжиною до 15 символів
/// </summary>
/// <param name="field">масив для введеного тексту</param>
void inputField(char field[])
{
    cin.getline(field, FIELD_SIZE);
    while (cin.fail())
    {
        cin.clear();            // скинути помилку введення
        cin.ignore(1000, '\n'); // і пропустити задовгий рядок
        cout << "Error! Enter at most 15 characters: ";
        cin.getline(field, FIELD_SIZE);
    }
}

/// <summary>
/// Вводить з клавіатури один запис
/// </summary>
/// <param name="number">номер запису для підказки</param>
/// <returns>заповнена структура</returns>
StudentRecord readRecord(int number)
{
    StudentRecord record = {}; // новий запис
    int i = 0;                 // номер іспиту

    cout << "Record " << number << endl;
    cout << "Enter faculty: ";
    inputField(record.faculty);
    cout << "Enter course (from 1 to " << MAX_COURSE << "): ";
    record.course = inputNumber(1, MAX_COURSE);
    cout << "Enter group: ";
    inputField(record.group);
    cout << "Enter surname: ";
    inputField(record.surname);

    for (i = 0; i < EXAM_COUNT; i++)
    {
        cout << "Enter grade " << i + 1 << " (from 2 to 5): ";
        record.grades[i] = inputNumber(FAIL_GRADE, TOP_GRADE);
    }

    return record;
}

/// <summary>
/// Створює випадковий запис. Найнижча оцінка студента теж випадкова, тому серед
/// записів є і відмінники, і студенти з двійками
/// </summary>
/// <returns>заповнена структура</returns>
StudentRecord generateRecord()
{
    StudentRecord record = {};                 // новий запис
    int facultyIndex = rand() % FACULTY_COUNT; // номер факультету
    int suffixIndex = rand() % SUFFIX_COUNT;   // номер закінчення групи
    // найнижча оцінка студента
    int lowestGrade = FAIL_GRADE + rand() % (TOP_GRADE - FAIL_GRADE + 1);
    int i = 0; // номер іспиту

    strcpy(record.faculty, FACULTIES[facultyIndex]);
    record.course = suffixIndex / 2 + 1;
    strcpy(record.group, FACULTIES[facultyIndex]);
    strcat(record.group, SUFFIXES[suffixIndex]);
    strcpy(record.surname, SURNAMES[rand() % SURNAME_COUNT]);

    for (i = 0; i < EXAM_COUNT; i++)
    {
        record.grades[i] = lowestGrade + rand() % (TOP_GRADE - lowestGrade + 1);
    }

    return record;
}

/// <summary>
/// Виводить масив записів таблицею
/// </summary>
/// <param name="list">покажчик на масив записів</param>
/// <param name="size">кількість записів</param>
void printJournal(StudentRecord* list, int size)
{
    int i = 0; // номер запису
    int j = 0; // номер іспиту

    if (size == 0)
    {
        cout << "No records." << endl;
    }
    else
    {
        cout << setw(3) << "No" << setw(9) << "Faculty" << setw(8) << "Course"
             << setw(17) << "Group" << setw(17) << "Surname" << "  Grades"
             << endl;

        for (i = 0; i < size; i++)
        {
            cout << setw(3) << i + 1 << setw(9) << list[i].faculty << setw(8)
                 << list[i].course << setw(17) << list[i].group << setw(17)
                 << list[i].surname << " ";
            for (j = 0; j < EXAM_COUNT; j++)
            {
                cout << setw(2) << list[i].grades[j];
            }
            cout << endl;
        }
    }
}

/// <summary>
/// Записує масив записів у бінарний файл
/// </summary>
/// <param name="fileName">ім'я файлу</param>
/// <param name="list">покажчик на масив</param>
/// <param name="size">кількість записів</param>
void saveRecords(const char fileName[], StudentRecord* list, int size)
{
    FILE* file = fopen(fileName, "wb"); // файл для запису

    if (file == NULL)
    {
        cout << "Cannot open file " << fileName << endl;
    }
    else
    {
        fwrite(list, sizeof(StudentRecord), size, file);
        fclose(file);
    }
}

/// <summary>
/// Читає записи з бінарного файлу в масив
/// </summary>
/// <param name="fileName">ім'я файлу</param>
/// <param name="list">покажчик на масив</param>
/// <returns>кількість прочитаних записів</returns>
int loadRecords(const char fileName[], StudentRecord* list)
{
    FILE* file = fopen(fileName, "rb"); // файл для читання
    int size = 0;                       // кількість записів

    if (file == NULL)
    {
        cout << "File " << fileName << " not found." << endl;
    }
    else
    {
        size = fread(list, sizeof(StudentRecord), MAX_RECORDS, file);
        fclose(file);
    }

    return size;
}

/// <summary>
/// Читає масив із файлу записів і виводить його таблицею
/// </summary>
void printFile()
{
    recordCount = loadRecords(JOURNAL_FILE, journal);
    printJournal(journal, recordCount);
}

/// <summary>
/// Створює масив, записує його у файл і виводить таблицю з файлу
/// </summary>
/// <param name="isRandom">true, якщо записи генеруються</param>
void createJournal(bool isRandom)
{
    int i = 0; // номер запису

    cout << "Enter number of records (from 1 to " << MAX_RECORDS << "): ";
    recordCount = inputNumber(1, MAX_RECORDS);

    for (i = 0; i < recordCount; i++)
    {
        if (isRandom)
        {
            journal[i] = generateRecord();
        }
        else
        {
            journal[i] = readRecord(i + 1);
        }
    }

    saveRecords(JOURNAL_FILE, journal, recordCount);
    printFile();
}

/// <summary>
/// Вводить новий запис і пише його у файл на задане місце. У режимі "ab" запис
/// завжди потрапляє в кінець файлу, у режимі "r+b" заміняє старий
/// </summary>
/// <param name="mode">режим відкриття файлу</param>
/// <param name="index">номер місця від нуля</param>
void writeRecord(const char mode[], int index)
{
    StudentRecord newRecord = readRecord(index + 1); // новий запис
    FILE* file = fopen(JOURNAL_FILE, mode);          // файл для запису

    if (file == NULL)
    {
        cout << "Cannot open file " << JOURNAL_FILE << endl;
    }
    else
    {
        fseek(file, index * sizeof(StudentRecord), SEEK_SET);
        fwrite(&newRecord, sizeof(StudentRecord), 1, file);
        fclose(file);
    }
}

/// <summary>
/// Дописує один новий запис у кінець файлу
/// </summary>
void addRecord()
{
    recordCount = loadRecords(JOURNAL_FILE, journal);

    if (recordCount == MAX_RECORDS)
    {
        cout << "The file is full." << endl;
    }
    else
    {
        writeRecord("ab", recordCount);
    }
}

/// <summary>
/// Виводить записи файлу і вводить номер вибраного запису
/// </summary>
/// <returns>номер запису або 0, якщо записів немає</returns>
int chooseRecord()
{
    int number = 0; // номер запису

    printFile();

    if (recordCount > 0)
    {
        cout << "Enter record number (from 1 to " << recordCount << "): ";
        number = inputNumber(1, recordCount);
    }

    return number;
}

/// <summary>
/// Заміняє вибраний запис у файлі на новий
/// </summary>
void replaceRecord()
{
    int number = chooseRecord(); // номер запису

    if (number > 0)
    {
        writeRecord("r+b", number - 1);
    }
}

/// <summary>
/// Видаляє вибраний запис: зсуває наступні записи масиву на одне місце вперед і
/// записує масив у файл
/// </summary>
void deleteRecord()
{
    int number = chooseRecord(); // номер запису
    int i = 0;                   // номер запису, що зсувається

    if (number > 0)
    {
        for (i = number; i < recordCount; i++)
        {
            journal[i - 1] = journal[i];
        }
        recordCount--;
        saveRecords(JOURNAL_FILE, journal, recordCount);
    }
}

/// <summary>
/// Рахує, скільки разів задана оцінка є в записі
/// </summary>
/// <param name="record">запис</param>
/// <param name="grade">оцінка</param>
/// <returns>кількість таких оцінок</returns>
int countGrades(StudentRecord record, int grade)
{
    int count = 0; // кількість оцінок
    int i = 0;     // номер іспиту

    for (i = 0; i < EXAM_COUNT; i++)
    {
        if (record.grades[i] == grade)
        {
            count++;
        }
    }

    return count;
}

/// <summary>
/// Знаходить перший запис масиву з тим самим факультетом і курсом, що в
/// заданого запису, а якщо isWholeCourse = false, то й з тією самою групою
/// </summary>
/// <param name="index">номер запису</param>
/// <param name="isWholeCourse">чи не враховувати групу</param>
/// <returns>номер першого такого запису</returns>
int findFirst(int index, bool isWholeCourse)
{
    int first = 0;        // номер запису, що перевіряється
    bool isFound = false; // чи знайдено запис

    while (!isFound)
    {
        if (strcmp(journal[first].faculty, journal[index].faculty) == 0
            && journal[first].course == journal[index].course
            && (isWholeCourse
                || strcmp(journal[first].group, journal[index].group) == 0))
        {
            isFound = true;
        }
        else
        {
            first++;
        }
    }

    return first;
}

/// <summary>
/// Виводить таблицею факультет, курс і групу кожного запису масиву
/// </summary>
/// <param name="list">покажчик на масив записів</param>
/// <param name="size">кількість записів</param>
void printGroups(StudentRecord* list, int size)
{
    int i = 0; // номер запису

    if (size == 0)
    {
        cout << "No results." << endl;
    }
    else
    {
        cout << setw(9) << "Faculty" << setw(8) << "Course" << setw(17)
             << "Group" << endl;

        for (i = 0; i < size; i++)
        {
            cout << setw(9) << list[i].faculty << setw(8) << list[i].course
                 << setw(17) << list[i].group << endl;
        }
    }
}

/// <summary>
/// Запит 1. Читає файл, рахує відмінників кожної пари "факультет, курс"
/// (лічильник лежить у першому записі пари), відбирає пари з найбільшою
/// кількістю, пише їх у файл результату і виводить цей файл
/// </summary>
void findBestCourses()
{
    StudentRecord results[MAX_RECORDS]; // перші записи знайдених пар
    int counts[MAX_RECORDS] = {};       // лічильники відмінників
    int maxCount = 0;                   // найбільша кількість
    int first = 0;                      // перший запис пари
    int size = 0;                       // кількість знайдених пар
    int i = 0;                          // номер запису

    recordCount = loadRecords(JOURNAL_FILE, journal);

    for (i = 0; i < recordCount; i++)
    {
        if (countGrades(journal[i], TOP_GRADE) == EXAM_COUNT)
        {
            first = findFirst(i, true);
            counts[first]++;
            if (counts[first] > maxCount)
            {
                maxCount = counts[first];
            }
        }
    }

    for (i = 0; i < recordCount; i++)
    {
        if (maxCount > 0 && counts[i] == maxCount)
        {
            results[size] = journal[i];
            strcpy(results[size].group, "all");
            size++;
        }
    }

    saveRecords(BEST_FILE, results, size);
    size = loadRecords(BEST_FILE, results);
    cout << "Maximum number of excellent students: " << maxCount << endl;
    printGroups(results, size);
}

/// <summary>
/// Запит 2. Читає файл, відбирає відмінників заданого факультету в окремий
/// масив, пише його у файл результату і виводить цей файл
/// </summary>
void printExcellent()
{
    StudentRecord excellent[MAX_RECORDS]; // знайдені відмінники
    char faculty[FIELD_SIZE] = "";        // ключ пошуку
    int size = 0;                         // кількість знайдених
    int i = 0;                            // номер запису

    recordCount = loadRecords(JOURNAL_FILE, journal);
    cout << "Enter faculty: ";
    inputField(faculty);

    for (i = 0; i < recordCount; i++)
    {
        if (strcmp(journal[i].faculty, faculty) == 0
            && countGrades(journal[i], TOP_GRADE) == EXAM_COUNT)
        {
            excellent[size] = journal[i];
            size++;
        }
    }

    saveRecords(EXCELLENT_FILE, excellent, size);
    size = loadRecords(EXCELLENT_FILE, excellent);
    printJournal(excellent, size);
}

/// <summary>
/// Запит 3. Читає файл, позначає групи, де є двійка (ознака лежить у першому
/// записі групи), відбирає решту груп заданого курсу, пише їх у файл результату
/// і виводить цей файл
/// </summary>
void findCleanGroups()
{
    StudentRecord results[MAX_RECORDS]; // перші записи знайдених груп
    bool hasFail[MAX_RECORDS] = {};     // чи є двійка в групі
    int course = 0;                     // ключ пошуку
    int size = 0;                       // кількість знайдених груп
    int i = 0;                          // номер запису

    recordCount = loadRecords(JOURNAL_FILE, journal);
    cout << "Enter course (from 1 to " << MAX_COURSE << "): ";
    course = inputNumber(1, MAX_COURSE);

    for (i = 0; i < recordCount; i++)
    {
        if (countGrades(journal[i], FAIL_GRADE) > 0)
        {
            hasFail[findFirst(i, false)] = true;
        }
    }

    for (i = 0; i < recordCount; i++)
    {
        if (journal[i].course == course && findFirst(i, false) == i
            && !hasFail[i])
        {
            results[size] = journal[i];
            size++;
        }
    }

    saveRecords(GROUPS_FILE, results, size);
    size = loadRecords(GROUPS_FILE, results);
    printGroups(results, size);
}

/// <summary>
/// Показує меню і викликає вибрані дії, поки не вибрано вихід
/// </summary>
void runMenu()
{
    int choice = -1; // вибраний пункт меню

    srand(time(NULL));
    while (choice != 0)
    {
        cout << endl << "1. Enter array from keyboard and save it" << endl;
        cout << "2. Generate array and save it" << endl;
        cout << "3. Print file" << endl;
        cout << "4. Add record to file" << endl;
        cout << "5. Replace record in file" << endl;
        cout << "6. Delete record from file" << endl;
        cout << "7. Faculty and course with most excellent students" << endl;
        cout << "8. Excellent students of a faculty" << endl;
        cout << "9. Groups of a course without fail grades" << endl;
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
            case 1 : createJournal(false); break;
            case 2 : createJournal(true); break;
            case 3 : printFile(); break;
            case 4 : addRecord(); break;
            case 5 : replaceRecord(); break;
            case 6 : deleteRecord(); break;
            case 7 : findBestCourses(); break;
            case 8 : printExcellent(); break;
            case 9 : findCleanGroups(); break;
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
