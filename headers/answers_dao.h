#pragma once
#include "IAnswerRepository.h"
#include "database_connection.h"

class answers_dao : public IAnswerRepository
{
private:
    connection *db_connection;

public:
    answers_dao(connection *db_connection) : db_connection(db_connection) {}

    [[nodiscard]] unique_ptr<answers> find_by_id(int id) override;
    [[nodiscard]] vector<answers> find_by_question_id(int id) override;

    vector<answers> find_all() override;

    void post_answer(int answered_question_id, int from_user_id, const string &answer_text, bool is_anonymous);
    void remove(const int id) override;

    ~answers_dao() override = default;
};