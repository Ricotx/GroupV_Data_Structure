#pragma once
#include "readcsv.hpp"
#include "linkedlist.hpp"
#include "model.hpp"
#include <chrono>

using namespace std;

class LinkedListDataStorage {
private:
    CustomLinkedList<Job> jobList;
    CustomLinkedList<Resume> resumeList;
    CustomArray<CustomString> validSkills;

    //Untouch copies to preserve the file order
    CustomLinkedList<Job> originalJobList;
    CustomLinkedList<Resume> originalResumeList;
    bool dataLoaded;
    
public:
    LinkedListDataStorage() : dataLoaded(false) {}
    
    ~LinkedListDataStorage() {
        // Linked lists will automatically clean up via their destructors
    }
    
    // Load data into linked lists
    bool loadLinkedListData(const char* jobFile = "csv/job_description.csv", 
                          const char* resumeFile = "csv/resume.csv") {
        try {
            cout << "=== Loading Linked List Data ===" << endl;
            
            // Load jobs into linked list
            cout << "Loading jobs into linked list from " << jobFile << "..." << endl;
            jobList = loadJobsAsLinkedList(jobFile);
            
            // Build valid skillset from job descriptions
            cout << "Building valid skillset..." << endl;
            validSkills = buildValidSkillset(jobList);
            
            // Load resumes into linked list with skillset filtering
            cout << "Loading resumes into linked list from " << resumeFile << "..." << endl;
            resumeList = loadResumesAsLinkedList(resumeFile, validSkills);

            originalJobList = jobList;
            originalResumeList = resumeList;
            
            dataLoaded = true;
            cout << "=== Linked List Data Loading Complete ===" << endl;
            cout << "Jobs loaded: " << jobList.getSize() << " (linked list)" << endl;
            cout << "Resumes loaded: " << resumeList.getSize() << " (linked list)" << endl;
            return true;
            
        } catch (const exception& e) {
            cerr << "Error loading linked list data: " << e.what() << endl;
            return false;
        }
    }
    
    // Getters for accessing the data
    CustomLinkedList<Job>& getJobList() { return jobList; }
    CustomLinkedList<Resume>& getResumeList() { return resumeList; }
    CustomArray<CustomString>& getValidSkills() { return validSkills; }
    

//  Codes to test the loading of data into linked list from the csv files -    
    // Status check
    bool isDataLoaded() const { return dataLoaded; }
    
    // Display sample data to test preprocessing
    void displaySampleData(int maxJobs = 3, int maxResumes = 3) {
        if (!dataLoaded) {
            cout << "Linked list data not loaded!" << endl;
            return;
        }
        
        cout << "\n=== SAMPLE LINKED LIST DATA ===" << endl;
        displaySampleJobs(jobList, maxJobs);
        displaySampleResumes(resumeList, maxResumes);
        
        cout << "\n=== VALID SKILLSET INFORMATION ===" << endl;
        cout << "Total unique skills from jobs: " << validSkills.size() << endl;
        cout << "Sample valid skills: ";
        int displayCount = min(10, validSkills.size());
        for (int i = 0; i < displayCount; i++) {
            cout << validSkills[i];
            if (i < displayCount - 1) cout << ", ";
        }
        cout << endl;
    }
    
