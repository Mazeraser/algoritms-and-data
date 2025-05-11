#pragma once

class DiagonalMatrix {
private:
    int n, m;
    int* shifts;
    int** diagonals;
    int diagCount;

public:
    DiagonalMatrix(int** mat, int rows, int cols);
    DiagonalMatrix();
    ~DiagonalMatrix();
    int** toDense() const;
    void printPacked() const;
    void printDense() const;
    int getRows() const;
    int getCols() const;

    DiagonalMatrix operator+(const DiagonalMatrix& other) const;
};
