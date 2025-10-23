#pragma once
#include "model.hpp"
#include "array.hpp"
#include "readcsv.hpp"
#include "preprocessor.hpp"
#include "matching.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstring>
#include <chrono>

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
            for (int j = 0; j < job.lowerCaseSkills.size(); j++) {
                CustomString skill = job.lowerCaseSkills[j];
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

        cout << "Built valid skillset with " << skillset.size() << " unique skills.\n";
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

        cout << "Loaded " << jobArray.getSize() << " jobs and " << resumeArray.getSize() << " resumes." << endl;
        return true;
    }

    
    void displaySampleData(int n = 10) const {
        cout << "\n=== DATA SUMMARY ===" << endl;
        cout << "Total Jobs Loaded: " << jobArray.getSize() << endl;
        cout << "Total Resumes Loaded: " << resumeArray.getSize() << endl;
        cout << "Displaying " << min(n, jobArray.getSize()) << " jobs and " << min(n, resumeArray.getSize()) << " resumes..." << endl;
        
        cout << "\n=== SAMPLE JOBS ===" << endl;
        for (int i = 0; i < min(n, jobArray.getSize()); i++)
            jobArray[i].display();

        cout << "\n=== SAMPLE RESUMES ===" << endl;
        for (int i = 0; i < min(n, resumeArray.getSize()); i++)
            resumeArray[i].display();
            
        if (jobArray.getSize() > n || resumeArray.getSize() > n) {
            cout << "\n... and " << (jobArray.getSize() - n) << " more jobs, " << (resumeArray.getSize() - n) << " more resumes available." << endl;
        }
    }

   
    void bubbleSortJobsByTitle() {
        int n = jobArray.getSize();
        cout << "Sorting " << n << " jobs by title... This may take a moment." << endl;
        
        auto start = chrono::high_resolution_clock::now();
        
        for (int i = 0; i < n - 1; i++) {
            bool swapped = false;
            
            // Show progress every 5000 iterations for large datasets
            if (i % 5000 == 0) {
                cout << "Progress: " << (i * 100) / (n - 1) << "%" << endl;
            }
            
            for (int j = 0; j < n - i - 1; j++) {
                if (strcmp(jobArray[j].jobTitle.c_str(), jobArray[j + 1].jobTitle.c_str()) > 0) {
                    Job temp = jobArray[j];
                    jobArray[j] = jobArray[j + 1];
                    jobArray[j + 1] = temp;
                    swapped = true;
                }
            }
            
            // Early termination if no swaps occurred
            if (!swapped) {
                cout << "Early termination: Array already sorted!" << endl;
                break;
            }
        }
        
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        
        cout << "Sorting complete! Time taken: " << duration.count() << " ms" << endl;
    }

    void bubbleSortJobsBySkillCount() {
        int n = jobArray.getSize();
        cout << "Sorting " << n << " jobs by skill count... This may take a moment." << endl;
        
        auto start = chrono::high_resolution_clock::now();
        
        for (int i = 0; i < n - 1; i++) {
            bool swapped = false;
            
            // Show progress every 5000 iterations for large datasets
            if (i % 5000 == 0) {
                cout << "Progress: " << (i * 100) / (n - 1) << "%" << endl;
            }
            
            for (int j = 0; j < n - i - 1; j++) {
                if (jobArray[j].skillCount > jobArray[j + 1].skillCount) {
                    Job temp = jobArray[j];
                    jobArray[j] = jobArray[j + 1];
                    jobArray[j + 1] = temp;
                    swapped = true;
                }
            }
            
            // Early termination if no swaps occurred
            if (!swapped) {
                cout << "Early termination: Array already sorted!" << endl;
                break;
            }
        }
        
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        
        cout << "Sorting complete! Time taken: " << duration.count() << " ms" << endl;
    }

    void bubbleSortResumesBySkillCount() {
        int n = resumeArray.getSize();
        cout << "Sorting " << n << " resumes by skill count... This may take a moment." << endl;
        
        auto start = chrono::high_resolution_clock::now();
        
        for (int i = 0; i < n - 1; i++) {
            bool swapped = false;
            
            // Show progress every 5000 iterations for large datasets
            if (i % 5000 == 0) {
                cout << "Progress: " << (i * 100) / (n - 1) << "%" << endl;
            }
            
            for (int j = 0; j < n - i - 1; j++) {
                if (resumeArray[j].skillCount > resumeArray[j + 1].skillCount) {
                    Resume temp = resumeArray[j];
                    resumeArray[j] = resumeArray[j + 1];
                    resumeArray[j + 1] = temp;
                    swapped = true;
                }
            }
            
            // Early termination if no swaps occurred
            if (!swapped) {
                cout << "Early termination: Array already sorted!" << endl;
                break;
            }
        }
        
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        
        cout << "Sorting complete! Time taken: " << duration.count() << " ms" << endl;
    }

    // QuickSort implementation for jobs by skill count
    void quickSortJobsBySkillCount() {
        quickSortJobsBySkillCountHelper(0, jobArray.getSize() - 1);
    }

