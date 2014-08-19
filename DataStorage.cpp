#include "DataStorage.h"
#include <sqlite3.h>
#define DB "test3.db"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
// sqlite database pointer 
sqlite3 *dbfile;

DataStorage::DataStorage() {
    if ( sqlite3_open(DB, &dbfile) == SQLITE_OK )
    {
        isOpenDB = true;
        cout << "Connection Sucuess"<<endl;
    }         
    else
    cout << "Connection Failed"<<endl;
}

DataStorage::DataStorage(const DataStorage& orig) {
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
	//SELECT * FROM test WHERE id=topicID,
/*topicId	totalMarks	questionId	topicId	marks	question	questionId	answer
1	25	1	1	25	How high is the sky	1	1
1	25	1	1	25	How high is the sky	1	2
1	25	1	1	25	How high is the sky	1	3
1	25	1	1	25	How high is the sky	1	4*/
    string query = "SELECT * FROM topic INNER JOIN Question ON topic.topicId=Question.topicId INNER JOIN QuestionOption ON Question.questionId=QuestionOption.questionId where topic.topicId="+to_string(topicId);
    sqlite3_stmt *statement;
    
    if ( sqlite3_prepare(dbfile, query.c_str(), -1, &statement, 0 ) == SQLITE_OK ) 
    {
        int ctotal = sqlite3_column_count(statement);
        int res = 0;

        while ( 1 )
        {
            res = sqlite3_step(statement);
            vector<string> qOpt;
                Question q;
                topic.SetTotalMarks(sqlite3_column_int(statement, 1));
                q.SetMarks((sqlite3_column_int(statement, 1)));
//                q.SetAnswer((char*)sqlite3_column_text(statement, 6));
//                q.SetQuestion((char*)sqlite3_column_int(statement, 1))
                topic.AddQuestion(q);
                 
            if ( res == SQLITE_ROW ) 
            {
                

            }
                q.SetOptions(qOpt);
            
            if ( res == SQLITE_DONE || res==SQLITE_ERROR)    
            {
                cout << "done " << endl;
                break;
            }    
        }
    }

}

bool DataStorage::DeleteTopic(int topicId)
{
doQuery("DELETE FROM topic WHERE id="+to_string(topicId));
}

User* DataStorage::RetrieveUser(string username)
{
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
                    
                cout << username << endl ;
                cout << pw << endl;
                cout << name << endl ;
                cout << s << endl ;
                
                if (s == 1)
                {
                    string testAccId = (char*)sqlite3_column_text(stmt, 4);
                    cout << "student " <<  testAccId << endl ;
                }
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
        cout << " NOT OK: " << sqlite3_errstr(code) ;
    }}

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
                for ( int i = 0; i < ctotal; i++ ) 
                {
                    Attempt at;
                    at.SetTopicId(sqlite3_column_int(statement, 0));
                    at.SetTotalScore(sqlite3_column_int(statement, 2));
                    vecAt.push_back(at);
//                    string s = (char*)sqlite3_column_text(statement, i);
                    // print or format the output as you want 
                }
                return vecAt;
            }
            
            if ( res == SQLITE_DONE || res==SQLITE_ERROR)    
            {
                cout << "done " << endl;
                break;
            }    
        }
    }
}

vector<Attempt> DataStorage::RetreiveAllAttempts() {

        string query = "SELECT * FROM Attempt";   
    sqlite3_stmt *statement;
    if ( sqlite3_prepare(dbfile, query.c_str(), -1, &statement, 0 ) == SQLITE_OK ) 
    {
        int ctotal = sqlite3_column_count(statement);
        int res = 0;

        while ( 1 )         
        {
            res = sqlite3_step(statement);
    vector<Attempt> vecAt;

            if ( res == SQLITE_ROW ) 
            { 
                    Attempt at;
                    at.SetCandidateId((char*)sqlite3_column_text(statement, 1));
                    at.SetTopicId(sqlite3_column_int(statement, 0));
                    at.SetTotalScore(sqlite3_column_int(statement, 2));
                    vecAt.push_back(at);

                }

            }
            
            if ( res == SQLITE_DONE || res==SQLITE_ERROR)    
            {
                cout << "done " << endl;
            }    
        }
    }

