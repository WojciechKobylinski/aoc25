#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <sstream>
#include <map>
#include <unordered_set>

using namespace std;

void after(map<string, vector<string>> graph, string at, set<string>& visited) {
    visited.insert(at);
    for (auto neigh : graph[at]) {
        if (visited.find(neigh) == visited.end()) after(graph, neigh, visited);
    }
}


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

void dfs(map<string, vector<string>> graph, string at, string goal, int& count, set<string>& allowed) {
    if (goal == at) {
        count++;
        // cout << "c " << count << endl;
        return;
    }
    if (allowed.find(at) != allowed.end()) return;
    for (auto neigh : graph[at]) {
        dfs(graph, neigh, goal, count, allowed);
    }
}

int main(int argc, char** argv) {
    ifstream f("long11.txt");

    string line;
    int N=0;
    long SUM=0;
    map<string, vector<string>> graph;
    map<string, vector<string>> revgraph;
    while (getline(f, line)) {
        stringstream ss(line);
        string from;
        ss >> from;
        from = from.substr(0,3);
        string to;
        vector<string> tos;
        while (ss >> to) {
            tos.push_back(to);
            if (revgraph.find(to) == revgraph.end()) {
                revgraph[to] = {};
            }
            revgraph[to].push_back(from);
        }
        graph[from] = tos;
        N++;
    }


    set<string> reachdac;
    set<string> reachfft;
    set<string> beforedac;
    set<string> afterdac;
    set<string> beforefft;
    set<string> afterfft;

    after(revgraph, "dac", beforedac);
    after(graph, "dac", afterdac);
    after(revgraph, "fft", beforefft);
    after(graph, "fft", afterfft);

    //join sets before and after
    reachdac = beforedac;
    reachdac.insert(afterdac.begin(), afterdac.end());

    reachfft = beforefft;
    reachfft.insert(afterfft.begin(), afterfft.end());

    // todo moze after i before dac i przyciac graf potem. nie dawac rest tylko keep.
    // odc 1 before fft,
    // odc 2 przeciecie before dac i after fft
    // odc 3 after fft

    if (reachdac.find("fft") == reachdac.end()) cout << "fft before dac";
    if (reachfft.find("dac") == reachdac.end()) cout << "dac before fft";

    // return 0;

    //fft before dac !!!

    cout << "N   " << N << endl;
    cout << "dac   " << reachdac.size() << endl;
    cout << "fft   " << reachfft.size() << endl;
    // cout << "WAYS TO out " << count << endl;

    //

    set<string> both;
    set<string> rest;

    // intersection
    for (const auto& x : reachfft) {
        if (reachdac.count(x)) both.insert(x);
    }

    // symmetric difference ("the rest")
    for (const auto& x : reachfft) {
        if (!reachdac.count(x)) rest.insert(x);
    }
    for (const auto& x : reachdac) {
        if (!reachfft.count(x)) rest.insert(x);
    }

    // for (auto st : rest) cout << st << " "; cout << endl;

    cout << "keep   " << both.size() << endl;
    cout << "not keep   " << rest.size() << endl;


    // cnt1 6296
    cout << "-----------" << endl;
for (auto s : beforefft) cout << s << " "; cout << endl;

    cout << "-----------" << endl;

    // dfs(graph2, "svr", count, );
    int cnt1=0;
    dfs(graph, "svr", "fft", cnt1, beforefft);
    cout << "cnt1 " << cnt1 << endl;

    // intersection of afterfft and beforedac
    set<string> middle;
    for (const auto& x : both) {
        if (afterfft.count(x) && beforedac.count(x)) middle.insert(x);
    }

    int cnt2=0;
    dfs(graph, "fft", "dac", cnt2, middle);
    cout << "cnt2 " << cnt2 << endl;

    int cnt3=0;
    dfs(graph, "dac", "out", cnt3, afterdac);
    cout << "cnt3 " << cnt3 << endl;

    long result = cnt1 * cnt2 * cnt3;

    cout << "RESULT  " << result << endl;

    // TODO ALBO PRZYCIAC GRAF I TERAZ POLICZYC

    map<string, vector<string>> g2;
    for (auto e : graph) {
        if (!rest.count(e.first)) {
            g2[e.first] = {};
            for (auto n : e.second) {
                if (!rest.count(n)) g2[e.first].push_back(n);
            }
        };
    }

    stack<string> stos;
    set<string> visited;
    reorder(g2, "svr", stos, visited);

    map<string, long> ways;
    string at = stos.top(); stos.pop();
    ways[at] = 1;
    for (auto n : g2[at]) {ways[n] += ways[at];}
    while (!stos.empty()) {
        at = stos.top(); stos.pop();
        for (auto n : g2[at]) {ways[n] += ways[at];}
    }

    cout << "N   " << N << endl;
    cout << "WAYS TO out " << ways["out"] << endl;


}
