#include<iostream>
#include<fstream>
#include <string>
#include <vector>

using namespace std;

const string FILENAME = "rotation";

//cin.tie(nullptr);
//ios::sync_with_stdio(false);

ifstream fin(FILENAME + ".in");
ofstream fout(FILENAME + ".out");

struct Node {
    int value;
    int left;
    int right;
    int height;

    Node() : left{-1}, right{-1}, height{-1} {}

    Node(int value, int left, int right) : value{value}, left{left}, right{right}, height{-1} {}
};

struct AVLTree {
    vector<Node> arr;
    int root;

    AVLTree() = default;

    explicit AVLTree(int n) : arr{vector<Node>(n)}, root{0} {}

    int height(int k) {
        if (k == -1) return 0;
        if (this->arr[k].height != -1) return this->arr[k].height;

        return this->arr[k].height = 1 + max(height(this->arr[k].left), height(this->arr[k].right));
    }

    int balance(int k) {
        return height(this->arr[k].right) - height(this->arr[k].left);
    }

    int singleRightRotate(int k) {
        int u = this->arr[k].left;
        this->arr[k].left = this->arr[u].right;
        this->arr[u].right = k;
        this->arr[k].height = max(height(this->arr[k].left), height(this->arr[k].right)) + 1;
        this->arr[u].height = max(height(this->arr[u].left), height(this->arr[u].right)) + 1;
        return u;
    }

    int singleLeftRotate(int k) {
        int u = this->arr[k].right;
        this->arr[k].right = this->arr[u].left;
        this->arr[u].left = k;
        this->arr[k].height = max(height(this->arr[k].left), height(this->arr[k].right)) + 1;
        this->arr[u].height = max(height(this->arr[u].left), height(this->arr[u].right)) + 1;

        this->root = u;

        return u;
    }

    int doubleLeftRotate(int k) {
//        cerr << "Doing right rotate -> left rotate\n";
        this->arr[k].right = singleRightRotate(this->arr[k].right);
//        debug_tree();
        return singleLeftRotate(k);
    }

    void doStuff() {
        if (balance(this->arr[0].right) == -1) {
//            cerr << "root->right balance  == -1\n";
            doubleLeftRotate(0);
        } else {
            singleLeftRotate(0);
        }
    }

    void debug_balance() {
        cerr << "DEBUG BALANCE\n";
        for (int i = 0; i < this->arr.size(); i++) {
            cerr << balance(i) << '\n';
        }
    }

    void debug_tree() {
        cerr << "DEBUG TREE\n";

        auto root = &this->arr[this->root];
        cerr << 1 << '\t' << root->value << ' ' << cmp(root->left, this->root) << ' ' << cmp(root->right, this->root)
             << '\n';

        for (int i = 0; i < this->arr.size(); i++) {
            if (i == this->root) continue;
            auto el = &this->arr[i];
            if (i < this->root) {
                cerr << i + 2 << '\t' << el->value << ' ' << cmp(el->left, this->root)
                     << ' ' << cmp(el->right, this->root) << '\n';
            } else {
                cerr << i + 1 << '\t' << el->value << ' ' << cmp(el->left, this->root) << ' ' << el->right + 1 << '\n';
            }
        }
    }

    void print() {
        auto root = &this->arr[this->root];
        fout << root->value << ' ' << cmp(root->left, this->root) << ' ' << cmp(root->right, this->root) << '\n';

        for (int i = 0; i < this->arr.size(); i++) {
            if (i == this->root) continue;
            auto el = &this->arr[i];
            if (i < this->root) {
                fout << el->value << ' ' << cmp(el->left, this->root)
                     << ' ' << cmp(el->right, this->root) << '\n';
            } else {
                fout << el->value << ' ' << cmp(el->left, this->root) << ' ' << el->right + 1 << '\n';
            }
        }
    }

    int cmp(int el1, int el2) {
        if (el1 == -1) return 0;
        if (el1 <= el2) return el1 + 2;
        else return el1 + 1;
    }
};


int main() {


    int n;
    fin >> n;
    auto *tree = new AVLTree(n);

    int val, l, r;
    int c = 0;
    while (fin >> val >> l >> r) {
        tree->arr[c] = Node(val, l - 1, r - 1);
        c++;
    }

    tree->doStuff();

//    tree->debug_tree();


    fout << n << '\n';
//    for (int i = 0; i < n; i++) {
//        auto el = &tree->arr[i];
//        fout << el->value << ' ' << el->left + 1 << ' ' << el->right + 1 << '\n';
//    }
    tree->print();

    return 0;
}