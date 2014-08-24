#include "DataStorage.h"
#include <sqlite3.h>
#define DB "test3.db"
#include <iostream>
#include <string>
#include <vector>
#include <string.h>
using namespace std;
// sqlite database pointer 
sqlite3 *dbfile;

DataStorage::DataStorage() {
    auto code = sqlite3_open(DB, &dbfile);
    if ( code == SQLITE_OK )
    {
        isOpenDB = true;
        cout << "Connection Success"<<endl;
    }         
    else
    cout << "Connection Failed"<<endl;
}

DataStorage::~DataStorage() {
    if ( isOpenDB == true ) 
    {
        sqlite3_close(dbfile);
    }
}

bool DataStorage::RetrieveTopic(int topicId, Topic& topic) {
    //true if topic is found with specified ID false otherwise
    //concurrently return values of the topic id specificed into topic
    sqlite3_stmt *statement;
    
    string query = "select * from topic where topicid=" + to_string(topicId);
    
    if ( sqlite3_prepare(dbfile, query.c_str(), -1, &statement, 0 ) == SQLITE_OK ) 
    {
        int ctotal = sqlite3_column_count(statement);
        int res = 0;

        while ( 1 )
        {
            res = sqlite3_step(statement);
            
            if ( res == SQLITE_ROW ) 
            {
                topic.SetId(sqlite3_column_int(statement, 0));
                topic.SetTotalMarks(sqlite3_column_int(statement, 1));
            }
            
            if ( res == SQLITE_DONE || res==SQLITE_ERROR)    
            {
                //cout << "done " << endl;
                break;
            }    
        }
    }
    
    sqlite3_finalize(statement);
    
    query = "select questionId,marks, question, answer from question where topicid=" + to_string(topicId);
    
    vector<Question> questions;
    
    if ( sqlite3_prepare(dbfile, query.c_str(), -1, &statement, 0 ) == SQLITE_OK ) 
    {
        int ctotal = sqlite3_column_count(statement);
        int res = 0;

        while ( 1 )
        {
            Question q;
            
            res = sqlite3_step(statement);
            
            if ( res == SQLITE_ROW ) 
            {
                q.SetId(sqlite3_column_int(statement, 0));
                q.SetQuestion(string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 2))));
                q.SetMarks(sqlite3_column_int(statement, 1));
                q.SetAnswer(sqlite3_column_text(statement, 3)[0]);
                
                questions.push_back(q);
            }         
                        
            if ( res == SQLITE_DONE || res==SQLITE_ERROR)    
            {
                //cout << "done " << endl;
                break;
            }    
        }
    }
    else
    {
        cout << "ERROR: " << sqlite3_errmsg(dbfile) << endl;
        return false;
    }
    
    sqlite3_finalize(statement);
    
    for (int i=0; i < questions.size(); i++)
    {
        query = "select answer from QuestionOption where questionId=" + to_string(questions[i].GetId()) + " order by rowid";
    
        vector<string> options;
        
        Question q = questions[i];

        if ( sqlite3_prepare(dbfile, query.c_str(), -1, &statement, 0 ) == SQLITE_OK ) 
        {
            int ctotal = sqlite3_column_count(statement);
            int res = 0;

            while ( 1 )
            {
                res = sqlite3_step(statement);
                
                if ( res == SQLITE_ROW ) 
                {
                    options.push_back(string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 0))));
                }

                if ( res == SQLITE_DONE || res==SQLITE_ERROR)    
                {
                    //cout << "done " << endl;
                    break;
                }    
            }
            
            q.SetOptions(options);
        }
        else
        {
            return false;
        }
        
        questions[i] = q;
    }
    
    topic.SetQuestions(questions);
}

bool DataStorage::DeleteTopic(int topicId)
{     
     Topic t;
     bool result = RetrieveTopic(topicId, t);
     
     if (!result)
         return false;
     
     vector<Question> vq = t.GetQuestions();
     for (int i =0; i < vq.size(); i++)
     {
         Question q = vq[i];
         doQuery("delete from QuestionOption where questionId =" + to_string(q.GetId()));
         doQuery("delete from Question where questionId =" + to_string(q.GetId()));         
     }
     
     doQuery("delete from Topic where topicId =" + to_string(t.GetId()));

     return true;     
}

