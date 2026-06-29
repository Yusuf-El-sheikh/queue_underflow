#include "../headers/answers_dao.h"
#include "../headers/exceptions.h"

answers_dao::answers_dao(connection *db_connection) : db_connection(db_connection) {}

unique_ptr<answers> answers_dao::find_by_id(int id)
{
    sqlite3_stmt *stmt;

    const char *find_by_id_query = ""
                                   "SELECT answer_id, answered_question_id, from_user_id, answer_text, is_anonymous FROM answers WHERE answer_id = ?";

    int operation_code = sqlite3_prepare_v2(db_connection->handle_getter(), find_by_id_query, -1, &stmt, nullptr);

    if (operation_code != SQLITE_OK)
    {
        throw database_exception(sqlite3_errmsg(db_connection->handle_getter()));
    }

    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) != SQLITE_ROW)
    {
        sqlite3_finalize(stmt);

        return nullptr;
    }

    int answer_id = sqlite3_column_int(stmt, 0);
    int answered_question_id = sqlite3_column_int(stmt, 1);
    int from_user_id = sqlite3_column_int(stmt, 2);

    string answer_text = (const char *)sqlite3_column_text(stmt, 3);

    bool is_anonymous = sqlite3_column_int(stmt, 4);

    sqlite3_finalize(stmt);

    return make_unique<answers>(answer_id, answered_question_id, from_user_id, answer_text, is_anonymous);
}

vector<answers> answers_dao::find_by_question_id(int id)
{
    sqlite3_stmt *stmt;

    vector<answers> q_answers;

    const char *find_by_question_id_query = ""
                                            "SELECT answer_id, answered_question_id, from_user_id, answer_text, is_anonymous FROM answers "
                                            "WHERE answered_question_id = ?";

    int operation_code = sqlite3_prepare_v2(db_connection->handle_getter(), find_by_question_id_query, -1, &stmt, nullptr);

    if (operation_code != SQLITE_OK)
    {
        throw database_exception(sqlite3_errmsg(db_connection->handle_getter()));
    }

    sqlite3_bind_int(stmt, 1, id);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int answer_id = sqlite3_column_int(stmt, 0);
        int answered_question_id = sqlite3_column_int(stmt, 1);
        int from_user_id = sqlite3_column_int(stmt, 2);

        string answer_text = (const char *)sqlite3_column_text(stmt, 3);

        bool is_anonymous = sqlite3_column_int(stmt, 4);

        q_answers.push_back(answers(answer_id, answered_question_id, from_user_id, answer_text, is_anonymous));
    }

    sqlite3_finalize(stmt);

    return q_answers;
}

vector<answers> answers_dao::find_all()
{
    sqlite3_stmt *stmt;

    vector<answers> all_answers;

    const char *find_by_question_id_query = ""
                                            "SELECT answer_id, answered_question_id, from_user_id, answer_text, is_anonymous FROM answers ";

    int operation_code = sqlite3_prepare_v2(db_connection->handle_getter(), find_by_question_id_query, -1, &stmt, nullptr);

    if (operation_code != SQLITE_OK)
    {
        throw database_exception(sqlite3_errmsg(db_connection->handle_getter()));
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int answer_id = sqlite3_column_int(stmt, 0);
        int answered_question_id = sqlite3_column_int(stmt, 1);
        int from_user_id = sqlite3_column_int(stmt, 2);

        string answer_text = (const char *)sqlite3_column_text(stmt, 3);

        bool is_anonymous = sqlite3_column_int(stmt, 4);

        all_answers.push_back(answers(answer_id, answered_question_id, from_user_id, answer_text, is_anonymous));
    }

    sqlite3_finalize(stmt);

    return all_answers;
}

void answers_dao::save(const answers &object)
{
    sqlite3_stmt *stmt;

    const char *save_query = "INSERT INTO answers (answered_question_id, from_user_id, answer_text, is_anonymous) VALUES (?, ?, ?, ?)";

    int operation_code = sqlite3_prepare_v2(db_connection->handle_getter(), save_query, -1, &stmt, nullptr);

    if (operation_code != SQLITE_OK)
    {
        throw database_exception(sqlite3_errmsg(db_connection->handle_getter()));
    }

    sqlite3_bind_int(stmt, 1, object.answered_question_id_getter());
    sqlite3_bind_int(stmt, 2, object.from_user_id_getter());

    sqlite3_bind_text(stmt, 3, object.text_getter().c_str(), -1, SQLITE_TRANSIENT);

    sqlite3_bind_int(stmt, 4, object.is_anonymous_getter());

    if(sqlite3_step(stmt) != SQLITE_DONE)
    {
        sqlite3_finalize(stmt);

        throw database_exception(sqlite3_errmsg(db_connection->handle_getter()));
    }

    sqlite3_finalize(stmt);
}

void answers_dao::remove(const int id)
{
    sqlite3_stmt *stmt;

    const char *remove_query = "DELETE FROM answers WHERE answer_id = ?";

    int operation_code = sqlite3_prepare_v2(db_connection->handle_getter(), remove_query, -1, &stmt, nullptr);

    if (operation_code != SQLITE_OK)
    {
        throw database_exception(sqlite3_errmsg(db_connection->handle_getter()));
    }

    sqlite3_bind_int(stmt, 1, id);

    if(sqlite3_step(stmt) != SQLITE_DONE)
    {
        sqlite3_finalize(stmt);

        throw database_exception(sqlite3_errmsg(db_connection->handle_getter()));
    }

    sqlite3_finalize(stmt);
}