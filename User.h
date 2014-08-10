#ifndef USER_H
#define	USER_H

#include <string>

using namespace std;

class User {
public:
    User();
    User(string username, string pw, string name, int type);
    User(const User& orig);
    virtual ~User();

    void SetType(int type) {
        this->type = type;
    }

    int GetType() const {
        return type;
    }

    void SetName(string name) {
        this->name = name;
    }

    string GetName() const {
        return name;
    }

    void SetPassword(string password) {
        this->password = password;
    }

    string GetPassword() const {
        return password;
    }

    void SetUsername(string username) {
        this->username = username;
    }

    string GetUsername() const {
        return username;
    }
    
    
private:
    string username;
    string password;
    string name;
    int type;
};

#endif	/* USER_H */

