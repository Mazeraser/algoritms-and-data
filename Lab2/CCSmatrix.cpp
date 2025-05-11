#include "CCSMatrix.h"
#include <iostream>

using namespace std;

CCSMatrix::CCSMatrix(int** mat, int rows, int cols) {
    n = rows;
    m = cols;

    // Подсчёт ненулевых элементов
    nnz = 0;
    for (int j = 0; j < m; ++j)
        for (int i = 0; i < n; ++i)
            if (mat[i][j] != 0)
                ++nnz;

    A = new int[nnz];
    LI = new int[nnz];
    LJ = new int[m + 1];

    int pos = 0;
    for (int j = 0; j < m; ++j) {
        LJ[j] = pos;
        for (int i = 0; i < n; ++i) {
            if (mat[i][j] != 0) {
                A[pos] = mat[i][j];
                LI[pos] = i;
                ++pos;
            }
        }
    }
    LJ[m] = nnz;
}

CCSMatrix::~CCSMatrix() {
    delete[] A;
    delete[] LI;
    delete[] LJ;
}

void CCSMatrix::printPacked() const {
    std::cout << "\nУпакованный формат (CCS):\n";

    std::cout << "A (значения): ";
    for (int i = 0; i < nnz; ++i)
        std::cout << A[i] << " ";
    std::cout << std::endl;

    std::cout << "LI (строки):   ";
    for (int i = 0; i < nnz; ++i)
        std::cout << LI[i] << " ";
    std::cout << std::endl;

    std::cout << "LJ (столбцы):  ";
    for (int i = 0; i <= m; ++i)
        std::cout << LJ[i] << " ";
    std::cout << std::endl;
}
void CCSMatrix::printDense() const {
    int** mat = new int* [n];
    for (int i = 0; i < n; ++i) {
        mat[i] = new int[m];
        for (int j = 0; j < m; ++j)
            mat[i][j] = 0;
    }

    for (int j = 0; j < m; ++j)
        for (int k = LJ[j]; k < LJ[j + 1]; ++k)
            mat[LI[k]][j] = A[k];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            cout << mat[i][j] << " ";
        cout << endl;
        delete[] mat[i];
    }
    delete[] mat;
}