    // Test linked list operations and data access
    void testLinkedListOperations() {
        if (!dataLoaded) {
            cout << "Linked list data not loaded!" << endl;
            return;
        }
        
        cout << "\n=== TESTING LINKED LIST OPERATIONS ===" << endl;
        
        // Test job data access
        if (jobList.getSize() > 0) {
            cout << "First job title: " << jobList[0].jobTitle << endl;
            cout << "Last job title: " << jobList[jobList.getSize()-1].jobTitle << endl;
            if (jobList.getSize() > 500) {
                cout << "Middle job (index 500): " << jobList[500].jobTitle << endl;
            }
        }
        
        // Test resume data access
        if (resumeList.getSize() > 0) {
            cout << "First resume skills: " << resumeList[0].resumeSkills[0] << endl;
            cout << "Last resume skills: " << resumeList[resumeList.getSize()-1].resumeSkills[0] << endl;
            if (resumeList.getSize() > 500) {
                cout << "Middle resume (index 500): " << resumeList[500].resumeSkills[0] << endl;
            }
        }
    }




// Richard's code for searching algorithms
    CustomLinkedList<Job> linearSearchJobsByTitle(const CustomString& title){
        CustomLinkedList<Job> searchJobTitleList;
        
        if (!dataLoaded || jobList.empty()){
            return searchJobTitleList;
        }

        ListNode<Job>* current = jobList.getHead();

        while (current != nullptr){
            if (strcmp(current->data.jobTitle.c_str(), title.c_str()) == 0 ){
                searchJobTitleList.push_back(current->data);
            }
            current = current->next;
        }
        return searchJobTitleList;
    }

    CustomLinkedList<Job> linearSearchJobsBySkills(const CustomString& skill){
        CustomLinkedList<Job> searchJobSkillList;
        
        if (!dataLoaded || jobList.empty()){
            return searchJobSkillList;
        }

        ListNode<Job>* current = jobList.getHead();

        while (current != nullptr){
            for (int i = 0; i < current->data.skills.size(); ++i){
                if (strcmp(current->data.skills[i].c_str(), skill.c_str()) == 0 ){
                    searchJobSkillList.push_back(current->data);
                    break;
                }
            }
            current = current->next;
        }
        return searchJobSkillList;
    }

