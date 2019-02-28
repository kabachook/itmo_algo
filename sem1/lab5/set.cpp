#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <math.h>

using namespace std;

const size_t SET_SIZE = 1000003;

//const double PHI = (1+sqrt(5))/2;

template<class T>
struct MySet {
    int_fast64_t* arr;
    bool* deleted;

    MySet(){
        this->arr = new int_fast64_t[SET_SIZE];
        this->deleted = new  bool[SET_SIZE]();

        for (auto i = 0; i < SET_SIZE; i++){
            this->arr[i] = INT_FAST64_MIN;
        }

    };

    size_t hash(T el){
//        return ((el * 11400714819323198485llu) >> 61 )% SET_SIZE;
//        size_t h = 0;
//        auto key = 2, i = 0;
//        while (el) {
//            h += (el % 10) * (size_t) pow(key, i);
//            el /= 10;
//            i++;
//        }
//        return h % SET_SIZE;
//        return SET_SIZE * (el*PHI % 1);
//        return el % SET_SIZE;
        el = ((el >> 16) ^ el) * 0x45d9f3b;
        el = ((el >> 16) ^ el) * 0x45d9f3b;
        el = (el >> 16) ^ el;
        return el % SET_SIZE;
    }


    void insert(T element){
        auto h = hash(element);
        while(this->arr[h] != INT_FAST64_MIN && this->arr[h] != element){
            h = (h+1) % SET_SIZE;
        }
        this->arr[h] = element;
        this->deleted[h] = false;
    }

    bool exists(T element){
        auto h = hash(element);
        int i = 0;
        while (this->arr[h] != element) {
            if (this->arr[h] == INT_FAST64_MIN || i >= SET_SIZE) return false;
            h = (h+1) % SET_SIZE;
            i++;
        }
        return !this->deleted[h];
    }

    void remove(T element){
        auto h = hash(element);
        while(this->arr[h] != INT_FAST64_MIN){
            if(this->arr[h] == element){
                deleted[h] = true;
                return;
            }
            h = (h+1) % SET_SIZE;
        }

    }
};

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    ifstream fin("set.in");
    ofstream fout("set.out");

    auto set = MySet<int64_t>();

    while(!fin.eof()){
        string s;
        int x;
        fin >> s >> x;
        if (s[0] == 'i'){
            set.insert(x);
        }
        if (s[0] == 'd'){
            set.remove(x);
        }
        if (s[0] == 'e'){
            auto res = set.exists(x);
            if (res){
                fout << "true\n";
            }
            else{
                fout << "false\n";
            }
        }
    }


    return 0;
}