#pragma once
#include <iostream>
#include <string>

#include "post.h"

using namespace std;

class answers : public post
{
    /*
  this class will only be used as a container made to hold data retrived by the database
  instead of havin a dedicated logic for file handeling.

  this class is connected to answers_manager class so before making any changes keep it in mind
  that u gotta make sure your changes allign with the answers_manager class
  */
private:
    int answered_question_id;

public:
    /*
    there will be no setters since it will be handeled by the Dao using the constructor
    */

    answers(int answer_id, int answered_question_id, int from_user_id, const string &answer_text, bool is_anonymous);

    void display() override;

    [[nodiscard]] int answered_question_id_getter() const;
};