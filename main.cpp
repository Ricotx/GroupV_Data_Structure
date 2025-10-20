// main.cpp — Job Description Linked List Implementation Driver
#include "linkedlist_datastorage.hpp"
#include "array_datastorage.hpp"
#include <iostream>

using namespace std;

// Include the array menu implementation directly to avoid separate linkage
#include "test_array.cpp"

int main() {
    cout << "=== Job Description & Resume Data Structures Project ===" << endl;
    cout << "Phase 1 & 2: Core Structures and Data Loading" << endl;
    cout << "================================================" << endl;
    
    // Create separate data storage for linked lists and arrays
    LinkedListDataStorage linkedListStorage;
    ArrayDataStorage arrayStorage;
    
    // Load linked list data (uses default CSV paths)
    if (!linkedListStorage.loadLinkedListData()) {
        cerr << "Failed to load linked list data!" << endl;
        // continue to array path even if linked list fails
    } else {
        // Display sample linked list data
        linkedListStorage.displaySampleData(3, 3);
        // Test some linked list operations
        linkedListStorage.testLinkedListOperations();
    }
    
    // Load array data with explicit CSV paths
    if (!arrayStorage.loadArrayData("csv/job_description.csv", "csv/resume.csv")) {
        cerr << "Failed to load array data!" << endl;
    } else {
        // Display sample array data
        arrayStorage.displaySampleData(3);
    }
    
    cout << "\n=== Launching Array Team Menu ===" << endl;
    runArrayMenu();
    
    cout << "\n=== Program Complete ===" << endl;
    return 0;
}