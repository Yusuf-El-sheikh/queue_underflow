#include <bits/stdc++.h>
#include "user_info.h"
using namespace std;

user_info::user_info() {}

bool user_info::username_setter(const string &name)
{
    username = name;

    return true;
}

string user_info::username_getter() const
{
    return username;
}

void user_info::user_email_setter(const string &email)
{
    user_email = email;
}

string user_info::user_email_getter() const
{
    return user_email;
}

void user_info::user_password_setter(const string &password)
{
    user_password = password;
}

string user_info::user_password_getter() const
{
    return user_password;
}

bool user_info::preference_setter(const bool &pref)
{
    preference = pref;

    return true;
}

bool user_info::preference_getter() const
{
    return preference;
}

bool user_info::user_id_setter(const int &id)
{
    user_id = id;

    return true;
}

int user_info::user_id_getter() const
{
    return user_id;
}