#pragma once
#include <exception>
#include <string>
using namespace std;

/*we start off by making an app exception class derived from std::exception
where we will take a message as a parameter so we can display it in case of any problem
, later we will make more classes so we can specify what kind of issue are we facing by 
overrideing the what() function which operates by returning a const char* that will be stringified
using a c_str() which we will use to return our message*/

class app_exception : public std::exception
{
private:
    string err_msg; //our message variable

public:
    app_exception(const string &msg)
        : err_msg(msg) {} //we initialize the value of the message in the constructor

    //here we override the what(), noexecpt is a promise it wont throw exceptions
    const char *what() const noexcept override { return err_msg.c_str(); } 
};

class database_exception : public app_exception
{
public:
    database_exception(const string &msg)//here we just pass the message to the parent class and the what() will do the job
        : app_exception(msg) {}
};

class authentication_exception : public app_exception
{
public:
    authentication_exception(const string &msg)
        : app_exception(msg) {}
};

class not_found_exception : public app_exception
{
public:
    not_found_exception(const string &msg)
        : app_exception(msg) {}
};

class validation_exception : public app_exception
{
public:
    validation_exception(const string &msg)
        : app_exception(msg) {}
};