#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <string>
#include <utility>

using namespace std;

const size_t SET_SIZE = 1000003;


template<class K, class V>
struct MultiMap {
    struct OrderNode {
        K key;
        V value;
        OrderNode *prev;
        OrderNode *next;

        OrderNode(K key, V value) : key{key}, value{value}, prev{nullptr}, next{nullptr} {}

        bool operator==(const OrderNode &rhs) {
            return (this->key == rhs.key && this->value == rhs.value && this->prev == rhs.prev &&
                    this->next == rhs.next);
        };

        bool operator!=(const OrderNode &rhs) {
            return !(this->key == rhs.key && this->value == rhs.value && this->prev == rhs.prev &&
                     this->next == rhs.next);
        };
    };

    vector<OrderNode> table;
    vector<bool> deleted;

    const OrderNode null_node = OrderNode("", "");

    OrderNode *last;

    MultiMap() : table{vector<OrderNode>(SET_SIZE, OrderNode("", ""))}, deleted{vector<bool>(SET_SIZE, false)},
            last{nullptr} {}

    void put(K key, V value) {
        auto h = hash(hash(key));
        while (this->table[h] != null_node && this->table[h].key != key) {
            h = (h + 1) % SET_SIZE;
        }

//        cerr << key << " " << h << endl;

        if (this->table[h].key == key){
            this->table[h].value = value;
            return;
        }

        this->table[h].key = key;
        this->table[h].value = value;
        this->table[h].prev = last;
        this->table[h].next = nullptr;
        this->deleted[h] = false;

        if (last != nullptr) {
            last->next = &table[h];
        }

        last = &this->table[h];
    }

    pair<size_t, OrderNode *> search(K key) {
        auto h = hash(hash(key));
        int i = 0;
        while (this->table[h].key != key) {
            if (this->table[h] == null_node || i >= SET_SIZE) return make_pair(h, nullptr);
            h = (h + 1) % SET_SIZE;
            i++;
        }
        return make_pair(h, &table[h]);
    }

    string get(K key) {
        auto res = search(key);
        if (res.second == nullptr || this->deleted[res.first]) return "";

        return res.second->value;
    }

    void set_null(OrderNode* n){
        n->key = "";
        n->value = "";
        n->prev  = nullptr;
        n->next = nullptr;
    }

    void delete_key(K key) {
        auto res = search(key);

        OrderNode* n = res.second;

        if (this->deleted[res.first] || res.second == nullptr) return;

        if (n->prev == nullptr && n->next == nullptr){
            last = nullptr;
        }
        else if (n->prev == nullptr){
            n->next->prev = nullptr;
        }
        else if (n->next == nullptr){
            n->prev->next = nullptr;
            last = n->prev;
        }
        else {
            n->prev->next = n->next;
            n->next->prev = n->prev;

//            if (n->next == last){
//                last->prev = n->prev;
//            }
        }

        n->key = "";

        this->deleted[res.first] = true;
    }


    string prev(K key) {
        auto res = search(key);
        if (res.second == nullptr || this->deleted[res.first]) return "";

        return res.second->prev == nullptr ? "" : res.second->prev->value;

    }

    string next(K key) {
        auto res = search(key);
        if (res.second == nullptr || this->deleted[res.first]) return "";

        return res.second->next == nullptr ? "" : res.second->next->value;

    }

    size_t hash(size_t el) {
        el = ((el >> 16) ^ el) * 0x45d9f3b;
        el = ((el >> 16) ^ el) * 0x45d9f3b;
        el = (el >> 16) ^ el;
        return el % SET_SIZE;
//        return 1;
    }

    size_t hash(string const &s) {
        const size_t p = 53;
        size_t result = 0, h_pow = 1;
        for (auto c: s) {
            result = (result + (c - 'a' + 1) * h_pow) % SET_SIZE;
            h_pow = (h_pow * p) % SET_SIZE;
        }
        return result % SET_SIZE;
    }

};

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    ifstream fin("linkedmap.in");
    ofstream fout("linkedmap.out");

    MultiMap<string, string> map;

    string command, key;

    while (fin >> command >> key) {
        if (command[0] == 'p' && command[1] == 'u') {
            string value;
            fin >> value;
            map.put(key, value);
        } else if (command[0] == 'd') {
            map.delete_key(key);
        } else if (command[0] == 'g') {
            string res = map.get(key);
            if (res == "") {
                fout << "none\n";
            } else {
                fout << res << '\n';
            }
        } else if (command[0] == 'p') {
            string res = map.prev(key);
            if (res == "") {
                fout << "none\n";
            } else {
                fout << res << '\n';
            }
        } else if (command[0] == 'n') {
            string res = map.next(key);
            if (res == "") {
                fout << "none\n";
            } else {
                fout << res << '\n';
            }
        }
    }

    return 0;
}