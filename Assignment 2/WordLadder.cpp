/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */


#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <queue>
#include "lexicon.h"
//#include "console.h"
using namespace std;

/* Function Prototypes */
void findPath(string start, string end, Lexicon lexicon);
vector<string> bfs(string start, string end, Lexicon lexicon);
set<string> onlyChangeOneLetter(string word, Lexicon lexicon);

int main() {
    string start, end;
    while (true) {
        cout << "Enter start word (RETURN to quit) : ";
        getline(cin, start);
        if (start == "RETURN" || start.size() == 0) break;
        cout << "Enter destination word: ";
        getline(cin, end);
        Lexicon lexicon("EnglishWords.dat");
        findPath(start, end, lexicon);
        cout << "\n";
    }
    cout << "Thank you for using the application!";
    return 0;
}

set<string> onlyChangeOneLetter(string word, Lexicon lexicon) {
    set<string> oneLetterChanged;
    string duplicate = word;
    for (int i = 0; i < word.size(); i++) {
        for (int j = 0; j < 26; j++) {
            duplicate[i] = 'a' + j;
            if (lexicon.contains(duplicate) && duplicate != word) {
                oneLetterChanged.insert(duplicate);
            }
        }
        duplicate[i] = word[i];
    }
    return oneLetterChanged;
}

vector<string> bfs(string start, string end, Lexicon lexicon) {
    queue<vector<string>> paths;
    set<string> visited;
    vector<string> path;
    path.push_back(start);
    visited.insert(start);
    paths.push(path);
    while (!paths.empty()) {
        vector<string> curr = paths.front();
        paths.pop();
        if (curr.back() == end) return curr;
        set<string> oneLetterChanged = onlyChangeOneLetter(curr.back(),lexicon);
        for (string s : oneLetterChanged) {
            if (visited.find(s) == visited.end()) {
                vector<string> newPath = curr;
                newPath.push_back(s);
                visited.insert(s);
                paths.push(newPath);
            }
        }
    }
    vector<string> emptyVector;
    return emptyVector;
}

void findPath(string start, string end, Lexicon lexicon) {
    if (start.size() != end.size()) {
        cout << "No path from " << start << " to " << end;
        return;
    }
    if (!lexicon.contains(start)) {
        cout << "The word " << start << " is not present in the lexicon";
        return;
    }
    if (!lexicon.contains(end)) {
        cout << "The word " << end << " is not present in the lexicon";
        return;
    }
    vector<string> v = bfs(start, end, lexicon);
    if (v.empty()) {
        cout << "No path from " << start << " to " << end;
        return;
    }
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    return;
}
