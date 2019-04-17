#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#ifdef _WIN32
#define NULL_DEVICE "NUL:"
#else
#define NULL_DEVICE "/dev/null"
#endif

const string FILENAME = "maxflow";


int main() {
    ifstream in(FILENAME + ".in");
    ofstream out(FILENAME + ".out");


    in.close();
    out.close();
    return 0;
}
