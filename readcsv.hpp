#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "model.hpp"
#include "linkedlist.hpp"
#include "preprocessor.hpp"

using namespace std;

class CSVReader {
private:
    char* filename;
    
public:
    CSVReader(const char* filename) {
        this->filename = new char[strlen(filename) + 1];
        strcpy(this->filename, filename);
    }
    
    ~CSVReader() {
        delete[] filename;
    }
    
    // Read all lines from CSV file (excluding header)
    CustomArray<CustomString> readAllLines() {
        CustomArray<CustomString> lines;
        ifstream file(filename);
        
        if (!file.is_open()) {
            cerr << "Error: Could not open file " << filename << endl;
            return lines;
        }
        
        char line[10000]; // Fixed size buffer
        bool firstLine = true;
        while (file.getline(line, sizeof(line))) {
            if (firstLine) {
                firstLine = false;
                continue; // Skip header line
            }
            lines.push_back(CustomString(line));
        }
        
        file.close();
        return lines;
    }
    
    // Read first N lines from CSV file (excluding header)
    CustomArray<CustomString> readFirstNLines(int n) {
        CustomArray<CustomString> lines;
        ifstream file(filename);
        
        if (!file.is_open()) {
            cerr << "Error: Could not open file " << filename << endl;
            return lines;
        }
        
        char line[10000]; // Fixed size buffer
        bool firstLine = true;
        int count = 0;
        while (file.getline(line, sizeof(line)) && count < n) {
            if (firstLine) {
                firstLine = false;
                continue; // Skip header line
            }
            lines.push_back(CustomString(line));
            count++;
        }
        
        file.close();
        return lines;
    }
    
    // Parse CSV line and return array of fields
    CustomArray<CustomString> parseCSVLine(const char* line) {
        CustomArray<CustomString> fields;
        char* lineCopy = new char[strlen(line) + 1];
        strcpy(lineCopy, line);
        
        char* token = strtok(lineCopy, ",");
        while (token != nullptr) {
            // Remove quotes if present
            char* field = token;
            if (field[0] == '"' && field[strlen(field) - 1] == '"') {
                field[strlen(field) - 1] = '\0';
                field++;
            }
            fields.push_back(CustomString(field));
            token = strtok(nullptr, ",");
        }
        
        delete[] lineCopy;
        return fields;
    }
    
    // Display CSV content with formatting
    void displayCSV(int maxLines = 10) {
        cout << "\n=== Reading from " << filename << " ===" << endl;
        
        CustomArray<CustomString> lines = readFirstNLines(maxLines);
        
        for (int i = 0; i < lines.size(); i++) {
            cout << "Line " << (i + 1) << ": " << lines[i] << endl;
        }
        
        if (lines.size() == maxLines) {
            cout << "... (showing first " << maxLines << " lines)" << endl;
        }
        
        cout << "Total lines read: " << lines.size() << endl;
    }
    
    // Get total number of data lines in CSV (excluding header)
    int getTotalLines() {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Could not open file " << filename << endl;
            return 0;
        }
        
        int count = 0;
        char line[10000]; // Fixed size buffer
        bool firstLine = true;
        while (file.getline(line, sizeof(line))) {
            if (firstLine) {
                firstLine = false;
                continue; // Skip header line
            }
            count++;
        }
        
        file.close();
        return count;
    }
};

// Helper function to read job descriptions
void readJobDescriptions(const char* filename, int maxLines = 10) {
    CSVReader reader(filename);
    cout << "\n=== JOB DESCRIPTIONS ===" << endl;
    cout << "File: " << filename << endl;
    cout << "Total lines: " << reader.getTotalLines() << endl;
    reader.displayCSV(maxLines);
}

// Load jobs into linked list with preprocessing
CustomLinkedList<Job> loadJobsAsLinkedList(const char* filename) {
    CustomLinkedList<Job> jobList;
    CSVReader reader(filename);
    
    cout << "Loading jobs from " << filename << "..." << endl;
    
    CustomArray<CustomString> rawLines = reader.readAllLines();
    cout << "Read " << rawLines.size() << " raw lines from CSV" << endl;
    
    for (int i = 0; i < rawLines.size(); i++) {
        Job job = preprocessJobDescription(rawLines[i], i + 1);
        jobList.push_back(job);
        
        // Progress indicator
        if ((i + 1) % 1000 == 0) {
            cout << "Processed " << (i + 1) << " jobs..." << endl;
        }
    }
    
    cout << "Successfully loaded " << jobList.getSize() << " jobs into linked list" << endl;
    return jobList;
}

// Load resumes into linked list with preprocessing (with skillset filtering)
CustomLinkedList<Resume> loadResumesAsLinkedList(const char* filename, const CustomArray<CustomString>& validSkills) {
    CustomLinkedList<Resume> resumeList;
    CSVReader reader(filename);
    
    cout << "Loading resumes from " << filename << "..." << endl;
    
    CustomArray<CustomString> rawLines = reader.readAllLines();
    cout << "Read " << rawLines.size() << " raw lines from CSV" << endl;
    
    for (int i = 0; i < rawLines.size(); i++) {
        Resume resume = preprocessResumeDescription(rawLines[i], i + 1, validSkills);
        resumeList.push_back(resume);
        
        // Progress indicator
        if ((i + 1) % 1000 == 0) {
            cout << "Processed " << (i + 1) << " resumes..." << endl;
        }
    }
    
    cout << "Successfully loaded " << resumeList.getSize() << " resumes into linked list" << endl;
    return resumeList;
}

// Display sample of processed jobs
void displaySampleJobs(const CustomLinkedList<Job>& jobList, int maxJobs = 5) {
    cout << "\n=== SAMPLE PROCESSED JOBS ===" << endl;
    
    int displayCount = min(maxJobs, jobList.getSize());
    for (int i = 0; i < displayCount; i++) {
        cout << "Job " << (i + 1) << ":" << endl;
        jobList[i].display();
    }
    
    if (jobList.getSize() > maxJobs) {
        cout << "... and " << (jobList.getSize() - maxJobs) << " more jobs" << endl;
    }
}

// Display sample of processed resumes
void displaySampleResumes(const CustomLinkedList<Resume>& resumeList, int maxResumes = 5) {
    cout << "\n=== SAMPLE PROCESSED RESUMES ===" << endl;
    
    int displayCount = min(maxResumes, resumeList.getSize());
    for (int i = 0; i < displayCount; i++) {
        cout << "Resume " << (i + 1) << ":" << endl;
        resumeList[i].display();
    }
    
    if (resumeList.getSize() > maxResumes) {
        cout << "... and " << (resumeList.getSize() - maxResumes) << " more resumes" << endl;
    }
}
