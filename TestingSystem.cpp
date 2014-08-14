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
    
    Attempt a;
    
    switch (choice)
    {
        case 1:
            a =TakeTestUI();
            a.SetCandidateId(candidate->GetTestAccountID());
            ds.WriteAttempt(a);
            break;
        case 2:
            ShowCandiateResults();
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
            t = CreateSingleQuestionUI();
            ds.WriteTopic(t);
            break;
        case 8:
            t = ModifySingleQuestionUI();
            ds.WriteTopic(t);
            break;
        case 9:
            t = DeleteSingleQuestionUI();
            ds.WriteTopic(t);
            break;
        case 10:
            ShowCandiateResults();
            break;
        case 11:
            ShowAllResults();
            break;
        case 0:
            return;
    }
    
    LecturerMainMenu(user);
}

Topic TestingSystem::ChooseTopicUI()
{
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
    
    return topic;
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
        cout << "Enter password: ";
        cin >> pw;

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
    Topic topic = ChooseTopicUI();
    
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
    Topic topic = ChooseTopicUI();
    
    return topic.GetId();
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

Attempt TestingSystem::TakeTestUI()
{
    Topic topic = ChooseTopicUI();
    
    vector<Question> questions = topic.GetQuestions();
    vector<char> answers;
    Attempt attempt;
    for (int i=0; i<questions.size(); i++)
    {
        char answer;
        questions[i].Print();
        cout << "Enter answer: ";
        cin >> answer;
        answers.push_back(answer);
        
        cout << endl;
    }
    
    attempt.SetTopicId(topic.GetId());
    attempt.SetAnswers(answers);
    attempt.CalculateTotalScore();
    
    cout << "Total score: " << attempt.GetTotalScore() << endl;
    
    return attempt;
    //ds.WriteAttempt(attempt);
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

void TestingSystem::ShowCandiateResults()
{
    string testAccountID;
    cout << "Enter candidate's test account ID: ";
    cin >> testAccountID;
    
    vector<Attempt> attempts = ds.RetreiveAttempts(testAccountID);
    
    for (int i=0; i<attempts.size(); i++)
    {
        attempts[i].PrintAttemptResult();
    }
}

void TestingSystem::ShowAllResults()
{
    vector<Attempt> attempts = ds.RetreiveAllAttempts();
    for (int i=0; i<attempts.size(); i++)
    {
        attempts[i].PrintAttemptResult();
    }
}

Topic TestingSystem::CreateSingleQuestionUI()
{
    Topic topic = ChooseTopicUI();
    
    bool validQuestion = false;
    int questionNumber;

    while(!validQuestion)
    {
        int count = topic.GetQuestions().size();
        cout << "Enter question number (0-" << count-1 << "): ";
        cin >> questionNumber;
        
        validQuestion = questionNumber < 0 || questionNumber > count-1;
        if (!validQuestion)
            cout << "Invalid question number." << endl;
    }
    
    Question question = CreateQuestionUI();
    
    vector<Question> questions = topic.GetQuestions();
    questions.push_back(question);
    topic.SetQuestions(questions);
    
    return topic;
}

Topic TestingSystem::ModifySingleQuestionUI()
{
    Topic topic = ChooseTopicUI();
    
    bool validQuestion = false;
    int questionNumber;

    while(!validQuestion)
    {
        int count = topic.GetQuestions().size();
        cout << "Enter question number (0-" << count-1 << "): ";
        cin >> questionNumber;
        
        validQuestion = questionNumber < 0 || questionNumber > count-1;
        if (!validQuestion)
            cout << "Invalid question number." << endl;
    }
    
    Question question = CreateQuestionUI();
    
    vector<Question> questions = topic.GetQuestions();
    questions[questionNumber] = question;
    topic.SetQuestions(questions);
    
    return topic;
}

Topic TestingSystem::DeleteSingleQuestionUI()
{
    Topic topic = ChooseTopicUI();
    
    bool validQuestion = false;
    int questionNumber;

    while(!validQuestion)
    {
        int count = topic.GetQuestions().size();
        cout << "Enter question number (0-" << count-1 << "): ";
        cin >> questionNumber;
        
        validQuestion = questionNumber < 0 || questionNumber > count-1;
        if (!validQuestion)
            cout << "Invalid question number." << endl;
    }
    
    vector<Question> questions = topic.GetQuestions();
    questions.erase(questions.begin() + questionNumber);
    topic.SetQuestions(questions);
    
    return topic;
}