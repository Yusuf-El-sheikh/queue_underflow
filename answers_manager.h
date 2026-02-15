#pragma once
#include <bits/stdc++.h>
#include "answer_vote_manager.h"
#include "answers.h"
using namespace std;

class answers_manager
{
private:
    vector<answers> all_answers;
    answer_vote_manager a_vote_manager;

public:
    answers_manager();

    void answers_loader();

    void answer_writer();

    bool answer(const int &user_id, const int &question_id, const string &answer_text, bool is_anonymous);

    bool delete_answer(const int &current_user_id, const int &target_answer_id);

    vector<answers> answers_of_question_filter(const int &question_id);

    vector<answers>::const_iterator search_answers_by_id(const int &answer_id) const;

    int id_generator();
};