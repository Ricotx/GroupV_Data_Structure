#pragma once
#include "model.hpp"
#include <cstring>

using namespace std;

// Build a keyword list as CustomArray<CustomString>
inline CustomArray<CustomString> buildDefaultKeywords() {
    CustomArray<CustomString> keywords;
    keywords.push_back(CustomString("c++"));
    keywords.push_back(CustomString("python"));
    keywords.push_back(CustomString("java"));
    keywords.push_back(CustomString("teamwork"));
    keywords.push_back(CustomString("communication"));
    return keywords;
}

// Return 1 if both texts contain keyword (case-insensitive, expects lower-cased inputs upstream)
inline bool containsKeyword(const CustomString& text, const CustomString& keyword) {
    if (text.c_str() == nullptr || keyword.c_str() == nullptr) return false;
    return strstr(text.c_str(), keyword.c_str()) != nullptr;
}

// Calculate simple match score: number of keywords present in both texts
inline int calculateMatchScore(const CustomString& jobDesc,
                               const CustomString& resumeText,
                               const CustomArray<CustomString>& keywords = buildDefaultKeywords()) {
    int score = 0;
    for (int i = 0; i < keywords.size(); i++) {
        if (containsKeyword(jobDesc, keywords[i]) && containsKeyword(resumeText, keywords[i])) {
            score++;
        }
    }
    return score;
}

// Efficient multiple comparisons: pre-lowercased inputs recommended by preprocessor
inline void computeScoresForAllPairs(const CustomArrayV2<Job>& jobs,
                                     const CustomArrayV2<Resume>& resumes,
                                     CustomArrayV2<Job>& outJobsWithScores,
                                     const CustomArray<CustomString>& keywords = buildDefaultKeywords()) {
    // Copy jobs then assign matchScore as the max keyword overlap against any resume
    for (int i = 0; i < jobs.getSize(); i++) {
        Job j = jobs[i];
        int bestScore = 0;
        for (int r = 0; r < resumes.getSize(); r++) {
            int score = calculateMatchScore(j.fullDescription, resumes[r].fullDescription, keywords);
            if (score > bestScore) bestScore = score;
        }
        j.matchScore = static_cast<double>(bestScore);
        outJobsWithScores.push_back(j);
    }
}
