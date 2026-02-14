/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities, Vector< Set<string> >& locations, int numHospitals, Vector< Set<string> >& result);

int main() {
    /* TESTCASE 1 */
    Set<string> cities;
    cities.insert("A");
    cities.insert("B");
    cities.insert("C");
    cities.insert("D");
    cities.insert("E");
    cities.insert("F");

    Set<string> l1; 
    l1.insert("A");
    l1.insert("B");
    l1.insert("C");

    Set<string> l2;
    l2.insert("A");
    l2.insert("C");
    l2.insert("D");

    Set<string> l3;
    l3.insert("B");
    l3.insert("F");

    Set<string> l4;
    l4.insert("C");
    l4.insert("E");
    l4.insert("F");
    Vector<Set<string>> locations;
    locations.push_back(l1);
    locations.push_back(l2);
    locations.push_back(l3);
    locations.push_back(l4);
    Vector<Set<string>> result;
    cout << canOfferUniversalCoverage(cities, locations, 2, result) << endl; //FALSE (0)
    if (result.isEmpty()) {
        cout << "Can't offer universal coverage, result empty!" << endl;
    }
    cout << canOfferUniversalCoverage(cities, locations, 3, result) << endl; //TRUE (1)
    for (int i = 0; i < result.size(); i++) {
        for (string city : result[i]) {
            cout << city << endl;
        }
        cout << "\n";
    }
    cout << endl;
    /* TESTCASE 2 */
    Set<string> citiess;
    citiess.insert("A");
    citiess.insert("B");
    citiess.insert("C");
    citiess.insert("D");

    Set<string> L1;
    L1.insert("A");
    L1.insert("C");
    L1.insert("D");

    Set<string> L2;
    L2.insert("B");
    L2.insert("C");
    L2.insert("D");

    Vector<Set<string>> locationss;
    locationss.push_back(L1);
    locationss.push_back(L2);
    Vector<Set<string>> resultt;
    cout << canOfferUniversalCoverage(citiess, locationss, 2, resultt) << endl; //FALSE (0)
    if (resultt.isEmpty()) {
        cout << "Can't offer universal coverage, result empty!" << endl;
    }
    //cout << canOfferUniversalCoverage(citiess, locationss, 3, resultt) << endl; //TRUE (1)
    for (int i = 0; i < resultt.size(); i++) {
        for (string city : resultt[i]) {
            cout << city << endl;
        }
        cout << "\n";
    }

    return 0;
}

bool canOfferUniversalCoverage(Set<string>& cities, Vector< Set<string> >& locations, int numHospitals, Vector< Set<string> >& result) {
    if ((numHospitals == 0 && cities.size() > 0) || (cities.size() > 0 && locations.size() == 0)) return false;
    else if (cities.size() == 0) return true;
    else {
        Set<string> choose = locations[0];
        locations.remove(0);
        for (string city : choose) {
            cities.remove(city);
        }
        result.push_back(choose);

        if (canOfferUniversalCoverage(cities, locations, numHospitals - 1, result)) return true;
        else {
            for (string city : choose) {
                cities.insert(city);
            }
            result.remove(result.size()-1);
            if (canOfferUniversalCoverage(cities, locations, numHospitals, result)) {
                locations.add(choose);
                return true;
            }
            else {
                locations.add(choose);
                return false;
            }
        }
    }
}
