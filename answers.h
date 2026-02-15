#pragma once
#include <bits/stdc++.h>
using namespace std;

class answers
{
private:

    int answered_question_id = -1;
    int answer_id = 0;
    int from_user_id = 0;

    string answer_text = "";

    bool is_anonymous = false;

public:

    answers();

    void from_id_setter(const int &from_id);
    int from_id_getter() const;

    void answer_id_setter(const int &answer_id);
    int answer_id_getter() const;

    void answered_question_id_setter(const int &question_id);
    int answered_question_id_getter() const;

    bool answer_text_setter(const string &answer_text);
    string answer_text_getter() const;

    void is_anonymous_setter(const bool &pref);
    bool is_anonymous_getter() const;
};