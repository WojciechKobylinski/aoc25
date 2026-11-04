#include <iostream>
#include <fstream>
#include <map>
#include <unordered_set>

using namespace std;

struct point {
    long x, y;
};

bool inside(point a, point b, point c) {
    return (a.x < max(b.x, c.x)) && (a.x > min(b.x, c.x)) && (a.y < max(b.y, c.y)) && (a.y > min(b.y, c.y));
}

int main(int argc, char** argv) {
    ifstream f("long9.txt");

    vector<point> points;
    string line;
    int x, y;
    char comma;
    while (f >> x >> comma >> y) {
        point p = {x,y};
        points.push_back(p);
    }

    long maxDelta = 0;
    int cand = 0;
    for (int i=1; i<points.size(); i++) {
        long delta = max(
            points[i].x - points[i-1].x,
            points[i].y - points[i-1].y);
        if (maxDelta < delta) {
            maxDelta = delta;
            cand = i;
        }
    }
    cout << "CAND-1 " << cand-1 <<": "<< points[cand-1].x << ":" << points[cand-1].y << endl;
    cout << "CAND " << cand <<": "<< points[cand].x << ":" << points[cand].y << endl;
    cout << "CAND+1 " << cand+1 <<": "<< points[cand+1].x << ":" << points[cand+1].y << endl;
    cout << "CAND+2 " << cand+2 <<": "<< points[cand+2].x << ":" << points[cand+2].y << endl;

    vector<point> startPoints;
    // startPoints.push_back(points[cand-1]);
    startPoints.push_back(points[cand]);
    startPoints.push_back(points[cand+1]);

    long best = 0;

    for (int k=0; k<2; k++) {
        point p = startPoints[k];
        cout << "STARTING AT "<< p.x << "," << p.y << endl;
        for (int i=0; i<points.size(); i++) {
            bool anyinside = false;
            for (int j=0; j<points.size(); j++) {
                if (inside(points[j], points[i], p)) {
                    anyinside = true;
                    break;
                }
            }
            if (!anyinside) {
                if (k==0 && p.y < points[i].y
                    || k==1 && p.y > points[i].y) {
                    long cand = (abs(points[i].x - p.x)+1) * (abs(points[i].y - p.y)+1);
                    if (cand > best) {
                        best = cand;
                    }
                }

            }


        }
    }
    // sort(points.begin(), points.end(), [](point a, point b) { return a.x < b.x; });

    // for (auto p : points) {
    //
    // }
    //
    // long best = 0;
    // for (int i=0; i<points.size(); i++) {
    //     for (int j=i+1; j<points.size(); j++) {
    //         long cand = (points[i].x - points[j].x+1)
    //         * (points[i].y - points[j].y+1);
    //         best = max(best, cand);
    //     }
    // }

    cout << "BEST "<< best << endl;
    return 0;
}
