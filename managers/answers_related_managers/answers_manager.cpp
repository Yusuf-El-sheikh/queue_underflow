#include "../headers/answers_manager.h"

answers_manager::answers_manager(unique_ptr<IAnswerRepository> repo) : answers_repo(std::move(repo)) {}

void answers_manager::post_answer(int answered_question_id, int from_user_id, const string &answer_text, bool is_anonymous)
{
    /*we wont check the answered question id authenticity here, instead we will rely on the 
    database referencing better than either coupling the managers or duplicating SQL's*/

    /*we wont check the from user id aswell in here since that will be handeled by the 
    ui layer fetching the current user using the main function which will be orchestrating
    all the layers, so it will inject the right data to the managers ("supposedly")*/

    if(!validator::validate_text_size(answer_text, validator::MAX_POST_LENGTH))
    {
        throw validation_exception("Your answer is longer than 1000 characters");
    }
    
    answers_repo->post_answer(answered_question_id, from_user_id, answer_text, is_anonymous);
}

void answers_manager::delete_answer(int answer_id, int user_id)
{
    unique_ptr<answers> answer = answers_repo->find_by_id(answer_id);

    if(answer == nullptr)
    {
        throw not_found_exception("This answer doesn't exist");
    }

    if(answer->from_user_id_getter() != user_id)
    {
        throw authentication_exception("This answer isnt yours to delete");
    }

    answers_repo->remove(answer_id);
}

unique_ptr<answers> answers_manager::get_answer(int answer_id)
{
    unique_ptr<answers> answer = answers_repo->find_by_id(answer_id);

    if(answer == nullptr)
    {
        throw not_found_exception("This answer doesn't exist");
    }

    return answer;
}

vector<answers> answers_manager::get_all_answers()
{
    return answers_repo->find_all();
}

vector<answers> answers_manager::get_answers_by_question(int question_id)
{
    return answers_repo->find_by_question_id(question_id);
}