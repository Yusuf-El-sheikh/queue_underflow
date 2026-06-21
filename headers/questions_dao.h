#pragma once
#include "IQuestionRepository.h"
#include "database_connection.h"

class questions_dao : public IQuestionRepository
{
private:
    connection *db_connection;

public:
    questions_dao(connection *db_connection) : db_connection(db_connection) {}

    [[nodiscard]] unique_ptr<questions> find_by_id(int id) override;
    [[nodiscard]] vector<questions> find_by_user_id(int id) override;
    [[nodiscard]] vector<questions> find_descendants(int parent_id) override;

    vector<questions> find_all() override;

    void save(const questions &object) override;
    void remove(const int id) override;

    ~questions_dao() override = default;
};