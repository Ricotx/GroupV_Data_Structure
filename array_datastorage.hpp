#pragma once
#include "model.hpp"
#include "array.hpp"
#include "readcsv.hpp"
#include "preprocessor.hpp"
#include "matching.hpp"
#include <iostream>
#include <ctime>
#include <cstring>

using namespace std;

class ArrayDataStorage {
private:
    CustomArrayV2<Job> jobArray;
    CustomArrayV2<Resume> resumeArray;
    CustomArray<CustomString> validSkills; 

public:
    ArrayDataStorage() {}

    
    CustomArray<CustomString> buildValidSkillsetFromJobs() {
        CustomArray<CustomString> skillset;

        for (int i = 0; i < jobArray.getSize(); i++) {
            const Job& job = jobArray[i];
            for (int j = 0; j < job.skills.size(); j++) {
                CustomString skill = job.skills[j];
                bool exists = false;
                for (int k = 0; k < skillset.size(); k++) {
                    if (strcmp(skillset[k].c_str(), skill.c_str()) == 0) {
                        exists = true;
                        break;
                    }
                }
                if (!exists)
                    skillset.push_back(skill);
            }
        }

        cout << "✅ Built valid skillset with " << skillset.size() << " unique skills.\n";
        return skillset;
    }

   
    bool loadArrayData(const char* jobFile, const char* resumeFile) {
        CSVReader jobReader(jobFile);
        CustomArray<CustomString> jobLines = jobReader.readAllLines();
        cout << "Loading " << jobLines.size() << " jobs..." << endl;

        for (int i = 0; i < jobLines.size(); i++) {
            jobArray.push_back(preprocessJobDescription(jobLines[i], i + 1));
        }

        
        validSkills = buildValidSkillsetFromJobs();

        CSVReader resumeReader(resumeFile);
        CustomArray<CustomString> resumeLines = resumeReader.readAllLines();
        cout << "Loading " << resumeLines.size() << " resumes..." << endl;

        for (int i = 0; i < resumeLines.size(); i++) {
            resumeArray.push_back(preprocessResumeDescription(resumeLines[i], i + 1, validSkills));
        }

        cout << "✅ Loaded " << jobArray.getSize() << " jobs and " << resumeArray.getSize() << " resumes." << endl;
        return true;
    }

    
    void displaySampleData(int n = 5) const {
        cout << "\n=== SAMPLE JOBS ===" << endl;
        for (int i = 0; i < min(n, jobArray.getSize()); i++)
            jobArray[i].display();

        cout << "\n=== SAMPLE RESUMES ===" << endl;
        for (int i = 0; i < min(n, resumeArray.getSize()); i++)
            resumeArray[i].display();
    }

   
    void bubbleSortJobsByTitle() {
        int n = jobArray.getSize();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (strcmp(jobArray[j].jobTitle.c_str(), jobArray[j + 1].jobTitle.c_str()) > 0) {
                    Job temp = jobArray[j];
                    jobArray[j] = jobArray[j + 1];
                    jobArray[j + 1] = temp;
                }
            }
        }
    }

    void bubbleSortJobsBySkillCount() {
        int n = jobArray.getSize();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (jobArray[j].skillCount > jobArray[j + 1].skillCount) {
                    Job temp = jobArray[j];
                    jobArray[j] = jobArray[j + 1];
                    jobArray[j + 1] = temp;
                }
            }
        }
    }

   
    Job* linearSearchJobByTitle(const CustomString& title) {
        for (int i = 0; i < jobArray.getSize(); i++) {
            if (strcmp(jobArray[i].jobTitle.c_str(), title.c_str()) == 0)
                return &jobArray[i];
        }
        return nullptr;
    }

    Job* binarySearchJobByTitle(const CustomString& title) {
        int low = 0, high = jobArray.getSize() - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            int cmp = strcmp(jobArray[mid].jobTitle.c_str(), title.c_str());
            if (cmp == 0)
                return &jobArray[mid];
            else if (cmp < 0)
                low = mid + 1;
            else
                high = mid - 1;
        }
        return nullptr;
    }

   
    double calculateWeightedMatchScore(const Job& job, const Resume& resume) {
        int matchCount = 0;
        for (int i = 0; i < job.skills.size(); i++) {
            for (int j = 0; j < resume.resumeSkills.size(); j++) {
                if (strcmp(job.skills[i].c_str(), resume.resumeSkills[j].c_str()) == 0)
                    matchCount++;
            }
        }
        if (job.skills.size() == 0)
            return 0.0;
        return (double)matchCount / job.skills.size();
    }

    // Simple keyword-based score based on full descriptions
    int calculateKeywordOverlapScore(const Job& job, const Resume& resume) {
        return calculateMatchScore(job.fullDescription, resume.fullDescription);
    }

    // Rank all jobs for a given resume using keyword overlap (bubble sort)
    void rankJobsForResumeByKeywords(const Resume& resume) {
        for (int i = 0; i < jobArray.getSize(); i++) {
            jobArray[i].matchScore = static_cast<double>(calculateKeywordOverlapScore(jobArray[i], resume));
        }
        int n = jobArray.getSize();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (jobArray[j].matchScore < jobArray[j + 1].matchScore) {
                    Job tmp = jobArray[j];
                    jobArray[j] = jobArray[j + 1];
                    jobArray[j + 1] = tmp;
                }
            }
        }
    }

    // Linear search for a resume by id
    Resume* linearSearchResumeById(int targetId) {
        for (int i = 0; i < resumeArray.getSize(); i++) {
            if (resumeArray[i].id == targetId) return &resumeArray[i];
        }
        return nullptr;
    }

    // Filter jobs whose title contains a keyword (case-insensitive using stored lowerCaseTitle)
    CustomArrayV2<Job> filterJobsByTitleKeyword(const CustomString& keyword) const {
        CustomArrayV2<Job> results;
        CustomString lowerKey = convertToLowerCase(keyword);
        for (int i = 0; i < jobArray.getSize(); i++) {
            const Job& j = jobArray[i];
            if (j.lowerCaseTitle.c_str() && lowerKey.c_str() && strstr(j.lowerCaseTitle.c_str(), lowerKey.c_str())) {
                results.push_back(j);
            }
        }
        return results;
    }

    void findTopMatchesForResume(const Resume& resume, int topN = 5) {
        CustomArrayV2<Job> matches;
        for (int i = 0; i < jobArray.getSize(); i++) {
            Job job = jobArray[i];
            job.matchScore = calculateWeightedMatchScore(job, resume);
            matches.push_back(job);
        }

        
        for (int i = 0; i < matches.getSize() - 1; i++) {
            for (int j = 0; j < matches.getSize() - i - 1; j++) {
                if (matches[j].matchScore < matches[j + 1].matchScore) {
                    Job temp = matches[j];
                    matches[j] = matches[j + 1];
                    matches[j + 1] = temp;
                }
            }
        }

        cout << "\n=== Top " << topN << " Matches for Resume " << resume.id << " ===" << endl;
        for (int i = 0; i < min(topN, matches.getSize()); i++) {
            cout << i + 1 << ". " << matches[i].jobTitle << " (Score: " << matches[i].matchScore << ")\n";
        }
    }

    // === Getters ===
    CustomArrayV2<Job>& getJobArray() { return jobArray; }
    CustomArrayV2<Resume>& getResumeArray() { return resumeArray; }
};
