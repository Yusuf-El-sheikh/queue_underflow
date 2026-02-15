#pragma once
#include <bits/stdc++.h>
using namespace std;

class user_info
{
    friend class user_manager;

private:
    int user_id = 0;

    string user_password = "";
    string user_email = "";
    string username = "";

    bool preference = false;

public:
    user_info(); /*default constructor as any logic here would be redundant in case of one parameter failure*/

    bool username_setter(const string &name);
    string username_getter() const;

    void user_email_setter(const string &email);
    string user_email_getter() const;

    void user_password_setter(const string &password);
    string user_password_getter() const;

    bool user_id_setter(const int &id);
    int user_id_getter() const;

    bool preference_setter(const bool &pref);
    bool preference_getter() const;
};