#pragma once
#include "model.hpp"
#include <cctype>

using namespace std;

// Convert string to lowercase
CustomString convertToLowerCase(const CustomString& str) {
    if (str.c_str() == nullptr) {
        return CustomString("");
    }
    
    int len = str.size();
    char* result = new char[len + 1];
    
    for (int i = 0; i < len; i++) {
        result[i] = tolower(str.c_str()[i]);
    }
    result[len] = '\0';
    
    CustomString lowerStr(result);
    delete[] result;
    return lowerStr;
}

// Count words in a string
int countWords(const CustomString& str) {
    if (str.c_str() == nullptr) {
        return 0;
    }
    
    int count = 0;
    bool inWord = false;
    const char* text = str.c_str();
    
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            if (!inWord) {
                count++;
                inWord = true;
            }
        } else {
            inWord = false;
        }
    }
    
    return count;
}

// Trim whitespace from string
CustomString trim(const CustomString& str) {
    if (str.c_str() == nullptr) {
        return CustomString("");
    }
    
    const char* text = str.c_str();
    int start = 0;
    int end = str.size() - 1;
    
    // Find start of non-whitespace
    while (start <= end && isspace(text[start])) {
        start++;
    }
    
    // Find end of non-whitespace
    while (end >= start && isspace(text[end])) {
        end--;
    }
    
    if (start > end) {
        return CustomString("");
    }
    
    int len = end - start + 1;
    char* result = new char[len + 1];
    for (int i = 0; i < len; i++) {
        result[i] = text[start + i];
    }
    result[len] = '\0';
    
    CustomString trimmed(result);
    delete[] result;
    return trimmed;
}

// Extract job title from description
CustomString extractJobTitle(const CustomString& line) {
    if (line.c_str() == nullptr) {
        return CustomString("");
    }
    
    const char* text = line.c_str();
    const char* pattern = "needed with experience in";
    
    // Find the pattern
    const char* found = strstr(text, pattern);
    if (found == nullptr) {
        return CustomString("");
    }
    
    // Extract text before the pattern
    int titleLen = found - text;
    if (titleLen <= 0) {
        return CustomString("");
    }
    
    char* title = new char[titleLen + 1];
    for (int i = 0; i < titleLen; i++) {
        title[i] = text[i];
    }
    title[titleLen] = '\0';
    
    CustomString jobTitle = trim(CustomString(title));
    delete[] title;
    
    // Remove leading quote if present
    if (jobTitle.size() > 0 && jobTitle.c_str()[0] == '"') {
        CustomString cleanedTitle = CustomString(jobTitle.c_str() + 1);
        return cleanedTitle;
    }
    
    return jobTitle;
}

// Extract skills from description
CustomArray<CustomString> extractSkills(const CustomString& line) {
    CustomArray<CustomString> skills;
    
    if (line.c_str() == nullptr) {
        return skills;
    }
    
    const char* text = line.c_str();
    const char* startPattern = "needed with experience in";
    const char* endPattern = ".";
    
    // Find start of skills section
    const char* start = strstr(text, startPattern);
    if (start == nullptr) {
        return skills;
    }
    
    // Move to after "needed with experience in"
    start += strlen(startPattern);
    
    // Find end of skills section
    const char* end = strstr(start, endPattern);
    if (end == nullptr) {
        return skills;
    }
    
    // Extract skills text
    int skillsLen = end - start;
    if (skillsLen <= 0) {
        return skills;
    }
    
    char* skillsText = new char[skillsLen + 1];
    for (int i = 0; i < skillsLen; i++) {
        skillsText[i] = start[i];
    }
    skillsText[skillsLen] = '\0';
    
    // Split by commas
    char* token = strtok(skillsText, ",");
    while (token != nullptr) {
        CustomString skill = trim(CustomString(token));
        if (skill.size() > 0) {
            skills.push_back(skill);
        }
        token = strtok(nullptr, ",");
    }
    
    delete[] skillsText;
    return skills;
}

// Categorize job based on title
CustomString categorizeJob(const CustomString& title) {
    if (title.c_str() == nullptr) {
        return CustomString("unknown");
    }
    
    CustomString lowerTitle = convertToLowerCase(title);
    const char* text = lowerTitle.c_str();
    
    if (strstr(text, "analyst")) {
        return CustomString("analyst");
    } else if (strstr(text, "engineer")) {
        return CustomString("engineer");
    } else if (strstr(text, "manager")) {
        return CustomString("manager");
    } else if (strstr(text, "developer")) {
        return CustomString("developer");
    } else if (strstr(text, "scientist")) {
        return CustomString("scientist");
    } else if (strstr(text, "designer")) {
        return CustomString("designer");
    } else {
        return CustomString("other");
    }
}


// Calculate priority based on job attributes
int calculatePriority(const Job& job) {
    int priority = 1;
    
    // Higher priority for more skills
    if (job.skillCount > 5) {
        priority += 1;
    }
    
    // Higher priority for certain categories
    if (strcmp(job.jobCategory.c_str(), "engineer") == 0 ||
        strcmp(job.jobCategory.c_str(), "scientist") == 0) {
        priority += 1;
    }
    
    return priority;
}

