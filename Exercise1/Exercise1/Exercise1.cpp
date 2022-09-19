#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
using namespace std;

void ConvertString(string&); // Конвертирует строку в скобки
bool ContainsSeveralSymbols(const string, const char); // Получает true, если символ встречается в строке более одного раза
bool FindSymbolInVector(const vector <char>, const char); // Проверяет встречался ли уже символ в строке более одного раза или нет 

int main()
{
    // Для корректной работы на русском языке
    setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Введите сообщение: ";
    string text = "";
    getline(cin, text);
    ConvertString(text);
    cout << text;

    cout << '\n';
    system("pause"); // Используется для того, чтобы консоль не закрывалась сразу после выполнения программы

    return 0;
}

void ConvertString(string& text)
{
    string local_text = text;
    vector <char> SeveralSymbolsArr; // В нем будут храниться символы, которые встречались в тексте несколько раз
    for (const char symbol : local_text)
    {
        // Для начала проверяем встречался ли символ в строке более одного раза или нет
        if (FindSymbolInVector(SeveralSymbolsArr, symbol)) {
            text[text.find(symbol)] = ')';
        }
        // В случае неудачи проверяем встречается ли символ более 1 раза в тексте. Если да, то добавляем его в SeveralSymbolsArr
        else if (ContainsSeveralSymbols(local_text, symbol)) {
            text[text.find(symbol)] = ')';
            SeveralSymbolsArr.push_back(tolower(symbol)); // Переводим символ в нижний регистр, так как в задании регистр игнорируется
        }
        // Если ни одно из условий не выполняется, то меняем символ на ( - скобку
        else {
            text[text.find(symbol)] = '(';
        }
    }
}

bool FindSymbolInVector(const vector <char> frequent_symbols, const char find_symbol)
{
    // Функция представлена для оптимизации кода и процесса. Если наш символ уже встречался в тексте, то функция вернет true
   
    if (frequent_symbols.size() == 0) return false; // Если вектор пустой, возвращаем false
    const char local_symbol = tolower(find_symbol); // Переводим символ в нижний регистр, так как в задании регистр игнорируется
    for (const char symbol : frequent_symbols) {
        if (local_symbol == symbol) return true; // Если символ встречается в нашем vector, то возвращаем true
    }
    return false;
}

bool ContainsSeveralSymbols(const string text, const char contained_symbol)
{
    const char local_symbol = tolower(contained_symbol); // Переводим символ в нижний регистр, так как в задании регистр игнорируется

    /* Оптимизируем текст для поиска.
    Т.к.символ, который мы хотим найти встречается впервые, то и смысла нет перебирать все символы, которые шли до него.
    Таким образом мы оптимизируем программу, уменьшив кол-во итераций цикла */
    const string local_text = text.substr(text.find(contained_symbol)); 
   
    int count = 0; // Счетчик появления символа в тексте
    for (const char symbol : local_text) {
        if (local_symbol == (char)tolower(symbol)) {
            ++count;
            if (count > 1) return true; // Возвращаем true, если символ встретился в строке более одного раза
        }
    }
    return false;
}