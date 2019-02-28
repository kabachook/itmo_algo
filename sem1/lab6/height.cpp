#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const string FILENAME = "height";

struct Node {
    int value;
    int left;
    int right;

    Node() : left{-1}, right{-1} {}

};

size_t height(const vector<Node> &tree, int n){
    if (n > tree.size() || n == -1 || tree.size() == 0) return 0;
    return 1 + max(height(tree, tree[n].left), height(tree, tree[n].right));
}

int main() {
//    cin.tie(NULL);
//    ios::sync_with_stdio(false);

    ifstream fin(FILENAME + ".in");
    ofstream fout(FILENAME + ".out");

    size_t size;
    fin >> size;

    int value, left, right;

    vector<Node> tree(size);

    for (size_t i = 0; i < size; i++) {
        fin >> value >> left >> right;
        tree[i].value = value;
        tree[i].left = left - 1;
        tree[i].right = right - 1;
    }

    fout << height(tree, 0);
}