#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <sstream>

using namespace std;

int bfs(set<vector<int>> states, vector<int >goal, vector<vector<int>> buttons, int N, int lvl) {
    for (auto st: states) {
        if (st == goal) return lvl;
    }
    set<vector<int>> next;
    for (auto st: states) {
        for (auto b: buttons) {
            vector<int> n(N);
            for (int i=0; i<N; i++) {
                n[i] = st[i];
            }

            bool toohigh=false;
            for (auto i: b) {
                if (n[i] > goal[i]) toohigh=true;
                else n[i]++;
            }
            if (!toohigh) next.insert(n);
        }
    }
    cout << "LVL " << lvl << endl;
    return bfs(next, goal, buttons, N, lvl+1);
    // return 7;
}

int main(int argc, char ** argv) {
    ifstream f("long10.txt");


        int M = 0;
    string line;
    long SUM=0;
    while (getline(f, line)) {
        vector<bool> goal;
        int i=1;
        while (line[i] != ']') goal.push_back(line[i++] == '#');
        int N = goal.size();
        i++;
        vector<vector<int>> buttons;
        vector<int> cur;
        while (line[i] != '{') {
            switch (line[i]) {
                case '(': cur.clear(); break;
                case ')': buttons.push_back(cur); break;
                case ' ':
                case ',': break;
                default: cur.push_back(line[i]-'0');
            }
            ++i;
        }

        vector<int> biggoal;
        string rest = line.substr(i+1, line.size()-i-2);
        cout << "REST:" <<rest << endl;


        stringstream ss(rest);
        string token;
        while (std::getline(ss, token, ',')) {
            if (!token.empty()) biggoal.push_back(std::stoi(token));
        }


        vector<int> start(N);
        set<vector<int>> states;
        states.insert(start);

        for (auto st:biggoal) {
            M = max(M, st);
        }
        // SUM += bfs(states, biggoal, buttons, N, 0);
        // cout << endl;
        // cout << line << endl;
    }
    cout <<  "SUM "<< SUM << endl;
    cout << "M" <<M<< endl;
}