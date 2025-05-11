#include "DiagonalMatrix.h"
#include <iostream>

using namespace std;

DiagonalMatrix::DiagonalMatrix(int** mat, int rows, int cols) {
    n = rows;
    m = cols;
    diagCount = 0;

    // Определим количество диагоналей
    for (int d = -n + 1; d < m; ++d) {
        for (int i = 0; i < n; ++i) {
            int j = i + d;
            if (j >= 0 && j < m && mat[i][j] != 0) {
                diagCount++;
                break;
            }
        }
    }

    shifts = new int[diagCount];
    diagonals = new int* [diagCount];

    int k = 0;
    for (int d = -n + 1; d < m; ++d) {
        bool found = false;
        for (int i = 0; i < n; ++i) {
            int j = i + d;
            if (j >= 0 && j < m && mat[i][j] != 0) {
                found = true;
                break;
            }
        }

        if (found) {
            shifts[k] = d;
            diagonals[k] = new int[n];
            for (int i = 0; i < n; ++i)
                diagonals[k][i] = (i + d >= 0 && i + d < m) ? mat[i][i + d] : 0;
            ++k;
        }
    }

    int* shifts_copy = shifts;
    shifts = new int[k];
    for (int i = 0; i < k; i++) {
        shifts[i] = shifts_copy[i];
    }
    delete[] shifts_copy;
}
DiagonalMatrix::DiagonalMatrix() {
    n = m = diagCount = 0;
    shifts = nullptr;
    diagonals = nullptr;
}


DiagonalMatrix::~DiagonalMatrix() {
    for (int i = 0; i < diagCount; ++i)
        delete[] diagonals[i];
    delete[] diagonals;
    delete[] shifts;
}

int** DiagonalMatrix::toDense() const {
    int** mat = new int* [n];
    for (int i = 0; i < n; ++i) {
        mat[i] = new int[m];
        for (int j = 0; j < m; ++j)
            mat[i][j] = 0;
    }

    for (int d = 0; d < diagCount; ++d) {
        int shift = shifts[d];
        for (int i = 0; i < n; ++i) {
            int j = i + shift;
            if (j >= 0 && j < m)
                mat[i][j] = diagonals[d][i];
        }
    }

    return mat;
}

void DiagonalMatrix::printPacked() const {
    cout << "Смещения диагоналей: ";
    for (int i = 0; i < diagCount; ++i)
        cout << shifts[i] << " ";
    cout << endl;

    cout << "Диагонали:\n";
    for (int d = 0; d < diagCount; ++d) {
        cout << "diag[" << shifts[d] << "]: ";
        for (int i = 0; i < n; ++i)
            cout << diagonals[d][i] << " ";
        cout << endl;
    }
}
void DiagonalMatrix::printDense() const {
    int** mat = toDense();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            cout << mat[i][j] << " ";
        cout << endl;
        delete[] mat[i];
    }
    delete[] mat;
}

int DiagonalMatrix::getRows() const { return n; }
int DiagonalMatrix::getCols() const { return m; }

DiagonalMatrix DiagonalMatrix::operator+(const DiagonalMatrix& other) const {
    // Максимально возможное число диагоналей — объединение всех уникальных смещений
    int* resultShifts = new int[diagCount + other.diagCount];
    int shiftCount = 0;

    // Сначала копируем все смещения первого
    for (int i = 0; i < diagCount; ++i)
        resultShifts[shiftCount++] = shifts[i];

    // Добавим только уникальные смещения второго
    for (int i = 0; i < other.diagCount; ++i) {
        bool found = false;
        for (int j = 0; j < diagCount; ++j) {
            if (other.shifts[i] == shifts[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            resultShifts[shiftCount++] = other.shifts[i];
        }
    }

    // Выделим память под итоговые диагонали
    int** resultDiagonals = new int* [shiftCount];
    for (int i = 0; i < shiftCount; ++i) {
        resultDiagonals[i] = new int[n];
        for (int j = 0; j < n; ++j)
            resultDiagonals[i][j] = 0; // обнулим
    }

    // Заполняем из первого
    for (int d = 0; d < diagCount; ++d) {
        int shift = shifts[d];
        int idx = -1;
        for (int i = 0; i < shiftCount; ++i)
            if (resultShifts[i] == shift) idx = i;
        for (int i = 0; i < n; ++i)
            resultDiagonals[idx][i] += diagonals[d][i];
    }

    // Заполняем из второго
    for (int d = 0; d < other.diagCount; ++d) {
        int shift = other.shifts[d];
        int idx = -1;
        for (int i = 0; i < shiftCount; ++i)
            if (resultShifts[i] == shift) idx = i;
        for (int i = 0; i < n; ++i)
            resultDiagonals[idx][i] += other.diagonals[d][i];
    }

    // Создаем результат
    DiagonalMatrix result;
    result.n = n;
    result.m = m;
    result.diagCount = shiftCount;
    result.shifts = new int[shiftCount];
    result.diagonals = new int* [shiftCount];

    for (int i = 0; i < shiftCount; ++i) {
        result.shifts[i] = resultShifts[i];
        result.diagonals[i] = new int[n];
        for (int j = 0; j < n; ++j)
            result.diagonals[i][j] = resultDiagonals[i][j];
    }

    // Чистим временные массивы
    for (int i = 0; i < shiftCount; ++i)
        delete[] resultDiagonals[i];
    delete[] resultDiagonals;
    delete[] resultShifts;

    return result;
}