#include "../headers/user_info.h"
using namespace std;

user_info::user_info(int id, const string &email, const string &password, const string &username)
    : user_id(id), user_email(email), user_password(password), username(username) {}

const string& user_info::username_getter() const
{
    return username;
}

const string& user_info::user_email_getter() const
{
    return user_email;
}

int user_info::user_id_getter() const
{
    return user_id;
}

ostream& operator<<(ostream &os, const user_info &others)
{
    os << "User ID: " << others.user_id_getter() << endl;
    os << "Username: " << others.username_getter() << endl;
    os << "Email: " << others.user_email_getter() << endl;
    return os;
}