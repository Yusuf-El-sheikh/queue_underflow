#pragma once
#include "IUserRepository.h"
#include "validator.h"
#include "exceptions.h"


class user_manager {
private:
    unique_ptr<IUserRepository> user_repo; //this will be polymorphed into an users_dao implementation in main()
    unique_ptr<user_info> current_user;
public:
    user_manager(unique_ptr<IUserRepository> repo) : user_repo(std::move(repo)) {}//std::move() transfers pointer ownership from parameter to variable
    
    void register_user(const string &username, const string &email, const string &password);
    void login(const string &email, const string &password);
    void logout();

    user_info* get_current_user();
};