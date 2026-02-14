/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include "random.h"
//#include "console.h"
using namespace std;

/* Constants */
int TOTAL = 2000;

/* Function Prototypes */
ifstream tryReadingFile();
int inputOrder();
string getSeed(map<string, vector<char>>& stats);
void getStats(ifstream& file, int order, map<string, vector<char>>& stats);
void generateMarkovText(map<string, vector<char>>& stats, int total);

int main() {
    ifstream file = tryReadingFile();
    int order = inputOrder();
    map<string, vector<char>> stats;
    getStats(file, order, stats);
    generateMarkovText(stats, TOTAL);
    return 0;
}

ifstream tryReadingFile() {
    ifstream file;
    string fileName;
    cout << "Which file stats do you want to see? ";
    cin >> fileName;
    file.open(fileName);
    while (!file) {
        cout << "Please enter a valid file name ";
        cin >> fileName;
        file.open(fileName);
    }
    return file;
}

int inputOrder() {
    int order;
    while (true) {
        cout << "Enter an integer from 1 to 10: ";
        cin >> order;
        if (order >= 1 && order <= 10) return order;
    }
    return order;
}

void getStats(ifstream& file, int order, map<string, vector<char>>& stats) {
    char c;
    string curr;
    for (int i = 0; i < order; i++) {
        file.get(c);
        curr += c;
    }
    while (file.get(c)) {
        stats[curr].push_back(c);
        curr = curr.substr(1) + c;
    }
}

void generateMarkovText(map<string, vector<char>>& stats, int total) {
    string mostCommon = getSeed(stats);
    for (int i = 0; i < total; i++) {
        if (stats[mostCommon].size() == 0) break;
        char c = stats[mostCommon][randomInteger(0, stats[mostCommon].size()-1)];
        cout << c;
        mostCommon = mostCommon.substr(1) + c;
    }
    cout << "\n";
}

string getSeed(map<string, vector<char>>& stats) {
    string seed = "";
    size_t count = 0;
    vector<string> v;
    for (auto it : stats) {
        if (it.second.size() > count) {
            count = it.second.size();
            seed = it.first;
        }
    }

    for (auto it : stats) {
        if (it.second.size() == count) v.push_back(it.first);
    }
    return v[randomInteger(0, v.size() - 1)];
}