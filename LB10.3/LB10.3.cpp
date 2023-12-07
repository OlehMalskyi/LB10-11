#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <windows.h>

using namespace std;

#pragma pack(push, 1)

struct Bday
{
    int day;
    int month;
    int year;
};

struct Zodiac
{
    string surname;
    string name;
    string zodiac_sign;
};

#pragma pack(pop)

void Create(const string file_name, const int option);
void Print(const string file_name);
void Find(const string file_name);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string file_name = "test.txt";

    int MenuItem;

    while (true)
    {
        cout << endl
            << endl
            << endl;
        cout << "Оберіть дію:" << endl;
        cout << "1 - Ввести інформацію про користувача" << endl;
        cout << "2 - Вивести інформацію про користувачів" << endl;
        cout << "3 - Пошук людини за прізвищем" << endl;
        cout << "0 - Завершити роботу програми" << endl;
        cout << "Введіть: ";
        cin >> MenuItem;
        cout << endl;

        switch (MenuItem)
        {
        case 1:
            Create(file_name, 1);
            break;
        case 2:
            Print(file_name);
            break;
        case 3:
            Find(file_name);
            break;
        }
        if (MenuItem == 0)
            break;
    }

    return 0;
}

void Create(const string file_name, int option)
{
    Zodiac S;
    Bday B{};

    ofstream f;

    if (option == 1)
        f.open(file_name, ios::out);
    else
        f.open(file_name, ios::app);

    if (!f.is_open())
    {
        cout << "Файл не відкрито!" << endl;
        return;
    }
    cin.get();

    string keep;

    do
    {
        cout << endl << endl;
        cout << "Введіть прізвище: "; getline(cin, S.surname);
        f << S.surname << endl;

        cout << "Введіть імя: "; getline(cin, S.name);
        f << S.name << endl;

        cout << "Введіть знак зодіаку: "; getline(cin, S.zodiac_sign);
        f << S.zodiac_sign << endl;

        cout << "Введіть день народження: "; cin >> B.day;
        f << B.day << endl;

        cout << "Введіть місяць народження: "; cin >> B.month;
        f << B.month << endl;

        cout << "Введіть рік народження: "; cin >> B.year;
        f << B.year << endl;

        cin.get();
        cout << "Щоб продовжити введіть (Y): "; getline(cin, keep); cout << endl;
    } while (keep == "Y");
}

void Print(const string file_name)
{
    ifstream f(file_name, ios::in);

    char line[50];
    string str;

    cout << "==============================================================================================================" << endl;
    cout << "| № |    Прізвище   |     І'мя     |  Знак зодіаку  |  День народження  | Місяць народження | Рік народження |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;

    string lines;
    int n = 0;
    while (getline(f, lines))
    {
        n++;
    }
    f.close();
    f.open(file_name, ios::in);

    int number = 1;

    for (int i = 0; i < n / 6; i++)
    {
        cout << "|" << setw(2) << number++ << setw(2);

        f.getline(line, sizeof(line));
        cout << "|" << setw(9) << line << setw(7);

        f.getline(line, sizeof(line));
        cout << "|" << setw(9) << line << setw(6);

        f.getline(line, sizeof(line));
        cout << "|" << setw(9) << line << setw(8);

        f.getline(line, sizeof(line));
        cout << "|" << setw(9) << line << setw(11);

        f.getline(line, sizeof(line));
        cout << "|" << setw(9) << line << setw(11);

        f.getline(line, sizeof(line));
        cout << "|" << setw(9) << line << setw(8) << "|" << endl;
    }
    cout << "==============================================================================================================" << endl;
}

void Find(const string file_name)
{
    ifstream f(file_name, ios::in);

    if (!f.is_open())
    {
        cout << "Файл не відкрито!" << endl;
        return;
    }

    string surname;
    cout << "Введіть прізвище: ";
    cin >> surname;

    cout << "=========================================================================================================" << endl;
    cout << "| № |   Прізвище   |   І'мя   |  Знак зодіаку  |  День народження  | Місяць народження | Рік народження |" << endl;
    cout << "---------------------------------------------------------------------------------------------------------" << endl;

    Zodiac S;
    Bday B;

    int i = 1;
    bool found = false;
    while (f >> S.surname >> S.name >> S.zodiac_sign >> B.day >> B.month >> B.year)
    {
        if (S.surname == surname)
        {
            cout << "|" << setw(2) << i << " |" << setw(13) << S.surname << " |" << setw(9) << S.name << " |" << setw(15) << S.zodiac_sign << " |" << setw(18) << B.day << " |" << setw(18) << B.month << " |" << setw(15) << B.year << " |\n";
            i++;
            found = true;
        }
    }

    cout << "=========================================================================================================" << endl;

    if (!found)
    {
        cout << "Користувач не знайдений." << endl;
    }

    f.close();
}
