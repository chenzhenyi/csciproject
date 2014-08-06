#include "Topic.h"

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

