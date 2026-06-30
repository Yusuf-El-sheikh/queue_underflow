#pragma once
#include "IQuestionRepository.h"
#include "validator.h"
#include "exceptions.h"

class questions_manager
{
private:
    unique_ptr<IQuestionRepository> questions_repo;

public:
    questions_manager(unique_ptr<IQuestionRepository> repo) : questions_repo(std::move(repo)) {};

    void post_question(int from_user_id, const string &text, bool is_anonymous, int parent_question_id = -1);
    void delete_question(int question_id);

    unique_ptr<questions> get_question(int question_id);

    vector<questions> get_all_questions(); // feed view feature
    vector<questions> get_user_questions(int user_id);
};