#include<iostream>
#include<fstream>
#include <string>
#include <vector>

using namespace std;

const string FILENAME = "addition";

//cin.tie(nullptr);
//ios::sync_with_stdio(false);

ifstream fin(FILENAME + ".in");
ofstream fout(FILENAME + ".out");

struct Line {
    int data;
    int left;
    int right;

    Line() = default;

    Line(int data, int left, int right) : data{data}, left{left}, right{right} {}
};

struct AVLTree {
    struct node {
        int value;
        node *left;
        node *right;
        int height;

        node() : value{-1}, left{nullptr}, right{nullptr}, height{-1} {}
    };

    AVLTree() : root{nullptr} {}

    node *root;


    node *singleRightRotate(node *&t) {
        node *u = t->left;
        t->left = u->right;
        u->right = t;
        t->height = max(height(t->left), height(t->right)) + 1;
        u->height = max(height(u->left), t->height) + 1;
        return u;
    }

    node *singleLeftRotate(node *&t) {
        node *u = t->right;
        t->right = u->left;
        u->left = t;
        t->height = max(height(t->left), height(t->right)) + 1;
        u->height = max(height(t->right), t->height) + 1;
        return u;
    }

    node *doubleLeftRotate(node *&t) {
        t->right = singleRightRotate(t->right);
        return singleLeftRotate(t);
    }

    node *doubleRightRotate(node *&t) {
        t->left = singleLeftRotate(t->left);
        return singleRightRotate(t);
    }


    int height(node *t) {
        if (t == nullptr) return -1;
        if (t->height == -1) t->height = max(height(t->left), height(t->right)) + 1;
        return t->height;
    }

    node *insert(int x, node *t) {
        if (t == nullptr) {
            t = new node;
            t->value = x;
            t->height = 0;
            t->left = nullptr;
            t->right = nullptr;
        } else if (x < t->value) {
            t->left = insert(x, t->left);
            if (height(t->left) - height(t->right) == 2) {
                if (x < t->left->value)
                    t = singleRightRotate(t);
                else
                    t = doubleRightRotate(t);
            }
        } else if (x > t->value) {
            t->right = insert(x, t->right);
            if (height(t->right) - height(t->left) == 2) {
                if (x > t->right->value)
                    t = singleLeftRotate(t);
                else
                    t = doubleLeftRotate(t);
            }
        }

        t->height = max(height(t->left), height(t->right)) + 1;
        return t;
    }

    void insert(int x) {
        root = insert(x, root);
    }

    vector<Line> toPrint;

    void preorder(int &curr, node *t) {
        if (t == nullptr) return;
        int curr_save = curr;
        toPrint[curr - 1].data = t->value;
        if (t->left == nullptr) toPrint[curr - 1].left = 0;
        else {
            toPrint[curr - 1].left = curr + 1;
            curr++;
            preorder(curr, t->left);
        }

        if (t->right == nullptr) toPrint[curr_save - 1].right = 0;
        else {
            toPrint[curr_save - 1].right = curr + 1;
            curr++;
            preorder(curr, t->right);
        }
    }

    void print(int n) {
        toPrint.resize(n);
        int i = 1;
        preorder(i, root);

        for (auto x: toPrint) {
            fout << x.data << ' ' << x.left << ' ' << x.right << '\n';
        }
    }

};


int main() {
    int n;
    fin >> n;

    vector<AVLTree::node> arr(n + 1);

    int val, l, r;

    for (auto i = 0; i < n; i++) {
        fin >> val >> l >> r;
        arr[i].value = val;
        if (l - 1 != -1) arr[i].left = &arr[l - 1];
        else arr[i].left = nullptr;
        if (r - 1 != -1) arr[i].right = &arr[r - 1];
        else arr[i].right = nullptr;

    }

    int toInsert;
    fin >> toInsert;
    AVLTree tree;
    if (n != 0) tree.root = &arr[0];
    tree.insert(toInsert);

    fout << n + 1 << '\n';
    tree.print(n + 1);

    return 0;
}