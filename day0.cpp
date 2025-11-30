//
// Created by Wojciech Kobylinski on 30/11/2025.
//

#include "day0.h"

void day0::run(const string& filename1, const string& filename2) {
    cout << "Part 1: " << part1(readInput(filename1)) << endl;
    cout << "Part 2: " << part2(readInput(filename2)) << endl;
}

vector<string> day0::readInput(const string& filename) {
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

long long day0::part1(const vector<string>& input) {
    long long sum = 0;
    for (const auto& line : input) {
        stringstream ss(line);
        long long num;
        while (ss >> num) {
            sum += num;
        }
    }
    return sum;
}

long long day0::part2(const vector<string>& input) {
    long long product = 1;
    for (const auto& line : input) {
        stringstream ss(line);
        long long num;
        while (ss >> num) {
            product = (product * num) % 1007;
        }
    }
    return product;
}