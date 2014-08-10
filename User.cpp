#include "User.h"

User::User(): username(""), password(""),name(""),type (0)
{
}

User::User(string username, string pw, string name, int type): 
        username(username), password(pw),name(name),type (type)
{
}

User::User(const User& orig) {
}

User::~User() {
}

