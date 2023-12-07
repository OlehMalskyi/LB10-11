#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstring>
#include <windows.h>

using namespace std;

enum Specialty
{
    KN,
    IK,
    PZ,
    VP,
    SA
};

string strSpecialty[] = { "КН", "ІК", "ПЗ", "ВП", "СА" };

struct Student
{
    char surname[64];
    Specialty specialty;
    short unsigned course;
    short unsigned grade_physics;
    short unsigned grade_math;
    short unsigned grade_info;
};

void Create(char* file_name);
void Print(char* file_name);
void SortBin(char* file_name);
double avgGrade(fstream& f, const int i);
int fGrade(fstream& f, const int i);
char fsurname(fstream& f, const int i);
void fChange(fstream& f, const int i, const int j);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char file_name[81];
    int menu;

    cin.get();
    cin.sync();
    cout << "Введіть назву файла ";
    cin.getline(file_name, sizeof(file_name));

    do
    {
        cout << "[1] - Створити список студентів" << endl;
        cout << "[2] - Вивести інформацію про студентів" << endl;
        cout << "[3] - Впорядкувати" << endl;
        cout << "[4] - Закінчити виконання програми" << endl;

        cout << "Меню: ";
        cin >> menu;
        switch (menu)
        {
        case 1:
            Create(file_name);
            break;
        case 2:
            Print(file_name);
            break;
        case 3:
            SortBin(file_name);
            break;
        }
    } while (menu != 4);
}

void Create(char* file_name)
{
    ofstream f(file_name, ios::binary);
    if (!f)
    {
        cerr << "Error opening file '" << file_name << "'" << endl;
        exit(1);
    }

    Student s;
    int specialty;
    char ch;
    int i = 0;
    do
    {
        cout << endl;
        cout << "Студен № " << i + 1 << ":" << endl;
        ++i;
        cin.sync();
        cout << "Прізвище: "; cin >> s.surname;

        cout << "Курс: "; cin >> s.course;
        cout << "Спеціальність (0 - КН, 1 - ІК, 2 - ПЗ, 3 - ВП, 4 - СА): ";
        cin >> specialty;
        s.specialty = (Specialty)specialty;
        cout << "Оцінка з фізики: ";
        cin >> s.grade_physics;
        cout << "Оцінка з метематики: ";
        cin >> s.grade_math;
        cout << "Оцінка з інформатики: ";
        cin >> s.grade_info;
        if (!f.write((char*)&s, sizeof(Student)))
        {
            cerr << "Помилка запису" << endl;
            exit(1);
        }
        cout << "Продовжити виконання програми?? (Y/N): ";
        cin >> ch;

    } while (ch == 'Y' || ch == 'y');
}

void Print(char* file_name)
{
    ifstream f(file_name, ios::binary);
    if (!f)
    {
        cerr << "Error opening file" << endl;
        exit(1);
    }
    Student s;
    int i = 0;
    cout << "==============================================================================="
        << endl;
    cout << "| # |  Прізвище  | Курс |  Спеціальність  | Фізика | Математика | Інформатика |"
        << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
    while (f.read((char*)&s, sizeof(Student)))
    {
        cout << "|" << setw(2) << right << i + 1 << " "
            << "|" << setw(12) << left << s.surname
            << "|" << setw(3) << right << s.course << "   "
            << "|" << setw(9) << right << strSpecialty[s.specialty] << "        "
            << "|" << setw(4) << right << s.grade_physics << "    "
            << "|" << setw(6) << right << s.grade_math << "      "
            << "|" << setw(7) << right << s.grade_info << "      |" << endl;
        ++i;
    }
    cout << "===============================================================================" << endl;
}

void SortBin(char* fname)
{
    fstream f(fname, ios::binary | ios::in | ios::out);
    if (!f)
    {
        cerr << "Error opening file" << endl;
        exit(1);
    }

    f.seekg(0 * (long)sizeof(Student), ios::end);
    int size = f.tellg() / (sizeof(Student));
    f.seekg(0, ios::beg);
    for (int i0 = 1; i0 < size; i0++)
        for (int i1 = 0; i1 < size - i0; i1++)
        {
            double avgGrade1 = avgGrade(f, i1);
            double avgGrade2 = avgGrade(f, i1 + 1);
            int grade = fGrade(f, i1);
            cout << grade << endl;
            int grade2 = fGrade(f, i1 + 1);
            char student1 = fsurname(f, i1);
            char student2 = fsurname(f, i1 + 1);
            if ((avgGrade1 > avgGrade2) || (avgGrade1 == avgGrade2 && grade > grade2) || (avgGrade1 == avgGrade2 && grade == grade2 && student1 > student2))
                fChange(f, i1, i1 + 1);
        }
    f.seekp(0, ios::end);
}

double avgGrade(fstream& f, const int i)
{
    Student s;
    f.seekg(i * static_cast<long>(sizeof(Student)));
    f.read(reinterpret_cast<char*>(&s), sizeof(Student));

    int physics = s.grade_physics;
    int math = s.grade_math;
    int info = s.grade_info;

    return (physics + math + info) / 3.0;
}


int fGrade(fstream& f, const int i)
{
    Student s;
    f.seekg(i * (long)sizeof(Student));
    f.read((char*)&s, sizeof(Student));
    int math = s.grade_math;
    return math;
}

char fsurname(fstream& f, const int i)
{
    Student s;
    f.seekg(i * (long)sizeof(Student));
    f.read((char*)&s, sizeof(Student));
    char surname[81];
    strcpy_s(surname, s.surname);
    return *surname;
}

void fChange(fstream& f, const int i, const int j)
{
    Student si, sj, temp;
    f.seekg(i * (long)sizeof(Student));
    f.read((char*)&si, sizeof(Student));
    temp = si;
    f.seekg(j * (long)sizeof(Student));
    f.read((char*)&sj, sizeof(Student));
    f.seekp(i * (long)sizeof(Student));
    f.write((char*)&sj, sizeof(Student));
    f.seekp(j * (long)sizeof(Student));
    f.write((char*)&temp, sizeof(Student));
}
