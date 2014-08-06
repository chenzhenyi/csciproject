/* 
 * File:   Candidate.cpp
 * Author: ethan
 * 
 * Created on August 6, 2014, 9:53 PM
 */

#include "Candidate.h"

Candidate::Candidate() {
}

Candidate::Candidate(const Candidate& orig) {
}

Candidate::~Candidate() {
}

void Candidate::SetTestAccountID(string testAccountID) {
    this->testAccountID = testAccountID;
}

string Candidate::GetTestAccountID() const {
    return testAccountID;
}

