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
        std::cout << "������� ���������� ������ �� " << parent.id << std::endl;
        input >> nodeCount;
    }

    addNodes(parent, nodeCount, input);

    int key;
    if (fromFile) {
        key = 0; // � ����� ������ ������������ ��� ������
    }
    else {
        std::cout << "������ ����� �������?\n"
            << "\t0-��\n"
            << "\t1-���" << std::endl;
        input >> key;
    }

    if (key == 0) {
        for (int i = 0; i < parent.childrenCount; i++)
            setupNodes(*parent.children[i], input, fromFile);
    }
}

void inputFromConsole(Tree& tree) {
    std::cout << "������� �������� �����" << std::endl;
    std::cin >> tree.getRoot()->id;
    setupNodes(*tree.getRoot(), std::cin, false);
}

void inputFromFile(Tree& tree) {
    std::string filename;
    std::cout << "������� ��� �����: ";
    std::cin >> filename;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "�� ������� ������� ����!" << std::endl;
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
    std::cout << "�������� ������ �����:\n"
        << "1 - ���� �� �������\n"
        << "2 - ���� �� �����\n"
        << "��� �����: ";
    std::cin >> choice;

    switch (choice) {
    case 1:
        inputFromConsole(tree);
        break;
    case 2:
        inputFromFile(tree);
        break;
    default:
        std::cout << "�������� �����, ������������ ���� �� �������" << std::endl;
        inputFromConsole(tree);
    }

    std::cout << "������ ������:\n";
    tree.print();

    std::cout << "\n��������� ������ ����������� �� �������:\n";
    tree.findSubtreesWithOddEvenRule();

    return 0;
}