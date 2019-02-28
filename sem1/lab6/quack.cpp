#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <fstream>

using namespace std;

const string FILENAME("quack");
const int64_t MOD = 65536;

deque<int> q;
vector<string> input;
map<string, int64_t> labels;
vector<int64_t> registers(27, 0);

int64_t get() {
    if (q.empty()) return 0;
    auto r = q.front() % MOD;
    q.pop_front();
    return r;
}

void put(int64_t x) {
    q.push_back(x % MOD);
}

void setReg(const string& reg, int64_t x) {
    registers[reg[0] - 'a'] = x;
}

int64_t getReg(const string& reg) {
    return registers[reg[0] - 'a'];
}

int64_t getReg(char reg) {
    return registers[reg - 'a'];
}


int main() {
    ifstream fin(FILENAME + ".in");
    ofstream fout(FILENAME + ".out");

    string line;
    int line_c = 0;
    while (fin >> line) {
        if (line.empty()) continue;

        input.push_back(line);
        if (line[0] == ':') {
            labels[line.substr(1)] = line_c;
        }

        line_c++;
    }

    fin.close();

    for (int64_t i = 0; i < input.size(); i++) {
        line = input[i];
        if (line == "+") {
            put(get() + get());
        } else if (line == "-") {
            auto a = get(), b = get();
            put((a + 65536 - b + 65536));
        } else if (line == "*") {
            auto a = get(), b = get();
//            cout << a << " " << b << " " << a*b <<  endl;
            put(b * a);
        } else if (line == "/") {
            auto a = get(), b = get();
            put(b == 0 ? 0 : a / b);
        } else if (line == "%"){
            auto a = get(), b = get();
            put(b == 0 ? 0 : a % b);
        }
        else if (line[0] == '>') {
            setReg(line.substr(1), get());
        } else if (line[0] == '<') {
            put(getReg(line.substr(1)));
        } else if (line[0] == 'P') {
            if (line.size() == 1) {
                fout << get() << '\n';
            } else {
                fout << getReg(line.substr(1)) << '\n';
            }
        } else if (line[0] == 'C') {
            auto x = line.size() == 1 ? get() : getReg(line.substr(1));
            char c = (char) (x % 256);
            fout << c;
        } else if (line[0] == 'J') {
            i = labels[line.substr(1)];
        } else if (line[0] == 'Z') {
            auto reg = getReg(line[1]);
            if (reg == 0) {
                i = labels[line.substr(2)];
            }
        } else if (line[0] == 'E') {
            auto r1 = getReg(line[1]);
            auto r2 = getReg(line[2]);
            if (r1 == r2) {
                i = labels[line.substr(3)];
            }
        } else if (line[0] == 'G') {
            auto r1 = getReg(line[1]);
            auto r2 = getReg(line[2]);
            if (r1 > r2) {
                i = labels[line.substr(3)];
            }
        } else if (line == "Q") {
            break;
        } else if (line[0] != ':') {
            put(stoi(line));
        }
    }

    fout.close();
    return 0;
}