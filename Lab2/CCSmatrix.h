#pragma once

class CCSMatrix {
private:
    int n, m;
    int* A;
    int* LI;
    int* LJ;
    int nnz;

public:
    CCSMatrix(int** mat, int rows, int cols);
    ~CCSMatrix();
    void printDense() const;
    void printPacked() const;
};
