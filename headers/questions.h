#pragma once
#include <iostream>
#include <string>
using namespace std;

class questions
{
    /*
   this class will only be used as a container made to hold data retrived by the database
   instead of havin a dedicated logic for file handeling.

   this class is connected to question_manager class so before making any changes keep it in mind
   that u gotta make sure your changes allign with the question_manager class
   */

private:
    int parent_question_id;
    int question_id;
    int from_user_id;

    string question_text;

    bool is_anonymous;
    bool is_answered;

public:
    /*
    there will be no setters since it will be handeled by the Dao using the constructor
    */

    questions(int question_id, int parent_question_id, int from_user_id, const string &question_text, bool is_anonymous, bool is_answered);

    int from_id_getter() const;

    int question_id_getter() const;

    int parent_question_id_getter() const;

    string question_text_getter() const;

    bool is_anonymous_getter() const;

    bool is_answered_getter() const;

    /*operators overloading
    here operators will be overloaded to make it simpler for filtering and search functions to
    compare data instead of making lambdas in every single one of them as a comparator
    */

    bool operator<(const questions &other) const;

    bool operator==(const questions &other) const;
};

/*
the output stream operator overload function shouldnt be a member function
meaning it shouldnt be a part of any class since the function itself belong to the ostream class which
we wont modify so we will keep it outside of this class  
*/

ostream& operator<<(ostream& os, const questions& q);