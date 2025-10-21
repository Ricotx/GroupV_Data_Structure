// test_linkedlist.cpp — Linked List Team Test Driver
#include "linkedlist_datastorage.hpp"
#include "model.hpp"
#include <cctype>
#include <iostream>
#include <chrono>
#include <limits> // Required for numeric_limits

using namespace std;

// Forward declaration of the data storage object (it will be created in main)
// This is done so helper functions can use it easily if needed, but in this case, 
// we pass it by reference.

void displayMenu() {
    cout << "\n=== LINKED LIST TEAM TEST MENU ===" << endl;
    cout << "1. Load Data" << endl;
    cout << "2. Display Sample Data" << endl;
    cout << "3. Test Linked List Operations" << endl;
    cout << "4. Test Bubble Sort Algorithms" << endl;
    cout << "5. Test Linear Search Algorithms (Job Title)" << endl;
    cout << "6. Test Linear Search (Job Skill)" << endl; 
    cout << "7. Test Resume Linear Search (Resume Skill)" << endl; 
    cout << "8. Test Binary Search Algorithms" << endl;
    cout << "9. Test Weighted Scoring Matching" << endl;
    cout << "10. Performance Testing" << endl;
    cout << "0. Exit" << endl;
    cout << "=================================" << endl;
    cout << "Enter your choice: ";
}


void testLinearSearchJobs(LinkedListDataStorage& dataStorage) {
    if (!dataStorage.isDataLoaded()) {
        cout << "\n[ERROR] Data must be loaded first (Option 1).Please try loading the data first" << endl;
        return;
    }
    
    cout << "\n--- Test Linear Search by Job Title ---" << endl;
    cout << "Enter the Job Title to search for: ";
    
    // Use a standard string for reading input, then convert to CustomString
    string searchTitleStr;
    
    // Clear the input buffer before reading a line
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, searchTitleStr);
    
    // Assuming CustomString can be constructed from std::string or c-string
    CustomString searchTitle(searchTitleStr.c_str());

    cout << "Searching for: \"" << searchTitle << "\"..." << endl;

    // Start timer
    auto start = chrono::high_resolution_clock::now();
    
    // Perform the search
    CustomLinkedList<Job> searchJobsTitleList = dataStorage.linearSearchJobsByTitle(searchTitle);
    
    // Stop timer
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    
    

    if (searchJobsTitleList.getSize() > 0) {
        cout << "\n[SUCCESS] Found " << searchJobsTitleList.getSize() << " job(s) matching \"" << searchTitle << "\"." << endl;
    
        // Iterate through the results and display them in the requested format
        for (int i = 0; i < searchJobsTitleList.getSize(); ++i) {
            const Job& job = searchJobsTitleList[i]; // Access job data by index
            cout << "\nJob Match #" << i + 1 << ":" << endl;
            job.display(); 
        }
    
    } else {
        cout << "[NOT FOUND] No job with the title \"" << searchTitle << "\" was found." << endl;
    }
    cout << "\nSearch Time: " << duration.count() << " microseconds." << endl;
}

void testLinearSearchJobsBySkill(LinkedListDataStorage& dataStorage) {
    if (!dataStorage.isDataLoaded()) {
        cout << "\n[ERROR] Data must be loaded first (Option 1). Please try loading the data first." << endl;
        return;
    }
    
    cout << "\n--- Test Linear Search by Job Skill ---" << endl;
    cout << "Enter the Skill to search for (e.g., java, git, python): ";
    
    string searchSkillStr;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, searchSkillStr);
    
    // Convert the input to your CustomString and to lowercase for matching
    CustomString searchSkill(searchSkillStr.c_str());

    cout << "Searching for jobs with skill: \"" << searchSkill << "\"..." << endl;

    // Start timer
    auto start = chrono::high_resolution_clock::now();
    
    // Perform the search using the new function
    CustomLinkedList<Job> searchJobsSkillList = dataStorage.linearSearchJobsBySkills(searchSkill);
    
    // Stop timer
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    
    if (searchJobsSkillList.getSize() > 0) {
        cout << "\n[SUCCESS] Found " << searchJobsSkillList.getSize() << " job(s) with the skill \"" << searchSkill << "\"." << endl;
    
        // Iterate through the results and display them
        for (int i = 0; i < searchJobsSkillList.getSize(); ++i) {
            const Job& job = searchJobsSkillList[i];
            cout << "\nJob Match #" << i + 1 << ":" << endl;
            job.display(); 
        }
    
    } else {
        cout << "[NOT FOUND] No job with the skill \"" << searchSkill << "\" was found." << endl;
    }
    cout << "\nSearch Time: " << duration.count() << " microseconds." << endl;
}