User* DataStorage::RetrieveUser(string username)
{
    User * user = NULL;
    string query = "select * from User where username='" + username + "'";

    sqlite3_stmt *stmt;
    const char *tail;
    int code = sqlite3_prepare(dbfile, query.c_str(), -1, &stmt, &tail );
    if (code == SQLITE_OK ) 
    {
        int res = 0;

        while ( true )         
        {
            res = sqlite3_step(stmt);

            if ( res == SQLITE_ROW ) 
            {
                string username = (char*)sqlite3_column_text(stmt, 0);
                string pw = (char*)sqlite3_column_text(stmt, 1);
                string name = (char*)sqlite3_column_text(stmt, 2);
                int s = sqlite3_column_int(stmt, 3);
                
                if (s == 1)
                {
                    string testAccId = (char*)sqlite3_column_text(stmt, 4);
                    cout << "Logged in as student " <<  testAccId << endl;
                    
                    Candidate * c = new Candidate();
                    c->SetName(name);
                    c->SetPassword(pw);
                    c->SetType(1);
                    c->SetUsername(username);
                    c->SetTestAccountID(testAccId);
                    
                    user = c;
                }
                else
                {
                    cout << "Logged in as lecturer" << endl;
                    User *u = new User();
                    u->SetName(name);
                    u->SetPassword(pw);
                    u->SetType(0);
                    u->SetUsername(username);
                    
                    user = u;
                }
            }
            
            if ( res == SQLITE_DONE || res==SQLITE_ERROR)    
            {
                break;
            }    
        }
    }
    else
    {
        cout << " NOT OK: " << sqlite3_errstr(code) ;
    }
    
    return user;
}

bool DataStorage::DeleteUser(string username)
{
        doQuery("DELETE FROM user WHERE username='"+username+"'");
}

vector<Attempt> DataStorage::RetreiveAttempts(string studentId) {
    vector<Attempt> vecAt;
    sqlite3_stmt *statement;
    //SELECT * FROM attempts WHERE id=studentId
    
    string query = "SELECT * FROM Attempt WHERE testAccId='"+studentId+"'";

    if ( sqlite3_prepare(dbfile, query.c_str(), -1, &statement, 0 ) == SQLITE_OK ) 
    {
        int ctotal = sqlite3_column_count(statement);
        int res = 0;

        while ( 1 )         
        {
            res = sqlite3_step(statement);

            if ( res == SQLITE_ROW ) 
            {
                Attempt at;
                at.SetTopicId(sqlite3_column_int(statement, 0));
                at.SetCandidateId((char*)sqlite3_column_text(statement, 1));
                at.SetTotalScore(sqlite3_column_int(statement, 2));
                vecAt.push_back(at);
            }
            
            if ( res == SQLITE_DONE || res==SQLITE_ERROR)    
            {
                cout << "done " << endl;
                break;
            }    
        }
    }
    
    return vecAt;
}

vector<Attempt> DataStorage::RetreiveAllAttempts() 
{
    vector<Attempt> vecAt;
    string query = "SELECT * FROM Attempt";   
    sqlite3_stmt *statement;
    if ( sqlite3_prepare(dbfile, query.c_str(), -1, &statement, 0 ) == SQLITE_OK ) 
    {
        int ctotal = sqlite3_column_count(statement);
        int res = 0;

        while ( 1 )         
        {
            res = sqlite3_step(statement);
    
            if ( res == SQLITE_ROW ) 
            { 
                Attempt at;
                at.SetCandidateId((char*)sqlite3_column_text(statement, 1));
                at.SetTopicId(sqlite3_column_int(statement, 0));
                at.SetTotalScore(sqlite3_column_int(statement, 2));
                vecAt.push_back(at);
            }
            
            if ( res == SQLITE_DONE || res==SQLITE_ERROR)    
            {
                cout << "done " << endl;
                break;
            } 
        }           
    }
    
    return vecAt;
}

bool DataStorage::CheckLogin(string username, string pw) {
    string query = "SELECT * FROM user WHERE username='"+username+"' AND password='"+ encryptDecrypt(pw) +"'";   
    sqlite3_stmt *statement;
    auto code  =sqlite3_prepare_v2(dbfile, query.c_str(), -1, &statement, 0 );
    if ( code == SQLITE_OK ) 
    {
        int ctotal = sqlite3_column_count(statement);
        int res = 0;

        while ( 1 )         
        {
            res = sqlite3_step(statement);

            if ( res == SQLITE_ROW ) 
            {
                return true;
            }
            
            if ( res == SQLITE_DONE || res==SQLITE_ERROR)    
            {
                cout << "done " << endl;
                break;
            }    
        }
    }
    else
    {
        cout << "SQLite error: " << sqlite3_errstr(code) << endl;
        cout << sqlite3_errstr(sqlite3_step(statement));
    }

}

