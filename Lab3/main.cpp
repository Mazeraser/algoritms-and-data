#include "tree.h"

int main() {
    setlocale(LC_ALL, "Russian");

    Tree tree;

    std::cout << "1-���� � ����������\n2-���� �� �����" << std::endl;
    int key;
    std::cin >> key;
    switch (key)
    {
    case 1:
        tree.readFromKeyboard();
        break;
    case 2:
        tree.readFromFile("test.txt");
        break;
    default:
        break;
    }

    /* ������ �������� ������ �������
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(6);
    root->right->right->right = new TreeNode(7);
    tree.setRoot(root); */

    std::cout << "������:\n";
    tree.print();

    int h = 0;

    std::cout << "������� ������ ���������: ";
    std::cin >> h;

    auto [widest, wSize] = tree.findWidestSubtree(h);
    std::cout << "\n����� ������� ��������� ������ " << h
        << " �������� " << wSize << " �����, ������: " << widest->value << std::endl;

    auto [narrowest, nSize] = tree.findNarrowestSubtree(h);
    std::cout << "����� ����� ��������� ������ " << h
        << " �������� " << nSize << " �����, ������: " << narrowest->value << std::endl;

    return 0;
}