    CustomLinkedList<Resume> linearSearchResumesBySkills(const CustomString& skill){
        CustomLinkedList<Resume> searchResumeSkillList;
        
        if (!dataLoaded || resumeList.empty()){
            return searchResumeSkillList;
        }

        ListNode<Resume>* current = resumeList.getHead();

        while (current != nullptr){
            for (int i = 0; i < current->data.resumeSkills.size(); ++i){
                if (strcmp(current->data.resumeSkills[i].c_str(), skill.c_str()) == 0 ){
                    searchResumeSkillList.push_back(current->data);
                    break;
                }
            }
            current = current->next;
        }
        return searchResumeSkillList;
    }

//Leon Kin's code - Bubble Sort and Job matching and performance testing.
    void bubbleSortJobsByTitle() {
        if (!dataLoaded || jobList.getSize() < 2) return;
        cout << "Sorting jobs by title (A-Z)..." << endl;
        bool swapped;
        do {
            swapped = false;
            ListNode<Job>* current = jobList.getHead();
            while (current && current->next) {
                if (strcmp(current->data.jobTitle.c_str(), current->next->data.jobTitle.c_str()) > 0) {
                    jobList.swapNodes(current, current->next);
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
        cout << "Jobs sorted by title." << endl;
    }

    void bubbleSortJobsBySkillCount() {
        if (!dataLoaded || jobList.getSize() < 2) return;
        cout << "Sorting jobs by skill count..." << endl;
        bool swapped;
        do {
            swapped = false;
            ListNode<Job>* current = jobList.getHead();
            while (current && current->next) {
                if (current->data.skillCount > current->next->data.skillCount) {
                    jobList.swapNodes(current, current->next);
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
        cout << "Jobs sorted by skill count." << endl;
    }

    void bubbleSortResumesBySkillCount() {
        if (!dataLoaded || resumeList.getSize() < 2) return;
        cout << "Sorting resumes by skill count..." << endl;
        bool swapped;
        do {
            swapped = false;
            ListNode<Resume>* current = resumeList.getHead();
            while (current && current->next) {
                if (current->data.skillCount > current->next->data.skillCount) {
                    resumeList.swapNodes(current, current->next);
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
        cout << "Resumes sorted by skill count." << endl;
    }

    void bubbleSortJobsByMatchScore() {
        if (!dataLoaded || jobList.getSize() < 2) return;
        cout << "Sorting jobs by match score..." << endl;
        bool swapped;
        do {
            swapped = false;
            ListNode<Job>* current = jobList.getHead();
            while (current && current->next) {
                if (current->data.matchScore < current->next->data.matchScore) { // Descending
                    jobList.swapNodes(current, current->next);
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
        cout << "Jobs sorted by match score." << endl;
    }

    void findAndDisplayTopMatches(int resumeIndex) {
        if (resumeIndex < 0 || originalResumeList.getSize() <= resumeIndex) {
            cout << "Invalid resume index." << endl;
            return;
        }

        Resume& selectedResume = originalResumeList[resumeIndex];
        
        cout << "\nFinding job matches for Resume ID: " << selectedResume.id << endl;
        cout << "Resume Skills (" << selectedResume.skillCount << "): ";
        for (int i = 0; i < selectedResume.resumeSkills.size(); i++) {
            cout << selectedResume.resumeSkills[i] << (i == selectedResume.resumeSkills.size() - 1 ? "" : ", ");
        }
        cout << endl;

        for (int i = 0; i < jobList.getSize(); ++i) {
            Job& currentJob = jobList[i];
            
            int matchingSkills = 0;
            for (int j = 0; j < selectedResume.lowerCaseSkills.size(); ++j) {
                for (int k = 0; k < currentJob.lowerCaseSkills.size(); ++k) {
                    if (strcmp(selectedResume.lowerCaseSkills[j].c_str(), currentJob.lowerCaseSkills[k].c_str()) == 0) {
                        matchingSkills++;
                        break;
                    }
                }
            }
            
            int unionSize = selectedResume.skillCount + currentJob.skillCount - matchingSkills;
            currentJob.matchScore = (unionSize > 0) ? static_cast<double>(matchingSkills) / unionSize : 0.0;
        }

        bubbleSortJobsByMatchScore();

        cout << "\n--- Top 5 Job Matches ---" << endl;
        int count = 0;
        for (int i = 0; i < jobList.getSize() && count < 5; ++i) {
            if (jobList[i].matchScore > 0) {
                cout << "Match Score: " << (jobList[i].matchScore * 100) << "%" << endl;
                jobList[i].display();
                count++;
            }
        }
    }

    void displaySampleJobsOnly(int maxJobs = 5) {
        if (!dataLoaded) return;
        cout << "\n--- Sample of Sorted Jobs ---" << endl;
        displaySampleJobs(jobList, maxJobs);
    }
    void displaySampleResumesOnly(int maxResumes = 5) {
        if (!dataLoaded) return;
        cout << "\n--- Sample of Sorted Resumes ---" << endl;
        displaySampleResumes(resumeList, maxResumes);
    }

    void runPerformanceTests() {
        if (!dataLoaded) {
            cout << "Please load data first." << endl;
            return;
        }
        cout << "\n[Executing: Full Performance Test Suite]" << endl;
        
        // Test 1: Sort Jobs by Title
        CustomLinkedList<Job> jobsToSortTitle = originalJobList;
        auto start1 = chrono::high_resolution_clock::now();
        // --- Bubble Sort Logic for Test 1 ---
        bool swapped1;
        do { 
            swapped1 = false; 
            ListNode<Job>* current = jobsToSortTitle.getHead(); 
            while (current && current->next) { 
                if (strcmp(current->data.jobTitle.c_str(), current->next->data.jobTitle.c_str()) > 0) { 
                    jobsToSortTitle.swapNodes(current, current->next); 
                    swapped1 = true; 
                } 
                // Advance current *after* potential swap or check
                if (current) current = current->next; // Need to re-check current in case it became tail after swap
            } 
        } while (swapped1);
        // --- End Sort Logic ---
        auto end1 = chrono::high_resolution_clock::now();
        auto duration1 = chrono::duration_cast<chrono::milliseconds>(end1 - start1);
        cout << "Time taken for Bubble Sort (Jobs by Title): " << duration1.count() << " ms" << endl;

        // Test 2: Sort Jobs by Skill Count
        CustomLinkedList<Job> jobsToSortSkill = originalJobList;
        auto start2 = chrono::high_resolution_clock::now();
        // --- Bubble Sort Logic for Test 2 ---
        bool swapped2;
        do { 
            swapped2 = false; 
            ListNode<Job>* current = jobsToSortSkill.getHead(); 
            while (current && current->next) { 
                if (current->data.skillCount > current->next->data.skillCount) { 
                    jobsToSortSkill.swapNodes(current, current->next); 
                    swapped2 = true; 
                } 
                if (current) current = current->next; 
            } 
        } while (swapped2);
        // --- End Sort Logic ---
        auto end2 = chrono::high_resolution_clock::now();
        auto duration2 = chrono::duration_cast<chrono::milliseconds>(end2 - start2);
        cout << "Time taken for Bubble Sort (Jobs by Skill Count): " << duration2.count() << " ms" << endl;

        // Test 3: Sort Resumes by Skill Count
        CustomLinkedList<Resume> resumesToSort = originalResumeList;
        auto start3 = chrono::high_resolution_clock::now();
        // --- Bubble Sort Logic for Test 3 ---
        bool swapped3;
        do { 
            swapped3 = false; 
            ListNode<Resume>* current = resumesToSort.getHead(); 
            while (current && current->next) { 
                if (current->data.skillCount > current->next->data.skillCount) { 
                    resumesToSort.swapNodes(current, current->next); 
                    swapped3 = true; 
                } 
                if (current) current = current->next; 
            } 
        } while (swapped3);
        // --- End Sort Logic ---
        auto end3 = chrono::high_resolution_clock::now();
        auto duration3 = chrono::duration_cast<chrono::milliseconds>(end3 - start3);
        cout << "Time taken for Bubble Sort (Resumes by Skill Count): " << duration3.count() << " ms" << endl;

        // Test 4: Job Matching Speed
        if (!originalResumeList.empty()) {
            Resume& testResume = originalResumeList[0]; // Use the first resume for the test
            auto start_match = chrono::high_resolution_clock::now();

            // --- Job Matching Logic ---
            for (int i = 0; i < jobList.getSize(); ++i) {
                Job& currentJob = jobList[i]; // Use operator[] on the main jobList
                int matchingSkills = 0;
                // Compare skills (using lowercase versions as intended)
                for (int j = 0; j < testResume.lowerCaseSkills.size(); ++j) {
                    for (int k = 0; k < currentJob.lowerCaseSkills.size(); ++k) {
                        if (strcmp(testResume.lowerCaseSkills[j].c_str(), currentJob.lowerCaseSkills[k].c_str()) == 0) { 
                            matchingSkills++; 
                            break; 
                        }
                    }
                }
                int unionSize = testResume.skillCount + currentJob.skillCount - matchingSkills;
                // Calculate match score (optional, can be commented out if not needed for timing)
                double score = (unionSize > 0) ? static_cast<double>(matchingSkills) / unionSize : 0.0;
                 (void)score; // Suppress unused variable warning if you only care about timing the loops
            }
            // --- End Matching Logic ---

            auto end_match = chrono::high_resolution_clock::now();
            auto match_duration = chrono::duration_cast<chrono::milliseconds>(end_match - start_match);
            cout << "Time taken for matching one resume to all jobs: " << match_duration.count() << " ms" << endl;
        }

        // Test 5: Linear Search (Worst-Case)
        if (!originalJobList.empty()) {
            // Get the title of the VERY LAST job from the original list
            CustomString worstCaseTitle = originalJobList[originalJobList.getSize() - 1].jobTitle;
    
            cout << "Searching for last job title: \"" << worstCaseTitle << "\"..." << endl;
            
            auto start_search = chrono::high_resolution_clock::now();
            
            // Perform the search on the main jobList (or originalJobList if you prefer)
            CustomLinkedList<Job> searchResult = linearSearchJobsByTitle(worstCaseTitle); 
            
            auto end_search = chrono::high_resolution_clock::now();
            // Calculate duration in milliseconds as integer
            auto search_duration = chrono::duration_cast<chrono::milliseconds>(end_search - start_search);
            
            cout << "Time taken for Linear Search (Jobs by Title, worst-case): " 
                 << search_duration.count() << " ms" << endl;
        }
    } 

};


    