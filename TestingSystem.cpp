#include "TestingSystem.h"

#include <iostream>

using namespace std;

TestingSystem::TestingSystem() {
}

TestingSystem::TestingSystem(const TestingSystem& orig) {
}

TestingSystem::~TestingSystem() {
}

void LoginUI()
{
    
}

void CreateTopicUI()
{
    // TODO: ask for a new question (loop), insert, calc total marks
}

void ModifyTopicUI()
{
    // TODO: print questions, ask for number to change (loop), ask for new question,
    // replace, calc total marks
}

int DeleteTopicUI()
{
    int id;
    cout << "Enter topic ID to delete: ";
    cin >> id;
    
    return id;
}

Question CreateQuestionUI()
{
    string question;
    vector<string> options;
    
    cout << "Enter question: ";
    cin >> question;
    
    bool done = false;
    while (!done)
    {
        string option;
        cout << "Enter an option: ";
        cin >> option;
        
        options.push_back(option);
        
        char cont;
        cout << "Add more options? (y/n) ";
        cin >> cont;
        
        done = cont == 'n';
    }
    
    char answer;
    cout << "Enter correct choice: ";
    cin >> answer;
    
    int marks;
    cout << "Enter marks: ";
    cin >> marks;
    
    Question q(question, options, answer, marks);    
    return q;
}

int DeleteQuestionUI()
{
    int index;
    cout << "Enter question number to delete: ";
    cin >> index;
    
    return index;
}