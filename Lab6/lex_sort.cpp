#include "lex_sort.h"
#include <cstring> 

void swap(char*& a, char*& b) {
    char* temp = a;
    a = b;
    b = temp;
}

void lexSort(char** arr, int left, int right) {
    if (left >= right) return;

    int i = left;
    int j = right;
    char* pivot = arr[(left + right) / 2];

    while (i <= j) {
        while (strcmp(arr[i], pivot) < 0) ++i;
        while (strcmp(arr[j], pivot) > 0) --j;
        if (i <= j) {
            swap(arr[i], arr[j]);
            ++i;
            --j;
        }
    }

    if (left < j) lexSort(arr, left, j);
    if (i < right) lexSort(arr, i, right);
}
