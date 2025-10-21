// test_linkedlist.cpp — Combined Team Test Driver
#include "linkedlist_datastorage.hpp"
#include "model.hpp"
#include <cctype>
#include <iostream>
#include <chrono>
#include <limits> // Required for numeric_limits

using namespace std;

// --- Main Menu (Your new requirement) ---

void displayMainMenu() {
    cout << "\n=== Job Matching System Menu ===" << endl;
    cout << "1. Load Data" << endl;
    cout << "2. Display Sample Data" << endl;
    cout << "3. Sort Data (Bubble Sort)" << endl;
    cout << "4. Search Data (Linear Search)" << endl;
    cout << "5. Find Job Matches for Resume" << endl;
    cout << "6. Performance Tests" << endl;
    cout << "0. Exit" << endl;
    cout << "=================================" << endl;
    cout << "Enter your choice: ";
}

// --- Linear Search Functions (From your code) ---

void testLinearSearchJobs(LinkedListDataStorage& dataStorage) {
    cout << "\n--- Test Linear Search by Job Title ---" << endl;
    cout << "Enter the Job Title to search for: ";
    
    string searchTitleStr;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, searchTitleStr);
    
    CustomString searchTitle(searchTitleStr.c_str());


    cout << "Searching for: \"" << searchTitle << "\"..." << endl;
    auto start = chrono::high_resolution_clock::now();
    
    CustomLinkedList<Job> searchJobsTitleList = dataStorage.linearSearchJobsByTitle(searchTitle);
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    if (searchJobsTitleList.getSize() > 0) {
        cout << "\n[SUCCESS] Found " << searchJobsTitleList.getSize() << " job(s) matching \"" << searchTitle << "\"." << endl;
        for (int i = 0; i < searchJobsTitleList.getSize(); ++i) {
            const Job& job = searchJobsTitleList[i];
            cout << "\nJob Match #" << i + 1 << ":" << endl;
            job.display(); 
        }
    } else {
        cout << "[NOT FOUND] No job with the title \"" << searchTitle << "\" was found." << endl;
    }
    cout << "\nSearch Time: " << duration.count() << " microseconds." << endl;
}

