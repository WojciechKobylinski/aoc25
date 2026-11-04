#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <sstream>
#include <map>

using namespace std;

struct combination {
    vector<int> counts;
    int pressed;
};

bool notbigger(vector<int> v, vector<int> goal) {
    for (int i=0; i<v.size(); i++) {
        if (v[i] > goal[i]) return false;
    }
    return true;
}

bool alleven(vector<int> v) {
    for (auto x: v) {
        if (x%2==1) return false;
    }
    return true;
}

bool iszero(vector<int> v) {
    for (auto x: v) if (x != 0) return false;
    return true;
}

bool equalsmod2(vector<int> v, vector<int> w) {
    for (int i=0; i<v.size(); i++) {
        if (v[i]%2 != w[i]%2) return false;
    }
    return true;
}

pair<long, bool> solve(
map<vector<int>, pair<long, bool>> memo, vector<int> goal, vector<combination> combinations, int N) {
    if (memo.count(goal)) return memo[goal];

    if (iszero(goal)) return {0, true};
    long res = INT_MAX;
    bool found = false;
    // cout << "#";
    for (auto c: combinations) {
        // cout << ".";
        if (!notbigger(c.counts , goal)) continue;
        // cout << "!";
        if (!equalsmod2(c.counts, goal)) continue;
        // cout << ":";
        auto nextGoal = vector<int>(N, 0);
        for (int i=0; i<N; i++) nextGoal[i] = (goal[i] - c.counts[i])/2;
        auto subresult=solve(memo, nextGoal, combinations, N);
        if (!subresult.second) continue;
        // cout << "SUB " << subresult.first << endl;
        auto x = 2*subresult.first + c.pressed;
        if (res > x) {
            res = x;
            found = true;
        }
    }
    if (res < INT_MAX) return {res, true};
    return memo[goal] = {res, found};
}

vector<combination> allcombinations(vector<vector<int>> buttons, int N) {
    vector<combination> res;

    // Zacznij od stanu "zero" - nic nie wciśnięte
    combination start;
    start.counts = vector<int>(N, 0);
    start.pressed = 0;
    res.push_back(start);

    // Dla każdego przycisku b
    for (const auto& b : buttons) {
        int current_size = res.size();
        // Przejdź przez wszystkie kombinacje wygenerowane do tej pory
        for (int i = 0; i < current_size; i++) {
            // Skopiuj istniejącą kombinację
            combination next = res[i];

            // "Wciśnij" w niej aktualny przycisk b
            next.pressed++;
            for (int lightIndex : b) {
                next.counts[lightIndex]++;
            }

            // Dodaj nowy wariant do kolekcji
            res.push_back(next);
        }
    }

    return res;
}

int main(int argc, char ** argv) {
    ifstream f("long10.txt");

    string line;
    long SUM=0;
    int which =1;
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
        // cout << "REST:" <<rest << endl;


        stringstream ss(rest);
        string token;
        while (std::getline(ss, token, ',')) {
            if (!token.empty()) biggoal.push_back(std::stoi(token));
        }

        auto combinations = allcombinations(buttons, N);
        map<vector<int>, pair<long, bool>> memo;
        pair<long, bool> x = solve(memo, biggoal, combinations, N);
        SUM += x.first;
        cout << which++ << endl;
        if (x.first == 0)    cout << x.first << endl;

    }
    cout <<  "SUM "<< SUM << endl;
}