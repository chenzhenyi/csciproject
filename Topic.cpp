#include "Topic.h"

#include <iostream>

using namespace std;

Topic::Topic() {
}

Topic::Topic(const Topic& orig) {
}

Topic::~Topic() {
}

void Topic::SetTotalMarks(int totalMarks) {
    this->totalMarks = totalMarks;
}

int Topic::GetTotalMarks() const {
    return totalMarks;
}

void Topic::SetQuestions(vector<Question> questions) {
    this->questions = questions;
}

vector<Question> Topic::GetQuestions() const {
    return questions;
}

void Topic::SetType(int type) {
    this->type = type;
}

int Topic::GetType() const {
    return type;
}

void Topic::SetId(int id) {
    this->id = id;
}

int Topic::GetId() const {
    return id;
}

void Topic::CalcTotalMarks()
{
    int total = 0;
    for (int i=0; i<questions.size(); i++)
        total += questions[i].GetMarks();
    
    totalMarks = total;
}

void Topic::AddQuestion(Question question){
    questions.push_back(question);
    CalcTotalMarks();
}

bool Topic::RemoveQuestion(int index){
    if (index < 0 || index > questions.size())
    {
        cout << "Invalid question index";
        return false;
    }
    
    questions.erase(questions.begin() + index);
    CalcTotalMarks();
    return true;
}

bool Topic::ReplaceQuestion(int index, Question question){
    if (index < 0 || index > questions.size())
    {
        cout << "Invalid question index";
        return false;
    }
    
    questions[index] = question;
    CalcTotalMarks();
    return true;
}

void Topic::PrintQuestion(int index){
    if (index < 0 || index > questions.size())
    {
        cout << "Invalid question index";
        return;
    }
    
    questions[index].Print();
}