#include "../headers/questions_manager.h"

questions_manager::questions_manager(unique_ptr<IQuestionRepository> repo) : questions_repo(std::move(repo)) {}

void questions_manager::post_question(int from_user_id, const string &text , bool is_anonymous, int parent_question_id)
{
    if(!validator::validate_text_size(text, validator::MAX_POST_LENGTH))
    {
        throw validation_exception("Your post is longer than 1000 characters");
    }

    questions_repo->post_question(from_user_id, text, is_anonymous, parent_question_id);
}

void questions_manager::delete_question(int question_id, int user_id)
{
    unique_ptr<questions> question = questions_repo->find_by_id(question_id);

    if(question == nullptr)
    {
        throw not_found_exception("This question doesn't exist");
    }

    if(question->from_user_id_getter() != user_id)
    {
        throw authentication_exception("This post isnt yours to delete");
    }

    questions_repo->remove(question_id);
}

vector<questions> questions_manager::get_all_questions()
{
    return questions_repo->find_all();
}

vector<questions> questions_manager::get_user_questions(int from_user_id)
{
    return questions_repo->find_by_user_id(from_user_id);
}

unique_ptr<questions> questions_manager::get_question(int question_id)
{
    unique_ptr<questions> question = questions_repo->find_by_id(question_id) ;

    if(question == nullptr)
    {
        throw not_found_exception("This question doesn't exist");
    }

    return question;
}

