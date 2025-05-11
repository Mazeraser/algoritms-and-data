#include "Tree.h"

Node::Node(int id) {
    this->id = id;
    childrenCount = 0;
    children = nullptr;
}

Node::~Node() {
    for (int i = 0; i < childrenCount; ++i)
        delete children[i];
    delete[] children;
}

void Node::addChild(Node* child) {
    Node** newChildren = new Node * [childrenCount + 1];
    for (int i = 0; i < childrenCount; ++i)
        newChildren[i] = children[i];
    newChildren[childrenCount] = child;
    delete[] children;
    children = newChildren;
    childrenCount++;
}

Tree::Tree(int rootId) {
    root = new Node(rootId);
}

Tree::~Tree() {
    delete root;
}

Node* Tree::getRoot() {
    return root;
}

void Tree::printTree(Node* node, std::string indent, bool isLast) {
    std::cout << indent;

    std::cout << node->id << "\n";

    std::string newIndent = indent + "\t";
    for (int i = 0; i < node->childrenCount; ++i)
        printTree(node->children[i], newIndent, i == node->childrenCount - 1);
}

void Tree::print() {
    printTree(root, "", true);
}

void Tree::findValidSubtrees(Node* node, int depth) {
    if (!node) return;

    bool valid = true;
    if ((depth % 2 == 0 && node->id % 2 != 0) ||
        (depth % 2 != 0 && node->id % 2 == 0)) {
        valid = false;
    }

    for (int i = 0; i < node->childrenCount; ++i)
        findValidSubtrees(node->children[i], depth + 1);

    if (valid) {
        std::cout << "Поддерево, начинающееся с вершины " << node->id << " на глубине " << depth << ":\n";
        printTree(node, "\t", true);
        std::cout << "--------------------------\n";
    }
}

void Tree::findSubtreesWithOddEvenRule() {
    std::cout << "Поиск поддеревьев, где на чётной глубине - чётные номера, на нечётной - нечётные:\n";
    findValidSubtrees(root, 0);
}
