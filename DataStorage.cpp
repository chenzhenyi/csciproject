#include "DataStorage.h"
#include <sqlite3.h>
#define DB "test.db"
#include <iostream>
#include <string>
#include <topic.h>
using namespace std;
// sqlite database pointer 
sqlite3 *dbfile;

DataStorage::DataStorage() {
    if ( sqlite3_open(DB, &dbfile) == SQLITE_OK )
    {
        isOpenDB = true;
        cout << "Connection Sucuess";
    }         
    cout << "Connection Failed";
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
	//SELECT * FROM test WHERE id=topicID,
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

bool DataStorage::DeleteTopic(int topicId)
{
 doQuery("DELETE FROM test WHERE id=topicID");
}

User* DataStorage::RetrieveUser(string username)
{
//SELECT * FROM users WHERE username=username
}

bool DataStorage::DeleteUser(string username)
{
doQuery(DELETE FROM user WHERE username=username);
}

vector<Attempt> DataStorage::RetreiveAttempts(string studentId) {
}

vector<Attempt> DataStorage::RetreiveAllAttempts() {
}

bool DataStorage::CheckLogin(string username, string pw) {
    //SELECT * FROM users
}

void DataStorage::WriteTopic(Topic topic) {
	//INSERT INTO test(text) VALUES("topic.getText")
}

void DataStorage::WriteCandidate(Candidate candidate) {
	//INSERT INTO candidate(testAccountID) values (candidate.getTestAccountID) <=== insert with foreign key constraint ?
}

void DataStorage::WriteUser(User user) {
	//INSERT INTO users(username,password) values (user.getUsername,user.getPass)
}

void DataStorage::WriteAttempt(Attempt attempt) {
	//INSERT INTO attempt(score,testID,testAccountID) VALUES (attempt.getScore,attempt.getTestID,attempt.getTestAccountID) <== foreign key ? 
}

int doQuery (string s)
{

//    string s = strm.str();
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
