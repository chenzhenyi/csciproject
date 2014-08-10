/* 
 * File:   DataStorage.h
 * Author: ethan
 *
 * Created on August 10, 2014, 10:36 AM
 */

#ifndef DATASTORAGE_H
#define	DATASTORAGE_H

#include "Attempt.h"

class DataStorage {
public:
    DataStorage();
    DataStorage(const DataStorage& orig);
    virtual ~DataStorage();
    
    /**
        Get topic data with given id.

        @param topicId ID of the topic.
        @param topic refenrece to output variable where retrieved topic is passed back.
        @return true if a topic with matching id exists, false otherwise.
    */
    bool RetrieveTopic(int topicId, Topic& topic);
    
    /**
        Get test attempts done by a student with given ID.

        @param studentId test account ID of student.
        @return vector of attempts.
    */
    vector<Attempt> RetreiveAttempts(int studentId);
    
    vector<Attempt> RetreiveAllAttempts();
    bool CheckLogin(string username, string pw);
    
    /**
        Write out an topic. If the topic passed in has an ID already exists in
        the database, it will overwrite the old row.

        @param topic topic to be written.
        @return none.
    */
    void WriteTopic(Topic topic);
    void WriteCandidate(Candidate candidate);
    void WriteUser(User user);
    void WriteAttempt(Attempt attempt);
private:
    
};

#endif	/* DATASTORAGE_H */

