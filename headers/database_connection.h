#include <string>
#include "exceptions.h"
#include "sqlite3.h"

using namespace std;
/*
this is the file where we implemented the database connection
, we started by using the singleton method which creates a single
instance by making the constructor private, then it checks whether
the instance value is null or not, and depending whether an instance
exists or not will we create a new instance by calling the constructor or not
*/
class connection
{
private:
    sqlite3 *connection_handle;
    /*the actual sqlite handle,
    When you call sqlite3_open(), SQLite internally allocates a big structure in memory
    that holds everything about your database connection (the file handle)
    , internal buffers, prepared statement cache, error state, transaction state, everything.
    SQLite then gives you back a pointer to that structure
    , you dont actually use it by yourself you just put it in sqlite3 functions as
    a parameter and they just do the job.*/

    static connection *instance; // our singular instance variable

    connection(const string &path)
    {
        int operation_code = sqlite3_open(path.c_str(), &connection_handle);

        if (operation_code != 0)
        {
            throw database_exception(sqlite3_errmsg(connection_handle));
        }
    }

public:
    static connection *make_instance(const string &path) // the core of singlton method i mentioned
    {
        if (instance == nullptr)
        {
            instance = new connection(path);
            return instance;
        }

        return instance;
    }

    sqlite3 *handle_getter() const // here we can access our connection handle so we cann pass it to DAO's
    {
        return connection_handle;
    }

    connection(const connection &) = delete;            // here we delete the default copy constructors
    connection &operator=(const connection &) = delete; // and here we delete the default assignment operator

    ~connection() // here we close the connection
    {
        sqlite3_close(connection_handle);
    }
};