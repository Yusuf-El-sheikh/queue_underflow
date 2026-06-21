#include "../headers/users_dao.h"
#include "../headers/database_connection.h"
#include "../headers/exceptions.h"

users_dao::users_dao(connection *db_connection) : db_connection(db_connection) {}

unique_ptr<user_info> users_dao::find_by_id(int id)
{
    sqlite3_stmt *stmt;
    const char *find_by_id_query = ""
                                   "SELECT user_id, username, user_email, user_password FROM users WHERE users_id = ?";

    int operation_code = sqlite3_prepare_v2(db_connection->handle_getter(), find_by_id_query, -1, &stmt, nullptr);

    if (operation_code != SQLITE_OK)
    {
        throw database_exception(sqlite3_errmsg(db_connection->handle_getter()));
    }

    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int user_id = sqlite3_column_int(stmt, 0);

        string username = (const char *)sqlite3_column_text(stmt, 1);
        string user_email = (const char *)sqlite3_column_text(stmt, 2);
        string user_password = (const char *)sqlite3_column_text(stmt, 3);

        sqlite3_finalize(stmt);

        return make_unique<user_info>(user_id, user_email, user_password, username);
    }

    sqlite3_finalize(stmt);
    return nullptr;
}

unique_ptr<user_info> users_dao::find_by_email(const string &email)
{
    sqlite3_stmt *stmt;
    const char *find_by_email_query = ""
                                   "SELECT user_id, username, user_email, user_password FROM users WHERE users_email = ?";

    int operation_code = sqlite3_prepare_v2(db_connection->handle_getter(), find_by_email_query, -1, &stmt, nullptr);

    if (operation_code != SQLITE_OK)
    {
        throw database_exception(sqlite3_errmsg(db_connection->handle_getter()));
    }

    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int user_id = sqlite3_column_int(stmt, 0);

        string username = (const char *)sqlite3_column_text(stmt, 1);
        string user_email = (const char *)sqlite3_column_text(stmt, 2);
        string user_password = (const char *)sqlite3_column_text(stmt, 3);

        sqlite3_finalize(stmt);

        return make_unique<user_info>(user_id, user_email, user_password, username);
    }

    sqlite3_finalize(stmt);
    return nullptr;
}