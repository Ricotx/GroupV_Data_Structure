// main.cpp — Job Description Linked List Implementation Driver
#include "linkedlist_datastorage.hpp"
#include "array_datastorage.hpp"
#include <iostream>

using namespace std;

// Include the array menu implementation directly to avoid separate linkage
#include "test_array.cpp"
#include "test_linkedlist.cpp"

void displayTopLevelMenu(){
    cout << "\n=== Job Matching System - Main Menu ===" << endl;
    cout << "Select a data structure to test:" << endl;
    cout << "1. Linked List Implementation" << endl;
    cout << "2. Array Implementation" << endl;
    cout << "0. Exit Program" << endl;
    cout << "=========================================" << endl;
    cout << "Enter your choice: ";
}

int main() {
    cout << "=== Job Description & Resume Data Structures Project ===" << endl;
    cout << "================================================" << endl;
    int choice;
    do {
        displayTopLevelMenu();
        if (!(cin >> choice)) {
            cout << "\n[INVALID INPUT] Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1; // Set to invalid choice to loop again
            continue;
        }

        switch (choice) {
            case 1:
                cout << "\n=== Launching Linked List Team Menu ===" << endl;
                runLinkedListMenu();
                break;
            case 2:
                cout << "\n=== Launching Array Team Menu ===" << endl;
                runArrayMenu();
                break;
            case 0:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
    
}