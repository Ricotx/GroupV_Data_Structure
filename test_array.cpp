// test_array.cpp — Array Team Test Driver
#include "array_datastorage.hpp"
#include <iostream>
#include <chrono>

using namespace std;

void displayMenu() {
    cout << "\n=== ARRAY TEAM TEST MENU ===" << endl;
    cout << "1. Load Data" << endl;
    cout << "2. Display Sample Data" << endl;
    cout << "3. Test Array Operations" << endl;
    cout << "4. Test Bubble Sort Algorithms" << endl;
    cout << "5. Test Linear Search Algorithms" << endl;
    cout << "6. Test Binary Search Algorithms" << endl;
    cout << "7. Test Weighted Scoring Matching" << endl;
    cout << "8. Performance Testing" << endl;
    cout << "0. Exit" << endl;
    cout << "=============================" << endl;
    cout << "Enter your choice: ";
}

