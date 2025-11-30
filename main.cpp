#include <iostream>
#include <string>
#include "day0.h"
// #include "day1.h" // Tutaj będziesz dodawał kolejne dni

using namespace std;

int main(int argc, char* argv[]) {
    // Jeśli podasz argument (np. ./aoc25 1), uruchomi dzień 1.
    // Jeśli nie, domyślnie uruchomi dzień 0.
    int day = 0;
    if (argc > 1) {
        day = stoi(argv[1]);
    }

    cout << "--- Running Day " << day << " ---" << endl;

    switch (day) {
        case 0: {
            day0 solver;
            solver.run("input0a.txt", "input0b.txt");
            break;
        }
        /* 
        case 1: {
            day1 solver;
            solver.run("input1a.txt", "input1b.txt");
            break;
        }
        */
        default:
            cerr << "Day " << day << " is not implemented yet!" << endl;
            return 1;
    }

    return 0;
}
