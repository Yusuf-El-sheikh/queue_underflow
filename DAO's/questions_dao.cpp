#include "../headers/questions_dao.h"
#include "../headers/exceptions.h"

questions_dao::questions_dao(connection *db_connection) : db_connection(db_connection) {}

unique_ptr<questions> questions_dao::find_by_id(int id)
{
    sqlite3_stmt *stmt;

    const char *find_by_id_query = ""
                                   "SELECT question_id, parent_question_id, from_user_id, question_text, is_anonymous, "
                                   "is_answered FROM questions WHERE question_id = ?";

    int operation_code = sqlite3_prepare_v2(db_connection->handle_getter(), find_by_id_query, -1, &stmt, nullptr);

    if (operation_code != SQLITE_OK)
    {
        throw database_exception(sqlite3_errmsg(db_connection->handle_getter()));
    }

    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int question_id = sqlite3_column_int(stmt, 0);
        int parent_question_id = sqlite3_column_int(stmt, 1);
        int from_user_id = sqlite3_column_int(stmt, 2);

        string question_text = (const char *)sqlite3_column_text(stmt, 3);
        bool is_anonymous = sqlite3_column_int(stmt, 4);
        bool is_answered = sqlite3_column_int(stmt, 5);

        sqlite3_finalize(stmt);

        return make_unique<questions>(question_id, parent_question_id, from_user_id, question_text, is_anonymous, is_answered);
    }

    sqlite3_finalize(stmt);

    return nullptr;
}

vector<questions> questions_dao::find_by_user_id(int id)
{
    vector<questions> user_questions;

    sqlite3_stmt *stmt;

    const char *find_by_user_query = ""
                                     "SELECT question_id, parent_question_id, from_user_id, question_text, is_anonymous, "
                                     "is_answered FROM questions WHERE from_user_id = ?";

    int operation_code = sqlite3_prepare_v2(db_connection->handle_getter(), find_by_user_query, -1, &stmt, nullptr);

    if (operation_code != SQLITE_OK)
    {
        throw database_exception(sqlite3_errmsg(db_connection->handle_getter()));
    }

    sqlite3_bind_int(stmt, 1, id);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int question_id = sqlite3_column_int(stmt, 0);
        int parent_question_id = sqlite3_column_int(stmt, 1);
        int from_user_id = sqlite3_column_int(stmt, 2);

        string question_text = (const char *)sqlite3_column_text(stmt, 3);

        bool is_anonymous = sqlite3_column_int(stmt, 4);
        bool is_answered = sqlite3_column_int(stmt, 5);

        user_questions.push_back(questions(question_id, parent_question_id, from_user_id, question_text, is_anonymous, is_answered));
    }

    sqlite3_finalize(stmt);

    return user_questions;
}

vector<questions> questions_dao::find_descendants(int id)
{
    vector<questions> child_questions;

    sqlite3_stmt *stmt;

    const char *find_by_user_query = ""
                                     "SELECT question_id, parent_question_id, from_user_id, question_text, is_anonymous, "
                                     "is_answered FROM questions WHERE parent_question_id = ?";

    int operation_code = sqlite3_prepare_v2(db_connection->handle_getter(), find_by_user_query, -1, &stmt, nullptr);

    if (operation_code != SQLITE_OK)
    {
        throw database_exception(sqlite3_errmsg(db_connection->handle_getter()));
    }

    sqlite3_bind_int(stmt, 1, id);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int question_id = sqlite3_column_int(stmt, 0);
        int parent_question_id = sqlite3_column_int(stmt, 1);
        int from_user_id = sqlite3_column_int(stmt, 2);

        string question_text = (const char *)sqlite3_column_text(stmt, 3);

        bool is_anonymous = sqlite3_column_int(stmt, 4);
        bool is_answered = sqlite3_column_int(stmt, 5);

        child_questions.push_back(questions(question_id, parent_question_id, from_user_id, question_text, is_anonymous, is_answered));
    }

    sqlite3_finalize(stmt);

    return child_questions;
}

vector<questions> questions_dao::find_all()
{
    vector<questions> all_questions;

    sqlite3_stmt *stmt;

    const char *find_by_user_query = ""
                                     "SELECT question_id, parent_question_id, from_user_id, question_text, is_anonymous, "
                                     "is_answered FROM questions";

    int operation_code = sqlite3_prepare_v2(db_connection->handle_getter(), find_by_user_query, -1, &stmt, nullptr);

    if (operation_code != SQLITE_OK)
    {
        throw database_exception(sqlite3_errmsg(db_connection->handle_getter()));
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int question_id = sqlite3_column_int(stmt, 0);
        int parent_question_id = sqlite3_column_int(stmt, 1);
        int from_user_id = sqlite3_column_int(stmt, 2);

        string question_text = (const char *)sqlite3_column_text(stmt, 3);

        bool is_anonymous = sqlite3_column_int(stmt, 4);
        bool is_answered = sqlite3_column_int(stmt, 5);

        all_questions.push_back(questions(question_id, parent_question_id, from_user_id, question_text, is_anonymous, is_answered));
    }

    sqlite3_finalize(stmt);

    return all_questions;
}

void questions_dao::save(const questions &object)
{
    sqlite3_stmt *stmt;

    const char *save_query = ""
                             "INSERT INTO questions(parent_question_id, from_user_id, question_text, is_anonymous, is_answered)"
                             "VALUES (?, ?, ?, ?, ?)";

    int operation_code = sqlite3_prepare_v2(db_connection->handle_getter(), save_query, -1, &stmt, nullptr);

    if (operation_code != SQLITE_OK)
    {
        throw database_exception(sqlite3_errmsg(db_connection->handle_getter()));
    }

    sqlite3_bind_int(stmt, 1, object.parent_question_id_getter());
    sqlite3_bind_int(stmt, 2, object.from_user_id_getter());

    sqlite3_bind_text(stmt, 3, object.text_getter().c_str(), -1, SQLITE_TRANSIENT);

    sqlite3_bind_int(stmt, 4, object.is_anonymous_getter());

    sqlite3_bind_int(stmt, 5, object.is_answered_getter());

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        sqlite3_finalize(stmt);

        throw database_exception(sqlite3_errmsg(db_connection->handle_getter()));
    }

    sqlite3_finalize(stmt);

    return;
}

void questions_dao::remove(int id)
{
    sqlite3_stmt *stmt;

    const char *remove_query = ""
                               "DELETE FROM questions WHERE question_id = ?";

    int operation_code = sqlite3_prepare_v2(db_connection->handle_getter(), remove_query, -1, &stmt, nullptr);

    if(operation_code != SQLITE_OK)
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

    return;
}