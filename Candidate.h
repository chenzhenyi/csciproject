#ifndef CANDIDATE_H
#define	CANDIDATE_H

#include "User.h"

class Candidate: public User
{
public:
    Candidate();
    Candidate(const Candidate& orig);
    virtual ~Candidate();
    void SetTestAccountID(string testAccountID);
    string GetTestAccountID() const;
private:
    string testAccountID;
};

#endif	/* CANDIDATE_H */

