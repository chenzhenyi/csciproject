#ifndef TESTINGSYSTEM_H
#define	TESTINGSYSTEM_H

#include "DataStorage.h"

class TestingSystem {
public:
    TestingSystem();
    TestingSystem(const TestingSystem& orig);
    virtual ~TestingSystem();
    
    // IMPORTANT: *all* these UI methods are not allowed to alter any info in the DB
    // New data should be returned, and passed to actual data manipulation methods.
    void LoginUI();
    Topic CreateTopicUI();
    Topic ModifyTopicUI();
    /**
        Ask user for topic ID.

        @return topic Id to be deleted.
    */
    int DeleteTopicUI();
    Question CreateQuestionUI();
    int DeleteQuestionUI();
    void TakeTestUI();
    
private:
    DataStorage ds;
};

#endif	/* TESTINGSYSTEM_H */

