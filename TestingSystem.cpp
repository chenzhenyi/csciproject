#include "TestingSystem.h"
#include "Topic.h"

#include <iostream>

using namespace std;

TestingSystem::TestingSystem() {
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
    cout << "9. Delete test question" << endl;
    cout << "10. View candidate's test result" << endl;
    cout << "11. View results summary" << endl;
    cout << "0. Quit" << endl;
    
    int choice;
    cin >> choice;
    
    Topic t;
    int id;
    Candidate c;
    string username;
    Candidate *pc;
    
    switch (choice)
    {
        case 1:
            c = CreateCandiateUI();
            ds.WriteCandidate(c);
            break;
        case 2:
            pc = ModifyCandidateUI();
            if (pc != NULL)
                ds.WriteCandidate(*pc);
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
            ds.ModifyTopic(t);
            for (int i=0; i<t.GetQuestions().size(); i++)
            {
                ds.ModifyQuestion(t.GetQuestions()[i]);
            }
            break;
        case 6:
            id = DeleteTopicUI();
            ds.DeleteTopic(id);
            break;
        case 7:
            t = CreateSingleQuestionUI();
            ds.ModifyTopic(t);            
            break;
        case 8:
            t = ModifySingleQuestionUI();
            ds.ModifyTopic(t);
            break;
        case 9:
            t = DeleteSingleQuestionUI();
            ds.ModifyTopic(t);
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
    Topic topic;
    
    bool done = false;
    while (!done)
    {      
        Question q = CreateQuestionUI();
        
        topic.AddQuestion(q);
        
        char cont;
        cout << "Add more questions? (y/n) ";
        cin >> cont;
        
        done = cont == 'n';
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
        cout << "Enter topic question number to modify (0 to " << topic.GetQuestions().size()-1 << ", -1 to quit): ";
        cin >> questionNo;
        
        done = questionNo == -1;
        
        if (done)
            break;
        
        Question oldQuestion = topic.GetQuestions()[questionNo];
        oldQuestion.Print();        
        
        // simply create new question and over write the old one
        Question q = CreateQuestionUI();
        q.SetId(oldQuestion.GetId());
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
    std::getline(std::cin, question); // hack
    cout << "Enter question: ";
    std::getline(std::cin, question);
    
    bool done = false;
    while (!done)
    {
        string option;
        cout << "Enter an option: ";
        std::getline(std::cin, option);
        
        options.push_back(option);
        
        char cont;
        cout << "Add more options? (y/n) ";
        cin >> cont;
        
        done = cont == 'n';
        
        std::getline(std::cin, option); // hack
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
    attempt.CalculateTotalScore(topic);
    
    cout << "Total score: " << attempt.GetTotalScore() << endl;
    
     return attempt;
    //ds.WriteAttempt(attempt);
}

Candidate TestingSystem::CreateCandiateUI()
{
    Candidate c;
    string username;
    cout << "Enter candidate's username: ";
    cin >> username;
    string password;
    cout << "Enter new password: ";
    cin >> password;
    string name;
    cout << "Enter name: ";
    cin >> name;
    string testAccId;
    cout << "Enter test account ID: ";
    cin >> testAccId;
    
    c.SetUsername(username);
    c.SetPassword(password);
    c.SetName(name);
    c.SetType(1);
    c.SetTestAccountID(testAccId);
    
    return c;
}
    
Candidate* TestingSystem::ModifyCandidateUI()
{
    string username;
    cout << "Enter candidate's username: ";
    cin >> username;
    
    User * u = (User*)ds.RetrieveUser(username);
    if (u == NULL)
    {
        cout << "Username does not exist" << endl;
        return NULL;
    }
    
    if (u->GetType() != 1)
    {
        cout << "Username is not candidate" << endl;
        return NULL;
    }
    
    Candidate *c = new Candidate();
    *c = CreateCandiateUI(); 
    
    return c;
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
    cout << "candidateId" << "   "  << "topicId" << "   " << "totalScore" << endl;
    for (int i=0; i<attempts.size(); i++)
    {
        attempts[i].PrintAttemptResult();
    }
}

void TestingSystem::ShowAllResults()
{
    vector<Attempt> attempts = ds.RetreiveAllAttempts();
    cout << "candidateId" << "   "  << "topicId" << "   " << "totalScore" << endl;
    for (int i=0; i<attempts.size(); i++)
    {
        attempts[i].PrintAttemptResult();
    }
}

Topic TestingSystem::CreateSingleQuestionUI()
{
    Topic topic = ChooseTopicUI();
        
    Question question = CreateQuestionUI();
    ds.WriteQuestion(question, topic.GetId());
    
    topic.AddQuestion(question);
    
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
        
        validQuestion = questionNumber >= 0 || questionNumber < count;
        if (!validQuestion)
            cout << "Invalid question number." << endl;
    }
    
    int oldId = topic.GetQuestions()[questionNumber].GetId();
    Question question = CreateQuestionUI();
    question.SetId(oldId);
    ds.ModifyQuestion(question);
    
    topic.ReplaceQuestion(questionNumber, question);
    
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
        
        validQuestion = questionNumber >= 0 || questionNumber < count;
        if (!validQuestion)
            cout << "Invalid question number." << endl;
    }
    
    ds.DeleteQuestion(topic.GetQuestions()[questionNumber].GetId());
    topic.RemoveQuestion(questionNumber);
    
    return topic;
}