void testLinearSearchJobsBySkill(LinkedListDataStorage& dataStorage) {
    cout << "\n--- Test Linear Search by Job Skill ---" << endl;
    cout << "Enter the Skill to search for (e.g., java, git, python): ";
    
    string searchSkillStr;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, searchSkillStr);
    
    CustomString searchSkill(searchSkillStr.c_str());

    cout << "Searching for jobs with skill: \"" << searchSkill << "\"..." << endl;
    auto start = chrono::high_resolution_clock::now();
    
    CustomLinkedList<Job> searchJobsSkillList = dataStorage.linearSearchJobsBySkills(searchSkill);
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    
    if (searchJobsSkillList.getSize() > 0) {
        cout << "\n[SUCCESS] Found " << searchJobsSkillList.getSize() << " job(s) with the skill \"" << searchSkill << "\"." << endl;
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
    cout << "\n--- Test Linear Search by Resume Skill ---" << endl;
    cout << "Enter the Skill to search for (e.g., java, git, python): ";
    
    string searchSkillStr;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, searchSkillStr);
    
    CustomString searchSkill(searchSkillStr.c_str());

    cout << "Searching for resumes with skill: \"" << searchSkill << "\"..." << endl;
    auto start = chrono::high_resolution_clock::now();
    
    CustomLinkedList<Resume> searchResumeSkillList = dataStorage.linearSearchResumesBySkills(searchSkill);
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    
    if (searchResumeSkillList.getSize() > 0) {
        cout << "\n[SUCCESS] Found " << searchResumeSkillList.getSize() << " resume(s) with the skill \"" << searchSkill << "\"." << endl;
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

// --- Search Sub-Menu 

void displaySearchMenu() {
    cout << "\n--- Linear Search Menu ---" << endl;
    cout << "1. Search Jobs by Title" << endl;
    cout << "2. Search Jobs by Skill" << endl;
    cout << "3. Search Resumes by Skill" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "--------------------------" << endl;
    cout << "Enter your choice: ";
}

void handleSearchMenu(LinkedListDataStorage& dataStorage) {
    if (!dataStorage.isDataLoaded()) {
        cout << "\n[ERROR] Please load data first (Main Menu option 1)." << endl;
        return;
    }

    int choice;
    do {
        displaySearchMenu();
        
        if (!(cin >> choice)) {
            cout << "\n[INVALID INPUT] Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
            continue;
        }

        switch (choice) {
            case 1:
                testLinearSearchJobs(dataStorage);
                break;
            case 2:
                testLinearSearchJobsBySkill(dataStorage);
                break;
            case 3:
                testLinearSearchResumesBySkill(dataStorage);
                break;
            case 0:
                cout << "Returning to main menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

// --- Sort Sub-Menu 

void displaySortMenu() {
    cout << "\n--- Bubble Sort Menu ---" << endl;
    cout << "1. Sort Jobs by Title (A-Z)" << endl;
    cout << "2. Sort Jobs by Skill Count (Lowest to Highest)" << endl;
    cout << "3. Sort Resumes by Skill Count (Lowest to Highest)" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "----------------------" << endl;
    cout << "Enter your choice: ";
}

void handleSortMenu(LinkedListDataStorage& dataStorage) {
    if (!dataStorage.isDataLoaded()) {
        cout << "\n[ERROR] Please load data first (Main Menu option 1)." << endl;
        return;
    }

    int choice;
    do {
        displaySortMenu();
        
        if (!(cin >> choice)) {
            cout << "\n[INVALID INPUT] Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
            continue;
        }

        switch (choice) {
            case 1:
                dataStorage.bubbleSortJobsByTitle();
                dataStorage.displaySampleJobsOnly();
                break;
            case 2:
                dataStorage.bubbleSortJobsBySkillCount();
                dataStorage.displaySampleJobsOnly();
                break;
            case 3:
                dataStorage.bubbleSortResumesBySkillCount();
                dataStorage.displaySampleResumesOnly();
                break;
            case 0:
                cout << "Returning to main menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

// --- Main Function (Combined) ---

int main() {
    LinkedListDataStorage dataStorage;
    int choice;
    
    do {
        displayMainMenu(); 
        
        if (!(cin >> choice)) {
            cout << "\n[INVALID INPUT] Please enter a number from the menu." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
            continue;
        }

        switch (choice) {
            case 1:
                cout << "\nLoading data..." << endl;
                dataStorage.loadLinkedListData("csv/job_description.csv", "csv/resume.csv");
                break;
            case 2:
                // Your display function
                dataStorage.displaySampleData();
                break;
            case 3:
                // Call sort sub-menu
                handleSortMenu(dataStorage);
                break;
            case 4:
                handleSearchMenu(dataStorage);
                break;
            case 5:
                if (!dataStorage.isDataLoaded()) {
                    cout << "\n[ERROR] Please load data first (Main Menu option 1)." << endl;
                } else {
                    int resumeIndex;
                    cout << "Enter the index of the resume to match (0 to " 
                         << dataStorage.getResumeList().getSize() - 1 << "): ";
                    
                    if (!(cin >> resumeIndex)) {
                         cout << "\n[INVALID INPUT] Please enter a number." << endl;
                         cin.clear();
                         cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    } else {
                         dataStorage.findAndDisplayTopMatches(resumeIndex);
                    }
                }
                break;
            case 6:
                dataStorage.runPerformanceTests();
                break;
                break;
            case 0:
                cout << "\nExiting Job Matching System. Goodbye!" << endl;
                break;
            default:
                cout << "\n[INVALID CHOICE] Please select a valid option (0-7)." << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}