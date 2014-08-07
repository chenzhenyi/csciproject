#ifndef TESTINGSYSTEM_H
#define	TESTINGSYSTEM_H

#include "Candidate.h"
#include "Topic.h"

class TestingSystem {
public:
    TestingSystem();
    TestingSystem(const TestingSystem& orig);
    virtual ~TestingSystem();
    
    void LoginUI();
    void CreateTopicUI();
    void ModifyTopicUI();
    int DeleteTopicUI() const;
    Question CreateQuestionUI() const;
    int DeleteQuestionUI() const;
    
private:

};

#endif	/* TESTINGSYSTEM_H */

