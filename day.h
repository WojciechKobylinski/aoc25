//
// Created by Wojciech Kobylinski on 30/11/2025.
//

#ifndef AOC25_DAY0_H
#define AOC25_DAY0_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <sstream>

using namespace std;

class day0 {
public:
    void run(const string& filename1, const string& filename2);

private:
    vector<string> readInput(const string& filename) {
        vector<string> lines;
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return lines;
        }
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }
        return lines;
    }

    static long long part1(const vector<string>& input);
    static long long part2(const vector<string>& input);
};


#endif //AOC25_DAY0_H