bool DataStorage::CheckLogin(string username, string pw) {
    string query = "SELECT * FROM user WHERE username='"+username+"' AND password='"+ encryptDecrypt(pw) +"')";   
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
                return true;
                /*
                string u = (char*)sqlite3_column_text(statement, 0);
                string p = (char*)sqlite3_column_text(statement, 1);              
                    
                cout << u << endl;
                cout << p << endl;
                cout << username << endl;
                cout << pw << endl;
                if(u==username&&p==pw){
                    return true;
                }
                else
                    return false;
                */

            }
            
            if ( res == SQLITE_DONE || res==SQLITE_ERROR)    
            {
                cout << "done " << endl;
                break;
            }    
        }
    }

}

void DataStorage::WriteTopic(Topic topic) {
	doQuery("INSERT INTO test(text) VALUES('"+to_string(topic.GetId())+"','"+to_string(topic.GetTotalMarks())+"')");
}

void DataStorage::WriteCandidate(Candidate candidate) {
    doQuery("INSERT INTO candidate(testAccountID) values ('"+candidate.GetTestAccountID()+"')");
	//"INSERT INTO candidate(testAccountID) values (+"candidate.getTestAccountID())" <=== insert with foreign key constraint ?
}

void DataStorage::WriteUser(User user) {
    doQuery("INSERT INTO users(username,password) values ('"+user.GetUsername()+"','"+encryptDecrypt(user.GetPassword())+"')");
	//"INSERT INTO users(username,password) values ("+user.getUsername","+user.getPass()")"
}

void DataStorage::WriteAttempt(Attempt attempt) {
    doQuery("INSERT INTO attempt(score,testID,testAccountID) VALUES ('"+to_string(attempt.GetTotalScore())+"','"+to_string(attempt.GetTopicId())+
    "','"+attempt.GetCandidateId()+"')");
	/*"INSERT INTO attempt(score,testID,testAccountID) VALUES ("+attempt.getScore+","+to_string(attempt.getTestID())+
    ","+attempt.getTestAccountID()")" <== foreign key ? 
         */
}

int DataStorage::doQuery (string s)
{
    char *str = &s[0];
    
    sqlite3_stmt *statement;
    int result;
    char *query = str;
    {
        if(sqlite3_prepare(dbfile,query,-1,&statement,0)==SQLITE_OK)
        {
            int res=sqlite3_step(statement);
            result=res;
            sqlite3_finalize(statement);
        }
        return result;
    }
    return 0;
}

string DataStorage::encryptDecrypt(string toEncrypt) {
    char key = 'K'; //Any char will work
    string output = toEncrypt;

    for (int i = 0; i < toEncrypt.size(); i++)
        output[i] = toEncrypt[i] ^ key;

    return output;
}
/*
void getTableData(string q)
{

    char *query = &q[0];

    if ( sqlite3_prepare(dbfile, query, -1, &statement, 0 ) == SQLITE_OK ) 
    {
        int ctotal = sqlite3_column_count(statement);
        int res = 0;

        while ( 1 )         
        {
            res = sqlite3_step(statement);

            if ( res == SQLITE_ROW ) 
            {
                for ( int i = 0; i < ctotal; i++ ) 
                {
                    string s = (char*)sqlite3_column_text(statement, i);
                    // print or format the output as you want 
                    cout << s << " " ;
                }
                cout << endl;
            }
            
            if ( res == SQLITE_DONE || res==SQLITE_ERROR)    
            {
                cout << "done " << endl;
                break;
            }    
        }
    }
} 
*/