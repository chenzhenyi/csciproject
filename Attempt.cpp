/* 
 * File:   Attempt.cpp
 * Author: ethan
 * 
 * Created on August 6, 2014, 10:21 PM
 */

#include <vector>

#include "Attempt.h"
#include "Topic.h"

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

void Attempt::SetAnswers(vector<char> answers) {
    this->answers = answers;
}

vector<char> Attempt::GetAnswers() const {
    return answers;
}

int Attempt::CalculateTotalScore()
{
    int score = 0;
    
    // TODO: retrieve topic from Id
    Topic t;
    vector<Question> questions = t.GetQuestions();
    
    // at this point it is assumed that the topic retrived is the right
    // topic for the attempt
    for (int i=0; i<answers.size();i++)
    {
        if (questions[i].CheckAnswer(i))
            score += questions[i].GetMarks();
    }
    
    totalScore = score;
    return score;
}