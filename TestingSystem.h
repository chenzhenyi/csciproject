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
    Topic CreateTopicUI() const;
    Topic ModifyTopicUI() const;
    /**
        Ask user for topic ID.

        @return topic Id to be deleted.
    */
    int DeleteTopicUI() const;
    Question CreateQuestionUI() const;
    int DeleteQuestionUI() const;
    void TakeTestUI();
    
private:
    DataStorage ds;
};

#endif	/* TESTINGSYSTEM_H */

