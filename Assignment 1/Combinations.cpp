/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "simpio.h"
using namespace std;
/* Function Prototypes */
int combinations(int n, int k);

int combinations(int n, int k) {
    if (n == k || k == 0) return 1; //the start or the end of the triangle
    return combinations(n - 1, k - 1) + combinations(n - 1, k); //recursive call
}

int main() {
    int n = getInteger("Enter a number: ");
    int k = getInteger("Enter a number: ");
    int answer = combinations(n, k);
    cout << answer;
    return 0;
}