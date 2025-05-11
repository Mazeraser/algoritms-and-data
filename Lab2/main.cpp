#include "diagonalMatrix.h"
#include "CCSmatrix.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int** readMatrixFromConsole(int& rows, int& cols) {
    cout << "Введите количество строк и столбцов: ";
    cin >> rows >> cols;

    int** mat = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        mat[i] = new int[cols];
        for (int j = 0; j < cols; ++j)
            cin >> mat[i][j];
    }
    return mat;
}

int** readMatrixFromFile(const char* filename, int& rows, int& cols) {
    ifstream fin(filename);
    string line;
    rows = 0;

    fin >> rows >> cols;

    int** mat = new int*[rows];
    for (int i = 0; i < cols; i++) {
        mat[i] = new int[cols];
        for (int j = 0; j < rows; j++)
            fin >> mat[i][j];
    }

    fin.close();
    return mat;
}

void deleteMatrix(int** mat, int rows) {
    for (int i = 0; i < rows; ++i)
        delete[] mat[i];
    delete[] mat;
}

int main() {
    setlocale(LC_ALL, "Russian");

    int choice;
    int rows, cols;
    int** A = nullptr;
    int** B = nullptr;

    cout << "Выберите способ ввода:\n1. Консоль\n2. Файл\n> ";
    cin >> choice;

    if (choice == 1) {
        cout << "\nВведите первую матрицу:\n";
        A = readMatrixFromConsole(rows, cols);

        cout << "\nВведите вторую матрицу:\n";
        B = readMatrixFromConsole(rows, cols);
    }
    else {
        A = readMatrixFromFile("input1.txt", rows, cols);
        B = readMatrixFromFile("input2.txt", rows, cols);
    }

    DiagonalMatrix d1(A, rows, cols);
    DiagonalMatrix d2(B, rows, cols);
    DiagonalMatrix sum = d1 + d2;

    cout << "\nПервая матрица:\n";
    d1.printPacked();
    cout << "\nВторая матрица:\n";
    d2.printPacked();

    cout << "\nСумма в обычной форме:\n";
    sum.printDense();

    CCSMatrix ccs(sum.toDense(), rows, cols);

    cout << "\nСумма в CCS:\n";
    ccs.printPacked();
    ccs.printDense();

    deleteMatrix(A, rows);
    deleteMatrix(B, rows);
    return 0;
}