#include "diagonalMatrix.h"
#include "CCSmatrix.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int** readMatrixFromConsole(int& rows, int& cols) {
    cout << "������� ���������� ����� � ��������: ";
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

    cout << "�������� ������ �����:\n1. �������\n2. ����\n> ";
    cin >> choice;

    if (choice == 1) {
        cout << "\n������� ������ �������:\n";
        A = readMatrixFromConsole(rows, cols);

        cout << "\n������� ������ �������:\n";
        B = readMatrixFromConsole(rows, cols);
    }
    else {
        A = readMatrixFromFile("input1.txt", rows, cols);
        B = readMatrixFromFile("input2.txt", rows, cols);
    }

    DiagonalMatrix d1(A, rows, cols);
    DiagonalMatrix d2(B, rows, cols);
    DiagonalMatrix sum = d1 + d2;

    cout << "\n������ �������:\n";
    d1.printPacked();
    cout << "\n������ �������:\n";
    d2.printPacked();

    cout << "\n����� � ������� �����:\n";
    sum.printDense();

    CCSMatrix ccs(sum.toDense(), rows, cols);

    cout << "\n����� � CCS:\n";
    ccs.printPacked();
    ccs.printDense();

    deleteMatrix(A, rows);
    deleteMatrix(B, rows);
    return 0;
}