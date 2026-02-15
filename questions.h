#pragma once
#include <bits/stdc++.h>
using namespace std;

class questions
{
private:
    int parent_question_id = -1;
    int question_id = 0;
    int from_user_id = 0;

    string question_text = "";

    bool is_anonymous = false;
    bool is_answered = false;

public:
    questions();

    void from_id_setter(const int &from_id);
    int from_id_getter() const;

    void question_id_setter(const int &question_id);
    int question_id_getter() const;

    void parent_question_id_setter(const int &parent_id);
    int parent_question_id_getter() const;

    bool question_text_setter(const string &question_text);
    string question_text_getter() const;

    void is_anonymous_setter(const bool &pref);
    bool is_anonymous_getter() const;

    void is_answered_setter(const bool &answered);
    bool is_answered_getter() const;
};