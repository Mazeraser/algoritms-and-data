#include <iostream>
#include <fstream>
#include "hash_table.h"

int main() {
    setlocale(LC_ALL, "Russian");

    HashTable* ht = new HashTable();

    int n;
    std::string* keys=new string[1];
    

    std::cout << "0 - Ввод с клавиатуры\n1 - Ввод из файла\n";
    int key=0;
    std::cin >> key;
    std::ifstream in("file.txt");
    string plug;
    switch (key)
    {
    case 0:
        std::cout << "Введите количество вводимых элементов" << std::endl;
        std::cin >> n;
        keys = new string[n]; 
        std::getline(std::cin, plug);
        for (int i = 0; i < n; i++) {
            getline(std::cin,keys[i]);
            ht->insert(keys[i]);
        }
        break;
    case 1:
        if (in.is_open()) {
            in >> n;
            keys = new string[n];
            string plug;
            std::getline(in, plug);
            for (int i = 0; i < n; i++) {
                std::getline(in, keys[i]);
                ht->insert(keys[i]);
            }
        }
        break;
    default:
        break;
    }

    ht->printTable();

    int randNum1 = rand() % n;
    int randNum2 = rand() % n;
    int randNum3 = rand() % n;
    std::cout << "\nУдаление " << keys[randNum1] <<"\n";
    ht->remove(keys[randNum1]);

    ht->printTable();

    std::cout << "\nПоиск" << keys[randNum2] << ": "
        << (ht->search(keys[randNum2]) ? "найден" : "не найден") << std::endl;
    std::cout << "\nПоиск" << keys[randNum3] << ": "
        << (ht->search(keys[randNum3]) ? "найден" : "не найден") << std::endl;

    delete ht; // Освобождение памяти

    return 0;
}