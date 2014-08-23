#ifndef ATTEMPT_H
#define	ATTEMPT_H

#include <string>
#include <vector>
#include "Topic.h"

using namespace std;

class Attempt {
public:
    Attempt();
    virtual ~Attempt();
    
    void SetTotalScore(int totalScore);
    int GetTotalScore() const;
    void SetCandidateId(string candidateId);
    string GetCandidateId() const;
    void SetTopicId(int topicId);
    int GetTopicId() const;
    void SetAnswers(vector<char> answers);
    vector<char> GetAnswers() const;
    
    int CalculateTotalScore(Topic t);
    void PrintAttemptResult();
private:
    int topicId;
    string candidateId;
    int totalScore;
    vector<char> answers;
};

#endif	/* ATTEMPT_H */

