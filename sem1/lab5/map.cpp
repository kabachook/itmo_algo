#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <string>
#include <utility>

using namespace std;

const size_t SET_SIZE = 1000003;
const auto null_node = make_pair(string(""), string(""));


template<class T, class K>
struct MultiMap {
    vector<pair<T, K>> table;
    vector<bool> deleted;

    MultiMap() : table{vector<pair<T, K>>(SET_SIZE, {"", ""})}, deleted{vector<bool>(SET_SIZE, false)} {}

    void put(T key, K value) {
        auto h = hash(key);
        while (this->table[h] != null_node && this->table[h].first != key) {
            h = (h + 1) % SET_SIZE;
        }
        this->table[h] = {key, value};
        this->deleted[h] = false;
    }

    string get(T key) {
        auto h = hash(key);
        int i = 0;
        while (this->table[h].first != key) {
            if (this->table[h] == null_node || i >= SET_SIZE) return "";
            h = (h + 1) % SET_SIZE;
            i++;
        }
//        cerr << "GET " << key << " " << h << " " << this->table[h].second << " DEL " << this->deleted[h] << endl;
        return !this->deleted[h] ? this->table[h].second : "";
    }

    void delete_key(T key) {
        auto h = hash(key);
        size_t count = 0;
        while (count != SET_SIZE && this->table[h] != null_node) {
            if (this->table[h].first == key) {
                deleted[h] = true;
//                cerr << "DEL " << key << " " << h << " " << this->table[h].second << endl;
                return;
            }
            h = (h + 1) % SET_SIZE;
            count++;
        }
    }

    size_t hash(int el) {
        el = ((el >> 16) ^ el) * 0x45d9f3b;
        el = ((el >> 16) ^ el) * 0x45d9f3b;
        el = (el >> 16) ^ el;
        return el % SET_SIZE;
    }

    size_t hash(string const &s) {
        const size_t p = 2;
        size_t result = 0, h_pow = 1;
        for (auto c: s) {
            result = (result + (c - 'a' + 1) * h_pow) % SET_SIZE;
            h_pow = (h_pow * p) % SET_SIZE;
        }
        return result;
    }

};

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    ifstream fin("map.in");
    ofstream fout("map.out");

    MultiMap<string, string> map;

    string command, key;

    while (fin >> command >> key) {
        if (command[0] == 'p') {
            string value;
            fin >> value;
            map.put(key, value);
        } else if (command[0] == 'd') {
            map.delete_key(key);
        } else if (command[0] == 'g') {
            string res = map.get(key);
//            cerr << "GET "<< key << " RES " << res << endl;
            if (res == "") {
                fout << "none\n";
            } else {
                fout << res << '\n';
            }
        }
    }

    return 0;
}