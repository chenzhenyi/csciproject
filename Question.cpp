#include "Question.h"

Question::Question() {
}

Question::Question(const Question& orig) {
}

Question::~Question() {
}

void Question::SetMarks(int marks) {
    this->marks = marks;
}

int Question::GetMarks() const {
    return marks;
}

void Question::SetAnswer(char answer) {
    this->answer = answer;
}

char Question::GetAnswer() const {
    return answer;
}

void Question::SetOptions(vector<string> options) {
    this->options = options;
}

vector<string> Question::GetOptions() const {
    return options;
}

void Question::SetQuestion(string question) {
    this->question = question;
}

string Question::GetQuestion() const {
    return question;
}