void testLinearSearchResumesBySkill(LinkedListDataStorage& dataStorage) {
    if (!dataStorage.isDataLoaded()) {
        cout << "\n[ERROR] Data must be loaded first (Option 1). Please try loading the data first." << endl;
        return;
    }
    
    cout << "\n--- Test Linear Search by Resume Skill ---" << endl;
    cout << "Enter the Skill to search for (e.g., java, git, python): ";
    
    string searchSkillStr;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, searchSkillStr);
    
    // Convert the input to your CustomString and to lowercase for matching
    CustomString searchSkill(searchSkillStr.c_str());

    cout << "Searching for resumes with skill: \"" << searchSkill << "\"..." << endl;

    // Start timer
    auto start = chrono::high_resolution_clock::now();
    
    // Perform the search using the new function
    CustomLinkedList<Resume> searchResumeSkillList = dataStorage.linearSearchResumesBySkills(searchSkill);
    
    // Stop timer
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    
    if (searchResumeSkillList.getSize() > 0) {
        cout << "\n[SUCCESS] Found " << searchResumeSkillList.getSize() << " resume(s) with the skill \"" << searchSkill << "\"." << endl;
    
        // Iterate through the results and display them
        for (int i = 0; i < searchResumeSkillList.getSize(); ++i) {
            const Resume& resume = searchResumeSkillList[i];
            cout << "\nResume Match #" << i + 1 << ":" << endl;
            resume.display(); 
        }
    
    } else {
        cout << "[NOT FOUND] No resume with the skill \"" << searchSkill << "\" was found." << endl;
    }
    cout << "\nSearch Time: " << duration.count() << " microseconds." << endl;
}


int main() {
    LinkedListDataStorage dataStorage;
    int choice;
    
    // Use a do-while loop for the main menu
    do {
        displayMenu();
        // Check if the user entered an integer
        if (!(cin >> choice)) {
            // Handle non-integer input
            cout << "\n[INVALID INPUT] Please enter a number from the menu." << endl;
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard bad input
            choice = -1; // Set choice to an invalid value
            continue;
        }

        switch (choice) {
            case 1:
                // Load Data
                dataStorage.loadLinkedListData();
                break;
            case 2:
                // Display Sample Data
                dataStorage.displaySampleData();
                break;
            case 3:
                // Test Linked List Operations
                dataStorage.testLinkedListOperations();
                break;
            case 4:
                cout << "\n[STUB] Bubble Sort Testing not implemented yet." << endl;
                break;
            case 5:
                // Test Linear Search Algorithms
                testLinearSearchJobs(dataStorage);
                break;
            case 6:
                testLinearSearchJobsBySkill(dataStorage);
                break;
            case 7:
                testLinearSearchResumesBySkill(dataStorage);
                break;
            case 8:
                cout << "\n[STUB] Binary Search Testing not implemented yet." << endl;
                break;
            case 9:
                cout << "\n[STUB] Weighted Scoring Testing not implemented yet." << endl;
                break;
            case 10:
                cout << "\n[STUB] Performance Testing not implemented yet." << endl;
                break;
            case 0:
                cout << "\nExiting Linked List Team Test Driver. Goodbye!" << endl;
                break;
            default:
                cout << "\n[INVALID CHOICE] Please select a valid option (0-9)." << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
