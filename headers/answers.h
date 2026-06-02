#pragma once
#include <iostream>
#include <string>
using namespace std;

class answers
{
    /*
  this class will only be used as a container made to hold data retrived by the database
  instead of havin a dedicated logic for file handeling.

  this class is connected to answers_manager class so before making any changes keep it in mind
  that u gotta make sure your changes allign with the answers_manager class
  */
private:
    int answered_question_id;

    int answer_id;
    
    int from_user_id;

    string answer_text;

    bool is_anonymous;

public:
    /*
    there will be no setters since it will be handeled by the Dao using the constructor
    */

    answers(int answer_id, int answered_question_id, int from_user_id, const string &answer_text, bool is_anonymous);

    int from_id_getter() const;

    int answer_id_getter() const;

    int answered_question_id_getter() const;

    string answer_text_getter() const;

    bool is_anonymous_getter() const;

    /*operators overloading
    here operators will be overloaded to make it simpler for filtering and search functions to
    compare data instead of making lambdas in every single one of them as a comparator
    */

    bool operator<(const answers &other) const;

    bool operator==(const answers &other) const;
};

/*
the output stream operator overload function shouldnt be a member function
meaning it shouldnt be a part of any class since the function itself belong to the ostream class which
we wont modify so we will keep it outside of this class  
*/

ostream& operator<<(ostream& os, const answers& other);