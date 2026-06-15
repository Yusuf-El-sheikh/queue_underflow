#pragma once
#include <iostream>
#include <string>

#include "post.h"

using namespace std;

class questions : public post
{
    /*
   this class will only be used as a container made to hold data retrived by the database
   instead of havin a dedicated logic for file handeling.

   this class is connected to question_manager class so before making any changes keep it in mind
   that u gotta make sure your changes allign with the question_manager class
   */

private:
    int parent_question_id = -1;

    bool is_answered;

public:
    /*
    there will be no setters since it will be handeled by the Dao using the constructor
    */

    questions(int question_id, int parent_question_id, int from_user_id, const string &question_text, bool is_anonymous, bool is_answered);

    void display() override;

    int parent_question_id_getter() const;

    bool is_answered_getter() const;
};
