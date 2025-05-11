#include <iostream>
#include <fstream>
#include <cstring>
#include "lex_sort.h"

int main() {
    setlocale(LC_ALL, "Russian");

    int n;
    char** arr = nullptr;
    int choice;

    while (true) {
        std::cout << "Выберите способ ввода:\n";
        std::cout << "1. Ввод из терминала\n";
        std::cout << "2. Ввод из файла\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;
        std::cin.ignore(); // очистка буфера

        if (choice == 1) {
            std::cout << "Введите количество строк: ";
            std::cin >> n;
            std::cin.ignore();

            arr = new char* [n];
            for (int i = 0; i < n; ++i) {
                arr[i] = new char[101]; // 100 + '\0'
                std::cout << "Введите строку " << i + 1 << ": ";
                std::cin.getline(arr[i], 101);
            }

        }
        else if (choice == 2) {
            std::string filename;
            std::cout << "Введите имя файла: ";
            std::cin >> filename;

            std::ifstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Ошибка открытия файла!\n";
                return 1;
            }

            file >> n;
            file.ignore();
            arr = new char* [n];
            for (int i = 0; i < n; ++i) {
                arr[i] = new char[101];
                file.getline(arr[i], 101);
            }
            file.close();
        }
        else {
            std::cerr << "Неверный выбор!\n";
            break;
        }

        lexSort(arr, 0, n - 1);

        std::cout << "\nОтсортированные строки:\n";
        for (int i = 0; i < n; ++i) {
            std::cout << arr[i] << std::endl;
            delete[] arr[i];
        }
        delete[] arr;
    }


    return 0;
}
