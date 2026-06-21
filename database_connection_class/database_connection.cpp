#include "../headers/database_connection.h"

unique_ptr<connection> connection::instance = nullptr; // we initialize our static instance variable to null