#pragma once
#include "IAnswerRepository.h"
#include "validator.h"
#include "exceptions.h"

class answers_manager
{
private:
    unique_ptr<IAnswerRepository> answers_repo;

public:
    answers_manager(unique_ptr<IAnswerRepository> repo) : answers_repo(std::move(repo)) {}

    void post_answer(int answered_question_id, int from_user_id, const string &answer_text, bool is_anonymous);
    void delete_answer(int answer_id, int user_id);

    vector<answers> get_all_answers();
    unique_ptr<answers> get_answer(int answer_id);
    vector<answers> get_answers_by_question(int question_id);
};