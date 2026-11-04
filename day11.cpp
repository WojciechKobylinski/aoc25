#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <set>
#include <sstream>
#include <map>

using namespace std;

void reorder(map<string, vector<string>> graph, string at, stack<string>& stos, set<string>& visited) {
    // cout << "NOW AT "<<at << endl;
    for (auto neigh : graph[at]) {
        if (visited.find(neigh) == visited.end()) {
            visited.insert(neigh);
            reorder(graph, neigh, stos, visited);
        }
    }
    stos.push(at);
}

int main(int argc, char** argv) {
    ifstream f("short11b.txt");

    string line;
    int N=0;
    long SUM=0;
    map<string, vector<string>> graph;
    while (getline(f, line)) {
        stringstream ss(line);
        string from;
        ss >> from;
        from = from.substr(0,3);
        string to;
        vector<string> tos;
        while (ss >> to) tos.push_back(to);
        graph[from] = tos;
        N++;
    }

    stack<string> stos;
    set<string> visited;
    reorder(graph, "you", stos, visited);

    map<string, int> ways;
    string at = stos.top(); stos.pop();
    ways[at] = 1;
    for (auto n : graph[at]) {ways[n] += ways[at];}
    while (!stos.empty()) {
        at = stos.top(); stos.pop();
        for (auto n : graph[at]) {ways[n] += ways[at];}
    }

    cout << "N   " << N << endl;
    cout << "WAYS TO out " << ways["out"] << endl;

}