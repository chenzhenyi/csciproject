#ifndef ATTEMPT_H
#define	ATTEMPT_H

#include <string>
#include <vector>

using namespace std;

class Attempt {
public:
    Attempt();
    Attempt(const Attempt& orig);
    virtual ~Attempt();
    
    void SetTotalScore(int totalScore);
    int GetTotalScore() const;
    void SetCandidateId(string candidateId);
    string GetCandidateId() const;
    void SetTopicId(int topicId);
    int GetTopicId() const;
    void SetAnswers(vector<char> answers);
    vector<char> GetAnswers() const;
    
    int CalculateTotalScore();
    void PrintAttemptResult();
private:
    int topicId;
    string candidateId;
    int totalScore;
    vector<char> answers;
};

#endif	/* ATTEMPT_H */

