#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <sstream>
#include <map>
#include <unordered_set>

using namespace std;

int main(int argc, char** argv) {
    ifstream f("long12.txt");

    string line;
    for (int i=0; i<30; i++) {
        getline(f, line);
    }

    int RESULT = 0;
    auto mul = new int[6]{7,7,6,7,7,5};

    for (int i=30; getline(f, line); i++) {
        cout << line << endl;
        stringstream ss(line);
        int X, Y;
        char delim;
        ss >> X >> delim >> Y >> delim;
        auto cnt = new int[6];
        for (int j=0; j<6; j++) {ss >> cnt[j];};
        int sumcnt = 0;
        for (int j=0; j<6; j++) {sumcnt += cnt[j]*mul[j];};
        int fullX = (X/3);
        int fullY = (Y/3);
        cout << "fullX" << (X/3) << endl;
        cout << "fullY" << (Y/3) << endl;
        cout << "sumcnt" << sumcnt << endl;
        if (X * Y >= sumcnt) RESULT++;
        free(cnt);
    }

    cout << RESULT << endl;

    return 0;
}