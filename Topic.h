/* 
 * File:   Topic.h
 * Author: ethan
 *
 * Created on August 6, 2014, 10:00 PM
 */

#ifndef TOPIC_H
#define	TOPIC_H

#include <vector>
#include "Question.h"

using namespace std;

class Topic {
public:
    Topic();
    Topic(const Topic& orig);
    virtual ~Topic();
    
    void SetTotalMarks(int totalMarks);
    int GetTotalMarks() const;
    void SetQuestions(vector<Question> questions);
    vector<Question> GetQuestions() const;
    void SetType(int type);
    int GetType() const;
    void SetId(int id);
    int GetId() const;
private:
    int id;
    int type;
    vector<Question> questions;
    int totalMarks;
};

#endif	/* TOPIC_H */

