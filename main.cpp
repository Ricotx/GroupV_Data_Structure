// main.cpp — Job Description Linked List Implementation Driver
#include "linkedlist_datastorage.hpp"
#include "array_datastorage.hpp"
#include <iostream>

using namespace std;

int main() {
    cout << "=== Job Description & Resume Linked List Data Structures Project ===" << endl;
    cout << "Phase 1 & 2: Core Structures and Data Loading" << endl;
    cout << "================================================" << endl;
    
    // Create separate data storage for linked lists and arrays
    LinkedListDataStorage linkedListStorage;
    ArrayDataStorage arrayStorage;
    
    // Load linked list data
    if (!linkedListStorage.loadLinkedListData()) {
        cerr << "Failed to load linked list data!" << endl;
        return 1;
    }
    
    // Load array data
    if (!arrayStorage.loadArrayData()) {
        cerr << "Failed to load array data!" << endl;
        return 1;
    }
    
    // Display sample data from both storage types
    linkedListStorage.displaySampleLinkedListData(3, 3);
    arrayStorage.displaySampleArrayData(3, 3);
    
    // Display statistics from both storage types
    linkedListStorage.displayLinkedListStats();
    arrayStorage.displayArrayStats();
    
    // Test operations on both storage types
    linkedListStorage.testLinkedListOperations();
    arrayStorage.testArrayOperations();
    
    cout << "\n=== Phase 1 & 2 Complete ===" << endl;
    cout << "Ready for Phase 3: Linked List Operations (Sorting, Searching, Matching)" << endl;
    
    return 0;
}