#pragma once
#include "IUserRepository.h"
#include "database_connection.h"

class users_dao : public IUserRepository
{
private:
    connection *db_connection;

public:
    users_dao(connection *db_connection) : db_connection(db_connection) {}

    [[nodiscard]] unique_ptr<user_info> find_by_id(int id) override;
    [[nodiscard]] unique_ptr<user_info> find_by_email(const string &email) override;

    vector<user_info> find_all() override;

    void create_user(const string &username, const string &email, const string &password) override;
    void remove(const int id) override;

    [[nodiscard]] bool validate_credentials(const string &email, const string &password) override;

    ~users_dao() override = default;
};