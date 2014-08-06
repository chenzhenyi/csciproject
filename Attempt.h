#ifndef ATTEMPT_H
#define	ATTEMPT_H

#include <string>

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
private:
    int topicId;
    string candidateId;
    int totalScore;
};

#endif	/* ATTEMPT_H */

