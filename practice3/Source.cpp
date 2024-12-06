#include <iostream>
#include <vector>

class intreeNode {
public:
    int data;
    intreeNode* left;
    intreeNode* right;
public:
    intreeNode(int value) : data(value), left(nullptr), right(nullptr) {}

    int getData() const {
        return data;
    }

    void setData(int value) {
        data = value;
    }
};

class Binaryintree {
public:
    intreeNode* root;
    Binaryintree() : root(nullptr) {}

    Binaryintree(std::initializer_list<int>values) : root(nullptr) {
        for (const auto& value : values) {
            add(value);
        }
    }

    Binaryintree(Binaryintree&& other) noexcept : root(other.root) {
        other.root = nullptr;
    }
    Binaryintree& operator=(Binaryintree&& other) noexcept {
        if (this != &other) {
            clear(root);
            root = other.root;
            other.root = nullptr;
        }
        return *this;
    }

    ~Binaryintree() {
        clear(root);
    }

    intreeNode* addNode(intreeNode* node, int value) {
        if (node == nullptr) {
            return new intreeNode(value);
        }
        if (value <= node->data) {
            node->left = addNode(node->left, value);
        }
        else {
            node->right = addNode(node->right, value);
        }
        return node;
    }

    intreeNode* findMin(intreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    intreeNode* removeNode(intreeNode* node, int value) {
        if (node == nullptr) return nullptr;

        if (value < node->data) {
            node->left = removeNode(node->left, value);
        }
        else if (value > node->data) {
            node->right = removeNode(node->right, value);
        }
        else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            else if (node->left == nullptr) {
                intreeNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                intreeNode* temp = node->left;
                delete node;
                return temp;
            }
            else {
                intreeNode* minRight = findMin(node->right);
                node->data = minRight->data;
                node->right = removeNode(node->right, minRight->data);
            }
        }
        return node;
    }

    intreeNode* copyintree(intreeNode* otherRoot) {
        if (otherRoot == nullptr) return nullptr;
        intreeNode* newNode = new intreeNode(otherRoot->data);
        newNode->left = copyintree(otherRoot->left);
        newNode->right = copyintree(otherRoot->right);
        return newNode;
    }

    void mergeintrees(intreeNode* node) {
        if (node == nullptr) return;
        addNode(root, node->data);
        mergeintrees(node->left);
        mergeintrees(node->right);
    }

    void clear(intreeNode* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    void add(int value) {
        root = addNode(root, value);
    }

    void remove(int value) {
        root = removeNode(root, value);
    }

    void copyFrom(const Binaryintree& other) {
        if (this != &other) {
            clear(root);
            root = copyintree(other.root);
        }
    }

    void mergeWith(const Binaryintree& other) {
        mergeintrees(other.root);
    }

    intreeNode* getRoot() const {
        return root;
    }

    void setRoot(intreeNode* newRoot) {
        root = newRoot;
    }

    void printintree(intreeNode* node, int space = 0, int level = 0) const {
        if (node == nullptr) return;
        space += 10;
        printintree(node->right, space, level + 1);
        std::cout << std::endl;
        for (int i = 10; i < space; i++) std::cout << ' ';
        std::cout << node->data << "\n";
        printintree(node->left, space, level + 1);
    }
};


class Operations {
public:

    intreeNode* replaceElement(Binaryintree& tree, int oldValue, int newValue) {
        tree.remove(oldValue);
        tree.add(newValue);
        return tree.getRoot();
    }

    intreeNode* filterNode(intreeNode* node, int minValue) {
        if (node == nullptr) return nullptr;

        node->left = filterNode(node->left, minValue);
        node->right = filterNode(node->right, minValue);

        if (node->data < minValue) {
            intreeNode* temp = node->right ? node->right : node->left;
            delete node;
            return temp;
        }
        return node;
    }

    intreeNode* filterElements(Binaryintree& tree, int minValue) {
        filterNode(tree.root, minValue);
        return tree.getRoot();
    }
};

class TreeProcession {
private:
    Binaryintree tree;
    Operations operations;

public:
    TreeProcession() : tree() {}

    TreeProcession(intreeNode* root) {
        tree.setRoot(tree.copyintree(root));
    }

    ~TreeProcession() = default;

    intreeNode* getRoot() const {
        return tree.getRoot();
    }

    void setRoot(intreeNode* newRoot) {
        tree.setRoot(newRoot);
    }

    intreeNode* filter(int minValue) {
        intreeNode* root = tree.getRoot();
        root = operations.filterNode(root, minValue);
        tree.setRoot(root);
        return root;
    }

    intreeNode* replaceElement(int oldValue, int newValue) {
        intreeNode* root = operations.replaceElement(tree, oldValue, newValue);
        tree.setRoot(root);
        return root;
    }

    intreeNode* printTree() const {
        tree.printintree(tree.getRoot());
        return tree.getRoot();
    }

    void GlobalChanges(int oldValue, int newValue, int minValue) {
        intreeNode* root = tree.getRoot();
        root = replaceElement(oldValue, newValue);
        std::cout << "Replacement is finished" << std::endl;
        root = filter(minValue);
        std::cout << "Filtration is finished" << std::endl;
        root = printTree();
        std::cout << "Printing is finished" << std::endl;
    }

};


int main() {
    Binaryintree tree1 = { 5, 3, 7, 2, 4 };
    std::cout << "Tree 1: ";
    tree1.printintree(tree1.getRoot());

    TreeProcession operated_tree(tree1.getRoot());
    operated_tree.GlobalChanges(7, 20, 3);

}

