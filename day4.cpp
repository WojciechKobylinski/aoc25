
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void add(vector<vector<int>>& neighbors, int i, int j, int LN, int CN) {
    if (i >= 0 && i < LN && j >= 0 && j < CN) neighbors[i][j]++;
}

int removePaperRolls(int LN, int CN, vector<vector<bool>>& paper) {
    vector<vector<int>> neighbors(LN, vector<int>(CN, 0));
    for (int i=0; i<LN; i++) {
        for (int j=0; j<CN; j++) {
            if (paper[i][j]) {
                add(neighbors, i-1, j-1, LN, CN);
                add(neighbors, i-1, j, LN, CN);
                add(neighbors, i-1, j+1,  LN, CN);
                add(neighbors, i, j+1,  LN, CN);
                add(neighbors, i, j-1,  LN, CN);
                add(neighbors, i+1, j-1,  LN, CN);
                add(neighbors, i+1, j,  LN, CN);
                add(neighbors, i+1, j+1,  LN, CN);
            }
        }
    }

    int sum = 0;
    for (int i=0; i<LN; i++) {
        for (int j=0; j<CN; j++) {

            if (paper[i][j]) {
                if (neighbors[i][j] < 4) {
                    // cout << "X";
                    sum ++;
                    paper[i][j] = false;
                } else {
                    // cout << "@";
                }
            } else {
                // cout << ".";
            }
        }
        // cout << endl;
    }
    // cout << endl;
    return sum;
}

int main(int argc, char** argv) {
    ifstream file("long4.txt");
    string line;
    vector<string> lines;
    while (file >> line) {
        lines.push_back(line);
    }
    int LN = lines.size();
    int CN = lines[0].size();
    vector<vector<bool>> paper(LN, vector<bool>(CN, false));
    for (int i=0; i<LN; i++) {
        for (int j=0; j<CN; j++) {
            paper[i][j] = lines[i][j] == '@';
        }
    }

    int removed = 0 ;
    int sum = 0;

    do {
        removed = removePaperRolls(LN, CN, paper);
        sum += removed;
    } while (removed > 0);
    cout << "SUM: " << sum << endl;

    return 0;

}