#pragma once
#include <bits/stdc++.h>
#include "user_info.h"
using namespace std;

class user_manager
{
    friend class questions_manager ;

    private:
    
    int last_id = 0 ;
    vector<user_info> all_users;

    public:
    
    user_info *current_user = nullptr ;
    user_manager();

    void data_loader();
    void data_writer();

    void sign_up();
    void login();
    void logout();

    user_info* search_user(const int &id);
    
    int id_generator();

    bool user_email_authentication(const string &email);
    bool user_password_authenticaton(const string &password);
};