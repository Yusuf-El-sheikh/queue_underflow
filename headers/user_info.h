#pragma once
#include <iostream>
#include <string>
using namespace std;

class user_info
{
    /*
    this class will only be used as a container made to hold data retrived by the database
    instead of havin a dedicated logic for file handeling.

    this class is connected to user_manager class so before making any changes keep it in mind
    that u gotta make sure your changes allign with the user_manager class
    */

private:
    int user_id ;

    string user_password ;
    string user_email ;
    string username ;

public:
    /*
    there will be no setters since it will be handeled by the Dao constructor

    the passwords will have no getter, the Dao handles comparison at the database level
    */

    user_info(int id, const string& email, const string& password, const string& username);

    string username_getter() const;

    string user_email_getter() const;

    int user_id_getter() const;

    /*operators overloading
    here operators will be overloaded to make it simpler for filtering and search functions to
    compare data instead of making lambdas in every single one of them as a comparator
    */

    bool operator<(const user_info &other) const;

    bool operator==(const user_info &other) const;
};

/*
the output stream operator overload function shouldnt be a member function
meaning it shouldnt be a part of any class since the function itself belong to the ostream class which
we wont modify so we will keep it outside of this class  
*/

ostream& operator<<(ostream &os, const user_info &others);