private:
    void quickSortJobsBySkillCountHelper(int low, int high) {
        if (low < high) {
            int pivotIndex = partitionJobsBySkillCount(low, high);
            quickSortJobsBySkillCountHelper(low, pivotIndex - 1);
            quickSortJobsBySkillCountHelper(pivotIndex + 1, high);
        }
    }

    int partitionJobsBySkillCount(int low, int high) {
        int pivot = jobArray[high].skillCount;
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (jobArray[j].skillCount <= pivot) {
                i++;
                Job temp = jobArray[i];
                jobArray[i] = jobArray[j];
                jobArray[j] = temp;
            }
        }
        
        Job temp = jobArray[i + 1];
        jobArray[i + 1] = jobArray[high];
        jobArray[high] = temp;
        
        return i + 1;
    }

public:
    // MergeSort implementation for jobs by skill count
    void mergeSortJobsBySkillCount() {
        mergeSortJobsBySkillCountHelper(0, jobArray.getSize() - 1);
    }

private:
    void mergeSortJobsBySkillCountHelper(int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSortJobsBySkillCountHelper(left, mid);
            mergeSortJobsBySkillCountHelper(mid + 1, right);
            mergeJobsBySkillCount(left, mid, right);
        }
    }

    void mergeJobsBySkillCount(int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        
        // Create temporary arrays
        Job* leftArray = new Job[n1];
        Job* rightArray = new Job[n2];
        
        // Copy data to temporary arrays
        for (int i = 0; i < n1; i++) {
            leftArray[i] = jobArray[left + i];
        }
        for (int j = 0; j < n2; j++) {
            rightArray[j] = jobArray[mid + 1 + j];
        }
        
        // Merge the temporary arrays back
        int i = 0, j = 0, k = left;
        
        while (i < n1 && j < n2) {
            if (leftArray[i].skillCount <= rightArray[j].skillCount) {
                jobArray[k] = leftArray[i];
                i++;
            } else {
                jobArray[k] = rightArray[j];
                j++;
            }
            k++;
        }
        
        // Copy remaining elements
        while (i < n1) {
            jobArray[k] = leftArray[i];
            i++;
            k++;
        }
        while (j < n2) {
            jobArray[k] = rightArray[j];
            j++;
            k++;
        }
        
        // Clean up temporary arrays
        delete[] leftArray;
        delete[] rightArray;
    }

