#include<iostream>
#include<windows.h>
#include<string>
#include<iomanip>
#include<fstream>
#include <sstream>

using namespace std;

void Process();
void Create(string text, string product);
int file_length(const string file_name);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Process();
    return 0;
}

void Create(string text, string product)
{
    ifstream f("t3.txt");
    string line;

    while (getline(f, line))
    {
        if (line.find(product) != string::npos)
            return;
    }

    f.close();
    ofstream f3("t3.txt", ios::app);
    f3 << text << endl;
}

void Process()
{
    ifstream f("t.txt");
    ifstream f2("t2.txt");

    char ch = 0;
    string s;
    string b;
    string res;

    for (int i = 0, j = 1; i < file_length("t.txt"); i++, j += 2)
    {
        res = "";
        f >> s >> b;

        res += s;
        res += ' ' + b;
        f2 >> s >> b;
        res += ' ' + b;

        Create(res, s);
    }
}

int file_length(const string file_name) {
    ifstream f(file_name, ios::in);

    if (!f.is_open())
    {
        cout << "Файл не відкрито!" << endl;
        return 0;
    }

    string lines;
    int n = 0;

    while (getline(f, lines))
    {
        n++;
    }
    f.close();

    return n;
}
