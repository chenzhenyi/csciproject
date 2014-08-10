#include "DataStorage.h"

DataStorage::DataStorage() {
}

DataStorage::DataStorage(const DataStorage& orig) {
}

DataStorage::~DataStorage() {
}

bool DataStorage::RetrieveTopic(int topicId, Topic& topic) {
}

vector<Attempt> DataStorage::RetreiveAttempts(int studentId) {
}

vector<Attempt> DataStorage::RetreiveAllAttempts() {
}

bool DataStorage::CheckLogin(string username, string pw) {
}

void DataStorage::WriteTopic(Topic topic) {
}

void DataStorage::WriteCandidate(Candidate candidate) {
}

void DataStorage::WriteUser(User user) {
}

void DataStorage::WriteAttempt(Attempt attempt) {
}