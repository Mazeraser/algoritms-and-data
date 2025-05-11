#pragma once
#include <iostream>
#include <string>

struct Node {
    int id;
    int childrenCount;
    Node** children;

    Node(int id);
    ~Node();

    void addChild(Node* child);
};

class Tree {
private:
    Node* root;

    void printTree(Node* node, std::string indent, bool isLast);
    void findValidSubtrees(Node* node, int depth);

public:
    Tree(int rootId);
    ~Tree();

    Node* getRoot();
    void print();
    void findSubtreesWithOddEvenRule();
};
