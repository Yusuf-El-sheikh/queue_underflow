#include <bits/stdc++.h>
#include "questions.h"
using namespace std;

questions::questions() {}

void questions::from_id_setter(const int &from_id)
{
    from_user_id = from_id;
}

int questions::from_id_getter() const
{
    return from_user_id;
}

void questions::question_id_setter(const int &quest_id)
{
    question_id = quest_id;
}

int questions::question_id_getter() const
{
    return question_id;
}

void questions::parent_question_id_setter(const int &parent_id)
{
    parent_question_id = parent_id;
}

int questions::parent_question_id_getter() const
{
    return parent_question_id;
}

bool questions::question_text_setter(const string &quest_text)
{
    if (quest_text.size() <= 1000)
    {
        question_text = quest_text;
        return true;
    }
    else
    {
        cout << "Question text exceeds maximum length of 1000 characters \n";
        return false;
    }
}

string questions::question_text_getter() const
{
    return question_text;
}

void questions::is_anonymous_setter(const bool &pref)
{
    is_anonymous = pref;
}

bool questions::is_anonymous_getter() const
{
    return is_anonymous;
}

void questions::is_answered_setter(const bool &answered)
{
    is_answered = answered;
}

bool questions::is_answered_getter() const
{
    return is_answered;
}
