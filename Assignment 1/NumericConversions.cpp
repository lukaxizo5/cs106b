/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include <simpio.h>
using namespace std;

/* Function Prototypes */
string intToString(int n);
int stringToInt(string str);

/* Main program */

int main() {
	string s;
	int n;
	cin >> s >> n;
	int intS = stringToInt(s);
	string stringN = intToString(n);
	cout << intS << "\n";
	cout << stringN << "\n";
    return 0;
}

string intToString(int n) {
	if (n < 10) return string(1, char(n + '0'));
	else return intToString(n / 10) + char(n % 10 + '0');
}

int stringToInt(string s) {
		if (s[0] == '-') return -1 * stringToInt(s.substr(1));
		else if (s.size() == 1) return (s[0] - '0');
		else return 10 * stringToInt(s.substr(0, s.size() - 1)) + (s[s.size() - 1] - '0');
}
