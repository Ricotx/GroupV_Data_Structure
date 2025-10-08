#pragma once
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

// Custom String class
class CustomString {
private:
    char* data;
    int length;
    
public:
    CustomString() : data(nullptr), length(0) {}
    
    CustomString(const char* str) {
        if (str) {
            length = strlen(str);
            data = new char[length + 1];
            strcpy(data, str);
        } else {
            data = nullptr;
            length = 0;
        }
    }
    
    CustomString(const CustomString& other) {
        if (other.data) {
            length = other.length;
            data = new char[length + 1];
            strcpy(data, other.data);
        } else {
            data = nullptr;
            length = 0;
        }
    }
    
    ~CustomString() {
        delete[] data;
    }
    
    CustomString& operator=(const CustomString& other) {
        if (this != &other) {
            delete[] data;
            if (other.data) {
                length = other.length;
                data = new char[length + 1];
                strcpy(data, other.data);
            } else {
                data = nullptr;
                length = 0;
            }
        }
        return *this;
    }
    
    const char* c_str() const { return data; }
    int size() const { return length; }
    
    friend ostream& operator<<(ostream& os, const CustomString& str) {
        if (str.data) os << str.data;
        return os;
    }
};

// Custom Array class
template<typename T>
class CustomArray {
private:
    T* data;
    int capacity;
    int currentSize;
    
public:
    CustomArray() : data(nullptr), capacity(0), currentSize(0) {}
    
    // Copy constructor
    CustomArray(const CustomArray& other) : data(nullptr), capacity(0), currentSize(0) {
        for (int i = 0; i < other.currentSize; i++) {
            push_back(other.data[i]);
        }
    }
    
    // Assignment operator
    CustomArray& operator=(const CustomArray& other) {
        if (this != &other) {
            delete[] data;
            data = nullptr;
            capacity = 0;
            currentSize = 0;
            
            for (int i = 0; i < other.currentSize; i++) {
                push_back(other.data[i]);
            }
        }
        return *this;
    }
    
    ~CustomArray() {
        delete[] data;
    }
    
    void push_back(const T& item) {
        if (currentSize >= capacity) {
            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
            T* newData = new T[newCapacity];
            for (int i = 0; i < currentSize; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
        data[currentSize] = item;
        currentSize++;
    }
    
    T& operator[](int index) {
        return data[index];
    }
    
    const T& operator[](int index) const {
        return data[index];
    }
    
    int size() const { return currentSize; }
    bool empty() const { return currentSize == 0; }
};

struct Job {
    // Basic attributes
    int id;
    CustomString jobTitle;
    CustomArray<CustomString> skills;
    CustomString fullDescription;
    
    // Calculated attributes for sorting
    int skillCount;
    int titleLength;
    int priority;
    
    // Attributes for searching
    CustomString lowerCaseTitle;
    CustomArray<CustomString> lowerCaseSkills;
    
    // Attributes for job matching
    CustomString jobCategory;
    int experienceLevel;
    double matchScore;
    
    // Constructors
    Job() : id(0), skillCount(0), titleLength(0), priority(0), 
            experienceLevel(0), matchScore(0.0) {}
    
    Job(int id, const CustomString& title) : id(id), jobTitle(title), skillCount(0), 
            titleLength(0), priority(0), experienceLevel(0), matchScore(0.0) {}
    
    // Display function for debugging
    void display() const {
        cout << "Job ID: " << id << endl;
        cout << "Title: " << jobTitle << endl;
        cout << "Skills (" << skillCount << "): ";
        for (int i = 0; i < skills.size(); i++) {
            cout << skills[i];
            if (i < skills.size() - 1) cout << ", ";
        }
        cout << endl;
        cout << "Category: " << jobCategory << endl;
        cout << "Priority: " << priority << endl;
        cout << "---" << endl;
    }
};

struct Resume {
    // Basic attributes
    int id;
    CustomString fullDescription;
    
    // Skills extracted from resume
    CustomArray<CustomString> resumeSkills;
    int skillCount;
    
    // For searching
    CustomArray<CustomString> lowerCaseSkills;
    
    // For matching with jobs
    double matchScore;
    
    // Constructors
    Resume() : id(0), skillCount(0), matchScore(0.0) {}
    
    Resume(int id, const CustomString& desc) : id(id), fullDescription(desc), 
            skillCount(0), matchScore(0.0) {}
    
    // Display function for debugging
    void display() const {
        cout << "Resume ID: " << id << endl;
        cout << "Skills (" << skillCount << "): ";
        for (int i = 0; i < resumeSkills.size(); i++) {
            cout << resumeSkills[i];
            if (i < resumeSkills.size() - 1) cout << ", ";
        }
        cout << endl;
        cout << "Match Score: " << matchScore << endl;
        cout << "---" << endl;
    }
};