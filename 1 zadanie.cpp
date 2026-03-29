#include <iostream>
#include <string>
using namespace std;

int main() {
    setlocale(LC_ALL, "");

    //Ввод размеров матрицы
    int rows, cols;
    cout << "Введите количество строк (включая строку с номерами столбцов): ";
    cin >> rows;
    cout << "Введите количество столбцов: ";
    cin >> cols;

    if (rows < 2 || cols < 1) {
        cout << "Ошибка: матрица должна иметь хотя бы 2 строки и 1 столбец." << endl;
        return 1;
    }

    // Динамический двумерный массив через одномерный (rows * cols)
    int* matrix = new int[rows * cols];

    // --- Ввод матрицы ---
    cout << "Введите матрицу построчно (" << rows << " строк, " << cols << " столбцов):" << endl;
    cout << "(Первая строка — номера столбцов)" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> matrix[i * cols + j];
        }
    }

    //Ввод K
    int K;
    cout << "Введите K (номер столбца для сортировки): ";
    cin >> K;

    // Оптимизация 3: ищем позицию столбца K в заголовочной строке один раз
    int colIndex = -1;
    for (int j = 0; j < cols; j++) {
        if (matrix[0 * cols + j] == K) {
            colIndex = j;
            break;
        }
    }

    if (colIndex == -1) {
        cout << "Ошибка: столбец с номером " << K << " не найден в заголовочной строке." << endl;
        delete[] matrix;
        return 1;
    }

    // Оптимизация 2: индексная сортировка
    // Создаём массив индексов строк данных (без строки-заголовка)
    int dataRows = rows - 1;
    int* idx = new int[dataRows];
    for (int i = 0; i < dataRows; i++) idx[i] = i + 1; 

    //Оптимизация 1: пузырёк с ранней остановкой
    for (int i = 0; i < dataRows - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < dataRows - 1 - i; j++) {
            int valJ  = matrix[idx[j]  * cols + colIndex];
            int valJ1 = matrix[idx[j+1] * cols + colIndex];
            if (valJ > valJ1) {
                // Меняем только индексы — не трогаем саму матрицу
                int tmp = idx[j];
                idx[j]  = idx[j+1];
                idx[j+1] = tmp;
                swapped = true;
            }
        }
        if (!swapped) break; // ранняя остановка
    }

    //Вывод результата
    cout << "\nМатрица после сортировки по столбцу " << K << ":" << endl;

    // Сначала выводим заголовочную строку
    for (int j = 0; j < cols; j++) {
        cout << matrix[0 * cols + j];
        if (j < cols - 1) cout << "\t";
    }
    cout << endl;

    // Затем строки в отсортированном порядке
    for (int i = 0; i < dataRows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[idx[i] * cols + j];
            if (j < cols - 1) cout << "\t";
        }
        cout << endl;
    }

    delete[] matrix;
    delete[] idx;
    return 0;
}
