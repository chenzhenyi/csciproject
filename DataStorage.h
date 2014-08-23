#ifndef DATASTORAGE_H
#define	DATASTORAGE_H

#include "Attempt.h"
#include "Topic.h"
#include "Candidate.h"
#include <string>

class DataStorage {
public:
    DataStorage();
    virtual ~DataStorage();
    
    /**
        Get topic data with given id.

        @param topicId ID of the topic.
        @param topic refenrece to output variable where retrieved topic is passed back.
        @return true if a topic with matching id exists, false otherwise.
    */
    bool RetrieveTopic(int topicId, Topic& topic);
    
    bool DeleteTopic(int topicId);
    
    /**
        Get test attempts done by a student with given ID.

        @param studentId test account ID of student.
        @return vector of attempts.
    */
    vector<Attempt> RetreiveAttempts(string studentId);
    
    vector<Attempt> RetreiveAllAttempts();
    bool CheckLogin(string username, string pw);
    
    /**
        Get user information. If the user is a candidate, 
        it will be casted to an User pointer.

        @param username username.
        @return A pointer to User object.
    */
    User* RetrieveUser(string username);
    bool DeleteUser(string username);
    
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
	bool isOpenDB = false;
	int doQuery(string s);
        string encryptDecrypt(string toEncrypt);
    
};

#endif	/* DATASTORAGE_H */

