#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {
    cout << "Hello World!" << endl;
    ifstream file("long3.txt");

    int N = 12;

    string line;

    auto const best = new long[N];

    long sum = 0;

    while (file >> line) {
        cout << line << endl;

        for (int i=0; i<N; i++) best[i] = 0;

        for (int ci=0; ci<line.size(); ci++) {
            char c = line[ci];
            int val = c - '0';

            for (int i=min(ci, N-1); i>=1; i--) {
                long b = best[i];
                long first = (b/10)*10 + val;
                long prev = (best[i-1])*10 +val;
                long limit = pow(10, N);
                if (first >= limit) first = first % limit;
                if (prev >= limit) prev = prev % limit;

                long new_best = max(b, (max(first, prev)));
                if (new_best > best[i]) {
                    // cout << "i=" << i << " b=" << b << " first=" << first << " prev=" << prev << " new_best=" << new_best << endl;
                    best[i] = new_best;
                }

            }
            best[0] = max(best[0], (long)val);


        }

        // cout << "BEST : " << best[N-1] << endl;
        sum += best[N-1];
        cout << "SUM : " << sum << endl;


        // break; // after first
    }
    free(best);
    return 0;
}