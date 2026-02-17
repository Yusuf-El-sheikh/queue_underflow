#pragma once
#include <bits/stdc++.h>
#include "question_vote_manager.h"
#include "questions.h"
using namespace std;

class questions_manager
{
private:
    vector<questions> all_questions;
    question_vote_manager q_vote_manager;

public:
    questions_manager();

    void questions_loader();

    void question_writer();

    void save_votes();

    bool delete_question(const int &current_user_id, const int &target_question_from_id);

    vector<questions>::const_iterator search_questions_by_id(const int &question_id) const;

    vector<questions> questions_of_user_filter(const int &current_user_id);

    vector<int> collect_all_descendants(const int &parent_id);

    int id_generator();

    bool ask(const int &user_id, const string &question, bool is_anonymous, int parent_id = -1);
};