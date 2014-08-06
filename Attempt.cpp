/* 
 * File:   Attempt.cpp
 * Author: ethan
 * 
 * Created on August 6, 2014, 10:21 PM
 */

#include "Attempt.h"

Attempt::Attempt() {
}

Attempt::Attempt(const Attempt& orig) {
}

Attempt::~Attempt() {
}

void Attempt::SetTotalScore(int totalScore) {
    this->totalScore = totalScore;
}

int Attempt::GetTotalScore() const {
    return totalScore;
}

void Attempt::SetCandidateId(string candidateId) {
    this->candidateId = candidateId;
}

string Attempt::GetCandidateId() const {
    return candidateId;
}

void Attempt::SetTopicId(int topicId) {
    this->topicId = topicId;
}

int Attempt::GetTopicId() const {
    return topicId;
}

