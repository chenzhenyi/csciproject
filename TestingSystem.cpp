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

void TestingSystem::CandidateMainMenu(Candidate* candidate)
{
    cout << "1. Take test" << endl;
    cout << "2. View test results" << endl;
    cout << "0. Quit" << endl;
    
    int choice;
    cin >> choice;
    
    switch (choice)
    {
        case 1:
            TakeTestUI();
            break;
        case 2:
            
            break;
        case 0:
            return;
    }
    
    CandidateMainMenu(candidate);
}

void TestingSystem::LecturerMainMenu(User* user)
{
    cout << "1. Create Candiate" << endl;
    cout << "2. Modify Candidate" << endl;
    cout << "3. Delete candidate" << endl;
    cout << "4. Create test topic" << endl;
    cout << "5. Modify test topic" << endl;
    cout << "6. Delete test topic" << endl;
    cout << "7. Create test question" << endl;
    cout << "8. Modify test question" << endl;
    cout << "9. Delete test topic" << endl;
    cout << "10. View candidate's test result" << endl;
    cout << "11. View results summary" << endl;
    cout << "0. Quit" << endl;
    
    int choice;
    cin >> choice;
    
    Topic t;
    int id;
    Candidate c;
    string username;
    
    switch (choice)
    {
        case 1:
            c = CreateCandiateUI();
            ds.WriteCandidate(c);
            break;
        case 2:
            c = ModifyCandidateUI();
            ds.WriteCandidate(c);
            break;
        case 3:
            username = DeleteCandidateUI();
            ds.DeleteUser(username);
            break;
        case 4:
            t = CreateTopicUI();
            ds.WriteTopic(t);
            break;
        case 5:
            t = ModifyTopicUI();
            ds.WriteTopic(t);
            break;
        case 6:
            id = DeleteTopicUI();
            ds.DeleteTopic(id);
            break;
        case 7:
            // TODO
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            break;
        case 0:
            return;
    }
    
    LecturerMainMenu(user);
}

void TestingSystem::LoginUI()
{
    string username;
    string pw;
    bool success = false;
    
    while (!success)
    {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter username: ";
        cin >> username;

        success = ds.CheckLogin(username, pw);
        
        if (!success)
            cout << "Wrong username or password." << endl;
    }
    
    User* user = ds.RetrieveUser(username);
    
    if (user->GetType() == 1)
    {
        Candidate* candidate = (Candidate*)user;
        CandidateMainMenu(candidate);
    }
    else
    {
        LecturerMainMenu(user);
    }
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

Candidate TestingSystem::CreateCandiateUI()
{
    
}
    
Candidate TestingSystem::ModifyCandidateUI()
{
    
}
    
string TestingSystem::DeleteCandidateUI()
{
    string username;
    cout << "Enter candidate's username: ";
    cin >> username;
    
    return username;
}

void TestingSystem::ShowCanddiateResults()
{
    string testAccountID;
    cout << "Enter candidate's test account ID: ";
    cin >> testAccountID;
    
    vector<Attempt> attempts = ds.RetreiveAttempts(testAccountID);
    
    for (int i=0; i<attempts.size(); i++)
    {
        // TODO
    }
}

void TestingSystem::ShowAllResutls()
{
    vector<Attempt> attempts = ds.RetreiveAllAttempts();
    for (int i=0; i<attempts.size(); i++)
    {
        // TODO
    }
}