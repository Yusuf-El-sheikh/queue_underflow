#pragma once
#include "database_connection.h"

class setup
{
public:
    setup() = delete;

    static void db_setup(connection *db_connection) ;
};