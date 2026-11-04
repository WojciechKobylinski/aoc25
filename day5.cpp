#include <iostream>
#include <fstream>
#include <map>
#include <unordered_set>

using namespace std;

int main(int argc, char** argv) {
    ifstream f("long5.txt");

    vector<pair<long, long>> ranges;

    string s;
    while (f >> s) {
        auto dashPos = s.find('-');
        if (dashPos == string::npos) break;
        long L = stol(s.substr(0, dashPos));
        long R = stol(s.substr(dashPos+1));
        ranges.emplace_back(L, R);
    }

    map<long,long> m;
    unordered_set<long> ends;

    for (auto [L, R]: ranges) {
        m[L] += 1;
        m[R+1] -= 1;
        ends.insert(L);
        ends.insert(R);
    }



    map<long, int> running;
    int curr = 0;
    for (auto [place, delta] : m) {
        curr += delta;
        running[place] = curr;
    }
    //
    // for (auto [x, d] : running) {
    //     cout << "x = " << x << ", active intervals = " << d << "\n";
    // }

    long query;
    int count = 0;
    while (f >> query) {
        if (ends.find(query) != ends.end()) {
            count++;
            continue;
        }
        auto it = running.upper_bound(query);
        if (it == running.begin()) {
            continue;
        }
        // cout << "query" << query << " it " << it->first << endl;;
        it--;
        if (it->second > 0) {
            count++;
        }
    }

    cout << "COUNT " << count << endl;

    return 0;
}