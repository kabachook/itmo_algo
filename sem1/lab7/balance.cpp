#include<iostream>
#include<fstream>
#include <string>
#include <vector>

using namespace std;

const string FILENAME = "balance";

struct Node {
    int left;
    int right;
    int height;

    Node() : left{-1}, right{-1}, height{-1} {}

    Node(int left, int right) : left{left}, right{right}, height{-1} {}
};

struct AVLTree {
    vector<Node> arr;

    AVLTree() = default;

    explicit AVLTree(int n) : arr{vector<Node>(n)} {}

    int height(int k) {
        if (k == -1) return 0;
        if (this->arr[k].height != -1) return this->arr[k].height;

        return this->arr[k].height = 1 + max(height(this->arr[k].left), height(this->arr[k].right));
    }

    int balance(int k){
        return height(this->arr[k].right) - height(this->arr[k].left);
    }
};


int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    ifstream fin(FILENAME + ".in");
    ofstream fout(FILENAME + ".out");

    int n;
    fin >> n;
    auto *tree = new AVLTree(n);

    int val, l, r;
    int c = 0;
    while (fin >> val >> l >> r) {
        tree->arr[c] = Node(l - 1, r - 1);
        c++;
    }

    for (int i = 0; i < n; i++){
        fout << tree->balance(i) << '\n';
    }

    return 0;
}