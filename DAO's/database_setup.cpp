#include "../headers/database_setup.h"

void setup::db_setup(connection *db_connection)
{
    const char *create_tables = ""
                                "CREATE TABLE IF NOT EXISTS users"
                                "(user_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                " username TEXT NOT NULL, user_email TEXT NOT NULL UNIQUE, "
                                "user_password TEXT NOT NULL);"

                                "CREATE TABLE IF NOT EXISTS questions "
                                "(question_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                " parent_question_id INTEGER DEFAULT -1,"
                                " from_user_id INTEGER NOT NULL,"
                                " question_text TEXT NOT NULL,"
                                " is_anonymous INTEGER NOT NULL,"
                                " is_answered INTEGER NOT NULL,"
                                " FOREIGN KEY (from_user_id) REFERENCES users(user_id)"
                                ");"

                                "CREATE TABLE IF NOT EXISTS answers "
                                "(answer_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                " answered_question_id INTEGER NOT NULL,"
                                " from_user_id INTEGER NOT NULL,"
                                " answer_text TEXT NOT NULL,"
                                " is_anonymous INTEGER NOT NULL,"
                                " FOREIGN KEY (answered_question_id) REFERENCES questions(question_id),"
                                " FOREIGN KEY (from_user_id) REFERENCES users(user_id)"
                                ");"

                                "CREATE TABLE IF NOT EXISTS question_votes "
                                "(question_id INTEGER NOT NULL,"
                                " voter_id INTEGER NOT NULL,"
                                " vote_type INTEGER NOT NULL,"
                                " PRIMARY KEY (question_id, voter_id),"
                                " FOREIGN KEY (question_id) REFERENCES questions(question_id),"
                                " FOREIGN KEY (voter_id) REFERENCES users(user_id)"
                                ");"

                                "CREATE TABLE IF NOT EXISTS answer_votes "
                                "(answer_id INTEGER NOT NULL,"
                                " voter_id INTEGER NOT NULL,"
                                " vote_type INTEGER NOT NULL,"
                                " PRIMARY KEY (answer_id, voter_id),"
                                " FOREIGN KEY (answer_id) REFERENCES answers(answer_id),"
                                " FOREIGN KEY (voter_id) REFERENCES users(user_id)"
                                ");";

    sqlite3_stmt *stmt;
    
    char *err_msg = nullptr;

    int operation_code = sqlite3_exec(db_connection->handle_getter(), create_tables, nullptr, nullptr, &err_msg);

    if (operation_code != SQLITE_OK)
    {
        string error = err_msg;
        sqlite3_free(err_msg);
        throw database_exception(error);
    }

    return;
}