// Extract skills from resume description
CustomArray<CustomString> extractResumeSkills(const CustomString& line) {
    CustomArray<CustomString> skills;
    
    if (line.c_str() == nullptr) {
        return skills;
    }
    
    const char* text = line.c_str();
    const char* startPattern = "experienced professional skilled in";
    const char* endPattern = ".";
    
    // Find start of skills section
    const char* start = strstr(text, startPattern);
    if (start == nullptr) {
        return skills;
    }
    
    // Move to after "experienced professional skilled in"
    start += strlen(startPattern);
    
    // Find end of skills section
    const char* end = strstr(start, endPattern);
    if (end == nullptr) {
        return skills;
    }
    
    // Extract skills text
    int skillsLen = end - start;
    if (skillsLen <= 0) {
        return skills;
    }
    
    char* skillsText = new char[skillsLen + 1];
    for (int i = 0; i < skillsLen; i++) {
        skillsText[i] = start[i];
    }
    skillsText[skillsLen] = '\0';
    
    // Split by commas
    char* token = strtok(skillsText, ",");
    while (token != nullptr) {
        CustomString skill = trim(CustomString(token));
        if (skill.size() > 0) {
            skills.push_back(skill);
        }
        token = strtok(nullptr, ",");
    }
    
    delete[] skillsText;
    return skills;
}

// Main preprocessing function for jobs
Job preprocessJobDescription(const CustomString& rawLine, int id) {
    Job job;
    job.id = id;
    job.fullDescription = rawLine;
    
    // Step 1: Convert to lowercase for processing
    CustomString lowerLine = convertToLowerCase(rawLine);
    
    // Step 2: Extract job title
    job.jobTitle = extractJobTitle(lowerLine);
    job.lowerCaseTitle = job.jobTitle;
    
    // Step 3: Extract skills
    job.skills = extractSkills(lowerLine);
    job.skillCount = job.skills.size();
    
    // Step 4: Create lowercase skills array
    for (int i = 0; i < job.skills.size(); i++) {
        job.lowerCaseSkills.push_back(convertToLowerCase(job.skills[i]));
    }
    
    // Step 5: Calculate additional attributes
    job.titleLength = job.jobTitle.size();
    
    // Step 6: Categorize job
    job.jobCategory = categorizeJob(job.jobTitle);
    
    // Step 7: Set experience level (default to mid-level)
    job.experienceLevel = 2;
    
    // Step 8: Calculate priority
    job.priority = calculatePriority(job);
    
    // Step 9: Initialize match score
    job.matchScore = 0.0;
    
    return job;
}

// Build valid skillset from job descriptions
CustomArray<CustomString> buildValidSkillset(const CustomLinkedList<Job>& jobList) {
    CustomArray<CustomString> validSkills;
    
    cout << "Building valid skillset from job descriptions..." << endl;
    
    // Traverse all jobs and collect unique skills
    for (int i = 0; i < jobList.getSize(); i++) {
        for (int j = 0; j < jobList[i].skills.size(); j++) {
            CustomString skill = jobList[i].skills[j];
            
            // Check if skill already exists
            bool exists = false;
            for (int k = 0; k < validSkills.size(); k++) {
                if (strcmp(skill.c_str(), validSkills[k].c_str()) == 0) {
                    exists = true;
                    break;
                }
            }
            
            if (!exists) {
                validSkills.push_back(skill);
            }
        }
    }
    
    cout << "Valid skillset built with " << validSkills.size() << " unique skills" << endl;
    return validSkills;
}

// Filter resume skills against valid job skillset
CustomArray<CustomString> filterResumeSkills(const CustomArray<CustomString>& resumeSkills, 
                                            const CustomArray<CustomString>& validSkills) {
    CustomArray<CustomString> filteredSkills;
    
    for (int i = 0; i < resumeSkills.size(); i++) {
        // Check if resume skill exists in valid skillset
        for (int j = 0; j < validSkills.size(); j++) {
            if (strcmp(resumeSkills[i].c_str(), validSkills[j].c_str()) == 0) {
                filteredSkills.push_back(resumeSkills[i]);
                break;
            }
        }
    }
    
    return filteredSkills;
}

// Main preprocessing function for resumes (with skillset filtering)
Resume preprocessResumeDescription(const CustomString& rawLine, int id, 
                                  const CustomArray<CustomString>& validSkills) {
    Resume resume;
    resume.id = id;
    resume.fullDescription = rawLine;
    
    // Step 1: Convert to lowercase for processing
    CustomString lowerLine = convertToLowerCase(rawLine);
    
    // Step 2: Extract raw skills
    CustomArray<CustomString> rawSkills = extractResumeSkills(lowerLine);
    
    // Step 3: Filter against valid skillset
    resume.skillCount = resume.resumeSkills.size();
    resume.resumeSkills = filterResumeSkills(rawSkills, validSkills);
    
    
    // Step 4: Create lowercase skills array
    for (int i = 0; i < resume.resumeSkills.size(); i++) {
        resume.lowerCaseSkills.push_back(convertToLowerCase(resume.resumeSkills[i]));
    }
    
    // Step 5: Initialize match score
    resume.matchScore = 0.0;
    
    return resume;
}
