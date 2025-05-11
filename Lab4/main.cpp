#include <locale>
#include <fstream>
#include "Tree.h"

void addNodes(Node& parent, int nodeCount, std::istream& input) {
    Node** nodes = new Node * [nodeCount];
    for (int i = 0; i < nodeCount; i++) {
        int nodeId;
        input >> nodeId;
        nodes[i] = new Node(nodeId);
        parent.addChild(nodes[i]);
    }
}

void setupNodes(Node& parent, std::istream& input, bool fromFile) {
    int nodeCount = 0;
    if (fromFile) {
        input >> nodeCount;
    }
    else {
        std::cout << "Введите количество вершин от " << parent.id << std::endl;
        input >> nodeCount;
    }

    addNodes(parent, nodeCount, input);

    int key;
    if (fromFile) {
        key = 0; // В файле всегда обрабатываем все уровни
    }
    else {
        std::cout << "Ввести новую глубину?\n"
            << "\t0-Да\n"
            << "\t1-Нет" << std::endl;
        input >> key;
    }

    if (key == 0) {
        for (int i = 0; i < parent.childrenCount; i++)
            setupNodes(*parent.children[i], input, fromFile);
    }
}

void inputFromConsole(Tree& tree) {
    std::cout << "Введите значение корня" << std::endl;
    std::cin >> tree.getRoot()->id;
    setupNodes(*tree.getRoot(), std::cin, false);
}

void inputFromFile(Tree& tree) {
    std::string filename;
    std::cout << "Введите имя файла: ";
    std::cin >> filename;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл!" << std::endl;
        return;
    }

    int rootId;
    file >> rootId;
    tree.getRoot()->id = rootId;
    setupNodes(*tree.getRoot(), file, true);
    file.close();
}

int main() {
    setlocale(LC_ALL, "");

    Tree tree(0);

    int choice;
    std::cout << "Выберите способ ввода:\n"
        << "1 - Ввод из консоли\n"
        << "2 - Ввод из файла\n"
        << "Ваш выбор: ";
    std::cin >> choice;

    switch (choice) {
    case 1:
        inputFromConsole(tree);
        break;
    case 2:
        inputFromFile(tree);
        break;
    default:
        std::cout << "Неверный выбор, используется ввод из консоли" << std::endl;
        inputFromConsole(tree);
    }

    std::cout << "Полное дерево:\n";
    tree.print();

    std::cout << "\nРезультат поиска поддеревьев по правилу:\n";
    tree.findSubtreesWithOddEvenRule();

    return 0;
}