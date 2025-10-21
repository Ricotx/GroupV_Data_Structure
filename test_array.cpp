// test_array.cpp — Array Team Test Driver
#include "array_datastorage.hpp"
#include <iostream>
#include <chrono>
#include <limits>

using namespace std;

void displayMenu() {
    cout << "\n=== ARRAY TEAM TEST MENU ===" << endl;
    cout << "1. Load Data" << endl;
    cout << "2. Display Sample Data" << endl;
    cout << "3. Rank Jobs by Keyword Overlap (for a resume)" << endl;
    cout << "4. Bubble Sort Jobs by Title" << endl;
    cout << "5. Bubble Sort Jobs by Skill Count" << endl;
    cout << "6. Linear Search Job by Title" << endl;
    cout << "7. Binary Search Job by Title (requires sorted by title)" << endl;
    cout << "8. Weighted Matching: Top Matches for a Resume" << endl;
    cout << "9. Filter Jobs by Title Keyword" << endl;
    cout << "10. Performance: Sort (Title) Time" << endl;
    cout << "11. Performance: Linear vs Binary Search Time" << endl;
    cout << "0. Exit" << endl;
    cout << "=============================" << endl;
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

    cout << "\nTop 5 jobs by simple keyword overlap for resume " << sampleResume.id << ":" << endl;
    int top = min(5, storage.getJobArray().getSize());
    for (int i = 0; i < top; i++) {
        const Job& j = storage.getJobArray()[i];
        cout << (i + 1) << ". " << j.jobTitle << " | keywordScore=" << j.matchScore << endl;
    }
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
        cout << "Found job with id=" << found->id << " and title=" << found->jobTitle << endl;
    } else {
        cout << "Job not found" << endl;
    }
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
    cout << "Found " << filtered.getSize() << " jobs with keyword '" << keyword << "' in title." << endl;
    for (int i = 0; i < min(5, filtered.getSize()); i++) {
        cout << "- " << filtered[i].jobTitle << endl;
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

// Expose a menu runner without defining main() to avoid multiple-entry conflicts
void runArrayMenu() {
    ArrayDataStorage storage;
    bool loaded = false;

    while (true) {
        displayMenu();
        int choice;
        if (!(cin >> choice)) {
            cout << "Invalid input. Exiting." << endl;
            return;
        }

        if (choice == 0) {
            cout << "Exiting." << endl;
            return;
        }

        switch (choice) {
            case 1: {
                cout << "Enter job CSV path [default csv/job_description.csv]: ";
                string jobPath;
                cin >> jobPath;
                if (jobPath.empty()) jobPath = "csv/job_description.csv";

                cout << "Enter resume CSV path [default csv/resume.csv]: ";
                string resumePath;
                cin >> resumePath;
                if (resumePath.empty()) resumePath = "csv/resume.csv";

                loaded = storage.loadArrayData(jobPath.c_str(), resumePath.c_str());
                break;
            }
            case 2: {
                if (!loaded) { cout << "Load data first." << endl; break; }
                storage.displaySampleData(5);
                break;
            }
            case 3: {
                if (!loaded) { cout << "Load data first." << endl; break; }
                runKeywordMatchingDemo(storage);
                break;
            }
            case 4: {
                if (!loaded) { cout << "Load data first." << endl; break; }
                storage.bubbleSortJobsByTitle();
                cout << "Jobs sorted by title." << endl;
                break;
            }
            case 5: {
                if (!loaded) { cout << "Load data first." << endl; break; }
                storage.bubbleSortJobsBySkillCount();
                cout << "Jobs sorted by skill count." << endl;
                break;
            }
            case 6: {
                if (!loaded) { cout << "Load data first." << endl; break; }
                runLinearSearchDemo(storage);
                break;
            }
            case 7: {
                if (!loaded) { cout << "Load data first." << endl; break; }
                cout << "Enter exact job title to binary search: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                {
                    string titleInput;
                    getline(cin, titleInput);
                    CustomString title(titleInput.c_str());
                    Job* found = storage.binarySearchJobByTitle(title);
                    if (found) {
                        cout << "Found job id=" << found->id << " title=" << found->jobTitle << endl;
                    } else {
                        cout << "Job not found (ensure list sorted by title)." << endl;
                    }
                }
                break;
            }
            case 8: {
                if (!loaded) { cout << "Load data first." << endl; break; }
                if (storage.getResumeArray().getSize() == 0) { cout << "No resumes loaded." << endl; break; }
                int idx = 0;
                cout << "Enter resume index (0-" << (storage.getResumeArray().getSize() - 1) << "): ";
                cin >> idx;
                if (idx < 0 || idx >= storage.getResumeArray().getSize()) { cout << "Invalid index." << endl; break; }
                storage.findTopMatchesForResume(storage.getResumeArray()[idx], 5);
                break;
            }
            case 9: {
                if (!loaded) { cout << "Load data first." << endl; break; }
                runFilterDemo(storage);
                break;
            }
            case 10: {
                if (!loaded) { cout << "Load data first." << endl; break; }
                runSortPerformance(storage);
                break;
            }
            case 11: {
                if (!loaded) { cout << "Load data first." << endl; break; }
                runSearchPerformance(storage);
                break;
            }
            default:
                cout << "Unknown choice." << endl;
        }
    }
}

