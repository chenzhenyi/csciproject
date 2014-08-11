#include "DataStorage.h"
#include <sqlite3.h>
#define DB "test.db"
#include <iostream>
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

}

bool DataStorage::DeleteTopic(int topicId)
{
    //DELETE FROM test WHERE id=topicID;
}

User* DataStorage::RetrieveUser(string username)
{
//SELECT * FROM users WHERE username=username
}

bool DataStorage::DeleteUser(string username)
{
    //DELETE FROM user WHERE username=username;
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
