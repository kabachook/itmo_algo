#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const string FILENAME = "bstsimple";

struct BST {
    struct Node {
        int value;
        Node *left;
        Node *right;

        Node() : left{nullptr}, right{nullptr} {}

        Node(int value) : value{value}, left{nullptr}, right{nullptr} {}

    };

    Node *root;

    BST() : root{nullptr} {};


    bool exists(int key) {
        if(this->root == nullptr)
            return false;

        Node* node = this->root;
        while (node != nullptr){
            if(node->value == key)
                return true;
            if(key < node->value)
                node = node->left;
            else
                node = node->right;
        }
        return false;
    }

    int next(Node *node, int key, Node *result) {
        if (node == nullptr)
            return result->value;

        if (node->value <= key) {
            next(node->right, key, result);
        } else {
            result->value = node->value;
            next(node->left, key, result);
        }

        return (result->value);
    }

    int prev(Node *node, int key, Node *result) {
        if (node == nullptr)
            return result->value;

        if (node->value >= key) {
            prev(node->left, key, result);
        } else {
            result->value = node->value;
            prev(node->right, key, result);
        }

        return (result->value);
    }

    void insert(int key) {
        Node *node = this->root;
        if (node == nullptr) {
            this->root = new Node(key);
        } else {
            while (true) {
                if (node->value == key) return;
                if (key < node->value) {
                    if (node->left == nullptr) {
                        node->left = new Node(key);
                        return;
                    } else
                        node = node->left;
                } else {
                    if (node->right == nullptr) {
                        node->right = new Node(key);
                        return;
                    } else
                        node = node->right;
                }
            }
        }
    }

    void remove(int key) {
        if(this->root == nullptr)
            return;
        Node *node = root, *parent = nullptr;
        while (node != nullptr){
            if(node->value == key)
                break;
            parent = node;
            if(key < node->value)
                node = node->left;
            else
                node = node->right;
        }
        if(node == nullptr)
            return;

        if(node->right == nullptr){
            if(parent == nullptr)
                root = node->left;
            else
            if(node == parent->left)
                parent->left = node->left;
            else
                parent->right = node->left;
        } else {
            Node *mostLeft = node->right;
            parent = nullptr;
            while (mostLeft->left != nullptr) {
                parent = mostLeft;
                mostLeft = mostLeft->left;
            }

            if(parent != nullptr)
                parent->left = mostLeft->right;
            else
                node->right = mostLeft->right;

            node->value = mostLeft->value;
        }
    }

};

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    ifstream fin(FILENAME + ".in");
    ofstream fout(FILENAME + ".out");

    string command;
    int key;

    auto bst = BST();

    while (fin >> command >> key) {
        if (command == "insert") {
            bst.insert(key);
        } else if (command == "delete") {
            bst.remove(key);
        } else if (command == "exists") {
            auto res = bst.exists(key);
            if (res == false) fout << "false" << endl;
            else fout << "true" << endl;
        } else if (command == "next") {
            auto result = new BST::Node(key);
            int m = bst.next(bst.root, key, result);
            if (m != key) {
                fout << m << endl;
            } else {
                fout << "none" << endl;
            }

        } else if (command == "prev") {
            auto result = new BST::Node(key);
            int m = bst.prev(bst.root, key, result);
            if (m != key) {
                fout << m << endl;
            } else {
                fout << "none" << endl;
            }
        }
    }

}