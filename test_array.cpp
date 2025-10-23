// test_array.cpp — Array Team Test Driver
#include "array_datastorage.hpp"
#include <iostream>
#include <chrono>
#include <limits>

using namespace std;

void displayArrayMainMenu() {
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

// Demo: Load data, run keyword overlap ranking, and show top results
void runKeywordMatchingDemo(ArrayDataStorage& storage) {
    if (storage.getResumeArray().getSize() == 0) {
        cout << "No resumes available for demo" << endl;
        return;
    }

    int resumeIndex = 0;
    cout << "Enter resume index (0-" << (storage.getResumeArray().getSize() - 1) << "): ";
    cin >> resumeIndex;
    if (resumeIndex < 0 || resumeIndex >= storage.getResumeArray().getSize()) {
        cout << "Invalid resume index" << endl;
        return;
    }

    const Resume& sampleResume = storage.getResumeArray()[resumeIndex];
    storage.rankJobsForResumeByKeywords(sampleResume);

    cout << "\n=== Top 5 Jobs by Keyword Overlap for Resume " << sampleResume.id << " ===" << endl;
    cout << "Resume Skills: ";
    for (int i = 0; i < sampleResume.resumeSkills.size(); i++) {
        cout << sampleResume.resumeSkills[i];
        if (i < sampleResume.resumeSkills.size() - 1) cout << ", ";
    }
    cout << endl;
    cout << "=========================================" << endl;
    
    int top = min(5, storage.getJobArray().getSize());
    for (int i = 0; i < top; i++) {
        const Job& j = storage.getJobArray()[i];
        cout << "\nJob Match #" << (i + 1) << " (Keyword Score: " << j.matchScore << "):" << endl;
        j.display();
    }
}

// Show comprehensive data statistics
void showDataStatistics(ArrayDataStorage& storage) {
    if (storage.getJobArray().getSize() == 0) {
        cout << "No data loaded." << endl;
        return;
    }
    
    cout << "\n=== COMPREHENSIVE DATA STATISTICS ===" << endl;
    cout << "Total Jobs: " << storage.getJobArray().getSize() << endl;
    cout << "Total Resumes: " << storage.getResumeArray().getSize() << endl;
    
    // Job statistics
    int totalJobSkills = 0;
    int maxJobSkills = 0;
    int minJobSkills = INT_MAX;
    for (int i = 0; i < storage.getJobArray().getSize(); i++) {
        int skillCount = storage.getJobArray()[i].skillCount;
        totalJobSkills += skillCount;
        maxJobSkills = max(maxJobSkills, skillCount);
        minJobSkills = min(minJobSkills, skillCount);
    }
    
    cout << "\n--- JOB STATISTICS ---" << endl;
    cout << "Average Skills per Job: " << (double)totalJobSkills / storage.getJobArray().getSize() << endl;
    cout << "Max Skills in a Job: " << maxJobSkills << endl;
    cout << "Min Skills in a Job: " << minJobSkills << endl;
    
    // Resume statistics
    int totalResumeSkills = 0;
    int maxResumeSkills = 0;
    int minResumeSkills = INT_MAX;
    for (int i = 0; i < storage.getResumeArray().getSize(); i++) {
        int skillCount = storage.getResumeArray()[i].skillCount;
        totalResumeSkills += skillCount;
        maxResumeSkills = max(maxResumeSkills, skillCount);
        minResumeSkills = min(minResumeSkills, skillCount);
    }
    
    cout << "\n--- RESUME STATISTICS ---" << endl;
    cout << "Average Skills per Resume: " << (double)totalResumeSkills / storage.getResumeArray().getSize() << endl;
    cout << "Max Skills in a Resume: " << maxResumeSkills << endl;
    cout << "Min Skills in a Resume: " << minResumeSkills << endl;
    
    cout << "\n=== END STATISTICS ===" << endl;
}

// --- Sort Sub-Menu (Like Linked List) ---

void displayArraySortMenu() {
    cout << "\n--- Bubble Sort Menu ---" << endl;
    cout << "1. Sort Jobs by Title (A-Z)" << endl;
    cout << "2. Sort Jobs by Skill Count (Lowest to Highest)" << endl;
    cout << "3. Sort Resumes by Skill Count (Lowest to Highest)" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "----------------------" << endl;
    cout << "Enter your choice: ";
}

void handleSortMenu(ArrayDataStorage& storage) {
    if (storage.getJobArray().getSize() == 0) {
        cout << "\n[ERROR] Please load data first (Main Menu option 1)." << endl;
        return;
    }

    int choice;
    do {
        displayArraySortMenu();
        
        if (!(cin >> choice)) {
            cout << "\n[INVALID INPUT] Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
            continue;
        }

        switch (choice) {
            case 1:
                storage.bubbleSortJobsByTitle();
                cout << "Jobs sorted by title." << endl;
                storage.displaySampleData(5);
                break;
            case 2:
                storage.bubbleSortJobsBySkillCount();
                cout << "Jobs sorted by skill count." << endl;
                storage.displaySampleData(5);
                break;
            case 3:
                storage.bubbleSortResumesBySkillCount();
                cout << "Resumes sorted by skill count." << endl;
                // Display sample resumes after sorting
                cout << "\n=== Sample Resumes After Sorting ===" << endl;
                for (int i = 0; i < min(5, storage.getResumeArray().getSize()); i++) {
                    cout << "Resume " << i + 1 << ": ID=" << storage.getResumeArray()[i].id 
                         << ", Skills=" << storage.getResumeArray()[i].skillCount << endl;
                }
                break;
            case 0:
                cout << "Returning to main menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

// Demo: Linear search by job title
void runLinearSearchDemo(ArrayDataStorage& storage) {
    if (storage.getJobArray().getSize() == 0) {
        cout << "No jobs available for search demo" << endl;
        return;
    }

    cout << "Enter exact job title to search: ";
    string titleInput;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, titleInput);
    CustomString title(titleInput.c_str());

    Job* found = storage.linearSearchJobByTitle(title);
    cout << "\nLinear search for title: '" << title << "'\n";
    if (found) {
        cout << "\n[SUCCESS] Found job matching \"" << title << "\":" << endl;
        cout << "=========================================" << endl;
        found->display();
    } else {
        cout << "[NOT FOUND] No job with the title \"" << title << "\" was found." << endl;
    }
}

// Demo: Search jobs by skill
void runJobSkillSearchDemo(ArrayDataStorage& storage) {
    if (storage.getJobArray().getSize() == 0) {
        cout << "No jobs available for skill search" << endl;
        return;
    }

    cout << "Enter skill to search for: ";
    string skillInput;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, skillInput);
    CustomString skill(skillInput.c_str());

    CustomArrayV2<Job> results = storage.searchJobsBySkill(skill);
    cout << "\nSearch results for skill: '" << skill << "'" << endl;
    cout << "Found " << results.getSize() << " jobs with this skill." << endl;
    
    if (results.getSize() > 0) {
        cout << "\n=== Job Results ===" << endl;
        for (int i = 0; i < min(10, results.getSize()); i++) {
            cout << "\nJob " << (i + 1) << ":" << endl;
            results[i].display();
        }
        if (results.getSize() > 10) {
            cout << "\n... and " << (results.getSize() - 10) << " more jobs found." << endl;
        }
    } else {
        cout << "No jobs found with the skill \"" << skill << "\"." << endl;
    }
}

// Demo: Search resumes by skill
void runResumeSkillSearchDemo(ArrayDataStorage& storage) {
    if (storage.getResumeArray().getSize() == 0) {
        cout << "No resumes available for skill search" << endl;
        return;
    }

    cout << "Enter skill to search for: ";
    string skillInput;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, skillInput);
    CustomString skill(skillInput.c_str());

    CustomArrayV2<Resume> results = storage.searchResumesBySkill(skill);
    cout << "\nSearch results for skill: '" << skill << "'" << endl;
    cout << "Found " << results.getSize() << " resumes with this skill." << endl;
    
    if (results.getSize() > 0) {
        cout << "\n=== Resume Results ===" << endl;
        for (int i = 0; i < min(10, results.getSize()); i++) {
            cout << "\nResume " << (i + 1) << ":" << endl;
            results[i].display();
        }
        if (results.getSize() > 10) {
            cout << "\n... and " << (results.getSize() - 10) << " more resumes found." << endl;
        }
    } else {
        cout << "No resumes found with the skill \"" << skill << "\"." << endl;
    }
}

// --- Search Sub-Menu (Like Linked List) ---

void displayArraySearchMenu() {
    cout << "\n--- Linear Search Menu ---" << endl;
    cout << "1. Search Jobs by Title" << endl;
    cout << "2. Search Jobs by Skill" << endl;
    cout << "3. Search Resumes by Skill" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "--------------------------" << endl;
    cout << "Enter your choice: ";
}

void handleSearchMenu(ArrayDataStorage& storage) {
    if (storage.getJobArray().getSize() == 0) {
        cout << "\n[ERROR] Please load data first (Main Menu option 1)." << endl;
        return;
    }

    int choice;
    do {
        displayArraySearchMenu();
        
        if (!(cin >> choice)) {
            cout << "\n[INVALID INPUT] Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
            continue;
        }

        switch (choice) {
            case 1:
                runLinearSearchDemo(storage);
                break;
            case 2:
                runJobSkillSearchDemo(storage);
                break;
            case 3:
                runResumeSkillSearchDemo(storage);
                break;
            case 0:
                cout << "Returning to main menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

// Demo: Filter by title keyword
void runFilterDemo(ArrayDataStorage& storage) {
    if (storage.getJobArray().getSize() == 0) {
        cout << "No jobs loaded." << endl;
        return;
    }
    cout << "Enter keyword to filter titles: ";
    string keyword;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, keyword);
    CustomString key(keyword.c_str());
    auto filtered = storage.filterJobsByTitleKeyword(key);
    cout << "\n[SUCCESS] Found " << filtered.getSize() << " jobs with keyword '" << keyword << "' in title." << endl;
    cout << "=========================================" << endl;
    
    int displayCount = min(5, filtered.getSize());
    for (int i = 0; i < displayCount; i++) {
        cout << "\nJob Match #" << (i + 1) << ":" << endl;
        filtered[i].display();
    }
    
    if (filtered.getSize() > 5) {
        cout << "\n... and " << (filtered.getSize() - 5) << " more jobs found." << endl;
    }
}

// Performance: sort by title timing
void runSortPerformance(ArrayDataStorage& storage) {
    if (storage.getJobArray().getSize() == 0) { cout << "Load data first." << endl; return; }
    auto start = chrono::high_resolution_clock::now();
    storage.bubbleSortJobsByTitle();
    auto end = chrono::high_resolution_clock::now();
    auto ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Bubble Sort by Title took: " << ms << " ms" << endl;
}

// Performance: linear vs binary search timing
void runSearchPerformance(ArrayDataStorage& storage) {
    if (storage.getJobArray().getSize() == 0) { cout << "Load data first." << endl; return; }

    // Ensure sorted for binary search
    storage.bubbleSortJobsByTitle();

    // Pick a target: middle element title (exists case)
    int midIdx = storage.getJobArray().getSize() / 2;
    CustomString target = storage.getJobArray()[midIdx].jobTitle;

    // Linear search timing
    auto t1 = chrono::high_resolution_clock::now();
    Job* lf = storage.linearSearchJobByTitle(target);
    auto t2 = chrono::high_resolution_clock::now();

    // Binary search timing
    auto t3 = chrono::high_resolution_clock::now();
    Job* bf = storage.binarySearchJobByTitle(target);
    auto t4 = chrono::high_resolution_clock::now();

    auto linMs = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
    auto binMs = chrono::duration_cast<chrono::microseconds>(t4 - t3).count();

    cout << "Linear Search time: " << linMs << " µs | Found? " << (lf != nullptr) << endl;
    cout << "Binary Search time: " << binMs << " µs | Found? " << (bf != nullptr) << endl;
}

// Main Function (Like Linked List)
void runArrayMenu() {
    ArrayDataStorage storage;
    int choice;
    
    do {
        displayArrayMainMenu(); 
        
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
                storage.loadArrayData("csv/job_description.csv", "csv/resume.csv");
                break;
            case 2:
                if (storage.getJobArray().getSize() == 0) {
                    cout << "\n[ERROR] Please load data first (Main Menu option 1)." << endl;
                } else {
                    cout << "\nHow many records would you like to display? (Enter number or press Enter for 20): ";
                    
                    string input;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, input);
                    
                    int displayCount = 20; // Default
                    if (!input.empty()) {
                        try {
                            displayCount = stoi(input);
                        } catch (...) {
                            displayCount = 20;
                        }
                    }
                    
                    cout << "\nDisplaying " << displayCount << " records..." << endl;
                    storage.displaySampleData(displayCount);
                }
                break;
            case 3:
                // Call sort sub-menu
                handleSortMenu(storage);
                break;
            case 4:
                handleSearchMenu(storage);
                break;
            case 5:
                if (storage.getJobArray().getSize() == 0) {
                    cout << "\n[ERROR] Please load data first (Main Menu option 1)." << endl;
                } else {
                    int resumeIndex;
                    cout << "Enter the index of the resume to match (0 to " 
                         << storage.getResumeArray().getSize() - 1 << "): ";
                    
                    if (!(cin >> resumeIndex)) {
                         cout << "\n[INVALID INPUT] Please enter a number." << endl;
                         cin.clear();
                         cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    } else {
                         storage.findTopMatchesForResume(storage.getResumeArray()[resumeIndex], 5);
                    }
                }
                break;
            case 6:
                if (storage.getJobArray().getSize() == 0) {
                    cout << "\n[ERROR] Please load data first (Main Menu option 1)." << endl;
                } else {
                    cout << "\n[Executing: Full Performance Test Suite]" << endl;
                    runSortPerformance(storage);
                    runSearchPerformance(storage);
                }
                break;
            case 0:
                cout << "\nExiting Job Matching System. Goodbye!" << endl;
                break;
            default:
                cout << "\n[INVALID CHOICE] Please select a valid option (0-6)." << endl;
                break;
        }
    } while (choice != 0);
}