public:
    // Memory estimation functions
    size_t estimateMemoryUsage() const {
        size_t totalMemory = 0;
        
        // Job array memory
        totalMemory += jobArray.getCapacity() * sizeof(Job);
        
        // Resume array memory
        totalMemory += resumeArray.getCapacity() * sizeof(Resume);
        
        // Additional memory for strings and arrays within Job/Resume objects
        for (int i = 0; i < jobArray.getSize(); i++) {
            const Job& job = jobArray[i];
            totalMemory += job.jobTitle.size() + 1; // +1 for null terminator
            totalMemory += job.fullDescription.size() + 1;
            totalMemory += job.lowerCaseTitle.size() + 1;
            totalMemory += job.jobCategory.size() + 1;
            
            // Skills arrays
            for (int j = 0; j < job.skills.size(); j++) {
                totalMemory += job.skills[j].size() + 1;
            }
            for (int j = 0; j < job.lowerCaseSkills.size(); j++) {
                totalMemory += job.lowerCaseSkills[j].size() + 1;
            }
        }
        
        for (int i = 0; i < resumeArray.getSize(); i++) {
            const Resume& resume = resumeArray[i];
            totalMemory += resume.fullDescription.size() + 1;
            
            // Resume skills arrays
            for (int j = 0; j < resume.resumeSkills.size(); j++) {
                totalMemory += resume.resumeSkills[j].size() + 1;
            }
            for (int j = 0; j < resume.lowerCaseSkills.size(); j++) {
                totalMemory += resume.lowerCaseSkills[j].size() + 1;
            }
        }
        
        return totalMemory;
    }
    
    void printMemoryStats() const {
        size_t memoryUsage = estimateMemoryUsage();
        cout << "\n=== MEMORY USAGE STATISTICS ===" << endl;
        cout << "Total Memory Usage: " << memoryUsage << " bytes (" << (memoryUsage / 1024.0 / 1024.0) << " MB)" << endl;
        cout << "Job Array Capacity: " << jobArray.getCapacity() << " elements" << endl;
        cout << "Job Array Size: " << jobArray.getSize() << " elements" << endl;
        cout << "Resume Array Capacity: " << resumeArray.getCapacity() << " elements" << endl;
        cout << "Resume Array Size: " << resumeArray.getSize() << " elements" << endl;
        cout << "Memory Efficiency: " << ((double)(jobArray.getSize() + resumeArray.getSize()) / (jobArray.getCapacity() + resumeArray.getCapacity())) * 100 << "%" << endl;
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

    // Search jobs by skill
    CustomArrayV2<Job> searchJobsBySkill(const CustomString& skill) {
        CustomArrayV2<Job> results;
        CustomString lowerSkill = convertToLowerCase(skill);
        
        for (int i = 0; i < jobArray.getSize(); i++) {
            const Job& job = jobArray[i];
            for (int j = 0; j < job.skills.size(); j++) {
                CustomString jobSkill = convertToLowerCase(job.skills[j]);
                if (strcmp(jobSkill.c_str(), lowerSkill.c_str()) == 0) {
                    results.push_back(job);
                    break; // Found the skill, no need to check other skills for this job
                }
            }
        }
        return results;
    }

    // Search resumes by skill
    CustomArrayV2<Resume> searchResumesBySkill(const CustomString& skill) {
        CustomArrayV2<Resume> results;
        CustomString lowerSkill = convertToLowerCase(skill);
        
        for (int i = 0; i < resumeArray.getSize(); i++) {
            const Resume& resume = resumeArray[i];
            for (int j = 0; j < resume.resumeSkills.size(); j++) {
                CustomString resumeSkill = convertToLowerCase(resume.resumeSkills[j]);
                if (strcmp(resumeSkill.c_str(), lowerSkill.c_str()) == 0) {
                    results.push_back(resume);
                    break; // Found the skill, no need to check other skills for this resume
                }
            }
        }
        return results;
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
        cout << "\n=== Finding Job Matches for Resume " << resume.id << " ===" << endl;
        cout << "Processing " << jobArray.getSize() << " jobs..." << endl;
        
        auto start = chrono::high_resolution_clock::now();
        
        CustomArrayV2<Job> matches;
        for (int i = 0; i < jobArray.getSize(); i++) {
            Job job = jobArray[i];
            job.matchScore = calculateWeightedMatchScore(job, resume);
            matches.push_back(job);
        }

        // Sort by match score (QuickSort for better performance)
        quickSortJobsByMatchScore(matches, 0, matches.getSize() - 1);
        
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

        cout << "\n=== Top " << topN << " Job Matches for Resume " << resume.id << " ===" << endl;
        cout << "Resume Skills: ";
        for (int i = 0; i < resume.resumeSkills.size(); i++) {
            cout << resume.resumeSkills[i];
            if (i < resume.resumeSkills.size() - 1) cout << ", ";
        }
        cout << endl << endl;
        
        // Display top N different jobs with full details
        int displayed = 0;
        for (int i = 0; i < matches.getSize() && displayed < topN; i++) {
            cout << "Match " << (displayed + 1) << ":" << endl;
            cout << "Job ID: " << matches[i].id << endl;
            cout << "Title: " << matches[i].jobTitle << endl;
            cout << "Skills (" << matches[i].skillCount << "): ";
            for (int j = 0; j < matches[i].skills.size(); j++) {
                cout << matches[i].skills[j];
                if (j < matches[i].skills.size() - 1) cout << ", ";
            }
            cout << endl;
            cout << "Category: " << matches[i].jobCategory << endl;
            cout << "Priority: " << matches[i].priority << endl;
            cout << "Match Score: " << fixed << setprecision(6) << matches[i].matchScore << endl;
            cout << "---" << endl;
            displayed++;
        }
        
        cout << "\nJob matching completed in: " << duration.count() << " ms" << endl;
    }

    // === Getters ===
    CustomArrayV2<Job>& getJobArray() { return jobArray; }
    CustomArrayV2<Resume>& getResumeArray() { return resumeArray; }

    // QuickSort for job matching (by match score)
    void quickSortJobsByMatchScore(CustomArrayV2<Job>& jobs, int low, int high) {
        if (low < high) {
            int pivotIndex = partitionJobsByMatchScore(jobs, low, high);
            quickSortJobsByMatchScore(jobs, low, pivotIndex - 1);
            quickSortJobsByMatchScore(jobs, pivotIndex + 1, high);
        }
    }
    
    int partitionJobsByMatchScore(CustomArrayV2<Job>& jobs, int low, int high) {
        double pivot = jobs[high].matchScore;
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (jobs[j].matchScore >= pivot) { // Descending order
                i++;
                Job temp = jobs[i];
                jobs[i] = jobs[j];
                jobs[j] = temp;
            }
        }
        Job temp = jobs[i + 1];
        jobs[i + 1] = jobs[high];
        jobs[high] = temp;
        return i + 1;
    }

