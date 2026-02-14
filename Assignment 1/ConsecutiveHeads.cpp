/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <cstdlib>
#include "simpio.h"
#include "random.h"
//#include "console.h"
using namespace std;

/* Constants */
const int DEMAND = 3;

/* Function Prototypes */
int simulate();

int main() {
    int n = simulate();
    cout << "It took " << n << " flips to get " << DEMAND << " consecutive heads.";
    return 0;
}

int simulate() {
    //true - heads, false - tails
    int counter = 0;
    int consecutiveHeads = 0;
    while (true) {
        bool coin = randomInteger(0,1);
        counter++;
        if (coin) {
            cout << "Heads\n";
            consecutiveHeads++;
            if (consecutiveHeads == DEMAND) break;
        }
        else {
            cout << "Tails\n";
            consecutiveHeads = 0;
        }
    }
    return counter;
}