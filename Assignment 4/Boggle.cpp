/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <set>
#include <vector>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
//#include "gboggle.cpp"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

string CUBES[16];
char board[4][4];
Lexicon lexicon;
set<string> humanGuessedWords;
bool visited[4][4];
vector<pair<int, int>> choices;
set<string> computerGuessedWords;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function prototypes */

void welcome();
void giveInstructions();
void setUpBoard(string cubes[]);
void askQuestion();
void userMove();
bool isValid(string word);
void makeLexicon();
bool isConstructable(string word, int row, int col);
void fillVisited();
void fillChoices();
void computerMove();
void findAllWordsWithStart(string &start, int row, int col);
void unhighlightAll();

/* Main program */

int main() {
    string response;
    makeLexicon();
    fillChoices();
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);
    welcome();
    giveInstructions();
    while (true) {
        askQuestion();
        setUpBoard(CUBES);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        userMove();
        computerMove();
        cin >> response;
        if (response != "yes") break;
        else {
            humanGuessedWords.clear();
            computerGuessedWords.clear();
        }
    }
    cout << "THANKS FOR PLAYING!" << endl;
    return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

void askQuestion() {
    cout << "Do you want to play with your cubes?";
    cout << " yes to continue, no otherwise.";
    cout << endl;
    string response;
    cin >> response;
    if (toUpperCase(response) == "YES") {
        string cube;
        cin >> cube;
        cube = toUpperCase(cube);
        for (int i = 0; i < 16; i++) {
            string curr;
            for (int cnt = 0; cnt < 6; cnt++) curr += cube[i];
            CUBES[i] = curr;
        }
    }
    else {
        for (int i = 0; i < 16; i++) {
            CUBES[i] = STANDARD_CUBES[i];
        }
    }
}

void setUpBoard(string cubes[]) {
    drawBoard(4, 4);
    int row = 0;
    int col = 0;
    for (int i = 0; i < 16; i++) {
        int x = randomInteger(0, 5);
        labelCube(row, col, cubes[i][x]);
        board[row][col] = cubes[i][x];
        if (col < 3) col++;
        else {
            row++;
            col = 0;
        }
    }
}

void userMove() {
    cout << "Input the words you can find:" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string word;
    while (true) {
        getline(cin, word);
        unhighlightAll();
        if (word.size() == 0) break;
        if (isValid(toUpperCase(word))) {
            if (humanGuessedWords.find(toUpperCase(word)) == humanGuessedWords.end()) {
                humanGuessedWords.insert(toUpperCase(word));
                recordWordForPlayer(word, HUMAN);
                for (string s : humanGuessedWords) {
                    cout << s << endl;
                }
            }
            else {
                cout << "You have already guessed that word." << endl;
            }
        }
        fillVisited();
    }
}

bool isValid(string word) {
    if (word.size() < 4) {
        cout << "Word is too small." << endl;
        return false;
    }
    if (!lexicon.contains(word)) {
        cout << "That is not a word at all." << endl;
        return false;
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (word[0] == board[i][j]) {
                cout << i << " " << j << " " << board[i][j] << endl;
                visited[i][j] = true;
                highlightCube(i, j, true);
                if (isConstructable(word, i, j)) {
                    return true;
                }
                highlightCube(i, j, false);
            }
            else {
                fillVisited();
            }
        }
    }
    cout << "You can not make that word on the board!" << endl;
    return false;
}

void computerMove() {
    cout << "Okay, my turn now!" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            fillVisited();
            string start;
            start += board[i][j];
            visited[i][j] = true;
            highlightCube(i, j, true);
            findAllWordsWithStart(start, i, j);
            unhighlightAll();
        }
    }
    for (string word : computerGuessedWords) {
        if (humanGuessedWords.find(word) == humanGuessedWords.end()) {
            cout << "WOW THIS WORD IS NOT FOUND BY HUMAN " << word << endl;
            recordWordForPlayer(word, COMPUTER);
        }
        else cout << word << " SEEMS YOU'VE FOUND THAT!" << endl;
    }
    cout << "GGWP!" << endl;
    cout << "Do you want to play again? Input yes to continue" << endl;
}

void makeLexicon() {
    lexicon.addWordsFromFile("EnglishWords.dat");
}

bool isConstructable(string word, int row, int col) {
    if (word[0] != board[row][col]) return false;
    if (word.size() == 1 && word[0] == board[row][col]) { highlightCube(row, col, true);  return true; }
    int nextRow, nextCol;
    for (int i = 0; i < choices.size(); i++) {
        nextRow = row + choices[i].first;
        nextCol = col + choices[i].second;
        if (nextRow < 4 && nextRow >= 0 && nextCol < 4 && nextCol >= 0) {
            if (!visited[nextRow][nextCol]) {
                visited[nextRow][nextCol] = true;
                highlightCube(nextRow, nextCol, true);
                if (isConstructable(word.substr(1), nextRow, nextCol)) return true;
                visited[nextRow][nextCol] = false;
                highlightCube(nextRow, nextCol, false);
            }
        }
    }
    return false;
}

void fillVisited() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            visited[i][j] = false;
        }
    }
}

void fillChoices() {
    choices.push_back(make_pair(-1, 0));
    choices.push_back(make_pair(-1, 1));
    choices.push_back(make_pair(0, 1));
    choices.push_back(make_pair(1, 1));
    choices.push_back(make_pair(1, 0));
    choices.push_back(make_pair(1, -1));
    choices.push_back(make_pair(0, -1));
    choices.push_back(make_pair(-1, -1));
}

void findAllWordsWithStart(string& curr, int row, int col) {
    if (!lexicon.containsPrefix(curr)) return;
    if (lexicon.contains(curr) && curr.length() >= 4) {
        computerGuessedWords.insert(toUpperCase(curr));
    }
    for (int i = 0; i < choices.size(); i++) {
        row += choices[i].first;
        col += choices[i].second;
        if (row < 4 && row >= 0 && col < 4 && col >= 0) {
            if (!visited[row][col]) {
                visited[row][col] = true;
                highlightCube(row, col, true);
                curr += board[row][col];
                findAllWordsWithStart(curr, row, col);
                curr.pop_back();
                visited[row][col] = false;
                highlightCube(row, col, false);
            }
        }
        row -= choices[i].first;
        col -= choices[i].second;
    }
}

void unhighlightAll() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            highlightCube(i, j, false);
        }
    }
}