void DataStorage::WriteTopic(Topic topic) {
    doQuery("insert into Topic values(NULL," + to_string(topic.GetTotalMarks()) + ")");
    
    sqlite3_int64 topicid = sqlite3_last_insert_rowid(dbfile);
    
    vector<Question> questions = topic.GetQuestions();
    for (int i=0; i<questions.size(); i++)
    {
        Question q = questions[i];
        string answer(1,q.GetAnswer());
        doQuery("insert into Question values(NULL," 
                + to_string(topicid) + "," + to_string(q.GetMarks()) + ",'"
                + q.GetQuestion() + "','" + answer + "')");
        
        sqlite3_int64 qid = sqlite3_last_insert_rowid(dbfile);
        
        vector <string> ans = q.GetOptions();
        for (int j=0;j<ans.size();j++)
        {
            doQuery("insert into QuestionOption values(" + to_string(qid) + ",'" + ans[j] + "')");
        }
    }
}

void DataStorage::WriteQuestion(Question q, int topicId)
{
    string answer(1,q.GetAnswer());
    doQuery("insert into Question values(NULL," 
            + to_string(topicId) + "," + to_string(q.GetMarks()) + ",'"
            + q.GetQuestion() + "','" + answer + "')");

    sqlite3_int64 qid = sqlite3_last_insert_rowid(dbfile);

    vector <string> ans = q.GetOptions();
    for (int j=0;j<ans.size();j++)
    {
        doQuery("insert into QuestionOption values(" + to_string(qid) + ",'" + ans[j] + "')");
    }
}

void DataStorage::DeleteQuestion(int questionId)
{
    doQuery("delete from QuestionOption where questionId =" + to_string(questionId));
    doQuery("delete from Question where questionId =" + to_string(questionId));     
}

void DataStorage::ModifyTopic(Topic topic) {    
    doQuery("update Topic set totalMarks=" + to_string(topic.GetTotalMarks()) 
            + " where topicId=" + to_string(topic.GetId()));
    /*
    vector<Question> questions = topic.GetQuestions();
    for (int i=0; i<questions.size(); i++)
    {
        
        Question q = questions[i];
        
        doQuery("delete from QuestionOption where questionId =" + to_string(q.GetId()));
        
        string answer(1,q.GetAnswer());
        doQuery("update Question set marks=" + to_string(q.GetMarks()) 
                + ", question='" + q.GetQuestion() + "', answer ='" + answer 
                + "' where questionId=" + to_string(q.GetId()));
        
        vector <string> ans = q.GetOptions();
        for (int j=0;j<ans.size();j++)
        {
            doQuery("insert into QuestionOption values(" + to_string(q.GetId()) + ",'" + ans[j] + "')");
        }
        
    }*/
}

void DataStorage::ModifyQuestion(Question q)
{
    doQuery("delete from QuestionOption where questionId =" + to_string(q.GetId()));

    string answer(1,q.GetAnswer());
    doQuery("update Question set marks=" + to_string(q.GetMarks()) 
            + ", question='" + q.GetQuestion() + "', answer ='" + answer 
            + "' where questionId=" + to_string(q.GetId()));

    vector <string> ans = q.GetOptions();
    for (int j=0;j<ans.size();j++)
    {
        doQuery("insert into QuestionOption values(" + to_string(q.GetId()) + ",'" + ans[j] + "')");
    }
}

void DataStorage::WriteCandidate(Candidate c) {
    doQuery("INSERT INTO User values ('"+c.GetUsername()+"', '"+ encryptDecrypt(c.GetPassword()) 
            +"', '" + c.GetName() + "'," + to_string(c.GetType()) + " , '" + c.GetTestAccountID() +"')");
}

void DataStorage::WriteUser(User user) {
    //doQuery("INSERT INTO users(username,password) values ('"+user.GetUsername()+"','"+encryptDecrypt(user.GetPassword())+"')");
}

void DataStorage::WriteAttempt(Attempt attempt) {
    doQuery("INSERT INTO attempt VALUES (" + to_string(attempt.GetTopicId())
            + ",'" + attempt.GetCandidateId() + "'," + to_string(attempt.GetTotalScore()) +")");
}

int DataStorage::doQuery (string s)
{    
    sqlite3_stmt *statement;
    int result = sqlite3_prepare(dbfile,s.c_str(),-1,&statement,0);
    if (result != SQLITE_OK)
        cout << "ERROR prep: " << sqlite3_errmsg(dbfile) << endl;
    
    result = sqlite3_step(statement);
    if (result != SQLITE_DONE)
        cout << "ERROR step: " << sqlite3_errmsg(dbfile) << endl;
    
    sqlite3_finalize(statement);
    return result;
}

string DataStorage::encryptDecrypt(string toEncrypt) {
    char key = 'K'; //Any char will work
    string output = toEncrypt;

    for (int i = 0; i < toEncrypt.size(); i++)
        output[i] = toEncrypt[i] ^ key;

    return output;
}