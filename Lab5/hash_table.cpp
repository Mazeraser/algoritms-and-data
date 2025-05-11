#include <iostream>
#include <cstring>
#include "hash_table.h"

using namespace std;

Node::Node(const std::string& inputKey) {
    key = inputKey;
    next = nullptr;
}

Node::~Node() {}

HashTable::HashTable(int _size) {
    size = _size;
    count = 0;
    table = new Node * [size];
    for (int i = 0; i < size; ++i) {
        table[i] = nullptr;
    }
    cout << "������� ����������������" << endl;
}

HashTable::~HashTable() {
    for (int i = 0; i < size; ++i) {
        Node* current = table[i];
        while (current) {
            Node* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
    delete[] table;
}

int HashTable::hashFunction(const std::string& inputKey) {
    int sum = 0;
    for (char ch : inputKey) {
        sum += static_cast<int>(ch);
    }

    return abs(sum % size);
}

void HashTable::rehash() {
    int oldSize = size;
    size *= 2;
    Node** oldTable = table;

    table = new Node * [size];
    for (int i = 0; i < size; ++i) {
        table[i] = nullptr;
    }

    count = 0;

    for (int i = 0; i < oldSize; ++i) {
        Node* current = oldTable[i];
        while (current) {
            insert(current->key);
            Node* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
    delete[] oldTable;
}

void HashTable::insert(const std::string& inputKey) {
    cout << "���������: " << inputKey << endl;

    if ((count + 1.0) / size > 0.75) {
        cout << "����������������� ������ (rehash)" << endl;
        rehash();
    }

    int index = hashFunction(inputKey);
    cout << "���-������: " << index << endl;

    Node* current = table[index];

    while (current != nullptr) {
        if (current->key == inputKey) {
            cout << "���� ��� ����������: " << inputKey << endl;
            return;
        }
        current = current->next;
    }

    Node* newNode = new Node(inputKey);
    newNode->next = table[index];
    table[index] = newNode;
    count++;

    cout << "��������� ��������� " << endl;
}

void HashTable::remove(const std::string& inputKey) {
    int index = hashFunction(inputKey);
    cout << "��������: " << inputKey << " �� �������: " << index << endl;

    Node* current = table[index];
    Node* prev = nullptr;

    while (current) {
        if (current->key == inputKey) {
            if (prev) {
                prev->next = current->next;
            }
            else {
                table[index] = current->next;
            }
            delete current;
            count--;
            cout << "������ ����: " << inputKey << endl;
            return;
        }
        prev = current;
        current = current->next;
    }
    cout << "���� �� ������: " << inputKey << endl;
}

bool HashTable::search(const std::string& inputKey) {
    int index = hashFunction(inputKey);
    cout << "�����: " << inputKey << " �� �������: " << index << endl;

    Node* current = table[index];
    while (current) {
        if (current->key == inputKey) {
            cout << "���� ������!" << endl;
            return true;
        }
        current = current->next;
    }
    cout << "���� �� ������!" << endl;
    return false;
}

void HashTable::printTable() {
    for (int i = 0; i < size; ++i) {
        cout << "[" << i << "]: ";
        Node* current = table[i];
        while (current) {
            cout << current->key << " -> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }
}