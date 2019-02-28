#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <string>
#include <utility>

using namespace std;

const size_t SET_SIZE = 7;
const size_t MAP_SIZE = 99173;


struct MySet {
    vector<string> arr;
    vector<bool> deleted;

    const string null_el = "";
    size_t currentSize = 0;
    size_t maxSize = SET_SIZE;

    MySet(){
        this->arr = vector<string>(SET_SIZE, "");
        this->deleted = vector<bool>(SET_SIZE, false);
        currentSize = 0;
        maxSize = SET_SIZE;
    };

    size_t hash(size_t el) {
        el = ((el >> 16) ^ el) * 0x45d9f3b;
        el = ((el >> 16) ^ el) * 0x45d9f3b;
        el = (el >> 16) ^ el;
        return el % this->maxSize;
    }

    size_t hash(string const &s) {
        const size_t p = 2;
        size_t result = 0, h_pow = 1;
        for (auto c: s) {
            result = (result + (c - 'a' + 1) * h_pow) % this->maxSize;
            h_pow = (h_pow * p) % this->maxSize;
        }
        return result;
    }


    void rehash(){
        this->maxSize*=2;
        vector<string> newArr(this->maxSize, "");
        this->deleted.clear();
        this->deleted.resize(this->maxSize, false);
        for (auto x: this->arr) {
            insert(x, newArr);
        }
        this->arr.clear();
        this->arr = newArr;
    }

    void insert(const string &element, vector<string> &arr){
        auto h = hash(hash(element));
        while(arr[h] != null_el && arr[h] != element){
            h = (h+1) % this->maxSize;
        }

        arr[h] = element;
        this->deleted[h] = false;

    }

    void insert(const string &element){
//        if (this->currentSize && this->currentSize / this->maxSize > 0.8) rehash();

        auto h = hash(hash(element));
        while(this->arr[h] != null_el && this->arr[h] != element){
            h = (h+1) % this->maxSize;
        }

        if (element != this->arr[h]) this->currentSize++;

        this->arr[h] = element;
        this->deleted[h] = false;

    }

    void remove(const string &element){
        auto h = hash(hash(element));
        while(this->arr[h] != null_el){
            if(this->arr[h] == element){
                deleted[h] = true;
                currentSize--;
//                this->arr[h] = null_el;
                return;
            }
            h = (h+1) % this->maxSize;
        }

    }

    string get_all(){
        size_t count = 0;
        string result = "";
        for (size_t i = 0; i < this->maxSize; i++){
            if (this->arr[i].empty()) continue;
            if (!this->deleted[i]) {
                count++;
                result += " " + this->arr[i];
            }
        }
        return to_string(count)+result;
    }

    void clear(){
        this->arr.clear();
        this->deleted.clear();
        this->arr = vector<string>(this->maxSize, "");
        this->deleted = vector<bool>(this->maxSize, false);
    }

    void copy(const MySet &rhs){
        this->arr = rhs.arr;
        this->deleted = rhs.deleted;
    }
};

const auto null_node = make_pair(string(""), MySet());

struct MultiMap {
    vector<pair<string, MySet>> table;
    vector<bool> deleted;

    size_t currentSize = 0;
    size_t maxSize = MAP_SIZE;

    MultiMap(){
        table = vector<pair<string, MySet >>(MAP_SIZE, {"", MySet()});
        deleted = vector<bool>(MAP_SIZE, false);
        currentSize = 0;
        maxSize = MAP_SIZE;
    }

    void rehash(){
        this->maxSize*=2;
        vector<pair<string, MySet*>> newArr(this->maxSize, {"", nullptr});
        this->deleted.clear();
        this->deleted.resize(this->maxSize, false);
        for (auto x: this->table) {
//            insert(x, newArr);
            insert(make_pair(x.first, &x.second), newArr);
        }
        this->table.clear();
//        this->table = newArr;
        this->table.resize(this->maxSize);
        for (size_t i = 0; i< this->maxSize; i++){
            if (newArr[i].first.empty()) continue;
            this->table[i].first = newArr[i].first;
            this->table[i].second.copy(*newArr[i].second);
//            newArr[i].second.clear();
        }
    }

    void insert(pair<string, MySet*> element, vector<pair<string, MySet*>> &arr){
        auto h = hash(hash(element.first));
        while(arr[h].second!= nullptr && arr[h].first != element.first){
            h = (h+1) % this->maxSize;
        }

        arr[h].first = element.first;
        arr[h].second = element.second;
        this->deleted[h] = false;

    }

    void put(string key, string value) {
//        if (this->currentSize && this->currentSize / this->maxSize > 0.75) rehash();

        auto h = hash(hash(key));
        while (!this->table[h].first.empty() && this->table[h].first != key) {
            h = (h + 1) % this->maxSize;
        }

        if (this->table[h].first != key) this->currentSize++;

        this->table[h].first = key;
        this->table[h].second.insert(value);


        this->deleted[h] = false;
    }

    string get(string key) {
        auto h = hash(hash(key));
        int i = 0;
        while (this->table[h].first != key) {
            if (this->table[h].first.empty() || i >= this->maxSize) return "0";
            h = (h + 1) % this->maxSize;
            i++;
        }

        if (this->deleted[h]) return "0";

        return this->table[h].second.get_all();
    }

    void delete_value(string key, string value) {
        auto h = hash(hash(key));
        size_t count = 0;
        while (count != this->maxSize && !this->table[h].first.empty()) {
            if (this->table[h].first == key) {
                this->table[h].second.remove(value);
                this->currentSize--;
                return;
            }
            h = (h + 1) % this->maxSize;
            count++;
        }
    }

    void delete_key(string key){
        auto h = hash(hash(key));
        size_t count = 0;
        while (count != this->maxSize && !this->table[h].first.empty()) {
            if (this->table[h].first == key) {
                this->table[h].first = "";
                this->table[h].second.clear();
                this->deleted[h] = true;
                return;
            }
            h = (h + 1) % this->maxSize;
            count++;
        }
    }

    size_t hash(size_t el) {
        el = ((el >> 16) ^ el) * 0x45d9f3b;
        el = ((el >> 16) ^ el) * 0x45d9f3b;
        el = (el >> 16) ^ el;
        return el % this->maxSize;
    }

    size_t hash(string const &s) {
        const size_t p = 2;
        size_t result = 0, h_pow = 1;
        for (auto c: s) {
            result = (result + (c - 'a' + 1) * h_pow) % this->maxSize;
            h_pow = (h_pow * p) % this->maxSize;
        }
        return result % this->maxSize;
    }

};

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    ifstream fin("multimap.in");
    ofstream fout("multimap.out");

    MultiMap map;

    string command, key;

    while (fin >> command >> key) {
//        cerr<<command<<" "<<key<<endl;
        if (command[0] == 'p') {
            string value;
            fin >> value;
            map.put(key, value);
        } else if (command[0] == 'd' && command.size() == 6) {
            string value;
            fin >> value;
            map.delete_value(key, value);
        } else if (command[0] == 'g') {
            string res = map.get(key);
            fout << res << '\n';
        } else if (command[0] == 'd') {
            map.delete_key(key);
        }
    }

    return 0;
}