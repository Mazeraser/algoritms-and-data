#include "tree.h"

int main() {
    setlocale(LC_ALL, "Russian");

    Tree tree;

    std::cout << "1-Ввод с клавиатуры\n2-Ввод из файла" << std::endl;
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

    /* Строим бинарное дерево вручную
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(6);
    root->right->right->right = new TreeNode(7);
    tree.setRoot(root); */

    std::cout << "Дерево:\n";
    tree.print();

    int h = 0;

    std::cout << "Уровень высоты поддерева: ";
    std::cin >> h;

    auto [widest, wSize] = tree.findWidestSubtree(h);
    std::cout << "\nСамое широкое поддерево высоты " << h
        << " содержит " << wSize << " узлов, корень: " << widest->value << std::endl;

    auto [narrowest, nSize] = tree.findNarrowestSubtree(h);
    std::cout << "Самое узкое поддерево высоты " << h
        << " содержит " << nSize << " узлов, корень: " << narrowest->value << std::endl;

    return 0;
}
