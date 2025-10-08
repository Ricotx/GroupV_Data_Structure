#pragma once
#include "readcsv.hpp"
#include "model.hpp"

using namespace std;

class ArrayDataStorage {
private:
    CustomArray<Job> jobArray;
    CustomArray<Resume> resumeArray;
    CustomArray<CustomString> validSkills;
    bool dataLoaded;
    
public:
    ArrayDataStorage() : dataLoaded(false) {}
    
    ~ArrayDataStorage() {
        // Arrays will automatically clean up via their destructors
    }
    
}
