
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

class point {
public:
    long x, y, z;
    long dist(point p) const {
        return (x-p.x)*(x-p.x) + (y-p.y)*(y-p.y) + (z-p.z)*(z-p.z);
    }
};

class edge {
public:
    long dist, p1, p2;
};

struct EdgeCmp {
    bool operator()(const edge& a, const edge& b) const {
        return a.dist > b.dist;  // a ma „mniejszy priorytet”, jeśli ma mniejszy dystans
    }
};

int main(int argc, char** argv) {
    ifstream f("long8.txt");


    vector<point> points;
    string line;
    while (getline(f, line)) {
        point p;
        char comma;
        istringstream ss(line);
        ss >> p.x >> comma >> p.y >> comma >> p.z;
        points.push_back(p);
    }
    int N = points.size();
    cout << "N " << N << endl;

    priority_queue<edge, vector<edge>, EdgeCmp> edges;

    for (int i=0; i<N; i++) {
        for (int j=i+1; j<N; j++) {
            edge e;
            e.dist = points[i].dist(points[j]);
            e.p1 = i;
            e.p2 = j;
            edges.push(e);
        }
    }

    int parent[N];
    for (int i=0; i<N; i++) parent[i] = i;

    auto find_root = [&](int x, auto&& self) -> int {
        if (parent[x] == x) return x;
        return parent[x] = self(parent[x], self); // path compression
    };

    int numsets = N;

    int p1, p2;
    while (numsets > 1) {
        edge e = edges.top();
        edges.pop();
        p1 = e.p1; p2 = e.p2;

        int ra = find_root(e.p1, find_root);
        int rb = find_root(e.p2, find_root);
        if (ra != rb) {
            numsets--;
            parent[ra] = rb; // simple union, no rank
        }
    }
    long pl1 = points[p1].x;
    long pl2 = points[p2].x;
    long res = pl1 * pl2;
    cout << "THE RESULT " << res << endl;

    // for (int i=0; i<N; i++) find_root(i, find_root);

    // // for (int i=0; i<N; i++) {cout << parent[i] << " ";}
    // map<int, int> counts;
    // for (int i=0; i<N; i++) counts[parent[i]]++;
    //
    // priority_queue<int> pq;
    // for (auto [k, v] : counts) {
    //     pq.push(v);
    //     // cout << "K "<< k << " V " << v << endl;
    // }
    //
    // long result = 1;
    // for (int i=0; i<3; i++) {
    //     int x = pq.top(); pq.pop();
    //     // cout << "X "<< x << endl;
    //     result *= x;
    //
    // }
    //
    // cout << "RESULT " << result << endl;

    return 0;
}