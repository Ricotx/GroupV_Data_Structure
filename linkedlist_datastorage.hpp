#pragma once
#include "readcsv.hpp"
#include "linkedlist.hpp"
#include "model.hpp"

using namespace std;

class LinkedListDataStorage {
private:
    CustomLinkedList<Job> jobList;
    CustomLinkedList<Resume> resumeList;
    CustomArray<CustomString> validSkills;
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
};