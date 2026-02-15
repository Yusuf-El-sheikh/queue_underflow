#include <bits/stdc++.h>
#include "answers.h"
using namespace std;

answers::answers() {}

void answers::from_id_setter(const int &from_id)
{
    from_user_id = from_id;
}

int answers::from_id_getter() const
{
    return from_user_id;
}

void answers::answer_id_setter(const int &id)
{
    answer_id = id;
}

int answers::answer_id_getter() const
{
    return answer_id;
}

void answers::answered_question_id_setter(const int &question_id)
{
    answered_question_id = question_id;
}

int answers::answered_question_id_getter() const
{
    return answered_question_id;
}

bool answers::answer_text_setter(const string &text)
{
    if (text.size() <= 1000)
    {
        answer_text = text;
        return true;
    }

    cout << "Answer text exceeds maximum length of 1000 characters \n";
    return false;
}

string answers::answer_text_getter() const
{
    return answer_text;
}

void answers::is_anonymous_setter(const bool &pref)
{
    is_anonymous = pref;
}

bool answers::is_anonymous_getter() const
{
    return is_anonymous;
}
