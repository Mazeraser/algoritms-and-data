#include <iostream>
#include <string>

using namespace std;

struct Node {
    std::string key;
    Node* next;

    Node(const std::string& inputKey);
    ~Node();
};

class HashTable {
private:
    Node** table;
    int size;
    int count;

    int hashFunction(const std::string& inputKey);
    void rehash();

public:
    HashTable(int _size = 10);
    ~HashTable();

    void insert(const std::string& inputKey);
    void remove(const std::string& inputKey);
    bool search(const std::string& inputKey);
    void printTable();
};