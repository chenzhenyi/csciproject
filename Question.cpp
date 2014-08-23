#include "Question.h"

#include <iostream>

using namespace std;

Question::Question() {
}

Question::Question(string question, vector<string> options, char answer, int marks):
        question(question), options(options), answer(answer), marks(marks)
{
    
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

bool Question::CheckAnswer(char answer)
{
    return answer == this->answer;
}
    
void Question::Print()
{
    cout << question << endl;
    
    for (int i=0; i < options.size(); i++)
    {
        cout << (char)('a' + i) << options[i] << endl;
    }
}

void Question::SetId(int id) {
    this->id = id;
}

int Question::GetId() const {
    return id;
}