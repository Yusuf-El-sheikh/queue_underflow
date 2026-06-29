#include "../../headers/user_manager.h"
using namespace std;

user_manager::user_manager(unique_ptr<IUserRepository> repo) : user_repo(std::move(repo)) {}

void user_manager::register_user(const string &username, const string &email, const string &password)
{
    if(! validator::validate_email(email))
    {
        throw validation_exception("Invalid email format");
    }

    if(! validator::validate_password(password))
    {
        throw validation_exception("Invalid password format");
    }

    user_repo->create_user(username, email, password);
}

void user_manager::login(const string &email, const string &password)
{
    if(! user_repo->validate_credentials(email, password))
    {
        throw authentication_exception("Incorrect credentials");
    }

    current_user = user_repo->find_by_email(email);
}

void user_manager::logout()
{
    current_user = nullptr;
}

user_info* user_manager::get_current_user()
{
    return current_user.get(); 
}