private:
    double calculateWeightedMatchScore(const Job& job, const Resume& resume) {
        int matchCount = 0;
        int resumeSkillsUsed = 0;
        
        // Count matching skills
        for (int i = 0; i < job.skills.size(); i++) {
            for (int j = 0; j < resume.resumeSkills.size(); j++) {
                if (strcmp(job.skills[i].c_str(), resume.resumeSkills[j].c_str()) == 0) {
                    matchCount++;
                    break; // Found match, move to next job skill
                }
            }
        }
        
        // Count how many resume skills are utilized
        for (int j = 0; j < resume.resumeSkills.size(); j++) {
            for (int i = 0; i < job.skills.size(); i++) {
                if (strcmp(resume.resumeSkills[j].c_str(), job.skills[i].c_str()) == 0) {
                    resumeSkillsUsed++;
                    break; // Found match, move to next resume skill
                }
            }
        }
        
        if (job.skills.size() == 0 || resume.resumeSkills.size() == 0)
            return 0.0;
        
        // Calculate base score (job skill coverage)
        double jobCoverage = (double)matchCount / job.skills.size();
        
        // Calculate resume utilization bonus
        double resumeUtilization = (double)resumeSkillsUsed / resume.resumeSkills.size();
        
        // Calculate total matching skills bonus (more matches = higher score)
        double matchBonus = (double)matchCount / max(job.skills.size(), resume.resumeSkills.size());
        
        // Calculate skill density bonus (jobs with more skills get slight bonus)
        double skillDensityBonus = (double)job.skills.size() / 10.0; // Normalize to 0-1 range
        
        // Weighted combination: 40% job coverage + 25% resume utilization + 20% match bonus + 15% skill density
        double finalScore = (0.4 * jobCoverage) + (0.25 * resumeUtilization) + (0.2 * matchBonus) + (0.15 * skillDensityBonus);
        
        // Add tiny tie-breaker based on job ID to ensure different scores
        double tieBreaker = (double)job.id / 100000.0; // Very small adjustment
        finalScore += tieBreaker;
        
        return finalScore;
    }
};
