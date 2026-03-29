#include <iostream>
#include <string>
using namespace std;

int main() {
    setlocale(LC_ALL, "");

    // Считываем текст построчно, пока не введут пустую строку
    cout << "Введите текст (пустая строка — конец ввода):" << endl;
    string fullText = "";
    string line = "";
    getline(cin, line); 
    while (true) {
        getline(cin, line);
        if (line == "") break;
        fullText = fullText + " " + line;
    }


    string words[500];
    int wordCount = 0;

    string current = "";
    for (int i = 0; i < (int)fullText.size(); i++) {
        char ch = fullText[i];
        // Если символ — пробел или перенос строки, слово закончилось
        if (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t') {
            if (current != "") {
                words[wordCount] = current;
                wordCount++;
                current = "";
            }
        } else {
            current = current + ch;
        }
    }
    // Добавляем последнее слово, если оно есть
    if (current != "") {
        words[wordCount] = current;
        wordCount++;
    }

    cout << "\nКоличество магазинов «Пятёрочка» по городам:" << endl;
    bool found = false;

    for (int i = 0; i < wordCount - 1; i++) {
        string word = words[i];      // текущее слово
        string next = words[i + 1];  // следующее слово

        bool startsUpper = false;
        if (word.size() >= 2) {
            unsigned char b1 = (unsigned char)word[0];
            unsigned char b2 = (unsigned char)word[1];
            if (b1 == 0xD0 && b2 >= 0x90 && b2 <= 0xBF) startsUpper = true; // А-Я
            if (b1 == 0xD0 && b2 == 0x81)                startsUpper = true; // Ё
        }
        if ((unsigned char)word[0] >= 'A' && (unsigned char)word[0] <= 'Z') startsUpper = true;

        if (!startsUpper) continue; // не заглавная — пропускаем

        bool nextIsNumber = !next.empty();
        for (int j = 0; j < (int)next.size(); j++) {
            char c = next[j];
            bool isLastChar = (j == (int)next.size() - 1);
            if (isLastChar && (c == ',' || c == '.')) continue; // запятая в конце — ок
            if (c < '0' || c > '9') {
                nextIsNumber = false;
                break;
            }
        }

        if (!nextIsNumber) continue; // следующее слово не число — пропускаем

    
        bool isPrice = false;
        if (i + 2 < wordCount) {
            string afterNum = words[i + 2];
            if (afterNum == "р."     || afterNum == "руб."   ||
                afterNum == "руб"    || afterNum == "рублей" ||
                afterNum == "рубля"  || afterNum == "рублях") {
                isPrice = true;
            }
        }

        if (isPrice) continue; // это цена, а не количество магазинов — пропускаем

        bool afterCheck = false;
        if (i > 0) {
            string prev = words[i - 1];
            if (prev == "чек" || prev == "чека" || prev == "чеков") {
                afterCheck = true;
            }
        }

        if (afterCheck) continue;

        // Всё проверено — выводим результат
        // Убираем запятую или точку в конце числа, если есть
        string number = next;
        if (!number.empty() && (number.back() == ',' || number.back() == '.')) {
            number = number.substr(0, number.size() - 1);
        }

        cout << word << ": " << number << endl;
        found = true;

        i++; // перешагиваем число — оно уже обработано, заново смотреть не нужно
    }

    if (!found) {
        cout << "Информация о магазинах не найдена." << endl;
    }

    return 0;
}
