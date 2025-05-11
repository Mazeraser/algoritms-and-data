#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val);
};

class Tree {
private:
    TreeNode* root;

    void printLevel(TreeNode* node, int currentLevel, int maxLevel);
    void printRecursive(TreeNode* node, int indent);
    int countNodes(TreeNode* node);
    int height(TreeNode* node);
    void collectSubtrees(TreeNode* node, int targetHeight, std::vector<TreeNode*>& result);

public:
    Tree();

    TreeNode* getRoot();
    void setRoot(TreeNode* node);

    void print();
    std::pair<TreeNode*, int> findWidestSubtree(int targetHeight);
    std::pair<TreeNode*, int> findNarrowestSubtree(int targetHeight);

    void readFromKeyboard();
    void readFromFile(const std::string& filename);
};