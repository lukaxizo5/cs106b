/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <fstream>
#include <vector>
#include "tokenscanner.h"
#include <string>
#include "strlib.h"
using namespace std;

/* Constants */
const double C0 = -15.59;
const double C1 = 0.39;
const double C2 = 11.8;

/* Function Prototypes */
ifstream tryReadingFile();
vector<string> addTokens(TokenScanner tokenScanner, vector<string> tokens);
vector<int> getStats(TokenScanner tokenScanner, vector<string> tokens);
int countSyllables(string word);
bool isVowel(char c);
double getGrade(int words, int sentences, int syllables);
void updateTokenScanner(TokenScanner& tokenScanner);

int main() {
    ifstream file = tryReadingFile();
    TokenScanner tokenScanner(file);
    updateTokenScanner(tokenScanner);
    vector<string> tokens = addTokens(tokenScanner, tokens);
    vector<int> stats = getStats(tokenScanner, tokens);
    double grade = getGrade(stats[0], stats[1], stats[2]);
    cout << stats[0] << " " << stats[1] << " " << stats[2]<<"\n";
    cout << grade << "\n";
    return 0;
}

void updateTokenScanner(TokenScanner& tokenScanner) {
    tokenScanner.ignoreWhitespace();
    tokenScanner.addWordCharacters("-"); //making sure cream-brulee is counted as 1 word.
    tokenScanner.addWordCharacters("'"); //making sure isn't is counted as 1 word.
}

double getGrade(int words, int sentences, int syllables) {
    return C0 + C1 * double(words) / sentences + C2 * double(syllables) / words;
}

ifstream tryReadingFile() {
    ifstream file;
    string fileName;
    cout << "Which file stats do you want to see?\n";
    cin >> fileName;
    file.open(fileName);
    while (!file) {
        cout << "Pleas enter a valid file name\n";
        cin >> fileName;
        file.open(fileName);
    }
    return file;
}

vector<string> addTokens(TokenScanner tokenScanner, vector<string> tokens) {
    while (tokenScanner.hasMoreTokens()) {
        tokens.push_back(tokenScanner.nextToken());
    }
    return tokens;
}

vector<int> getStats(TokenScanner tokenScanner, vector<string> tokens) {
    int words = 0, sentences = 0, syllables = 0,op=0,sep=0;
    vector<int> v;
    for (int i = 0; i < tokens.size(); i++) {
        if (tokenScanner.getTokenType(tokens[i]) == WORD) {
            syllables += countSyllables(tokens[i]);
            words++;
        }
        if (tokens[i] == "." || tokens[i] == "?" || tokens[i] == "!") sentences++;
    }
    if (words == 0) words++;
    if (sentences == 0) sentences++;
    v.push_back(words);
    v.push_back(sentences);
    v.push_back(syllables);
    return v;
}

int countSyllables(string word) {
    int syllables = 0;
    bool previous = false;
    for (int i = 0; i < word.size(); i++) {
        if (i == word.size() - 1 && word[i] == 'e') continue;
        if (isVowel(word[i]) && !previous) {
            previous = true;
            syllables++;
        }
        else if (!isVowel(word[i])) previous = false;
    }
    return max(syllables, 1);
}

bool isVowel(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y');
}