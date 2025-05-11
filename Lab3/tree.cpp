#include "tree.h"
#include <climits>

using namespace std;

TreeNode::TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}

Tree::Tree() : root(nullptr) {}

TreeNode* Tree::getRoot() {
    return root;
}

void Tree::setRoot(TreeNode* node) {
    root = node;
}

void Tree::print() {
    printRecursive(root, 0);
}

void Tree::printRecursive(TreeNode* node, int indent) {
    if (!node) return;

    // Сначала правый ребёнок (он будет "сверху")
    printRecursive(node->right, indent + 1);

    // Печатаем текущий узел
    for (int i = 0; i < indent; ++i)
        std::cout << "\t";
    std::cout << node->value << std::endl;

    // Затем левый ребёнок (он будет "снизу")
    printRecursive(node->left, indent + 1);
}

void Tree::printLevel(TreeNode* node, int currentLevel, int maxLevel) {
    if (!node || currentLevel > maxLevel) return;
    cout << string(currentLevel * 2, ' ') << node->value << endl;
    printLevel(node->left, currentLevel + 1, maxLevel);
    printLevel(node->right, currentLevel + 1, maxLevel);
}

int Tree::countNodes(TreeNode* node) {
    if (!node) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

int Tree::height(TreeNode* node) {
    if (!node) return -1;
    return 1 + max(height(node->left), height(node->right));
}

void Tree::collectSubtrees(TreeNode* node, int targetHeight, vector<TreeNode*>& result) {
    if (!node) return;
    if (height(node) == targetHeight) {
        result.push_back(node);
    }
    collectSubtrees(node->left, targetHeight, result);
    collectSubtrees(node->right, targetHeight, result);
}

pair<TreeNode*, int> Tree::findWidestSubtree(int targetHeight) {
    vector<TreeNode*> subs;
    collectSubtrees(root, targetHeight, subs);
    TreeNode* best = nullptr;
    int maxSize = -1;
    for (TreeNode* node : subs) {
        int size = countNodes(node);
        if (size > maxSize) {
            maxSize = size;
            best = node;
        }
    }
    return { best, maxSize };
}

pair<TreeNode*, int> Tree::findNarrowestSubtree(int targetHeight) {
    vector<TreeNode*> subs;
    collectSubtrees(root, targetHeight, subs);
    TreeNode* best = nullptr;
    int minSize = INT_MAX;
    for (TreeNode* node : subs) {
        int size = countNodes(node);
        if (size < minSize) {
            minSize = size;
            best = node;
        }
    }
    return { best, minSize };
}

TreeNode* createNodeFromStream(std::istream& in) {
    int val;
    if (!(in >> val)) return nullptr;

    TreeNode* node = new TreeNode(val);

    int hasLeft = 0, hasRight = 0;
    in >> hasLeft;
    if (hasLeft)
        node->left = createNodeFromStream(in);

    in >> hasRight;
    if (hasRight)
        node->right = createNodeFromStream(in);

    return node;
}
void Tree::readFromKeyboard() {
    std::cout << "Введите дерево в формате:\n";
    std::cout << "значение_узла [0/1 есть левый] [левое поддерево если есть] [0/1 есть правый] [правое поддерево если есть]\n";
    std::cout << "Пример: 1 1 2 0 0 0  (корень 1, левый ребенок 2, без потомков)\n";

    root = createNodeFromStream(std::cin);
}
void Tree::readFromFile(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return;
    }
    root = createNodeFromStream(fin);
    fin.close();
}
