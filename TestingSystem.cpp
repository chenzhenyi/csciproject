#include "TestingSystem.h"
#include "Topic.h"

#include <iostream>

using namespace std;

TestingSystem::TestingSystem() {
}

TestingSystem::TestingSystem(const TestingSystem& orig) {
}

TestingSystem::~TestingSystem() {
}

void TestingSystem::LoginUI()
{
    
}

Topic TestingSystem::CreateTopicUI()
{
    // TODO: ask for a new question (loop), insert, calc total marks
    Topic topic;
    
    bool done = false;
    while (!done)
    {
        int questionNo; // index, starts from 0
        cout << "Enter a new question: ";
        cin >> questionNo;
        
        // simply create new question and over write the old one
        Question q = CreateQuestionUI();
        topic.ReplaceQuestion(questionNo, q);
    }
    
    topic.CalcTotalMarks();
    return topic;
}

Topic TestingSystem::ModifyTopicUI()
{
    // TODO: print questions, ask for number to change (loop), ask for new question,
    // replace, calc total marks
    bool validTopic = false;
    Topic topic;
    while(!validTopic)
    {
        int topicId;
        cout << "Enter topic ID: ";
        cin >> topicId;

        validTopic = ds.RetrieveTopic(topicId, topic);
        
        if (!validTopic)
            cout << "Invalid topic ID etered";
    }
    
    bool done = false;
    while (!done)
    {
        int questionNo; // index, starts from 0
        cout << "Enter topic question number to modify (0-" << topic.GetQuestions().size()-1 << "): ";
        cin >> questionNo;
        
        // simply create new question and over write the old one
        Question q = CreateQuestionUI();
        topic.ReplaceQuestion(questionNo, q);
    }
    
    topic.CalcTotalMarks();
    return topic;
}

int TestingSystem::DeleteTopicUI()
{
    int id;
    cout << "Enter topic ID to delete: ";
    cin >> id;
    
    return id;
}

Question TestingSystem::CreateQuestionUI()
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

int TestingSystem::DeleteQuestionUI()
{
    int index;
    cout << "Enter question number to delete: ";
    cin >> index;
    
    return index;
}

void TestingSystem::TakeTestUI()
{
    
}